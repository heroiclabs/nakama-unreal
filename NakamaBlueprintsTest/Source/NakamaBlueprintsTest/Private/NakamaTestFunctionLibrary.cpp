// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaTestFunctionLibrary.h"

FString UNakamaTestFunctionLibrary::GetMatchIdFromJsonString(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FString MatchId;
		if (JsonObject->TryGetStringField("match_id", MatchId))
		{
			return MatchId;
		}
	}

	// Return an empty string if the parsing fails or if the "match_id" field is not present
	return FString();
}

FString UNakamaTestFunctionLibrary::GenerateTournamentJSONString(bool bAuthoritative, const FString& SortOrder,
	const FString& Operator, int32 Duration, const FString& ResetSchedule, const FString& Title,
	const FString& Description, int32 Category, int64 StartTime, int64 EndTime, int32 MaxSize, int32 MaxNumScore,
	bool bJoinRequired)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	JsonObject->SetBoolField("authoritative", bAuthoritative);
	JsonObject->SetStringField("sort_order", SortOrder);
	JsonObject->SetStringField("operator", Operator);
	JsonObject->SetNumberField("duration", Duration);
	JsonObject->SetStringField("reset_schedule", ResetSchedule);
	JsonObject->SetStringField("title", Title);
	JsonObject->SetStringField("description", Description);
	JsonObject->SetNumberField("category", Category);
	JsonObject->SetNumberField("start_time", StartTime);
	JsonObject->SetNumberField("end_time", EndTime);
	JsonObject->SetNumberField("max_size", MaxSize);
	JsonObject->SetNumberField("max_num_score", MaxNumScore);
	JsonObject->SetBoolField("join_required", bJoinRequired);

	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	return JsonString;
}

int64 UNakamaTestFunctionLibrary::GetCurrentUnixTimestampInSeconds()
{
	return FDateTime::Now().ToUnixTimestamp();
}

FString UNakamaTestFunctionLibrary::GetTournamentIdFromJsonString(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FString TournamentId;
		if (JsonObject->TryGetStringField("tournament_id", TournamentId))
		{
			return TournamentId;
		}
	}

	// Return an empty string if the parsing fails or if the "tournament_id" field is not present
	return FString();
}
