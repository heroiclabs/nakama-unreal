/*
* Copyright 2025 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "NakamaTestBase.h"

// Send Notification to self from RPC and receive it
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(NotificationsCreateReceive, FNakamaTestBase, "Nakama.Base.Realtime.Notifications.CreateReceive", NAKAMA_MODULE_TEST_MASK)
inline bool NotificationsCreateReceive::RunTest(const FString& Parameters)
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
			UE_LOG(LogTemp, Warning, TEXT("Socket connected"));

			// Notification RPC
			auto RPCSuccessCallback = [&](const FNakamaRPC& RPC)
			{
				UE_LOG(LogTemp, Display, TEXT("Sent RPC: %s"), *RPC.Id);
			};

			auto RPCErrorCallback = [&](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Notification Test. ErrorMessage: %s"), *Error.Message);
				TestFalse("RPC error.", true);
				StopTest();
			};
			
			FString Payload = FString::Printf(TEXT("{\"user_id\":\"%s\"}"), *Session->GetUserId());

			Socket->RPC("clientrpc.send_notification", Payload, RPCSuccessCallback, RPCErrorCallback);
		});

		Socket->SetNotificationsCallback( [&](const FNakamaNotificationList& NotificationList)
		{
			UE_LOG (LogTemp, Warning, TEXT("Notification Received: %d"), NotificationList.Notifications.Num());

			for (auto Notification : NotificationList.Notifications)
			{
				UE_LOG (LogTemp, Warning, TEXT("Notification ID: %s"), *Notification.Id);
				UE_LOG (LogTemp, Warning, TEXT("Notification Subject: %s"), *Notification.Subject);
				UE_LOG (LogTemp, Warning, TEXT("Notification Content: %s"), *Notification.Content);
				UE_LOG (LogTemp, Warning, TEXT("Notification Code: %d"), Notification.Code);
				UE_LOG (LogTemp, Warning, TEXT("Notification SenderId: %s"), *Notification.SenderId);
				UE_LOG (LogTemp, Warning, TEXT("Notification CreateTime: %s"), *Notification.CreateTime.ToString());
				UE_LOG (LogTemp, Warning, TEXT("Notification Persistent: %d"), Notification.Persistent);
			}
			
			TestTrue("Notifications Test Passed", NotificationList.Notifications.Num() > 0);
			StopTest();
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


// Send Notification to self from RPC and receive it
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(NotificationsCreateListDelete, FNakamaTestBase, "Nakama.Base.Realtime.Notifications.CreateListDelete", NAKAMA_MODULE_TEST_MASK)
inline bool NotificationsCreateListDelete::RunTest(const FString& Parameters)
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
			UE_LOG(LogTemp, Warning, TEXT("Socket connected"));

			// Notification RPC
			auto RPCSuccessCallback = [&](const FNakamaRPC& RPC)
			{
				UE_LOG(LogTemp, Display, TEXT("Sent RPC: %s"), *RPC.Id);

				// List Notifications
				auto ListNotificationsSuccessCallback = [this](const FNakamaNotificationList& NotificationList)
				{
					if(NotificationList.Notifications.Num() > 0)
					{
						for (auto Notification : NotificationList.Notifications)
						{
							UE_LOG (LogTemp, Display, TEXT("Notification ID: %s"), *Notification.Id);
							UE_LOG (LogTemp, Display, TEXT("Notification Code: %d"), Notification.Code);
							UE_LOG (LogTemp, Display, TEXT("Notification Content: %s"), *Notification.Content);

							auto DeleteNotificationsSuccessCallback = [this, Notification]()
							{
								UE_LOG(LogTemp, Display, TEXT("Deleted Notification ID: %s"), *Notification.Id);
								TestTrue("Notifications Test Passed", true);
								StopTest();
							};

							auto DeleteNotificationsErrorCallback = [this](const FNakamaError& Error)
							{
								UE_LOG(LogTemp, Display, TEXT("Delete Notifications Error. ErrorMessage: %s"), *Error.Message);
								TestFalse("Delete Notifications Error.", true);
								StopTest();
							};

							// NOTE: Could also add Id's to an array and delete them all at once
							Client->DeleteNotifications(Session, {Notification.Id}, DeleteNotificationsSuccessCallback, DeleteNotificationsErrorCallback);
						}
					}
					else
					{
						UE_LOG(LogTemp, Display, TEXT("No Notifications Received"));
						TestFalse("No Notifications Received", true);
						StopTest();
					}
				};
				
				auto ListNotificationsErrorCallback = [this](const FNakamaError& Error)
				{
					UE_LOG(LogTemp, Display, TEXT("List Notifications Error. ErrorMessage: %s"), *Error.Message);
					TestFalse("List Notifications Error.", true);
					StopTest();
				};

				Client->ListNotifications(Session, {}, {}, ListNotificationsSuccessCallback, ListNotificationsErrorCallback);
			};

			auto RPCErrorCallback = [&](const FNakamaRtError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Notification Test. ErrorMessage: %s"), *Error.Message);
				TestFalse("RPC error.", true);
				StopTest();
			};
			
			FString Payload = FString::Printf(TEXT("{\"user_id\":\"%s\"}"), *Session->GetUserId());

			Socket->RPC("clientrpc.send_notification", Payload, RPCSuccessCallback, RPCErrorCallback);
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