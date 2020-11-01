/*
 * Copyright 2019 The Nakama Authors
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

#pragma once

#include "nakama-cpp/NTypes.h"
#include "nakama-c/NStringMap.h"
#include "nakama-c/data/NAccount.h"
#include "nakama-c/data/NGroup.h"
#include "nakama-c/data/NGroupList.h"
#include "nakama-c/data/NGroupUserList.h"
#include "nakama-c/data/NUsers.h"
#include "nakama-c/data/NUserGroupList.h"
#include "nakama-c/data/NFriendList.h"
#include "nakama-c/data/NLeaderboardRecordList.h"
#include "nakama-c/data/NMatchList.h"
#include "nakama-c/data/NNotificationList.h"
#include "nakama-c/data/NChannelMessageList.h"
#include "nakama-c/data/NTournamentList.h"
#include "nakama-c/data/NTournamentRecordList.h"
#include "nakama-c/data/NStorageObjectList.h"
#include "nakama-c/data/NStorageObjectAck.h"
#include "nakama-c/data/NStorageObjectWrite.h"
#include "nakama-c/data/NStorageObjectId.h"
#include "nakama-c/data/NRpc.h"

NAKAMA_NAMESPACE_BEGIN

NStringMap toCppNStringMap(::NStringMap map)
{
    NStringMap cppMap;

    if (map)
    {
        auto size = ::NStringMap_getSize(map);

        if (size > 0)
        {
            const char** keys = new const char* [size];
            ::NStringMap_getKeys(map, keys);

            for (uint16_t i = 0; i < size; ++i)
            {
                cppMap.emplace(keys[i], ::NStringMap_getValue(map, keys[i]));
            }

            delete[] keys;
        }
    }

    return cppMap;
}

NStringDoubleMap toCppNStringDoubleMap(::NStringDoubleMap map)
{
    NStringDoubleMap cppMap;

    if (map)
    {
        auto size = ::NStringDoubleMap_getSize(map);

        if (size > 0)
        {
            const char** keys = new const char* [size];
            ::NStringDoubleMap_getKeys(map, keys);
            double value = 0;

            for (uint16_t i = 0; i < size; ++i)
            {
                if (::NStringDoubleMap_getValue(map, keys[i], &value))
                {
                    cppMap.emplace(keys[i], value);
                }
            }

            delete[] keys;
        }
    }

    return cppMap;
}

::NStringMap toCNStringMap(const NStringMap& map)
{
    ::NStringMap cMap = nullptr;

    if (map.size() > 0)
    {
        cMap = ::NStringMap_create();

        for (auto it : map)
        {
            ::NStringMap_setValue(cMap, it.first.c_str(), it.second.c_str());
        }
    }

    return cMap;
}

::NStringDoubleMap toCNStringDoubleMap(const NStringDoubleMap& map)
{
    ::NStringDoubleMap cMap = nullptr;

    if (map.size() > 0)
    {
        cMap = ::NStringDoubleMap_create();

        for (auto it : map)
        {
            ::NStringDoubleMap_setValue(cMap, it.first.c_str(), it.second);
        }
    }

    return cMap;
}

void assign(sNBytes& cData, const NBytes& data)
{
    cData.bytes = (uint8_t*)data.data();
    cData.size = (uint32_t)data.size();
}

void assign(NBytes& data, const sNBytes* cData)
{
    data.assign((const char*)cData->bytes, cData->size);
}

void assign(NError& error, const sNError* cError)
{
    error.code = (ErrorCode)cError->code;
    error.message = cError->message;
}

void assign(NStringMap& map, const ::NStringMap cMap)
{
    map = toCppNStringMap(cMap);
}

void assign(NStringDoubleMap& map, const ::NStringDoubleMap cMap)
{
    map = toCppNStringDoubleMap(cMap);
}

void assign(NAccountDevice& device, const sNAccountDevice* cDevice)
{
    device.id = cDevice->id;
}

void assign(std::vector<NAccountDevice>& devices, const sNAccountDevice* cDevices, uint16_t devicesCount)
{
    devices.resize(devicesCount);

    for (uint16_t i=0; i < devicesCount; ++i)
    {
        assign(devices[i], &cDevices[i]);
    }
}

void assign(NUser& user, const sNUser* cUser)
{
    user.id           = cUser->id;
    user.username     = cUser->username;
    user.displayName  = cUser->displayName;
    user.avatarUrl    = cUser->avatarUrl;
    user.lang         = cUser->lang;
    user.location     = cUser->location;
    user.timeZone     = cUser->timeZone;
    user.metadata     = cUser->metadata;
    user.facebookId   = cUser->facebookId;
    user.googleId     = cUser->googleId;
    user.gameCenterId = cUser->gameCenterId;
    user.appleId      = cUser->appleId;
    user.steamId      = cUser->steamId;
    user.online       = cUser->online;
    user.edgeCount    = cUser->edgeCount;
    user.createdAt    = cUser->createdAt;
    user.updatedAt    = cUser->updatedAt;
}

void assign(NAccount& account, const sNAccount* cAccount)
{
    assign(account.user, &cAccount->user);
    account.wallet = cAccount->wallet;
    account.email = cAccount->email;
    assign(account.devices, cAccount->devices, cAccount->devicesCount);
    account.customId = cAccount->customId;
    account.verifyTime = cAccount->verifyTime;
    account.disableTime = cAccount->disableTime;
}

void assign(NUsers& users, const sNUsers* cUsers)
{
    users.users.resize(cUsers->usersCount);

    for (uint16_t i=0; i < cUsers->usersCount; ++i)
    {
        assign(users.users[i], &cUsers->users[i]);
    }
}

void assign(NFriend& aFriend, const sNFriend* cFriend)
{
    aFriend.state = (NFriend::State)cFriend->state;
    aFriend.updateTime = cFriend->updateTime;
    assign(aFriend.user, &cFriend->user);
}

void assign(NFriendList& friendList, const sNFriendList* cFriendList)
{
    friendList.cursor = cFriendList->cursor;
    friendList.friends.resize(cFriendList->friendsCount);

    for (uint16_t i = 0; i < cFriendList->friendsCount; ++i)
    {
        assign(friendList.friends[i], &cFriendList->friends[i]);
    }
}

void assign(NGroup& group, const sNGroup* cGroup)
{
    group.id = cGroup->id;
    group.creatorId = cGroup->creatorId;
    group.name = cGroup->name;
    group.description = cGroup->description;
    group.lang = cGroup->lang;
    group.metadata = cGroup->metadata;
    group.avatarUrl = cGroup->avatarUrl;
    group.open = cGroup->open;
    group.edgeCount = cGroup->edgeCount;
    group.maxCount = cGroup->maxCount;
    group.createTime = cGroup->createTime;
    group.updateTime = cGroup->updateTime;
}

void assign(NGroupUser& groupUser, const sNGroupUser* cGroupUser)
{
    assign(groupUser.user, &cGroupUser->user);
    groupUser.state = (NUserGroupState)cGroupUser->state;
}

void assign(NGroupUserList& groupUserList, const sNGroupUserList* cGroupUserList)
{
    groupUserList.cursor = cGroupUserList->cursor;
    groupUserList.groupUsers.resize(cGroupUserList->groupUsersCount);

    for (uint16_t i=0; i < cGroupUserList->groupUsersCount; ++i)
    {
        assign(groupUserList.groupUsers[i], &cGroupUserList->groupUsers[i]);
    }
}

void assign(NGroupList& groupList, const sNGroupList* cGroupList)
{
    groupList.cursor = cGroupList->cursor;
    groupList.groups.resize(cGroupList->groupsCount);

    for (uint16_t i = 0; i < cGroupList->groupsCount; ++i)
    {
        assign(groupList.groups[i], &cGroupList->groups[i]);
    }
}

void assign(NUserGroup& userGroup, const sNUserGroup* cUserGroup)
{
    assign(userGroup.group, &cUserGroup->group);
    userGroup.state = (NUserGroupState)cUserGroup->state;
}

void assign(NUserGroupList& userGroupList, const sNUserGroupList* cUserGroupList)
{
    userGroupList.cursor = cUserGroupList->cursor;
    userGroupList.userGroups.resize(cUserGroupList->userGroupsCount);

    for (uint16_t i = 0; i < cUserGroupList->userGroupsCount; ++i)
    {
        assign(userGroupList.userGroups[i], &cUserGroupList->userGroups[i]);
    }
}

void assign(NLeaderboardRecord& record, const sNLeaderboardRecord* cRecord)
{
    record.leaderboardId = cRecord->leaderboardId;
    record.ownerId = cRecord->ownerId;
    record.username = cRecord->username;
    record.score = cRecord->score;
    record.subscore = cRecord->subscore;
    record.numScore = cRecord->numScore;
    record.maxNumScore = cRecord->maxNumScore;
    record.metadata = cRecord->metadata;
    record.createTime = cRecord->createTime;
    record.updateTime = cRecord->updateTime;
    record.expiryTime = cRecord->expiryTime;
    record.rank = cRecord->rank;
}

void assign(std::vector<NLeaderboardRecord>& records, const sNLeaderboardRecord* cRecords, uint16_t count)
{
    records.resize(count);

    for (uint16_t i = 0; i < count; ++i)
    {
        assign(records[i], &cRecords[i]);
    }
}

void assign(NLeaderboardRecordList& list, const sNLeaderboardRecordList* cList)
{
    list.prevCursor = cList->prevCursor;
    list.nextCursor = cList->nextCursor;
    assign(list.records, cList->records, cList->recordsCount);
    assign(list.ownerRecords, cList->ownerRecords, cList->ownerRecordsCount);
}

void assign(sNUserPresence& cPresence, const NUserPresence& presence)
{
    cPresence.userId = presence.userId.c_str();
    cPresence.sessionId = presence.sessionId.c_str();
    cPresence.username = presence.username.c_str();
    cPresence.persistence = presence.persistence;
    cPresence.status = presence.status.c_str();
}

void assign(NUserPresence& presence, const sNUserPresence* cPresence)
{
    presence.userId = cPresence->userId;
    presence.sessionId = cPresence->sessionId;
    presence.username = cPresence->username;
    presence.persistence = cPresence->persistence;
    presence.status = cPresence->status;
}

void assign(std::vector<NUserPresence>& presences, const sNUserPresence* cPresences, uint16_t presencesCount)
{
    presences.resize(presencesCount);

    for (uint16_t i = 0; i < presencesCount; ++i)
    {
        assign(presences[i], &cPresences[i]);
    }
}

void assign(NMatch& match, const sNMatch* cMatch)
{
    match.matchId = cMatch->matchId;
    match.authoritative = cMatch->authoritative;
    match.label = cMatch->label;
    match.size = cMatch->size;
    assign(match.self, &cMatch->self);
    assign(match.presences, cMatch->presences, cMatch->presencesCount);
}

void assign(NMatchList& matchList, const sNMatchList* cMatchList)
{
    matchList.matches.resize(cMatchList->matchesCount);

    for (uint16_t i = 0; i < cMatchList->matchesCount; ++i)
    {
        assign(matchList.matches[i], &cMatchList->matches[i]);
    }
}

void assign(NRpc& rpc, const sNRpc* cRpc)
{
    rpc.id = cRpc->id;
    rpc.payload = cRpc->payload;
    rpc.httpKey = cRpc->httpKey;
}

void assign(NReadStorageObjectId& objId, const sNReadStorageObjectId* cObjId)
{
    objId.collection = cObjId->collection;
    objId.key = cObjId->key;
    objId.userId = cObjId->userId;
}

void assign(NDeleteStorageObjectId& objId, const sNDeleteStorageObjectId* cObjId)
{
    objId.collection = cObjId->collection;
    objId.key = cObjId->key;
    objId.version = cObjId->version;
}

void assign(NStorageObject& object, const sNStorageObject* cObject)
{
    object.collection = cObject->collection;
    object.key = cObject->key;
    object.userId = cObject->userId;
    object.value = cObject->value;
    object.version = cObject->version;
    object.permissionRead = (NStoragePermissionRead)cObject->permissionRead;
    object.permissionWrite = (NStoragePermissionWrite)cObject->permissionWrite;
    object.createTime = cObject->createTime;
    object.updateTime = cObject->updateTime;
}

void assign(sNStorageObject* cObject, const NStorageObject& object)
{
    cObject->collection = object.collection.c_str();
    cObject->key = object.key.c_str();
    cObject->userId = object.userId.c_str();
    cObject->value = object.value.c_str();
    cObject->version = object.version.c_str();
    cObject->permissionRead = (eNStoragePermissionRead)object.permissionRead;
    cObject->permissionWrite = (eNStoragePermissionWrite)object.permissionWrite;
    cObject->createTime = object.createTime;
    cObject->updateTime = object.updateTime;
}

void assign(NStorageObjects& objects, const sNStorageObject* cObjects, uint16_t count)
{
    objects.resize(count);

    for (uint16_t i=0; i < count; ++i)
    {
        assign(objects[i], &cObjects[i]);
    }
}

void assign(sNReadStorageObjectId& cObjectId, const NReadStorageObjectId& objectId)
{
    cObjectId.collection = objectId.collection.c_str();
    cObjectId.key = objectId.key.c_str();
    cObjectId.userId = objectId.userId.c_str();
}

void assign(sNStorageObject*& cObjects, uint16_t& count, const NStorageObjects& objects)
{
    cObjects = nullptr;
    count = (uint16_t)objects.size();

    if (count > 0)
    {
        cObjects = new sNStorageObject[count];

        for (uint16_t i=0; i < count; ++i)
        {
            assign(&cObjects[i], objects[i]);
        }
    }
}

void assign(sNReadStorageObjectId*& objectIdsArray, uint16_t& count, const std::vector<NReadStorageObjectId>& objectIds)
{
    count = (uint16_t)objectIds.size();
    objectIdsArray = nullptr;

    if (count > 0)
    {
        objectIdsArray = new sNReadStorageObjectId[count];

        for (uint16_t i=0; i < count; ++i)
        {
            assign(objectIdsArray[i], objectIds[i]);
        }
    }
}

void assign(sNStorageObjectWrite* cObject, const NStorageObjectWrite& object)
{
    cObject->collection = object.collection.c_str();
    cObject->key = object.key.c_str();
    cObject->value = object.value.c_str();
    cObject->version = object.version.c_str();
    cObject->permissionRead = nullptr;
    cObject->permissionWrite = nullptr;

    if (object.permissionRead) cObject->permissionRead = (eNStoragePermissionRead*)&(object.permissionRead.value());
    if (object.permissionWrite) cObject->permissionWrite = (eNStoragePermissionWrite*) & (object.permissionWrite.value());
}

void assign(sNStorageObjectWrite*& objectArray, uint16_t& count, const std::vector<NStorageObjectWrite>& objects)
{
    count = (uint16_t)objects.size();
    objectArray = nullptr;

    if (count > 0)
    {
        objectArray = new sNStorageObjectWrite[count];

        for (uint16_t i = 0; i < count; ++i)
        {
            assign(&objectArray[i], objects[i]);
        }
    }
}

void assign(NStorageObjectAck& ack, const sNStorageObjectAck* cAck)
{
    ack.collection = cAck->collection;
    ack.key = cAck->key;
    ack.version = cAck->version;
    ack.userId = cAck->userId;
}

void assign(NStorageObjectAcks& acks, const sNStorageObjectAck* cAcks, uint16_t count)
{
    acks.resize(count);

    for (uint16_t i = 0; i < count; ++i)
    {
        assign(acks[i], &cAcks[i]);
    }
}

void assign(NStorageObjectList& objList, const sNStorageObjectList* cObjList)
{
    objList.cursor = cObjList->cursor;
    objList.objects.resize(cObjList->objectsCount);

    for (uint16_t i=0; i < cObjList->objectsCount; ++i)
    {
        assign(objList.objects[i], &cObjList->objects[i]);
    }
}

void assign(NTournamentRecordList& recordList, const sNTournamentRecordList* cRecordList)
{
    assign(recordList.records, cRecordList->records, cRecordList->recordsCount);
    assign(recordList.ownerRecords, cRecordList->ownerRecords, cRecordList->ownerRecordsCount);
    recordList.nextCursor = cRecordList->nextCursor;
    recordList.prevCursor = cRecordList->prevCursor;
}

void assign(NTournament& t, const sNTournament* cT)
{
    t.id = cT->id;
    t.title = cT->title;
    t.description = cT->description;
    t.category = cT->category;
    t.sortOrder = cT->sortOrder;
    t.size = cT->size;
    t.maxSize = cT->maxSize;
    t.maxNumScore = cT->maxNumScore;
    t.canEnter = cT->canEnter;
    t.createTime = cT->createTime;
    t.startTime = cT->startTime;
    t.endTime = cT->endTime;
    t.endActive = cT->endActive;
    t.nextReset = cT->nextReset;
    t.duration = cT->duration;
    t.startActive = cT->startActive;
    t.metadata = cT->metadata;
}

void assign(NTournamentList& list, const sNTournamentList* cList)
{
    list.cursor = cList->cursor;
    list.tournaments.resize(cList->tournamentsCount);

    for (uint16_t i=0; i < cList->tournamentsCount; ++i)
    {
        assign(list.tournaments[i], &cList->tournaments[i]);
    }
}

void assign(NNotification& n, const sNNotification* cN)
{
    n.id = cN->id;
    n.subject = cN->subject;
    n.content = cN->content;
    n.code = cN->code;
    n.senderId = cN->senderId;
    n.createTime = cN->createTime;
    n.persistent = cN->persistent;
}

void assign(NNotificationList& list, const sNNotificationList* cList)
{
    list.cacheableCursor = cList->cacheableCursor;
    list.notifications.resize(cList->notificationsCount);

    for (uint16_t i = 0; i < cList->notificationsCount; ++i)
    {
        assign(list.notifications[i], &cList->notifications[i]);
    }
}

void assign(NChannelMessage& msg, const sNChannelMessage* cMsg)
{
    msg.channelId = cMsg->channelId;
    msg.messageId = cMsg->messageId;
    msg.code = cMsg->code;
    msg.senderId = cMsg->senderId;
    msg.username = cMsg->username;
    msg.content = cMsg->content;
    msg.createTime = cMsg->createTime;
    msg.updateTime = cMsg->updateTime;
    msg.persistent = cMsg->persistent;
    msg.roomName = cMsg->roomName;
    msg.groupId = cMsg->groupId;
    msg.userIdOne = cMsg->userIdOne;
    msg.userIdTwo = cMsg->userIdTwo;
}

void assign(NChannelMessageList& list, const sNChannelMessageList* cList)
{
    list.messages.resize(cList->messagesCount);
    for (uint16_t i=0; i < cList->messagesCount; ++i)
    {
        assign(list.messages[i], &cList->messages[i]);
    }

    list.nextCursor = cList->nextCursor;
    list.prevCursor = cList->prevCursor;
}

void assign(NRtError& error, const ::sNRtError* cError)
{
    error.code = (RtErrorCode)cError->code;
    error.message = cError->message;
    assign(error.context, cError->context);
}

void assign(NChannel& channel, const ::sNChannel* cChannel)
{
    channel.id = cChannel->id;
    assign(channel.presences, cChannel->presences, cChannel->presencesCount);
    assign(channel.self, &cChannel->self);
    channel.roomName = cChannel->roomName;
    channel.groupId = cChannel->groupId;
    channel.userIdOne = cChannel->userIdOne;
    channel.userIdTwo = cChannel->userIdTwo;
}

void assign(NStatus& status, const ::sNStatus* cStatus)
{
    assign(status.presences, cStatus->presences, cStatus->presencesCount);
}

void assign(NChannelMessageAck& ack, const ::sNChannelMessageAck* cAck)
{
    ack.channelId = cAck->channelId;
    ack.messageId = cAck->messageId;
    ack.username = cAck->username;
    ack.code = cAck->code;
    ack.createTime = cAck->createTime;
    ack.updateTime = cAck->updateTime;
    ack.persistent = cAck->persistent;
    ack.roomName = cAck->roomName;
    ack.groupId = cAck->groupId;
    ack.userIdOne = cAck->userIdOne;
    ack.userIdTwo = cAck->userIdTwo;
}

void assign(NMatchmakerTicket& ticket, const sNMatchmakerTicket* cTicket)
{
    ticket.ticket = cTicket->ticket;
}

void assign(NRtClientDisconnectInfo& info, const sNRtClientDisconnectInfo* cInfo)
{
    info.code = cInfo->code;
    info.reason = cInfo->reason;
    info.remote = cInfo->remote;
}

void assign(NChannelPresenceEvent& presence, const sNChannelPresenceEvent* cPresence)
{
    presence.channelId = cPresence->channelId;
    assign(presence.joins, cPresence->joins, cPresence->joinsCount);
    assign(presence.leaves, cPresence->leaves, cPresence->leavesCount);
    presence.roomName = cPresence->roomName;
    presence.groupId = cPresence->groupId;
    presence.userIdOne = cPresence->userIdOne;
    presence.userIdTwo = cPresence->userIdTwo;
}

void assign(NMatchmakerUser& user, const sNMatchmakerUser* cUser)
{
    assign(user.presence, &cUser->presence);
    assign(user.stringProperties, cUser->stringProperties);
    assign(user.numericProperties, cUser->numericProperties);
}

void assign(std::vector<NMatchmakerUser>& users, const sNMatchmakerUser* cUsers, uint16_t count)
{
    users.resize(count);

    for (uint16_t i = 0; i < count; ++i)
    {
        assign(users[i], &cUsers[i]);
    }
}

void assign(NMatchmakerMatched& matched, const sNMatchmakerMatched* cMatched)
{
    matched.ticket = cMatched->ticket;
    matched.matchId = cMatched->matchId;
    matched.token = cMatched->token;
    assign(matched.users, cMatched->users, cMatched->usersCount);
    assign(matched.self, &cMatched->self);
}

void assign(NMatchData& matchData, const sNMatchData* cMatchData)
{
    matchData.matchId = cMatchData->matchId;
    assign(matchData.presence, &cMatchData->presence);
    matchData.opCode = cMatchData->opCode;
    assign(matchData.data, &cMatchData->data);
}

void assign(NMatchPresenceEvent& matchPresence, const sNMatchPresenceEvent* cMatchPresence)
{
    matchPresence.matchId = cMatchPresence->matchId;
    assign(matchPresence.joins, cMatchPresence->joins, cMatchPresence->joinsCount);
    assign(matchPresence.leaves, cMatchPresence->leaves, cMatchPresence->leavesCount);
}

void assign(NStatusPresenceEvent& presence, const sNStatusPresenceEvent* cPresence)
{
    assign(presence.joins, cPresence->joins, cPresence->joinsCount);
    assign(presence.leaves, cPresence->leaves, cPresence->leavesCount);
}

void assign(NStream& stream, const sNStream* cStream)
{
    stream.mode = cStream->mode;
    stream.subject = cStream->subject;
    stream.subcontext = cStream->subcontext;
    stream.label = cStream->label;
}

void assign(NStreamPresenceEvent& presence, const sNStreamPresenceEvent* cPresence)
{
    assign(presence.stream, &cPresence->stream);
    assign(presence.joins, cPresence->joins, cPresence->joinsCount);
    assign(presence.leaves, cPresence->leaves, cPresence->leavesCount);
}

void assign(NStreamData& data, const sNStreamData* cData)
{
    assign(data.stream, &cData->stream);
    assign(data.sender, &cData->sender);
    data.data = cData->data;
}

void NReadStorageObjectId_free(sNReadStorageObjectId* objectIdsArray)
{
    delete[] objectIdsArray;
}

void NStorageObjectWrite_free(sNStorageObjectWrite* objectArray)
{
    delete[] objectArray;
}

NAKAMA_NAMESPACE_END
