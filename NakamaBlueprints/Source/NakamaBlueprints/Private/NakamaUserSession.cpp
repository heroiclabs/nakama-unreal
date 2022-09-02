#include "NakamaUserSession.h"

#include "NakamaUser.h"

#include "NakamaUtils.h"
#include "nakama-cpp/Nakama.h"
#include "nakama-cpp/NSessionInterface.h"

FNakamaUserSession::FNakamaUserSession(const NSessionPtr& NakamaNativeSession)
	: AuthToken(FNakamaUtils::StdStringToUEString(NakamaNativeSession->getAuthToken()))
	, RefreshToken(FNakamaUtils::StdStringToUEString(NakamaNativeSession->getRefreshToken()))
	, IsCreated(NakamaNativeSession->isCreated())
	, Username(FNakamaUtils::StdStringToUEString(NakamaNativeSession->getUsername()))
	, UserId(FNakamaUtils::StdStringToUEString(NakamaNativeSession->getUserId()))
	, CreateTime(FDateTime::FromUnixTimestamp(NakamaNativeSession->getCreateTime() / 1000))
	, ExpireTime(FDateTime::FromUnixTimestamp(NakamaNativeSession->getExpireTime() / 1000))
	, IsExpired(NakamaNativeSession->isExpired()) // Check against time?
	, IsRefreshExpired(NakamaNativeSession->isRefreshExpired()) // Check against time?
	, Variables(FNakamaUtils::NStringMapToTMap(NakamaNativeSession->getVariables()))
{
	
}

FNakamaUserSession::FNakamaUserSession(): IsCreated(false), CreateTime(FDateTime::MinValue()), ExpireTime(FDateTime::MinValue()), IsExpired(false), IsRefreshExpired(false)
{
	
}