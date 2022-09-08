#include "NakamaChat.h"

#include "NakamaUtils.h"

FNakamaChannel::FNakamaChannel(const NChannel& NakamaNativeChannel)
	: Id(FNakamaUtils::StdStringToUEString(NakamaNativeChannel.id))
	, Presences(FNakamaUtils::ConvertUserPresences(NakamaNativeChannel.presences))
	, Me(NakamaNativeChannel.self)
	, RoomName(FNakamaUtils::StdStringToUEString(NakamaNativeChannel.roomName))
	, GroupId(FNakamaUtils::StdStringToUEString(NakamaNativeChannel.groupId))
	, UserIdOne(FNakamaUtils::StdStringToUEString(NakamaNativeChannel.userIdOne))
	, UserIdTwo(FNakamaUtils::StdStringToUEString(NakamaNativeChannel.userIdTwo))
{
	
}

FNakamaChannel::FNakamaChannel()
{
	
}
