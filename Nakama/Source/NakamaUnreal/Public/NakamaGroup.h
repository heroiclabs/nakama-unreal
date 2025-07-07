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
#include "NakamaGroup.generated.h"

// The group role status.
UENUM(BlueprintType)
enum class ENakamaUserGroupState : uint8
{
	SUPERADMIN UMETA(DisplayName = "Superadmin"), // The user is a superadmin with full control of the group.
	ADMIN UMETA(DisplayName = "Admin"), // The user is an admin with additional privileges.
	MEMBER UMETA(DisplayName = "Member"), // The user is a regular member.
	JOIN_REQUEST UMETA(DisplayName = "Join Request"), // The user has requested to join the group
	ALL UMETA(DisplayName = "All"), // All group states
};

static ENakamaGroupState GetGroupStateFromString(const FString& StateString);


// A group in the server.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaGroup
{
	GENERATED_BODY()

	// The id of a group.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FString Id;

	// The id of the user who created the group.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FString CreatorId;

	// The id of the user who created the group.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FString Name;

	// A description for the group.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FString Description;

	// The language expected to be a tag which follows the BCP-47 spec.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FString Language;

	// Additional information stored as a JSON object.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FString MetaData;

	// A URL for an avatar image.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FString AvatarUrl;

	// Anyone can join open groups, otherwise only admins can accept members.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	bool open = false;

	// The current count of all members in the group.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	int32 EdgeCount = 0;

	// The maximum number of members allowed.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	int32 MaxCount = 0;

	// The UNIX time when the group was created.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FDateTime CreateTime = 0;
	// The UNIX time when the group was last updated.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FDateTime UpdateTime = 0;

	FNakamaGroup(const FString& JsonString);
    FNakamaGroup(const TSharedPtr<FJsonObject> JsonObject);
	FNakamaGroup() { }
};

// Group States
UENUM(BlueprintType)
enum class ENakamaGroupState : uint8
{
	SUPERADMIN UMETA(DisplayName = "Superadmin"),
	ADMIN UMETA(DisplayName = "Admin"),
	MEMBER UMETA(DisplayName = "Member"),
	JOIN_REQUEST UMETA(DisplayName = "Join Request"),
	ALL UMETA(DisplayName = "All"),
};

// Group User
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaGroupUser
{
	GENERATED_BODY()

	// User.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FNakamaUser User;

	// Their relationship to the group.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	ENakamaGroupState State;

	FNakamaGroupUser(const FString& JsonString);
	FNakamaGroupUser(const TSharedPtr<FJsonObject> JsonObject);
	FNakamaGroupUser();
};

// Group Users list (Members)
// A list of users belonging to a group, along with their role.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaGroupUsersList
{
	GENERATED_BODY()

	// User-role pairs for a group.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	TArray<FNakamaGroupUser> GroupUsers;

	// Cursor for the next page of results, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FString Cursor;

	FNakamaGroupUsersList(const FString& JsonString);
	FNakamaGroupUsersList() { }

};

// One or more groups returned from a listing operation.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaGroupList
{
	GENERATED_BODY()

	// One or more groups.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	TArray<FNakamaGroup> Groups;

	// A cursor used to get the next page.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FString Cursor;

	FNakamaGroupList(const FString& JsonString);
	FNakamaGroupList() { }
};

// Owned by a player (I am member of..)
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUserGroup
{
	GENERATED_BODY()

	// Group.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama|Groups") //VisibleAnywhere, BlueprintReadOnly
	FNakamaGroup Group;

	// The user's relationship to the group.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama|Groups") //BlueprintReadOnly
	ENakamaGroupState State;

	FNakamaUserGroup(const FString& JsonString);
	FNakamaUserGroup(const TSharedPtr<FJsonObject> JsonObject);
	FNakamaUserGroup();
};

// A list of groups belonging to a user, along with the user's role in each group.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUserGroupList
{
	GENERATED_BODY()

	// Group-role pairs for a user.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	TArray<FNakamaUserGroup> UserGroups;

	// Cursor for the next page of results, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Groups")
	FString Cursor;

	FNakamaUserGroupList(const FString& JsonString);
	FNakamaUserGroupList();

};