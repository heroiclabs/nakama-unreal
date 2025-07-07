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
#include "NakamaUser.h"
#include "NakamaFriend.generated.h"

// The friendship status.
UENUM(BlueprintType)
enum class ENakamaFriendState : uint8
{
	FRIEND UMETA(DisplayName = "Friend"), // The user is a friend of the current user.
	INVITE_SENT UMETA(DisplayName = "Invite Sent"), // The current user has sent an invite to the user.
	INVITE_RECEIVED UMETA(DisplayName = "Invite Received"), // The current user has received an invite from this user.
	BLOCKED UMETA(DisplayName = "Blocked"), // The current user has blocked this user.
	ALL UMETA(DisplayName = "All"), // Custom for this Plugin
};


// A friend of a user.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaFriend
{
	GENERATED_BODY()

	// The user object.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Friend")
	FNakamaUser NakamaUser;

	// The friend status.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Friend")
	ENakamaFriendState UserState;

	// Time of the latest relationship update.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FDateTime UpdateTime;

	FNakamaFriend(const FString& JsonString);
    FNakamaFriend(const TSharedPtr<FJsonObject> JsonObject);
	FNakamaFriend();

	static ENakamaFriendState GetFriendStateFromString(const FString& StateString);
};

USTRUCT(BlueprintType) // Internal Unreal Class (No Need to Convert)
struct NAKAMAUNREAL_API FNakamaFriendChat
{
	GENERATED_BODY()

	// User
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Friend")
	FNakamaUser NakamaUser;

	// Chat Id.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Friend")
	FString ChatId;

};

// A collection of zero or more friends of the user.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaFriendList
{
	GENERATED_BODY()

	// The Friend objects.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Friend")
	TArray<FNakamaFriend> NakamaUsers;

	// Cursor for the next page of results, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Friend")
	FString Cursor;

	FNakamaFriendList(const FString& JsonString);
	FNakamaFriendList();
};