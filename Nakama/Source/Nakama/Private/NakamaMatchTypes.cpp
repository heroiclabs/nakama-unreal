#include "NakamaMatchTypes.h"

#include "NakamaUtils.h"
#include "nakama-cpp/realtime/rtdata/NMatchmakerMatched.h"
#include "nakama-cpp/realtime/rtdata/NMatchPresenceEvent.h"

FNakamaMatchmakerUser::FNakamaMatchmakerUser()
{
	
}

FNakamaMatchmakerUser::FNakamaMatchmakerUser(const NMatchmakerUser NakamaNativeMatchmakerUser)
	: Presence(NakamaNativeMatchmakerUser.presence)
	, StringProperties(FNakamaUtils::NStringMapToTMap(NakamaNativeMatchmakerUser.stringProperties))
	, NumericProperties(FNakamaUtils::NNumericMapToTMap(NakamaNativeMatchmakerUser.numericProperties))
{
	
}

FNakamaMatchmakerMatched::FNakamaMatchmakerMatched()
{
	
}

FNakamaMatchmakerMatched::FNakamaMatchmakerMatched(const NMatchmakerMatched& NakamaNativeMatchmakerMatched)
	: Ticket(FNakamaUtils::StdStringToUEString(NakamaNativeMatchmakerMatched.ticket))
	, MatchId(FNakamaUtils::StdStringToUEString(NakamaNativeMatchmakerMatched.matchId))
	, Token(FNakamaUtils::StdStringToUEString(NakamaNativeMatchmakerMatched.token))
	, Users(FNakamaUtils::ConvertMatchmakerUsers(NakamaNativeMatchmakerMatched.users))
	, Me(NakamaNativeMatchmakerMatched.self)
{
	
}


FNakamaMatchPresenceEvent::FNakamaMatchPresenceEvent(const NMatchPresenceEvent& NakamaNativeMatchPresenceEvent)
	: MatchId(FNakamaUtils::StdStringToUEString(NakamaNativeMatchPresenceEvent.matchId))
	, Joins(FNakamaUtils::ConvertUserPresences(NakamaNativeMatchPresenceEvent.joins))
	, Leaves(FNakamaUtils::ConvertUserPresences(NakamaNativeMatchPresenceEvent.leaves))
{
	
}

FNakamaMatchPresenceEvent::FNakamaMatchPresenceEvent()
{
	
}

FNakamaMatchmakerTicket::FNakamaMatchmakerTicket(const NMatchmakerTicket& NakamaNativeMatchmakerTicket)
	: TicketId(FNakamaUtils::StdStringToUEString(NakamaNativeMatchmakerTicket.ticket))
{
	
}

FNakamaMatchmakerTicket::FNakamaMatchmakerTicket()
{
	
}
