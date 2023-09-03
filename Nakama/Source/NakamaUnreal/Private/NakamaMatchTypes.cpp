#include "NakamaMatchTypes.h"

#include "NakamaUtils.h"

FNakamaMatchmakerUser::FNakamaMatchmakerUser(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FString PresenceJsonString;
		auto Writer = TJsonWriterFactory<>::Create(&PresenceJsonString);
		if (FJsonSerializer::Serialize(JsonObject->GetObjectField("presence").ToSharedRef(), Writer))
		{
			Writer->Close();
			Presence = FNakamaUserPresence(PresenceJsonString);
		}

		const TSharedPtr<FJsonObject>* StringPropertiesObject;
		if (JsonObject->TryGetObjectField("string_properties", StringPropertiesObject))
		{
			for (const auto& Entry : (*StringPropertiesObject)->Values)
			{
				StringProperties.Add(Entry.Key, Entry.Value->AsString());
			}
		}

		const TSharedPtr<FJsonObject>* NumericPropertiesObject;
		if (JsonObject->TryGetObjectField("numeric_properties", NumericPropertiesObject))
		{
			for (const auto& Entry : (*NumericPropertiesObject)->Values)
			{
				NumericProperties.Add(Entry.Key, Entry.Value->AsNumber());
			}
		}
	}
}

FNakamaMatchmakerUser::FNakamaMatchmakerUser()
{
	
}

FNakamaMatchmakerMatched::FNakamaMatchmakerMatched(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField("ticket", Ticket);
		JsonObject->TryGetStringField("match_id", MatchId);
		JsonObject->TryGetStringField("token", Token);

		const TArray<TSharedPtr<FJsonValue>>* UsersJsonArray;
		if (JsonObject->TryGetArrayField("users", UsersJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserJson : *UsersJsonArray)
			{
				if (UserJson->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> UserJsonObject = UserJson->AsObject();
					FString UserJsonString;
					auto Writer = TJsonWriterFactory<>::Create(&UserJsonString);
					if (FJsonSerializer::Serialize(UserJsonObject.ToSharedRef(), Writer))
					{
						Writer->Close();
						FNakamaMatchmakerUser User(UserJsonString);
						Users.Add(User);
					}
				}
			}
		}

		FString MeJsonString;
		auto Writer = TJsonWriterFactory<>::Create(&MeJsonString);
		if (FJsonSerializer::Serialize(JsonObject->GetObjectField("self").ToSharedRef(), Writer))
		{
			Writer->Close();
			Me = FNakamaMatchmakerUser(MeJsonString);
		}
	}
}

FNakamaMatchmakerMatched::FNakamaMatchmakerMatched()
{
	
}

FNakamaMatchPresenceEvent::FNakamaMatchPresenceEvent(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField("match_id", MatchId);

		const TArray<TSharedPtr<FJsonValue>>* JoinsJsonArray;
		if (JsonObject->TryGetArrayField("joins", JoinsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& JoinJson : *JoinsJsonArray)
			{
				if (JoinJson->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> JoinJsonObject = JoinJson->AsObject();
					FString JoinJsonString;
					auto Writer = TJsonWriterFactory<>::Create(&JoinJsonString);
					if (FJsonSerializer::Serialize(JoinJsonObject.ToSharedRef(), Writer))
					{
						Writer->Close();
						FNakamaUserPresence Join(JoinJsonString);
						Joins.Add(Join);
					}
				}
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* LeavesJsonArray;
		if (JsonObject->TryGetArrayField("leaves", LeavesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& LeaveJson : *LeavesJsonArray)
			{
				if (LeaveJson->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> LeaveJsonObject = LeaveJson->AsObject();
					FString LeaveJsonString;
					auto Writer = TJsonWriterFactory<>::Create(&LeaveJsonString);
					if (FJsonSerializer::Serialize(LeaveJsonObject.ToSharedRef(), Writer))
					{
						Writer->Close();
						FNakamaUserPresence Leave(LeaveJsonString);
						Leaves.Add(Leave);
					}
				}
			}
		}
	}
}

FNakamaMatchPresenceEvent::FNakamaMatchPresenceEvent()
{
	
}

FNakamaMatchmakerTicket::FNakamaMatchmakerTicket(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TSharedPtr<FJsonObject> MatchmakerTicketObject = JsonObject->GetObjectField(TEXT("matchmaker_ticket"));
		if (MatchmakerTicketObject.IsValid())
		{
			MatchmakerTicketObject->TryGetStringField(TEXT("ticket"), TicketId);
		}
	}
}

FNakamaMatchmakerTicket::FNakamaMatchmakerTicket()
{
	
}
