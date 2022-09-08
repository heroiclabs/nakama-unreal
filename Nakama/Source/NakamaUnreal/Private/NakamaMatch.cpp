#include "NakamaMatch.h"
#include "nakama-cpp/Nakama.h"
#include "NakamaUtils.h"

FNakamaMatch::FNakamaMatch(const NMatch& NativeMatch)
	: MatchId(FNakamaUtils::StdStringToUEString(NativeMatch.matchId))
	, Authoritative(NativeMatch.authoritative)
	, Label(FNakamaUtils::StdStringToUEString(NativeMatch.label))
	, Size(NativeMatch.size)
	, Me(NativeMatch.self)
{
	for (const auto& NativeUserPresence : NativeMatch.presences)
	{
		Pressences.Add(FNakamaUserPresence(NativeUserPresence));
	}
}

FNakamaMatchData::FNakamaMatchData(const NMatchData& NativeMatchData)
	: MatchId(FNakamaUtils::StdStringToUEString(NativeMatchData.matchId))
	, Presence(NativeMatchData.presence)
	, OpCode(NativeMatchData.opCode)
	, Data(FNakamaUtils::StdStringToUEString(NativeMatchData.data))
{
	
}

FNakamaMatchData::FNakamaMatchData(): OpCode(0)
{
}

FNakamaMatchList::FNakamaMatchList(const NMatchList& NakamaNativeMatchList)
	: Matches()
{
	if(NakamaNativeMatchList.matches.size() > 0)
	{
		for(auto &match : NakamaNativeMatchList.matches)
		{
			Matches.Add(match); // Automatic Convert
		}
	}
}

FNakamaMatchList::FNakamaMatchList()
{
	
}
