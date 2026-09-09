/*
* Copyright 2026 The Nakama Authors
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

#include "SatoriErrorOutputDevice.h"

#include "SatoriLoggingMacros.h"

FSatoriErrorOutputDevice::FSatoriErrorOutputDevice(USatoriClient* InClient, USatoriSession* InSession)
{
	Client = InClient;
	Session = InSession;
}

void FSatoriErrorOutputDevice::Serialize(const TCHAR* Message, ELogVerbosity::Type Verbosity, const FName& Category)
{
	if (!Client || !Session)
	{
		return;
	}
	
	if (Verbosity == ELogVerbosity::Error)
	{
		// Walk the callstack
		ANSICHAR StackTraceBuffer[4096] = { 0 };
		FPlatformStackWalk::StackWalkAndDump(
			StackTraceBuffer,
			sizeof(StackTraceBuffer), 
			2 // skip stack frames from this handler
		);

		FString StackTrace = ANSI_TO_TCHAR(StackTraceBuffer);
		FString ErrorText = FString::Printf(TEXT("[%s] %s"), *Category.ToString(), Message);
			
		SATORI_LOG_INFO("Sending error text to Satori...");

		// TODO: Should this be an event? Which event?
		FSatoriEvent Event;
		Event.Name = TEXT("gameFinished");
		Event.Value = TEXT("satori-ue-module-error-trace");
		Event.Timestamp = FDateTime::UtcNow();
		
		Client->PostEvent(
			Session,
			{ Event }, 
			[]() { SATORI_LOG_INFO("error posted"); },
			[](const FSatoriError& Error)
			{
				SATORI_LOG_ERROR(FString::Printf(TEXT("Failed to post error event: %s"), *Error.Message));
			});
	}
}
