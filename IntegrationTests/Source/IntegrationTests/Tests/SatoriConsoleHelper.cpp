#include "SatoriConsoleHelper.h"

#include "Misc/Guid.h"
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
	// Schema UUIDs defined in Satori source (console_schema.go):
	// SchemaCoreObjectId = "00000000-0000-0000-0000-000000000001" (object/metadata)
	// SchemaCoreStringId = "00000000-0000-0000-0000-000000000002" (string value)
	const FString EventBody = TEXT("{\"value_schema_id\":\"00000000-0000-0000-0000-000000000002\",\"metadata_schema_id\":\"00000000-0000-0000-0000-000000000001\"");
	const FString PropBody  = TEXT("{\"schema_id\":\"00000000-0000-0000-0000-000000000002\"");

	TArray<TPair<FString, FString>> Steps = {
		{TEXT("/v1/console/event"),    FString::Printf(TEXT("{\"name\":\"game_start\",%s}"),    *EventBody.Mid(1))},
		{TEXT("/v1/console/event"),    FString::Printf(TEXT("{\"name\":\"level_complete\",%s}"), *EventBody.Mid(1))},
		{TEXT("/v1/console/event"),    FString::Printf(TEXT("{\"name\":\"purchase\",%s}"),      *EventBody.Mid(1))},
		{TEXT("/v1/console/property"), FString::Printf(TEXT("{\"name\":\"level\",%s}"),          *PropBody.Mid(1))},
		{TEXT("/v1/console/property"), FString::Printf(TEXT("{\"name\":\"rank\",%s}"),           *PropBody.Mid(1))},
		{TEXT("/v1/console/property"), FString::Printf(TEXT("{\"name\":\"preferred_mode\",%s}"), *PropBody.Mid(1))},
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

			// Step 2: Create a unique key for this test session.
			// Each shard runs as a separate process with its own GCachedApiKey, so using a
			// shared key (list + rotate) causes race conditions. A unique name per shard avoids conflicts.
			const FString KeyName = FGuid::NewGuid().ToString(EGuidFormats::Digits).ToLower();
			MakeConsoleRequest(TEXT("http://127.0.0.1:7451/v1/console/apikey"), TEXT("POST"), Token,
				FString::Printf(TEXT("{\"name\":\"%s\"}"), *KeyName),
				[Promise, Token](TSharedPtr<FJsonObject> Json)
				{
					FString KeyValue;
					if (Json.IsValid()) Json->TryGetStringField(TEXT("value"), KeyValue);
					GetKeyThenSeed(Token, KeyValue, Promise);
				});
		});

	return Future;
}
