#include "NakamaParty.h"
#include "NakamaUtils.h"
#include "NakamaParty.h"
#include "nakama-cpp/Nakama.h"

FNakamaParty::FNakamaParty(const NParty& NakamaNativeParty)
: Id(FNakamaUtils::StdStringToUEString(NakamaNativeParty.id))
, Open(NakamaNativeParty.open)
, MaxSize(NakamaNativeParty.maxSize)
, Me(NakamaNativeParty.self)
, Leader(NakamaNativeParty.leader)
, Presences()
{
	if(NakamaNativeParty.presences.size() > 0 )
	{
		for(auto &presence : NakamaNativeParty.presences)
		{
			Presences.Add(presence);
		}
	}
}

FNakamaParty::FNakamaParty(): Open(false), MaxSize(0)
{
}

FNakamaPartyJoinRequest::FNakamaPartyJoinRequest(const NPartyJoinRequest& NakamaNativePartyJoinRequest)
	: PartyId(FNakamaUtils::StdStringToUEString(NakamaNativePartyJoinRequest.partyId))
	, Presences(FNakamaUtils::ConvertUserPresences(NakamaNativePartyJoinRequest.presences))
{
	
}

FNakamaPartyJoinRequest::FNakamaPartyJoinRequest()
{
	
}

FNakamaPartyMatchmakerTicket::FNakamaPartyMatchmakerTicket(const NPartyMatchmakerTicket NakamaNativePartyMatchmakerTicket)
	: PartyId(FNakamaUtils::StdStringToUEString(NakamaNativePartyMatchmakerTicket.partyId))
	, Ticket(FNakamaUtils::StdStringToUEString(NakamaNativePartyMatchmakerTicket.ticket))
{
	
}

FNakamaPartyMatchmakerTicket::FNakamaPartyMatchmakerTicket()
{
	
}


FNakamaPartyClose::FNakamaPartyClose(const NPartyClose& NakamaNativePartyClose)
	: Id (FNakamaUtils::StdStringToUEString(NakamaNativePartyClose.id))
{
	
}

FNakamaPartyClose::FNakamaPartyClose()
{
	
}

FNakamaPartyData::FNakamaPartyData(const NPartyData& NakamaNativePartyData)
	: PartyId(FNakamaUtils::StdStringToUEString(NakamaNativePartyData.partyId))
	, Presence(NakamaNativePartyData.presence)
	, OpCode(NakamaNativePartyData.opCode)
	, Data(FNakamaUtils::StdStringToUEString(NakamaNativePartyData.data))
{
	
}

FNakamaPartyData::FNakamaPartyData(): OpCode(0)
{
}

FNakamaPartyLeader::FNakamaPartyLeader(const NPartyLeader& NakamaNativePartyLeader)
	: PartyId(FNakamaUtils::StdStringToUEString(NakamaNativePartyLeader.partyId))
	, Presence(NakamaNativePartyLeader.presence)
{
	
}

FNakamaPartyLeader::FNakamaPartyLeader()
{
	
}

FNakamaPartyPresenceEvent::FNakamaPartyPresenceEvent(const NPartyPresenceEvent& NakamaNativePartyPresenceEvent)
	: PartyId(FNakamaUtils::StdStringToUEString(NakamaNativePartyPresenceEvent.partyId))
	, Joins(FNakamaUtils::ConvertUserPresences(NakamaNativePartyPresenceEvent.joins))
	, Leaves(FNakamaUtils::ConvertUserPresences(NakamaNativePartyPresenceEvent.leaves))
{
	
}

FNakamaPartyPresenceEvent::FNakamaPartyPresenceEvent()
{
	
}
