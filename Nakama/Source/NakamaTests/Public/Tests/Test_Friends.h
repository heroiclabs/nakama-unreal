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

#pragma once

#include "CoreMinimal.h"
#include "NakamaTestBase.h"

// The base class for the tests
class FNakamaFriendsTestBase : public FNakamaTestBase
{
public:
	FNakamaFriendsTestBase(const FString& InName, bool bInComplexTask) : FNakamaTestBase(InName, bInComplexTask) { }
	virtual bool SuppressLogWarnings() override { return true; }

	// Other
	UPROPERTY()
	TArray<FString> FriendIds;

	int FriendsToAdd = 5;
	int ListFriendsLimit = 1;
	
};

