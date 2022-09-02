// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaLibrary.h"

#include "JsonObjectConverter.h"

UNakamaClient* UNakamaLibrary::CreateDefaultClient(const FString& ServerKey, const FString& Host, int32 Port,
                                                   bool UseSSL, bool EnableDebug, ENakamaClientType Type, float TickInterval, const FString& DisplayName)
{
	UNakamaClient* NewClient = NewObject<UNakamaClient>();
	NewClient->InitializeSystem(ServerKey, Host, Port, UseSSL, EnableDebug, Type, TickInterval, DisplayName);
	return NewClient;
}

FNakamaChatMessage UNakamaLibrary::ChatMessageJsonToStruct(FString JsonMessage)
{
	FNakamaChatMessage parsedStruct;

	FJsonObjectConverter::JsonObjectStringToUStruct(JsonMessage, &parsedStruct, 0, 0);

	return parsedStruct;	
}

FString UNakamaLibrary::ChatMessageStructToJson(FNakamaChatMessage MessageStruct)
{
	FString Message;
	FJsonObjectConverter::UStructToJsonObjectString(MessageStruct, Message, 0, 0, 0, 0, true);
	return Message;
}

