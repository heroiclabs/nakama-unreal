#pragma once

#include "CoreMinimal.h"
#include "NakamaNotification.generated.h"

// A notification in the server.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaNotification
{
	GENERATED_BODY()

	// ID of the Notification.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Notification")
	FString Id;

	// Subject of the notification.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Notification")
	FString Subject;

	// Content of the notification in JSON.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Notification")
	FString Content;

	// Category code for this notification.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Notification")
	int32 Code = 0;

	// ID of the sender, if a user. Otherwise 'null'.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Notification")
	FString SenderId;

	// The UNIX time when the notification was created.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Notification")
	FDateTime CreateTime = 0;

	// True if this notification was persisted to the database.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Notification")
	bool Persistent = false;

	FNakamaNotification(const FString& JsonString);
	FNakamaNotification();
};

// A collection of zero or more notifications.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaNotificationList
{
	GENERATED_BODY()

	// Collection of notifications
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Notification")
	TArray<FNakamaNotification> Notifications;

	// Use this cursor to paginate notifications. Cache this to catch up to new notifications.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Notification")
	FString CacheableCursor;

	FNakamaNotificationList(const FString& JsonString);
	FNakamaNotificationList();

};
