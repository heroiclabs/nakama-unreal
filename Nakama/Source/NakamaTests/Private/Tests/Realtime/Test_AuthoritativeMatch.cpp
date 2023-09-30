#include "Tests/Realtime/Test_AuthoritativeMatch.h"

#include "NakamaLoggingMacros.h"

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(AuthoritativeMatch, FNakamaAuthoritativeMatchTestBase, "Nakama.Base.Realtime.Matches.AuthoritativeMatch", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool AuthoritativeMatch::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;
		
		// Setup socket:
		Socket = Client->SetupRealtimeClient();

		Socket->SetConnectCallback([this]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Test Socket 1 Connected"));

			// Setup Client 2 and connect

			Client2 = CreateClient();

			auto Client2AuthenticateSuccess = [this] (UNakamaSession* Client2Session)
			{
				Session2 = Client2Session;

				Socket2 = Client2->SetupRealtimeClient();

				Socket2->SetConnectCallback([this]()
				{
					UE_LOG(LogTemp, Warning, TEXT("Test Socket 2 Connected"));

					auto RpcSuccessCallback = [this](const FNakamaRPC& Rpc)
					{
						FString MatchId = GetMatchIdFromJsonString(Rpc.Payload);
						if(!MatchId.IsEmpty())
						{
							auto JoinMatchSuccessCallback = [this](const FNakamaMatch& Match)
							{
								UE_LOG(LogTemp, Display, TEXT("Joined Match. MatchId: %s"), *Match.MatchId);
								TestTrue("Authoritative Match Test Passed", !Match.MatchId.IsEmpty());
								StopTest();
							};

							auto JoinMatchErrorCallback = [this](const FNakamaRtError& Error)
							{
								UE_LOG(LogTemp, Warning, TEXT("Join Match Error. Message: %s"), *Error.Message);
								TestFalse("Authoritative Match Test Failed - Join Match Error", true);
								StopTest();
							};
							
							Socket2->JoinMatch(MatchId, {}, JoinMatchSuccessCallback, JoinMatchErrorCallback);
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("MatchId is Empty"));
							TestFalse("MatchId is Empty", true);
							StopTest();
						}
					};

					auto RpcErrorCallback = [this](const FNakamaRtError& Error)
					{
						UE_LOG(LogTemp, Warning, TEXT("RPC Error. Message: %s"), *Error.Message);
						TestFalse("Authoritative Match Test Failed - RPC Error", true);
						StopTest();
					};

					const FString JsonPayload = "{\"debug\": true, \"label\": \"TestAuthoritativeMatch\"}";
					Socket->RPC("clientrpc.create_authoritative_match", JsonPayload, RpcSuccessCallback, RpcErrorCallback);
				});
				
				Socket2->Connect(Session, true);
			};

			auto Client2AuthenticateError = [this](const FNakamaError& Error)
			{
				UE_LOG(LogTemp, Warning, TEXT("Client 2 Authentication Error. Message: %s"), *Error.Message);
				TestFalse("Authoritative Match Test Failed - Client 2 Authentication Error", true);
				StopTest();
			};
			
			Client2->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, Client2AuthenticateSuccess, Client2AuthenticateError);
			
		});
		
		Socket->Connect(Session, true);
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Authoritative Match Auth Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

FString FNakamaAuthoritativeMatchTestBase::GetMatchIdFromJsonString(const FString& JsonString) const
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FString MatchId;
		if (JsonObject->TryGetStringField("match_id", MatchId))
		{
			return MatchId;
		}
	}

	// Return an empty string if the parsing fails or if the "match_id" field is not present
	return FString();
}
