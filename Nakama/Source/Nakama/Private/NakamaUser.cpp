
#include "NakamaUser.h"

#include "NakamaUtils.h"
#include "nakama-cpp/Nakama.h"

FNakamaUser::FNakamaUser(const NUser& NakamaNativeUser)
	: Id(FNakamaUtils::StdStringToUEString(NakamaNativeUser.id))
	, Username(FNakamaUtils::StdStringToUEString(NakamaNativeUser.username))
	, DisplayName(FNakamaUtils::StdStringToUEString(NakamaNativeUser.displayName))
	, AvatarUrl(FNakamaUtils::StdStringToUEString(NakamaNativeUser.avatarUrl))
	, Language(FNakamaUtils::StdStringToUEString(NakamaNativeUser.lang))
	, Location(FNakamaUtils::StdStringToUEString(NakamaNativeUser.location))
	, TimeZone(FNakamaUtils::StdStringToUEString(NakamaNativeUser.timeZone))
	, MetaData(FNakamaUtils::StdStringToUEString(NakamaNativeUser.metadata))
	, FacebookId(FNakamaUtils::StdStringToUEString(NakamaNativeUser.facebookId))
	, GoogleId(FNakamaUtils::StdStringToUEString(NakamaNativeUser.googleId))
	, GameCenterId(FNakamaUtils::StdStringToUEString(NakamaNativeUser.gameCenterId))
	, AppleId(FNakamaUtils::StdStringToUEString(NakamaNativeUser.appleId))
	, SteamId(FNakamaUtils::StdStringToUEString(NakamaNativeUser.steamId))
	, Online(NakamaNativeUser.online)
	, EdgeCount(NakamaNativeUser.edgeCount)
	, CreatedAt(FDateTime::FromUnixTimestamp(NakamaNativeUser.createdAt / 1000))
	, updatedAt(FDateTime::FromUnixTimestamp(NakamaNativeUser.updatedAt / 1000))
{
	
}
