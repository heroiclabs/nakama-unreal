/*
 * Copyright 2022 The Nakama Authors
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

#include "NakamaUnreal.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "UnrealLogSink.h"

#define LOCTEXT_NAMESPACE "FNakamaModule"

using namespace NAKAMA_NAMESPACE;

void FNakamaModule::StartupModule()
{
#if defined(PLATFORM_PS4) || defined(PLATFORM_PS5)
	FPlatformProcess::GetDllHandle(TEXT("nakama-sdk.prx"));
#endif

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogNakama, Log, TEXT("Nakama module loaded"));
}

void FNakamaModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNakamaModule, Nakama)