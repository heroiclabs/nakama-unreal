/**
* Copyright 2017 The Nakama Authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "NBPDataClasses.h"

using namespace Nakama;

// ------------------------- NError -------------------------

UNBPError* UNBPError::From(NError data)
{
	auto bpItem = NewObject<UNBPError>();
	bpItem->Wrapped = data;
	return bpItem;
}

FString UNBPError::GetErrorMessage() {
	return UTF8_TO_TCHAR(Wrapped.GetErrorMessage().c_str());
}

// ------------------------- NCursor -------------------------

UNBPCursor* UNBPCursor::From(NCursor data) {
	auto bpItem = NewObject<UNBPCursor>();
	bpItem->Wrapped = data;
	return bpItem;
}

// ------------------------- NFriend -------------------------

UNBPFriend* UNBPFriend::From(NFriend data) {
	auto bpItem = NewObject<UNBPFriend>();
	bpItem->Wrapped = data;
	return bpItem;
}

TArray<UNBPFriend*> UNBPFriend::FromResultSet(NResultSet<NFriend>* resultSet)
{
	TArray<UNBPFriend*> rVal;
	auto results = resultSet->GetResults();
	for (int i = 0, maxI = results.size(); i < maxI; i++)
	{
		rVal.Add(UNBPFriend::From(results[i]));
	}
	return rVal;
}

// ------------------------- NSelf -------------------------

UNBPSelf* UNBPSelf::From(NSelf data) {
	auto bpItem = NewObject<UNBPSelf>();
	bpItem->Wrapped = data;
	return bpItem;
}

TArray<FString> UNBPSelf::GetDeviceIds()
{
	auto ids = TArray<FString>();
	auto nIds = Wrapped.GetDeviceIds();
	for (int i = 0, maxI = nIds.size(); i < maxI; i++)
	{
		auto id = nIds[i];
		ids.Add(UTF8_TO_TCHAR(id.c_str()));
	}
	return ids;
}

// ------------------------- NGroup -------------------------

UNBPGroup* UNBPGroup::From(NGroup data) {
	auto bpItem = NewObject<UNBPGroup>();
	bpItem->Wrapped = data;
	return bpItem;
}

TArray<UNBPGroup*> UNBPGroup::FromResultSet(NResultSet<NGroup>* resultSet)
{
	TArray<UNBPGroup*> rVal;
	auto results = resultSet->GetResults();
	for (int i = 0, maxI = results.size(); i < maxI; i++)
	{
		rVal.Add(UNBPGroup::From(results[i]));
	}
	return rVal;
}

// ------------------------- NGroupUser -------------------------

UNBPGroupUser* UNBPGroupUser::From(NGroupUser data) {
	auto bpItem = NewObject<UNBPGroupUser>();
	bpItem->Wrapped = data;
	return bpItem;
}

TArray<UNBPGroupUser*> UNBPGroupUser::FromResultSet(NResultSet<NGroupUser>* resultSet)
{
	TArray<UNBPGroupUser*> rVal;
	auto results = resultSet->GetResults();
	for (int i = 0, maxI = results.size(); i < maxI; i++)
	{
		rVal.Add(UNBPGroupUser::From(results[i]));
	}
	return rVal;
}

// ------------------------- NUser -------------------------

UNBPUser* UNBPUser::From(NUser data) {
	auto bpItem = NewObject<UNBPUser>();
	bpItem->Wrapped = data;
	return bpItem;
}

TArray<UNBPUser*> UNBPUser::FromResultSet(NResultSet<NUser>* resultSet)
{
	TArray<UNBPUser*> rVal;
	auto results = resultSet->GetResults();
	for (int i = 0, maxI = results.size(); i < maxI; i++)
	{
		rVal.Add(UNBPUser::From(results[i]));
	}
	return rVal;
}

// ------------------------- NStorageKey -------------------------

UNBPStorageKey* UNBPStorageKey::From(NStorageKey data) {
	auto bpItem = NewObject<UNBPStorageKey>();
	bpItem->Wrapped = data;
	return bpItem;
}

TArray<UNBPStorageKey*> UNBPStorageKey::FromResultSet(NResultSet<NStorageKey>* resultSet)
{
	TArray<UNBPStorageKey*> rVal;
	auto results = resultSet->GetResults();
	for (int i = 0, maxI = results.size(); i < maxI; i++)
	{
		rVal.Add(UNBPStorageKey::From(results[i]));
	}
	return rVal;
}

// ------------------------- NStorageKey -------------------------

UNBPStorageData* UNBPStorageData::From(NStorageData data) {
	auto bpItem = NewObject<UNBPStorageData>();
	bpItem->Wrapped = data;
	return bpItem;
}

TArray<UNBPStorageData*> UNBPStorageData::FromResultSet(NResultSet<NStorageData>* resultSet)
{
	TArray<UNBPStorageData*> rVal;
	auto results = resultSet->GetResults();
	for (int i = 0, maxI = results.size(); i < maxI; i++)
	{
		rVal.Add(UNBPStorageData::From(results[i]));
	}
	return rVal;
}

// ------------------------- NUserPresence -------------------------

UNBPUserPresence* UNBPUserPresence::From(NUserPresence data) {
	auto bpItem = NewObject<UNBPUserPresence>();
	bpItem->Wrapped = data;
	return bpItem;
}

TArray<UNBPUserPresence*> UNBPUserPresence::FromArray(std::vector<NUserPresence> pArray)
{
	TArray<UNBPUserPresence*> rVal;
	for (int i = 0, maxI = pArray.size(); i < maxI; i++)
	{
		rVal.Add(UNBPUserPresence::From(pArray[i]));
	}
	return rVal;
}

// ------------------------- NMatch -------------------------

UNBPMatch* UNBPMatch::From(NMatch data)
{
	auto bpItem = NewObject<UNBPMatch>();
	bpItem->Wrapped = data;
	return bpItem;
}

// ------------------------- NMatchData -------------------------

UNBPMatchData* UNBPMatchData::From(NMatchData data)
{
	auto bpItem = NewObject<UNBPMatchData>();
	bpItem->Wrapped = data;
	return bpItem;
}

// ------------------------- NMatchPresence -------------------------

UNBPMatchPresence* UNBPMatchPresence::From(NMatchPresence data)
{
	auto bpItem = NewObject<UNBPMatchPresence>();
	bpItem->Wrapped = data;
	return bpItem;
}

// ------------------------- NTopicId -------------------------

UNBPTopicId* UNBPTopicId::From(NTopicId data)
{
	auto bpItem = NewObject<UNBPTopicId>();
	bpItem->Wrapped = data;
	return bpItem;
}

// ------------------------- NTopic -------------------------

UNBPTopic* UNBPTopic::From(NTopic data)
{
	auto bpItem = NewObject<UNBPTopic>();
	bpItem->Wrapped = data;
	return bpItem;
}

// ------------------------- NTopicMessage -------------------------

UNBPTopicMessage* UNBPTopicMessage::From(NTopicMessage data)
{
	auto bpItem = NewObject<UNBPTopicMessage>();
	bpItem->Wrapped = data;
	return bpItem;
}

TArray<UNBPTopicMessage*> UNBPTopicMessage::FromResultSet(NResultSet<NTopicMessage>* resultSet)
{
	TArray<UNBPTopicMessage*> rVal;
	auto results = resultSet->GetResults();
	for (int i = 0, maxI = results.size(); i < maxI; i++)
	{
		rVal.Add(UNBPTopicMessage::From(results[i]));
	}
	return rVal;
}

// ------------------------- NTopicMessageAck -------------------------

UNBPTopicMessageAck* UNBPTopicMessageAck::From(NTopicMessageAck data)
{
	auto bpItem = NewObject<UNBPTopicMessageAck>();
	bpItem->Wrapped = data;
	return bpItem;
}

// ------------------------- NTopicPresence -------------------------

UNBPTopicPresence* UNBPTopicPresence::From(NTopicPresence data)
{
	auto bpItem = NewObject<UNBPTopicPresence>();
	bpItem->Wrapped = data;
	return bpItem;
}

// ------------------------- NLeaderboard -------------------------

UNBPLeaderboard* UNBPLeaderboard::From(NLeaderboard data)
{
	auto bpItem = NewObject<UNBPLeaderboard>();
	bpItem->Wrapped = data;
	return bpItem;
}

TArray<UNBPLeaderboard*> UNBPLeaderboard::FromResultSet(NResultSet<NLeaderboard>* resultSet)
{
	TArray<UNBPLeaderboard*> rVal;
	auto results = resultSet->GetResults();
	for (int i = 0, maxI = results.size(); i < maxI; i++)
	{
		rVal.Add(UNBPLeaderboard::From(results[i]));
	}
	return rVal;
}

// ------------------------- NLeaderboardRecord -------------------------

UNBPLeaderboardRecord* UNBPLeaderboardRecord::From(NLeaderboardRecord data)
{
	auto bpItem = NewObject<UNBPLeaderboardRecord>();
	bpItem->Wrapped = data;
	return bpItem;
}

TArray<UNBPLeaderboardRecord*> UNBPLeaderboardRecord::FromResultSet(NResultSet<NLeaderboardRecord>* resultSet)
{
	TArray<UNBPLeaderboardRecord*> rVal;
	auto results = resultSet->GetResults();
	for (int i = 0, maxI = results.size(); i < maxI; i++)
	{
		rVal.Add(UNBPLeaderboardRecord::From(results[i]));
	}
	return rVal;
}
