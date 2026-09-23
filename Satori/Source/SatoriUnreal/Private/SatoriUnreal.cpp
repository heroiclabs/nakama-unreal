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

#include "SatoriUnreal.h"

#include "AssetDefinitionAssetInfo.h"
#include "SatoriClient.h"
#include "SatoriLogger.h"
#include "SatoriLoggingMacros.h"
#include "Engine/World.h"
#include "HAL/IConsoleManager.h"
#include "Misc/CoreDelegates.h"
#include "Modules/ModuleManager.h"

void FSatoriUnrealModule::StartupModule()
{
	USatoriLogger::EnableLogging(true);
	SATORI_LOG_INFO("Module Startup");
	PostEngineInitHandle = FCoreDelegates::GetOnPostEngineInit().AddRaw(this, &FSatoriUnrealModule::HandleAppLaunched);

	AppForegroundHandle = FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddRaw(this, &FSatoriUnrealModule::HandleAppForeground);
	AppBackgroundHandle = FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddRaw(this, &FSatoriUnrealModule::HandleAppBackground);

	PostWorldInitHandle = FWorldDelegates::OnPostWorldInitialization.AddRaw(this, &FSatoriUnrealModule::HandleWorldInitialized);

	EnginePreExitHandle = FCoreDelegates::OnEnginePreExit.AddRaw(this, &FSatoriUnrealModule::HandleAppShutdown);
}

void FSatoriUnrealModule::ShutdownModule()
{
	FCoreDelegates::GetOnPostEngineInit().Remove(PostEngineInitHandle);
	FCoreDelegates::ApplicationHasEnteredForegroundDelegate.Remove(AppForegroundHandle);
	FCoreDelegates::ApplicationWillEnterBackgroundDelegate.Remove(AppBackgroundHandle);
	FWorldDelegates::OnPostWorldInitialization.Remove(PostWorldInitHandle);
	FCoreDelegates::OnEnginePreExit.Remove(EnginePreExitHandle);
}

void FSatoriUnrealModule::HandleAppLaunched()
{
	SATORI_LOG_INFO("App Launched");
	
	// TODO: Get these from configuration.
	FString Host = "127.0.0.1";
	FString Key = "95e22293-6299-4758-ab6f-8d363e750b21";
	int32 Port = 7450;
	Client = USatoriClient::CreateDefaultClient(Key, Host, Port, false, true);
	Client->AddToRoot();
	Client->Authenticate(
		"test-player-123",
		{},
		{},
		false,
		[this](USatoriSession* InSession)
		{
			Session = InSession;
			Session->AddToRoot();
			SATORI_LOG_INFO("Authenticated with Satori");
			
			SatoriErrorLogDevice = MakeUnique<FSatoriErrorOutputDevice>(Client, Session);
			if (GLog)
			{
				GLog->AddOutputDevice(SatoriErrorLogDevice.Get());
				SATORI_LOG_INFO("Satori error forwarder registered.");
			}

			// TODO: remove before shipping
			IConsoleManager::Get().RegisterConsoleCommand(
				TEXT("Satori.TestError"),
				TEXT("Emit a test error to verify Satori error forwarding"),
				FConsoleCommandDelegate::CreateLambda([]()
				{
					UE_LOG(LogTemp, Error, TEXT("Satori test error"));
				}));
			
			FSatoriEvent Event;
			Event.Name = TEXT("appLaunched");
			Event.Value = TEXT("satori-ue-module-auto-event");
			Event.Timestamp = FDateTime::UtcNow();
		
			Client->PostEvent(
				Session,
				{ Event }, 
				[]() { SATORI_LOG_INFO("appLaunched event posted"); },
				[](const FSatoriError& Error)
				{
					SATORI_LOG_ERROR(FString::Printf(TEXT("Failed to post event: %s"), *Error.Message));
				});
			},
		[](const FSatoriError& Error)
		{
			SATORI_LOG_ERROR(FString::Printf(TEXT("Failed to authenticate: %s"), *Error.Message));
		});
}

void FSatoriUnrealModule::HandleWorldInitialized(UWorld* World, const UWorld::InitializationValues Values)
{
	if (Client && Session && World && World->IsGameWorld())
	{
		FSatoriEvent Event;
		Event.Name = TEXT("gameStarted");
		Event.Value = TEXT("satori-ue-module-auto-event");
		Event.Timestamp = FDateTime::UtcNow();
		
		Client->PostEvent(
			Session,
			{ Event }, 
			[]() { SATORI_LOG_INFO("gameStarted event posted"); },
			[](const FSatoriError& Error)
			{
				SATORI_LOG_ERROR(FString::Printf(TEXT("Failed to post event: %s"), *Error.Message));
			});
	}
}

void FSatoriUnrealModule::HandleAppForeground()
{
	// Track resume or send appForeground event
	SATORI_LOG_INFO("App in focus");
}

void FSatoriUnrealModule::HandleAppBackground()
{
	// TODO: Do we want to flush some events?
	SATORI_LOG_INFO("App out of focus");
}

void FSatoriUnrealModule::HandleAppShutdown()
{
	if (SatoriErrorLogDevice && GLog)
	{
		GLog->RemoveOutputDevice(SatoriErrorLogDevice.Get());
		SATORI_LOG_INFO("Satori error forwarder unregistered.");
		SatoriErrorLogDevice.Reset();
	}	
	if (Client)
	{
		Client->Disconnect();
		Client->RemoveFromRoot();
		Client = nullptr;
	}
	if (Session)
	{
		Session->RemoveFromRoot();
		Session = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSatoriUnrealModule, SatoriUnreal)
