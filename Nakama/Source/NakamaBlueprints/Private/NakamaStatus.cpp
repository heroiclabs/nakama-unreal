#include "NakamaStatus.h"

#include "NakamaUtils.h"
#include "NakamaAccount.h"

FNakamaStatus::FNakamaStatus(const NStatus& NakamaNativeStatus)
	: Presences(FNakamaUtils::ConvertUserPresences(NakamaNativeStatus.presences))
{
	
}

FNakamaStatus::FNakamaStatus()
{
	
}

FNakamaStatusPresenceEvent::FNakamaStatusPresenceEvent(const NStatusPresenceEvent& NakamaNativeStatusPresenceEvent)
	: Joins(FNakamaUtils::ConvertUserPresences(NakamaNativeStatusPresenceEvent.joins))
	, Leaves(FNakamaUtils::ConvertUserPresences(NakamaNativeStatusPresenceEvent.leaves))
{
	
}

FNakamaStatusPresenceEvent::FNakamaStatusPresenceEvent()
{
	
}
