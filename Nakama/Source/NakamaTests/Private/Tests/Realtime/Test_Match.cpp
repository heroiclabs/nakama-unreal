#include "Tests/Realtime/Test_Match.h"
#include "NakamaTestBase.h"
#include "Misc/AutomationTest.h"

// Create Match
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(CreateMatch, FNakamaTestBase, "Nakama.Base.Realtime.Matches.Match", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool CreateMatch::RunTest(const FString& Parameters)
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

			// Join Chat
			auto successCallback = [&](const FNakamaMatch& Match)
			{
				UE_LOG(LogTemp, Display, TEXT("Created Match: %s"), *Match.MatchId);
				UE_LOG(LogTemp, Display, TEXT("Created Match Self Id: %s"), *Match.Me.UserID);
				TestTrue("Create Match Test Passed", !Match.MatchId.IsEmpty() && !Match.Me.UserID.IsEmpty());
				StopTest();
			};

			auto errorCallback = [this](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Create Match error. ErrorMessage: %s"), *Error.Message);
				TestFalse("Create Match Test error.", true);
				StopTest();
			};

			Socket->CreateMatch(successCallback, errorCallback);
		});
		
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

// Add Matchmaker, must return a TicketId
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(AddMatchmaker, FNakamaTestBase, "Nakama.Base.Realtime.Matches"
																		".AddMatchmaker", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool AddMatchmaker::RunTest(const FString& Parameters)
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

		Socket->SetConnectCallback([&]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket connected"));

			// Add Matchmaker Callbacks
			auto successCallback = [&](const FNakamaMatchmakerTicket& Ticket)
			{
				UE_LOG(LogTemp, Display, TEXT("Added Matchmaker with Ticket: %s"), *Ticket.TicketId);
				TestTrue("Add Matchmaker Test Passed", !Ticket.TicketId.IsEmpty());
				StopTest();
			};

			auto errorCallback = [&](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Add Matchmaker. ErrorMessage: %s"), *Error.Message);
				TestFalse("Add Matchmaker Test error.", true);
				StopTest();
			};

			// Matchmaker Params
			// Note: Query: player_level >= 10 does not work. See: https://heroiclabs.com/docs/nakama/concepts/multiplayer/query-syntax/
			// Doing * instead
			TOptional<int32> MinCount = 2;
			TOptional<int32> MaxCount = 4;
			TOptional<FString> Query = FString("*");
			TMap<FString, FString> StringProperties;
			StringProperties.Add("region", "us");
			TMap<FString, double> NumericProperties;
			NumericProperties.Add("game_mode", 1);
			NumericProperties.Add("game_difficulty", 2);
			TOptional<int32> CountMultiple = 2;

			Socket->AddMatchmaker(MinCount, MaxCount, Query, StringProperties, NumericProperties, CountMultiple, successCallback, errorCallback);
		});

		Socket->SetDisconnectCallback( [&](const FNakamaDisconnectInfo& DisconnectInfo)
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket disconnected: %s"), *DisconnectInfo.Reason);
			TestFalse("Add Matchmaker Test error, socket disconnected", true);
			StopTest();
		});
		
		// Connect to Socket
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

// Add Matchmaker, wait for Match Matched and Join Match by Token
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(MatchmakerJoinMatch, FNakamaMatchTestBase, "Nakama.Base.Realtime.Matches"
																				   ".MatchmakerJoinMatch", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool MatchmakerJoinMatch::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	Client2 = CreateClient();
	
	// Define success callback
	auto successCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		// Setup socket:
		Socket = Client->SetupRealtimeClient();

		Socket->SetConnectCallback([this]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket connected"));

			// Add Matchmaker Callbacks
			auto successCallback = [&](const FNakamaMatchmakerTicket& Ticket)
			{
				UE_LOG(LogTemp, Display, TEXT("Added Matchmaker with Ticket: %s"), *Ticket.TicketId);
			};

			auto errorCallback = [&](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Add Matchmaker. ErrorMessage: %s"), *Error.Message);
				TestFalse("Add Matchmaker Test error.", true);
				StopTest();
			};
			
			Socket->AddMatchmaker(MinCount, MaxCount, Query, StringProperties, NumericProperties, CountMultiple, successCallback, errorCallback);
		});

		Socket->SetMatchmakerMatchedCallback( [&](const FNakamaMatchmakerMatched& MatchmakerMatched)
		{
			// Join Match by Token
			UE_LOG( LogTemp, Warning, TEXT( "Socket Matchmaker Matched" ) );
			auto JoinMatchSuccessCallback = [&](const FNakamaMatch& Match)
			{
				UE_LOG(LogTemp, Display, TEXT("Joined Match: %s"), *Match.MatchId);
				UE_LOG(LogTemp, Display, TEXT("Joined Match Self Id: %s"), *Match.Me.UserID);
				TestTrue("Join Match by Token Test Passed", !Match.MatchId.IsEmpty() && !Match.Me.UserID.IsEmpty());
				StopTest();
			};

			auto JoinMatchErrorCallback = [&](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Join Match by Token error. ErrorMessage: %s"), *Error.Message);
				TestFalse("Join Match by Token Test error.", true);
				StopTest();
			};
			
			Socket->JoinMatchByToken(MatchmakerMatched.Token, JoinMatchSuccessCallback, JoinMatchErrorCallback);
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

	// Call the Authenticate function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);
	

	// Client 2
	auto Client2AuthSuccessCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session2 = session;

		// Setup socket:
		Socket2 = Client2->SetupRealtimeClient();

		Socket2->SetConnectCallback([this]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket 2 connected"));

			// Add Matchmaker Callbacks
			auto successCallback = [&](const FNakamaMatchmakerTicket& Ticket)
			{
				UE_LOG(LogTemp, Display, TEXT("Added Matchmaker with Ticket: %s"), *Ticket.TicketId);
			};

			auto errorCallback = [&](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Add Matchmaker. ErrorMessage: %s"), *Error.Message);
				TestFalse("Add Matchmaker Test error.", true);
				StopTest();
			};

			// Matchmaker Params

			Socket2->AddMatchmaker(MinCount, MaxCount, Query, StringProperties, NumericProperties, CountMultiple, successCallback, errorCallback);
		});

		Socket2->SetMatchmakerMatchedCallback( [&](const FNakamaMatchmakerMatched& MatchmakerMatched)
		{
			UE_LOG( LogTemp, Warning, TEXT( "Socket 2 Matchmaker Matched" ) );
			// Join Match by Token
			auto JoinMatchSuccessCallback = [&](const FNakamaMatch& Match)
			{
				UE_LOG(LogTemp, Display, TEXT("Joined Match: %s"), *Match.MatchId);
				UE_LOG(LogTemp, Display, TEXT("Joined Match Self Id: %s"), *Match.Me.UserID);
				TestTrue("Join Match by Token Test Passed", !Match.MatchId.IsEmpty() && !Match.Me.UserID.IsEmpty());
				StopTest();
			};

			auto JoinMatchErrorCallback = [&](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Join Match by Token error. ErrorMessage: %s"), *Error.Message);
				TestFalse("Join Match by Token Test error.", true);
				StopTest();
			};
			
			Socket2->JoinMatchByToken(MatchmakerMatched.Token, JoinMatchSuccessCallback, JoinMatchErrorCallback);
		});
		
		// Connect with Socket
		Socket2->Connect(Session2, true); // NOTE: This must use Session2
	};

	auto Client2AuthErrorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Authentication Test Failed", true);
		StopTest();
	};
	Client2->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, Client2AuthSuccessCallback, Client2AuthErrorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));
	
	// Return true to indicate the test is complete
	return true;
}