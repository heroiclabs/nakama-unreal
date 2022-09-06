#include "NakamaPresence.h"

#include "NakamaUtils.h"

FNakamaUserPresence::FNakamaUserPresence(const NUserPresence& NakamaNativeUserPresence)
	: UserID(FNakamaUtils::StdStringToUEString(NakamaNativeUserPresence.userId))
	, SessionID(FNakamaUtils::StdStringToUEString(NakamaNativeUserPresence.sessionId))
	, Username(FNakamaUtils::StdStringToUEString(NakamaNativeUserPresence.username))
	, Persistence(NakamaNativeUserPresence.persistence)
	, Status (FNakamaUtils::StdStringToUEString(NakamaNativeUserPresence.status))
{
	
}

FNakamaUserPresence::FNakamaUserPresence()
{
	
}