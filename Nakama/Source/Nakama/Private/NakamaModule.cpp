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

#include "NakamaModule.h"
#include "NakamaApi.h"

void FNakamaModule::StartupModule()
{
	UE_LOG(LogNakama, Log, TEXT("Nakama module starting"));
}

void FNakamaModule::ShutdownModule()
{
	UE_LOG(LogNakama, Log, TEXT("Nakama module shutting down"));
}

IMPLEMENT_MODULE(FNakamaModule, Nakama)

