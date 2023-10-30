// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaUser.generated.h"

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUser
{
	GENERATED_BODY()

	// The id of the user's account.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString Id;

	// The username of the user's account.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString Username;

	// The display name of the user.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString DisplayName;

	// A URL for an avatar image.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString AvatarUrl;

	// The language expected to be a tag which follows the BCP-47 spec.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString Language;

	// The location set by the user.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString Location;

	// The timezone set by the user.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString TimeZone;

	// Additional information stored as a JSON object.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString MetaData;

	// The Facebook id in the user's account.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString FacebookId;

	// The Google id in the user's account.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString GoogleId;

	// The Apple Game Center in of the user's account.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString GameCenterId;

	// The Apple Sign In ID in the user's account.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString AppleId;

	// The Steam ID in the user's account.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FString SteamId;

	// Indicates whether the user is currently online.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	bool Online = false;

	// Number of related edges to this user (friends).
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	int32 EdgeCount;

	// The UNIX time when the user was created.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FDateTime CreatedAt;

	// The UNIX time when the user was last updated.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	FDateTime updatedAt;

	FNakamaUser(const FString& JsonString);
	FNakamaUser(): EdgeCount(0), CreatedAt(0), updatedAt(0) { }

};


USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUserList
{
	GENERATED_BODY()

	// List of Users
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User")
	TArray<FNakamaUser> Users;

	FNakamaUserList(const FString& JsonString);
	FNakamaUserList() { }
};
