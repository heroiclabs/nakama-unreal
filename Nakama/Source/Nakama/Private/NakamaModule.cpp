/**
* Copyright 2017 The Nakama Authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "NakamaPrivatePCH.h"

#include "Engine.h"
#include "Engine/EngineTypes.h"

#include "NakamaModule.h"
#include "ModuleManager.h"

IMPLEMENT_MODULE(UNakamaModule, Nakama)

DEFINE_LOG_CATEGORY(LogNakama);

void UNakamaModule::StartupModule()
{
	UE_LOG(LogNakama, Verbose, TEXT("Nakama::StartupModule"));
}

void UNakamaModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

UNakamaModule* UNakamaModule::GetModulePtr()
{
	return FModuleManager::GetModulePtr<UNakamaModule>("Nakama");
}
