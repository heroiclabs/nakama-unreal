#include "NakamaStorageObject.h"
#include "NakamaUtils.h"

FNakamaStoreObjectData::FNakamaStoreObjectData(const FString& JsonString) : FNakamaStoreObjectData(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FNakamaStoreObjectData::FNakamaStoreObjectData(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("collection"), Collection);
		JsonObject->TryGetStringField(TEXT("key"), Key);
		JsonObject->TryGetStringField(TEXT("user_id"), UserId);
		JsonObject->TryGetStringField(TEXT("value"), Value);
		JsonObject->TryGetStringField(TEXT("version"), Version);

		int32 PermissionReadValue;
		if (JsonObject->TryGetNumberField(TEXT("permission_read"), PermissionReadValue))
		{
			PermissionRead = static_cast<ENakamaStoragePermissionRead>(PermissionReadValue);
		}

		int32 PermissionWriteValue;
		if (JsonObject->TryGetNumberField(TEXT("permission_write"), PermissionWriteValue))
		{
			PermissionWrite = static_cast<ENakamaStoragePermissionWrite>(PermissionWriteValue);
		}
		
		FString CreatedAtString;
		if (JsonObject->TryGetStringField(TEXT("create_time"), CreatedAtString))
		{
			FDateTime::ParseIso8601(*CreatedAtString, CreateTime);
		}
		
		FString UpdatedAtString;
		if (JsonObject->TryGetStringField(TEXT("update_time"), UpdatedAtString))
		{
			FDateTime::ParseIso8601(*UpdatedAtString, UpdateTime);
		}
	}
}

FNakamaStoreObjectData::FNakamaStoreObjectData(): PermissionRead(ENakamaStoragePermissionRead::NO_READ), PermissionWrite(ENakamaStoragePermissionWrite::NO_WRITE)
{
	
}

FNakamaStoreObjectWrite::FNakamaStoreObjectWrite(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("collection"), Collection);
		JsonObject->TryGetStringField(TEXT("key"), Key);
		JsonObject->TryGetStringField(TEXT("value"), Value);
		JsonObject->TryGetStringField(TEXT("version"), Version);

		int32 PermissionReadValue;
		if (JsonObject->TryGetNumberField(TEXT("permission_read"), PermissionReadValue))
		{
			PermissionRead = static_cast<ENakamaStoragePermissionRead>(PermissionReadValue);
		}

		int32 PermissionWriteValue;
		if (JsonObject->TryGetNumberField(TEXT("permission_write"), PermissionWriteValue))
		{
			PermissionWrite = static_cast<ENakamaStoragePermissionWrite>(PermissionWriteValue);
		}
	}
}

FNakamaStoreObjectWrite::FNakamaStoreObjectWrite(): PermissionRead(), PermissionWrite()
{
}

FNakamaReadStorageObjectId::FNakamaReadStorageObjectId(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("collection"), Collection);
		JsonObject->TryGetStringField(TEXT("key"), Key);
		JsonObject->TryGetStringField(TEXT("user_id"), UserId);
	}
}

FNakamaReadStorageObjectId::FNakamaReadStorageObjectId()
{
	
}

FNakamaDeleteStorageObjectId::FNakamaDeleteStorageObjectId(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("collection"), Collection);
		JsonObject->TryGetStringField(TEXT("key"), Key);
		JsonObject->TryGetStringField(TEXT("version"), Version);
	}
}

FNakamaDeleteStorageObjectId::FNakamaDeleteStorageObjectId()
{
	
}

FNakamaStoreObjectAck::FNakamaStoreObjectAck(const FString& JsonString) : FNakamaStoreObjectAck(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FNakamaStoreObjectAck::FNakamaStoreObjectAck(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("collection"), Collection);
		JsonObject->TryGetStringField(TEXT("key"), Key);
		JsonObject->TryGetStringField(TEXT("version"), Version);
		JsonObject->TryGetStringField(TEXT("user_id"), UserId);
	}
}


FNakamaStoreObjectAck::FNakamaStoreObjectAck()
{
	
}

FNakamaStoreObjectAcks::FNakamaStoreObjectAcks(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* StorageJobjectsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("acks"), StorageJobjectsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& StorageJson : *StorageJobjectsJsonArray)
			{
				if (TSharedPtr<FJsonObject> StorageJsonObject = StorageJson->AsObject())
				{
					StorageObjects.Add(FNakamaStoreObjectAck(StorageJsonObject));
				}
			}
		}
	}
}


FNakamaStoreObjectAcks::FNakamaStoreObjectAcks()
{
	
}

FNakamaStorageObjectList::FNakamaStorageObjectList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* StorageJobjectsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("objects"), StorageJobjectsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& StorageJson : *StorageJobjectsJsonArray)
			{
				if (TSharedPtr<FJsonObject> StorageJsonObject = StorageJson->AsObject())
				{
					Objects.Add(FNakamaStoreObjectData(StorageJsonObject));
				}
			}
		}

		JsonObject->TryGetStringField(TEXT("cursor"), Cursor);
	}
}

FNakamaStorageObjectList::FNakamaStorageObjectList()
{
	
}
