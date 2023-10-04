#include "Tests/Realtime/Test_Tournament.h"

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(Tournament, FNakamaTournamentTestBase, "Nakama.Base.Realtime.Tournament", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool Tournament::RunTest(const FString& Parameters)
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
			UE_LOG(LogTemp, Warning, TEXT("Test Socket connected"));

			// Create a JSON object and add properties to it
			TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

			JsonObject->SetBoolField("authoritative", true);
			JsonObject->SetStringField("sort_order", "desc");
			JsonObject->SetStringField("operator", Operator);
			JsonObject->SetNumberField("duration", Duration);
			JsonObject->SetStringField("reset_schedule", ResetSchedule);
			JsonObject->SetStringField("title", "Daily Dash");
			JsonObject->SetStringField("description", "Dash past your opponents for high scores and big rewards!");
			JsonObject->SetNumberField("category", 1);
			JsonObject->SetNumberField("start_time", StartTime);
			JsonObject->SetNumberField("end_time", EndTime);
			JsonObject->SetNumberField("max_size", MaxSize);
			JsonObject->SetNumberField("max_num_score", MaxNumScore);
			JsonObject->SetBoolField("join_required", JoinRequired);

			// Convert the JSON object to a string
			FString JsonString;
			TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
			FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

			auto CreateTournamentSuccessCallback = [&](const FNakamaRPC& Rpc)
			{
				UE_LOG(LogTemp, Warning, TEXT("Tournament created: %s"), *Rpc.Payload );

				FString TournamentId = GetTournamentIdFromJsonString(Rpc.Payload);
				if(!TournamentId.IsEmpty())
				{
					// Join the tournament
					auto JoinTournamentSuccessCallback = [&, TournamentId]()
					{
						UE_LOG(LogTemp, Warning, TEXT("Joined Tournament ID: %s"), *TournamentId);
						TestTrue("Tournament Test Passed",true);
						StopTest();
					};

					auto JoinTournamentErrorCallback = [this](const FNakamaError& Error)
					{
						UE_LOG(LogTemp, Warning, TEXT("Join Tournament Error - Join Tournament. ErrorMessage: %s"), *Error.Message);
						TestFalse("Join Tournament Error - Join Tournament.", true);
						StopTest();
					};

					Client->JoinTournament(Session, TournamentId, JoinTournamentSuccessCallback, JoinTournamentErrorCallback);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("TournamentId is Empty"));
					TestFalse("TournamentId is Empty", true);
					StopTest();
				}
			};

			auto CreateTournamentErrorCallback = [this](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Warning, TEXT("Join Tournament Error - Create Tournament. ErrorMessage: %s"), *Error.Message);
				TestFalse("Join Tournament Error - Create Tournament.", true);
				StopTest();
			};

			Socket->RPC("clientrpc.create_tournament", JsonString, CreateTournamentSuccessCallback, CreateTournamentErrorCallback);
		});
		
		// In this test we use a custom external listener, instead of the one provided with the Realtime Client
		Socket->Connect(Session, true);
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Tournament Test Failed to Authenticate", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

FString FNakamaTournamentTestBase::GetTournamentIdFromJsonString(const FString& JsonString) const
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FString TournamentId;
		if (JsonObject->TryGetStringField("tournament_id", TournamentId))
		{
			return TournamentId;
		}
	}

	// Return an empty string if the parsing fails or if the "match_id" field is not present
	return FString();
}
