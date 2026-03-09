#include "SatoriConsoleHelper.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

static FString GCachedApiKey;

// Makes a Console REST request. OnComplete is always called; Json is null on failure.
static void MakeConsoleRequest(
	const FString& Url,
	const FString& Method,
	const FString& BearerToken,
	const FString& Body,
	TFunction<void(TSharedPtr<FJsonObject>)> OnComplete)
{
	auto Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(Method);
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	if (!BearerToken.IsEmpty())
	{
		Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *BearerToken));
	}
	if (!Body.IsEmpty())
	{
		Request->SetContentAsString(Body);
	}
	Request->OnProcessRequestComplete().BindLambda(
		[OnComplete](FHttpRequestPtr, FHttpResponsePtr Res, bool bSuccess)
		{
			TSharedPtr<FJsonObject> Json;
			if (bSuccess && Res.IsValid())
			{
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Res->GetContentAsString());
				FJsonSerializer::Deserialize(Reader, Json);
			}
			OnComplete(Json);
		});
	Request->ProcessRequest();
}

// Seeds event and property configurations sequentially (ignores errors, they may already exist).
// Resolves the promise with KeyValue when all steps complete.
static void SeedConfigAndFinish(
	const FString& Token,
	const FString& KeyValue,
	TSharedPtr<TPromise<FString>> Promise,
	TArray<TPair<FString, FString>> Steps,
	int32 Index)
{
	if (Index >= Steps.Num())
	{
		GCachedApiKey = KeyValue;
		Promise->SetValue(KeyValue);
		return;
	}

	const FString Url = FString::Printf(TEXT("http://127.0.0.1:7451%s"), *Steps[Index].Key);
	MakeConsoleRequest(Url, TEXT("POST"), Token, Steps[Index].Value,
		[Token, KeyValue, Promise, Steps, Index](TSharedPtr<FJsonObject>)
		{
			SeedConfigAndFinish(Token, KeyValue, Promise, Steps, Index + 1);
		});
}

static void GetKeyThenSeed(const FString& Token, const FString& KeyValue, TSharedPtr<TPromise<FString>> Promise)
{
	TArray<TPair<FString, FString>> Steps = {
		{TEXT("/v1/console/event"),    TEXT("{\"name\":\"game_start\"}")},
		{TEXT("/v1/console/event"),    TEXT("{\"name\":\"level_complete\"}")},
		{TEXT("/v1/console/event"),    TEXT("{\"name\":\"purchase\"}")},
		{TEXT("/v1/console/property"), TEXT("{\"name\":\"level\"}")},
		{TEXT("/v1/console/property"), TEXT("{\"name\":\"rank\"}")},
	};
	SeedConfigAndFinish(Token, KeyValue, Promise, MoveTemp(Steps), 0);
}

TFuture<FString> GetSatoriApiKey()
{
	TSharedPtr<TPromise<FString>> Promise = MakeShared<TPromise<FString>>();
	TFuture<FString> Future = Promise->GetFuture();

	if (!GCachedApiKey.IsEmpty())
	{
		Promise->SetValue(GCachedApiKey);
		return Future;
	}

	// Step 1: Authenticate with the Console API admin user.
	MakeConsoleRequest(
		TEXT("http://127.0.0.1:7451/v1/console/authenticate"),
		TEXT("POST"), TEXT(""),
		TEXT("{\"email\":\"admin@satoriserver.com\",\"password\":\"password\"}"),
		[Promise](TSharedPtr<FJsonObject> Json)
		{
			FString Token;
			if (!Json.IsValid() || !Json->TryGetStringField(TEXT("token"), Token) || Token.IsEmpty())
			{
				Promise->SetValue(TEXT(""));
				return;
			}

			// Step 2: List existing API keys.
			MakeConsoleRequest(TEXT("http://127.0.0.1:7451/v1/console/apikey"), TEXT("GET"), Token, TEXT(""),
				[Promise, Token](TSharedPtr<FJsonObject> Json)
				{
					FString KeyValue;
					const TArray<TSharedPtr<FJsonValue>>* Keys;
					if (Json.IsValid() && Json->TryGetArrayField(TEXT("keys"), Keys) && Keys->Num() > 0)
					{
						(*Keys)[0]->AsObject()->TryGetStringField(TEXT("value"), KeyValue);
					}

					if (KeyValue.IsEmpty())
					{
						// Step 3: No key exists — create one, then seed config.
						MakeConsoleRequest(TEXT("http://127.0.0.1:7451/v1/console/apikey"), TEXT("POST"), Token,
							TEXT("{\"name\":\"default\"}"),
							[Promise, Token](TSharedPtr<FJsonObject> Json)
							{
								FString KeyValue;
								if (Json.IsValid()) Json->TryGetStringField(TEXT("value"), KeyValue);
								GetKeyThenSeed(Token, KeyValue, Promise);
							});
					}
					else
					{
						// Step 3: Key already exists — just seed config.
						GetKeyThenSeed(Token, KeyValue, Promise);
					}
				});
		});

	return Future;
}
