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

#include "NakamaLeaderboard.h"
#include "NakamaUtils.h"

FNakamaLeaderboardRecord::FNakamaLeaderboardRecord(const FString& JsonString) : FNakamaLeaderboardRecord(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FNakamaLeaderboardRecord::FNakamaLeaderboardRecord(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
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
                if (TSharedPtr<FJsonObject> RecordJsonObject = RecordJsonValue->AsObject())
				{
					Records.Add(FNakamaLeaderboardRecord(RecordJsonObject));
				}
            }
        }

        const TArray<TSharedPtr<FJsonValue>>* OwnerRecordsJsonArray;
        if (JsonObject->TryGetArrayField(TEXT("owner_records"), OwnerRecordsJsonArray))
        {
            for (const TSharedPtr<FJsonValue>& OwnerRecordJsonValue : *OwnerRecordsJsonArray)
            {
				if (TSharedPtr<FJsonObject> OwnerRecordJsonObject = OwnerRecordJsonValue->AsObject())
				{
					OwnerRecords.Add(FNakamaLeaderboardRecord(OwnerRecordJsonObject));
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
