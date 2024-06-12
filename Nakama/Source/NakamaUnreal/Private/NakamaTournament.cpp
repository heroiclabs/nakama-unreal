#include "NakamaTournament.h"

#include "NakamaUtils.h"

FNakamaTournament::FNakamaTournament(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("id"), Id);
		JsonObject->TryGetStringField(TEXT("title"), Title);
		JsonObject->TryGetStringField(TEXT("description"), Description);
		JsonObject->TryGetNumberField(TEXT("category"), Category);
		JsonObject->TryGetNumberField(TEXT("sort_order"), SortOrder);
		JsonObject->TryGetNumberField(TEXT("size"), Size);
		JsonObject->TryGetNumberField(TEXT("max_size"), MaxSize);
		JsonObject->TryGetNumberField(TEXT("max_num_score"), MaxNumScore);
		JsonObject->TryGetBoolField(TEXT("can_enter"), CanEnter);

		FString CreateTimeString;
		if (JsonObject->TryGetStringField(TEXT("create_time"), CreateTimeString))
		{
			FDateTime::ParseIso8601(*CreateTimeString, CreateTime);
		}

		FString StartTimeString;
		if (JsonObject->TryGetStringField(TEXT("start_time"), StartTimeString))
		{
			FDateTime::ParseIso8601(*StartTimeString, StartTime);
		}

		FString EndTimeString;
		if (JsonObject->TryGetStringField(TEXT("end_time"), EndTimeString))
		{
			FDateTime::ParseIso8601(*EndTimeString, EndTime);
		}

		JsonObject->TryGetNumberField(TEXT("end_active"), EndActive);
		JsonObject->TryGetNumberField(TEXT("next_reset"), NextReset);
		JsonObject->TryGetNumberField(TEXT("duration"), Duration);
		JsonObject->TryGetNumberField(TEXT("start_active"), StartActive);

		JsonObject->TryGetStringField(TEXT("metadata"), Metadata);
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
        if (JsonObject->TryGetArrayField(TEXT("records"), RecordsJsonArray))
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
        if (JsonObject->TryGetArrayField(TEXT("owner_records"), OwnerRecordsJsonArray))
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

        JsonObject->TryGetStringField(TEXT("next_cursor"), NextCursor);
        JsonObject->TryGetStringField(TEXT("prev_cursor"), PrevCursor);
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
		if (JsonObject->TryGetArrayField(TEXT("tournaments"), TournamentsJsonArray))
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

		JsonObject->TryGetStringField(TEXT("cursor"), Cursor);
	}
}


FNakamaTournamentList::FNakamaTournamentList()
{
	
}
