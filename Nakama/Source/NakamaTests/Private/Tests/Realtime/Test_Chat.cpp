#include "NakamaTestBase.h"
#include "Misc/AutomationTest.h"

// Join Chat
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(JoinChat, FNakamaTestBase, "Nakama.Base.Realtime.Chat.JoinChat", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool JoinChat::RunTest(const FString& Parameters)
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
			auto successCallback = [&](const FNakamaChannel& Channel)
			{
				UE_LOG(LogTemp, Display, TEXT("Joined Chat ID: %s"), *Channel.Id);
				UE_LOG(LogTemp, Display, TEXT("Joined Chat Room: %s"), *Channel.RoomName);
				TestTrue("Join Chat Test Passed", !Channel.Id.IsEmpty());
				StopTest();
			};

			auto errorCallback = [this](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Warning, TEXT("Join Chat error. ErrorMessage: %s"), *Error.Message);
				TestFalse("Join Chat Test error.", true);
				StopTest();
			};

			Socket->JoinChat(TEXT("General"), ENakamaChannelType::ROOM, true, false, successCallback, errorCallback);
		});

		Socket->SetDisconnectCallback( [](const FNakamaDisconnectInfo& DisconnectInfo)
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket disconnected!"));
			UE_LOG(LogTemp, Warning, TEXT("Socket disconnected: %s"), *DisconnectInfo.Reason);
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


// Join Chat and Wirte Chat Message
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(JoinChatWriteMessage, FNakamaTestBase, "Nakama.Base.Realtime.Chat.JoinChatWriteMessage", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool JoinChatWriteMessage::RunTest(const FString& Parameters)
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
			auto successCallback = [&](const FNakamaChannel& Channel)
			{
				auto writeChatMessageSuccessCallback = [&](const FNakamaChannelMessageAck& ChannelMessageAck)
				{
					UE_LOG(LogTemp, Display, TEXT("Joined Chat ID: %s"), *ChannelMessageAck.ChannelId);
					UE_LOG(LogTemp, Display, TEXT("Joined Chat Room: %s"), *ChannelMessageAck.RoomName);
					TestTrue("Join Chat Test Passed", !ChannelMessageAck.ChannelId.IsEmpty());
					StopTest();
				};

				auto writechatMessageErrorCallback = [this](const FNakamaRtError& Error)
				{
					UE_LOG(LogTemp, Warning, TEXT("Write Chat Message error. ErrorMessage: %s"), *Error.Message);
					TestFalse("Write Chat Message Test error.", true);
					StopTest();
				};
				
				Socket->WriteChatMessage( Channel.Id, TEXT("{ \"Hello\" : \"World\" }"), writeChatMessageSuccessCallback, writechatMessageErrorCallback );
			};

			auto errorCallback = [this](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Warning, TEXT("Join Chat error. ErrorMessage: %s"), *Error.Message);
				TestFalse("Join Chat Test error.", true);
				StopTest();
			};

			Socket->JoinChat(TEXT("General"), ENakamaChannelType::ROOM, true, false, successCallback, errorCallback);
		});

		Socket->SetDisconnectCallback( [](const FNakamaDisconnectInfo& DisconnectInfo)
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket disconnected!"));
			UE_LOG(LogTemp, Warning, TEXT("Socket disconnected: %s"), *DisconnectInfo.Reason);
		});
		
		Socket->SetChannelMessageCallback( [](const FNakamaChannelMessage& ChannelMessage)
		{
			UE_LOG(LogTemp, Warning, TEXT("Channel Message: %s"), *ChannelMessage.Content);
		});

		Socket->SetNotificationsCallback( [](const FNakamaNotificationList& NotificationList)
		{
			UE_LOG(LogTemp, Warning, TEXT("Notifications: %d"), NotificationList.Notifications.Num());
			for (auto& Notification : NotificationList.Notifications)
			{
				UE_LOG(LogTemp, Warning, TEXT("Notification: %s"), *Notification.Content);
			}
		});

		Socket->SetStatusPresenceCallback( [](const FNakamaStatusPresenceEvent& StatusPresenceEvent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Status Presences: %d"), StatusPresenceEvent.Joins.Num());
			for (auto& Presence : StatusPresenceEvent.Joins)
			{
				UE_LOG(LogTemp, Warning, TEXT("Joined Presence: %s"), *Presence.UserID);
			}
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

// Join Chat
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(JoinGroupChat, FNakamaTestBase, "Nakama.Base.Realtime.Chat.JoinGroupChat", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool JoinGroupChat::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;
		
		// Setup socket:S
		Socket = Client->SetupRealtimeClient();

		Socket->SetConnectCallback([this]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Test Socket connected"));

			auto CreateGroupSuccessCallback = [&](const FNakamaGroup& Group)
			{
				UE_LOG(LogTemp, Warning, TEXT("Group created: %s"), *Group.Id);

				// Join the group chat

				auto JoinGroupSuccessCallback = [&](const FNakamaChannel& Channel)
				{
					UE_LOG(LogTemp, Warning, TEXT("Joined Group Chat ID: %s"), *Channel.Id);
					TestTrue("Join Group Chat Test Passed", !Channel.Id.IsEmpty());
					StopTest();
				};

				auto JoinGroupErrorCallback = [this](const FNakamaRtError& Error)
				{
					UE_LOG(LogTemp, Warning, TEXT("Join Group Chat Error - Join Group. ErrorMessage: %s"), *Error.Message);
					TestFalse("Join Group Chat Error - Join Group.", true);
					StopTest();
				};

				Socket->JoinChat(Group.Id, ENakamaChannelType::GROUP, {}, {}, JoinGroupSuccessCallback, JoinGroupErrorCallback);
			};

			auto CreateGroupErrorCallback = [this](const FNakamaError& Error)
			{
				UE_LOG(LogTemp, Warning, TEXT("Join Group Chat Error - Create Group. ErrorMessage: %s"), *Error.Message);
				TestFalse("Join Group Chat Error - Create Group.", true);
				StopTest();
			};

			FString GroupName = FString::Printf(TEXT("Group chat %s"), *Session->GetAuthToken());
			Client->CreateGroup(Session, GroupName, TEXT("A group for chatting"), {}, {}, false, {}, CreateGroupSuccessCallback, CreateGroupErrorCallback);
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
