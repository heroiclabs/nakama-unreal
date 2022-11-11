#include "NakamaStorageObject.h"

#include "NakamaUtils.h"

FNakamaStoreObjectData::FNakamaStoreObjectData(const NStorageObject& NakamaNativeStorageObject)
	: Collection(FNakamaUtils::StdStringToUEString(NakamaNativeStorageObject.collection))
	, Key(FNakamaUtils::StdStringToUEString(NakamaNativeStorageObject.key))
	, UserId(FNakamaUtils::StdStringToUEString(NakamaNativeStorageObject.userId))
	, Value(FNakamaUtils::StdStringToUEString(NakamaNativeStorageObject.value))
	, Version(FNakamaUtils::StdStringToUEString(NakamaNativeStorageObject.version))
	, PermissionRead(static_cast<ENakamaStoragePermissionRead>(NakamaNativeStorageObject.permissionRead))
	, PermissionWrite(static_cast<ENakamaStoragePermissionWrite>(NakamaNativeStorageObject.permissionWrite))
	, CreateTime(FDateTime::FromUnixTimestamp(NakamaNativeStorageObject.createTime / 1000))
	, UpdateTime(FDateTime::FromUnixTimestamp(NakamaNativeStorageObject.updateTime / 1000))
{
	
}

FNakamaStoreObjectData::FNakamaStoreObjectData(): PermissionRead(ENakamaStoragePermissionRead::NO_READ), PermissionWrite(ENakamaStoragePermissionWrite::NO_WRITE)
{
	
}

FNakamaStoreObjectWrite::FNakamaStoreObjectWrite(const NStorageObjectWrite& NakamaNativeStorageWrite)
	: Collection(FNakamaUtils::StdStringToUEString(NakamaNativeStorageWrite.collection))
	, Key(FNakamaUtils::StdStringToUEString(NakamaNativeStorageWrite.key))
	, Value(FNakamaUtils::StdStringToUEString(NakamaNativeStorageWrite.value))
	, Version(FNakamaUtils::StdStringToUEString(NakamaNativeStorageWrite.version))
	, PermissionRead(static_cast<ENakamaStoragePermissionRead>(NakamaNativeStorageWrite.permissionRead.value()))
	, PermissionWrite(static_cast<ENakamaStoragePermissionWrite>(NakamaNativeStorageWrite.permissionRead.value()))
{
	
}

FNakamaStoreObjectWrite::FNakamaStoreObjectWrite(): PermissionRead(), PermissionWrite()
{
}

FNakamaReadStorageObjectId::FNakamaReadStorageObjectId(const NReadStorageObjectId& NakamaNativeReadStorageObjectId)
	: Collection(FNakamaUtils::StdStringToUEString(NakamaNativeReadStorageObjectId.collection))
	, Key(FNakamaUtils::StdStringToUEString(NakamaNativeReadStorageObjectId.key))
	, UserId(FNakamaUtils::StdStringToUEString(NakamaNativeReadStorageObjectId.userId))
{
	
}

FNakamaReadStorageObjectId::FNakamaReadStorageObjectId()
{
	
}

FNakamaDeleteStorageObjectId::FNakamaDeleteStorageObjectId(const NDeleteStorageObjectId& NakamaNativeDeleteStorageObjectId)
	: Collection(FNakamaUtils::StdStringToUEString(NakamaNativeDeleteStorageObjectId.collection))
	, Key(FNakamaUtils::StdStringToUEString(NakamaNativeDeleteStorageObjectId.key))
	, Version(FNakamaUtils::StdStringToUEString(NakamaNativeDeleteStorageObjectId.version))
{
	
}

FNakamaDeleteStorageObjectId::FNakamaDeleteStorageObjectId()
{
	
}

FNakamaStoreObjectAck::FNakamaStoreObjectAck(const NStorageObjectAck& NakamaNativeStorageObjectAck)
	: Collection(FNakamaUtils::StdStringToUEString(NakamaNativeStorageObjectAck.collection))
	, Key(FNakamaUtils::StdStringToUEString(NakamaNativeStorageObjectAck.key))
	, Version(FNakamaUtils::StdStringToUEString(NakamaNativeStorageObjectAck.version))
	, UserId(FNakamaUtils::StdStringToUEString(NakamaNativeStorageObjectAck.userId))
{
	
}

FNakamaStoreObjectAck::FNakamaStoreObjectAck()
{
	
}

FNakamaStoreObjectAcks::FNakamaStoreObjectAcks(const NStorageObjectAcks& NakamaNativeStorageObjectAcks)
	: StorageObjects()
{
	if(NakamaNativeStorageObjectAcks.size() > 0)
	{
		for(auto &StorageObject : NakamaNativeStorageObjectAcks)
		{
			StorageObjects.Add(StorageObject);
		}
	}

}

FNakamaStoreObjectAcks::FNakamaStoreObjectAcks()
{
	
}

FNakamaStorageObjectList::FNakamaStorageObjectList(const NStorageObjectList& NakamaNativeStorageObjectList)
	: Objects()
	, Cursor(FNakamaUtils::StdStringToUEString(NakamaNativeStorageObjectList.cursor))
{
	if(NakamaNativeStorageObjectList.objects.size() > 0)
	{
		for(auto &StorageObject : NakamaNativeStorageObjectList.objects)
		{
			Objects.Add(StorageObject);
		}
	}
}

FNakamaStorageObjectList::FNakamaStorageObjectList()
{
	
}
