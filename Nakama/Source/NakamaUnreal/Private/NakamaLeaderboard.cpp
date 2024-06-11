﻿#include "NakamaLeaderboard.h"

#include "NakamaUtils.h"

FNakamaLeaderboardRecord::FNakamaLeaderboardRecord(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("leaderboard_id"), LeaderboardId);
		JsonObject->TryGetStringField(TEXT("owner_id"), OwnerId);
		JsonObject->TryGetStringField(TEXT("username"), Username);
		JsonObject->TryGetNumberField(TEXT("score"), Score);
		JsonObject->TryGetNumberField(TEXT("subscore"), SubScore);
		JsonObject->TryGetNumberField(TEXT("num_score"), NumScore);
		JsonObject->TryGetNumberField(TEXT("max_num_score"), MaxNumScore);
		JsonObject->TryGetStringField(TEXT("metadata"), Metadata);

		FString CreateTimeString;
		if (JsonObject->TryGetStringField(TEXT("create_time"), CreateTimeString))
		{
			FDateTime::ParseIso8601(*CreateTimeString, CreateTime);
		}
		
		FString UpdateTimeString;
		if (JsonObject->TryGetStringField(TEXT("update_time"), UpdateTimeString))
		{
			FDateTime::ParseIso8601(*UpdateTimeString, UpdateTime);
		}

		FString ExpiryTimeString;
		if (JsonObject->TryGetStringField(TEXT("expiry_time"), ExpiryTimeString))
		{
			FDateTime::ParseIso8601(*ExpiryTimeString, ExpiryTime);
		}
		
		JsonObject->TryGetNumberField(TEXT("rank"), Rank);
	}
}

FNakamaLeaderboardRecord::FNakamaLeaderboardRecord()
{
	
}

FNakamaLeaderboardRecordList::FNakamaLeaderboardRecordList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
    const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
        const TArray<TSharedPtr<FJsonValue>>* RecordsJsonArray;
        if (JsonObject->TryGetArrayField(TEXT("records"), RecordsJsonArray))
        {
            for (const TSharedPtr<FJsonValue>& RecordJsonValue : *RecordsJsonArray)
            {
                if (RecordJsonValue->Type == EJson::Object)
                {
                    TSharedPtr<FJsonObject> RecordJsonObject = RecordJsonValue->AsObject();

                    FString RecordJsonString;
                    auto Writer = TJsonWriterFactory<>::Create(&RecordJsonString);
                    if (FJsonSerializer::Serialize(RecordJsonObject.ToSharedRef(), Writer))
                    {
                        Writer->Close();
                        FNakamaLeaderboardRecord Record(RecordJsonString);
                        Records.Add(Record);
                    }
                }
            }
        }

        const TArray<TSharedPtr<FJsonValue>>* OwnerRecordsJsonArray;
        if (JsonObject->TryGetArrayField(TEXT("owner_records"), OwnerRecordsJsonArray))
        {
            for (const TSharedPtr<FJsonValue>& OwnerRecordJsonValue : *OwnerRecordsJsonArray)
            {
                if (OwnerRecordJsonValue->Type == EJson::Object)
                {
                    TSharedPtr<FJsonObject> OwnerRecordJsonObject = OwnerRecordJsonValue->AsObject();

                    FString OwnerRecordJsonString;
                    auto Writer = TJsonWriterFactory<>::Create(&OwnerRecordJsonString);
                    if (FJsonSerializer::Serialize(OwnerRecordJsonObject.ToSharedRef(), Writer))
                    {
                        Writer->Close();
                        FNakamaLeaderboardRecord OwnerRecord(OwnerRecordJsonString);
                        OwnerRecords.Add(OwnerRecord);
                    }
                }
            }
        }

        JsonObject->TryGetStringField(TEXT("next_cursor"), NextCursor);
        JsonObject->TryGetStringField(TEXT("prev_cursor"), PrevCursor);
    }
}

FNakamaLeaderboardRecordList::FNakamaLeaderboardRecordList()
{
	
}
