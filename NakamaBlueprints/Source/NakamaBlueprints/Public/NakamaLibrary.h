// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaClient.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NakamaLibrary.generated.h"


/**
 * 
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Creates a default client to interact with Nakama server.
	 *
	 * @param ServerKey Server key should match the one on the Nakama Server.
	 * @param Host The endpoint host name.
	 * @param Port The port to use, default is 7350.
	 * @param UseSSL Use "https" scheme if you've setup SSL.
	 * @param EnableDebug To enable logs output to console with debug logging level.
	 * @param Type Client type you wish to create.
	 * @param TickInterval How often Tick Event should happen on the client (0 = every frame).
	 * @param DisplayName (Optional) Name to identify the client
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	static UNakamaClient* CreateDefaultClient(const FString& ServerKey = "defaultkey", const FString& Host = "localhost", int32 Port = 7350, bool UseSSL = false, bool EnableDebug = true, ENakamaClientType Type = ENakamaClientType::DEFAULT, float TickInterval = 0.0f, const FString& DisplayName = "");

	//UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "Nakama|Realtime")
	//void SetupRealtimeClient(UNakamaSession* Session, bool ShowAsOnline, int32 Port, ENakamaRealtimeClientProtocol Protocol);

	UFUNCTION(BlueprintCallable, Category = "Nakama|Utilities")
	static FNakamaChatMessage ChatMessageJsonToStruct(FString JsonMessage);

	UFUNCTION(BlueprintCallable, Category = "Nakama|Utilities")
	static FString ChatMessageStructToJson(FNakamaChatMessage MessageStruct);
	
	
};
