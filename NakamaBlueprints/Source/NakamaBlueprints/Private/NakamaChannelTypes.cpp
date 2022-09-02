#include "NakamaChannelTypes.h"

#include "NakamaUtils.h"
#include "nakama-cpp/data/NChannelMessage.h"
#include "nakama-cpp/realtime/rtdata/NChannelPresenceEvent.h"

FNakamaChannelMessage::FNakamaChannelMessage(const NChannelMessage& NakamaNativeChannelMessage)
: ChannelId(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessage.channelId))
, MessageId(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessage.messageId))
, code(NakamaNativeChannelMessage.code)
, SenderId(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessage.senderId))
, Username(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessage.username))
, Content(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessage.content))
, CreateTime(FDateTime::FromUnixTimestamp(NakamaNativeChannelMessage.createTime / 1000))
, UpdateTime(FDateTime::FromUnixTimestamp(NakamaNativeChannelMessage.updateTime / 1000))
, Persistent(NakamaNativeChannelMessage.persistent)
, RoomName(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessage.roomName))
, GroupId(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessage.groupId))
, UserIdOne(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessage.userIdOne))
, UserIdTwo(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessage.userIdTwo))
{
	
}

FNakamaChannelMessage::FNakamaChannelMessage()
{
	
}

FNakamaChannelMessageAck::FNakamaChannelMessageAck(const NChannelMessageAck& NakamaNativeChannelMessageAck)
: ChannelId(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessageAck.channelId))
, MessageId(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessageAck.messageId))
, Username(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessageAck.username))
, code(NakamaNativeChannelMessageAck.code)
, CreateTime(FDateTime::FromUnixTimestamp(NakamaNativeChannelMessageAck.createTime / 1000))
, UpdateTime(FDateTime::FromUnixTimestamp(NakamaNativeChannelMessageAck.updateTime / 1000))
, Persistent(NakamaNativeChannelMessageAck.persistent)
, RoomName(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessageAck.roomName))
, GroupId(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessageAck.groupId))
, UserIdOne(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessageAck.userIdOne))
, UserIdTwo(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessageAck.userIdTwo))
{
	
}

FNakamaChannelMessageAck::FNakamaChannelMessageAck()
{
}

FNakamaChannelMessageList::FNakamaChannelMessageList(const NChannelMessageList& NakamaNativeChannelMessageList)
	: Messages()
	, NextCursor(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessageList.nextCursor))
	, PrevCursor(FNakamaUtils::StdStringToUEString(NakamaNativeChannelMessageList.prevCursor))
{
	if(NakamaNativeChannelMessageList.messages.size() > 0)
	{
		for(auto &Message : NakamaNativeChannelMessageList.messages)
		{
			Messages.Add(Message); // Converts
		}
	}
}

FNakamaChannelMessageList::FNakamaChannelMessageList()
{
}


FNakamaChannelPresenceEvent::FNakamaChannelPresenceEvent(const NChannelPresenceEvent& NakamaNativeChannelPresenceEvent)
	: ChannelId(FNakamaUtils::StdStringToUEString(NakamaNativeChannelPresenceEvent.channelId))
	, Joins(FNakamaUtils::ConvertUserPresences(NakamaNativeChannelPresenceEvent.joins))
	, Leaves(FNakamaUtils::ConvertUserPresences(NakamaNativeChannelPresenceEvent.leaves))
	, RoomName(FNakamaUtils::StdStringToUEString(NakamaNativeChannelPresenceEvent.roomName))
	, GroupId(FNakamaUtils::StdStringToUEString(NakamaNativeChannelPresenceEvent.groupId))
	, UserIdOne(FNakamaUtils::StdStringToUEString(NakamaNativeChannelPresenceEvent.userIdOne))
	, UserIdTwo(FNakamaUtils::StdStringToUEString(NakamaNativeChannelPresenceEvent.userIdTwo))
{
	
}

FNakamaChannelPresenceEvent::FNakamaChannelPresenceEvent()
{
	
}
