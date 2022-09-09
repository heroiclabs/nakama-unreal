// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaLibrary.h"

#include "JsonObjectConverter.h"

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

