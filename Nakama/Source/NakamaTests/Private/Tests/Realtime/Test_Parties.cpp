#include "Tests/Realtime/Test_Parties.h"

// Create Party and Join Party Test Case
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(CreateParty, FNakamaPartiesTestBase, "Nakama.Base.Realtime.Parties.CreateParty", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool CreateParty::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		// Setup socket:
		Socket = Client->SetupRealtimeClient();

		Socket->SetConnectCallback([this]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket 1 connected"));

			auto CreatePartySuccessCallback = [&](const FNakamaParty& CreateParty)
			{
				Party = CreateParty;
				SetupClient2AndJoinParty();
			};

			auto CreatePartyErrorCallback = [&](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Create Party. ErrorMessage: %s"), *Error.Message);
				TestFalse("Create Party Test error.", true);
				StopTest();
			};
			
			Socket->CreateParty(true, 2, CreatePartySuccessCallback, CreatePartyErrorCallback);
		});

		Socket->SetPartyDataCallback( [&](const FNakamaPartyData& PartyData)
		{
			UE_LOG(LogTemp, Warning, TEXT("Party Data Callback. Data: %s"), *PartyData.Data);
		});
		
		// Connect with Socket
		Socket->Connect(Session, true);
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Authentication Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));
	
	// Return true to indicate the test is complete
	return true;
}

void FNakamaPartiesTestBase::SetupClient2AndJoinParty()
{
	Client2 = CreateClient();
	
	auto Client2AuthSuccessCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session2 = session;

		// Setup socket:
		Socket2 = Client2->SetupRealtimeClient();

		Socket2->SetConnectCallback([this]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket 2 connected"));

			// Join Party Callbacks
			auto JoinPartySuccessCallback = [&]()
			{
				UE_LOG(LogTemp, Display, TEXT("Joined Party with Id: %s"), *Party.Id);
				
				Socket2->SendPartyData(Party.Id, 100, "Testing if it works");
				TestTrue("Create Party Test Passed", true);
				StopTest();
			};

			auto JoinPartyErrorCallback = [&](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Join Party. ErrorMessage: %s"), *Error.Message);
				TestFalse("Join Party Test error.", true);
				StopTest();
			};
			
			Socket2->JoinParty(Party.Id, JoinPartySuccessCallback, JoinPartyErrorCallback);
		});

		Socket2->SetPartyCallback( [&](const FNakamaParty& MyParty)
		{
			UE_LOG(LogTemp, Warning, TEXT("Party Callback. PartyId: %s"), *MyParty.Id);
			for (auto& Presence : MyParty.Presences)
			{
				UE_LOG(LogTemp, Display, TEXT("Event Presence: %s"), *Presence.UserID);
			}
		});
		
		// Connect with Socket
		Socket2->Connect(Session2, true);
	};

	auto Client2AuthErrorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Authentication Test Failed", true);
		StopTest();
	};
	
	Client2->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, Client2AuthSuccessCallback, Client2AuthErrorCallback);
}

// Create Party and Join Party Test Case
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(PartyMatchmaker, FNakamaPartiesTestBase, "Nakama.Base.Realtime.Parties.PartyMatchmaker", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool PartyMatchmaker::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		// Setup socket:
		Socket = Client->SetupRealtimeClient();

		Socket->SetConnectCallback([this]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket 1 connected"));

			auto CreatePartySuccessCallback = [&](const FNakamaParty& CreateParty)
			{
				Party = CreateParty;
				//SetupClient2AndJoinParty();

				auto AddMatchmakerPartySuccessCallback = [&](const FNakamaPartyMatchmakerTicket& Ticket)
				{
					UE_LOG(LogTemp, Warning, TEXT("Add Matchmaker Party Success Callback. Ticket: %s"), *Ticket.Ticket);
					TestTrue( "Add Matchmaker Party Success", !Ticket.Ticket.IsEmpty());
					StopTest();
				};

				auto AddMatchmakerPartyErrorCallback = [&](const FNakamaRtError& Error)
				{
					UE_LOG(LogTemp, Error, TEXT("Add Matchmaker Party Error Callback. ErrorMessage: %s"), *Error.Message);
					TestFalse("Add Matchmaker Party Error", true);
				};

				TOptional<int32> MinCount = 2;
				TOptional<int32> MaxCount = 2;
				TOptional<FString> Query(TEXT("*"));
				
				Socket->AddMatchmakerParty(Party.Id, MinCount, MaxCount, Query, {}, {} , {},AddMatchmakerPartySuccessCallback, AddMatchmakerPartyErrorCallback); 
			};

			auto CreatePartyErrorCallback = [&](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Create Party. ErrorMessage: %s"), *Error.Message);
				TestFalse("Create Party Test error.", true);
				StopTest();
			};
			
			Socket->CreateParty(false, 1, CreatePartySuccessCallback, CreatePartyErrorCallback);
		});

		Socket->SetPartyDataCallback( [&](const FNakamaPartyData& PartyData)
		{
			UE_LOG(LogTemp, Warning, TEXT("Party Data Callback. Data: %s"), *PartyData.Data);
		});
		
		// Connect with Socket
		Socket->Connect(Session, true);
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Authentication Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));
	
	// Return true to indicate the test is complete
	return true;
}