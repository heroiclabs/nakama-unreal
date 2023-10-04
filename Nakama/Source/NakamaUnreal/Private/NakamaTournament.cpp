#include "NakamaTournament.h"

#include "NakamaUtils.h"

FNakamaTournament::FNakamaTournament(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField("id", Id);
		JsonObject->TryGetStringField("title", Title);
		JsonObject->TryGetStringField("description", Description);
		JsonObject->TryGetNumberField("category", Category);
		JsonObject->TryGetNumberField("sort_order", SortOrder);
		JsonObject->TryGetNumberField("size", Size);
		JsonObject->TryGetNumberField("max_size", MaxSize);
		JsonObject->TryGetNumberField("max_num_score", MaxNumScore);
		JsonObject->TryGetBoolField("can_enter", CanEnter);

		FString CreateTimeString;
		if (JsonObject->TryGetStringField("create_time", CreateTimeString))
		{
			FDateTime::ParseIso8601(*CreateTimeString, CreateTime);
		}

		FString StartTimeString;
		if (JsonObject->TryGetStringField("start_time", StartTimeString))
		{
			FDateTime::ParseIso8601(*StartTimeString, StartTime);
		}

		FString EndTimeString;
		if (JsonObject->TryGetStringField("end_time", EndTimeString))
		{
			FDateTime::ParseIso8601(*EndTimeString, EndTime);
		}

		JsonObject->TryGetNumberField("end_active", EndActive);
		JsonObject->TryGetNumberField("next_reset", NextReset);
		JsonObject->TryGetNumberField("duration", Duration);
		JsonObject->TryGetNumberField("start_active", StartActive);

		JsonObject->TryGetStringField("metadata", Metadata);
	}
}

FNakamaTournament::FNakamaTournament()
{
	
}

FNakamaTournamentRecordList::FNakamaTournamentRecordList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
    const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
        const TArray<TSharedPtr<FJsonValue>>* RecordsJsonArray;
        if (JsonObject->TryGetArrayField("records", RecordsJsonArray))
        {
            for (const TSharedPtr<FJsonValue>& RecordJson : *RecordsJsonArray)
            {
                if (RecordJson->Type == EJson::Object)
                {
                    TSharedPtr<FJsonObject> RecordJsonObject = RecordJson->AsObject();
                    if (RecordJsonObject.IsValid())
                    {
                        FString RecordJsonString;
                        TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RecordJsonString);
                        if (FJsonSerializer::Serialize(RecordJsonObject.ToSharedRef(), JsonWriter))
                        {
                            JsonWriter->Close();
                            FNakamaLeaderboardRecord Record(RecordJsonString);
                            Records.Add(Record);
                        }
                    }
                }
            }
        }

        const TArray<TSharedPtr<FJsonValue>>* OwnerRecordsJsonArray;
        if (JsonObject->TryGetArrayField("owner_records", OwnerRecordsJsonArray))
        {
            for (const TSharedPtr<FJsonValue>& OwnerRecordJson : *OwnerRecordsJsonArray)
            {
                if (OwnerRecordJson->Type == EJson::Object)
                {
                    TSharedPtr<FJsonObject> OwnerRecordJsonObject = OwnerRecordJson->AsObject();
                    if (OwnerRecordJsonObject.IsValid())
                    {
                        FString OwnerRecordJsonString;
                        TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OwnerRecordJsonString);
                        if (FJsonSerializer::Serialize(OwnerRecordJsonObject.ToSharedRef(), JsonWriter))
                        {
                            JsonWriter->Close();
                            FNakamaLeaderboardRecord OwnerRecord(OwnerRecordJsonString);
                            OwnerRecords.Add(OwnerRecord);
                        }
                    }
                }
            }
        }

        JsonObject->TryGetStringField("next_cursor", NextCursor);
        JsonObject->TryGetStringField("prev_cursor", PrevCursor);
    }
	
}

FNakamaTournamentRecordList::FNakamaTournamentRecordList()
{
	
}

FNakamaTournamentList::FNakamaTournamentList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* TournamentsJsonArray;
		if (JsonObject->TryGetArrayField("tournaments", TournamentsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& TournamentJson : *TournamentsJsonArray)
			{
				if (TournamentJson->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> TournamentJsonObject = TournamentJson->AsObject();
					if (TournamentJsonObject.IsValid())
					{
						FString TournamentJsonString;
						TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&TournamentJsonString);
						if (FJsonSerializer::Serialize(TournamentJsonObject.ToSharedRef(), JsonWriter))
						{
							JsonWriter->Close();
							FNakamaTournament Tournament(TournamentJsonString);
							Tournaments.Add(Tournament);
						}
					}
				}
			}
		}

		JsonObject->TryGetStringField("cursor", Cursor);
	}
}


FNakamaTournamentList::FNakamaTournamentList()
{
	
}
