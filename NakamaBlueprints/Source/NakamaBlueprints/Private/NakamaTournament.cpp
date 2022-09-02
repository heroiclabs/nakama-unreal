#include "NakamaTournament.h"

#include "NakamaUtils.h"

FNakamaTournament::FNakamaTournament(const NTournament& NakamaNativeTournament)
	: Id(FNakamaUtils::StdStringToUEString(NakamaNativeTournament.id))
	, Title(FNakamaUtils::StdStringToUEString(NakamaNativeTournament.title))
	, Description(FNakamaUtils::StdStringToUEString(NakamaNativeTournament.description))
	, Category(NakamaNativeTournament.category)
	, SortOrder(NakamaNativeTournament.sortOrder)
	, Size(NakamaNativeTournament.size)
	, MaxSize(NakamaNativeTournament.maxSize)
	, MaxNumScore(NakamaNativeTournament.maxNumScore)
	, CanEnter(NakamaNativeTournament.canEnter)
	, CreateTime(FDateTime::FromUnixTimestamp(NakamaNativeTournament.createTime / 1000))
	, StartTime(FDateTime::FromUnixTimestamp(NakamaNativeTournament.startTime / 1000))
	, EndTime(FDateTime::FromUnixTimestamp(NakamaNativeTournament.endTime / 1000))
	, EndActive(NakamaNativeTournament.endActive)
	, NextReset(NakamaNativeTournament.nextReset)
	, Duration(NakamaNativeTournament.duration)
	, StartActive(NakamaNativeTournament.startActive)
	, Metadata(FNakamaUtils::StdStringToUEString(NakamaNativeTournament.metadata))
{
	
}

FNakamaTournament::FNakamaTournament()
{
	
}

FNakamaTournamentRecordList::FNakamaTournamentRecordList(const NTournamentRecordList& NakamaNativeTournamentRecordList)
	: Records()
	, OwnerRecords()
	, NextCursor(FNakamaUtils::StdStringToUEString(NakamaNativeTournamentRecordList.nextCursor))
	, PrevCursor(FNakamaUtils::StdStringToUEString(NakamaNativeTournamentRecordList.prevCursor))
{
	if(NakamaNativeTournamentRecordList.records.size() > 0 )
	{
		for (auto& record : NakamaNativeTournamentRecordList.records)
		{
			Records.Add(record);
		}
	}

	if(NakamaNativeTournamentRecordList.ownerRecords.size() > 0 )
	{
		for (auto& ownerRecord : NakamaNativeTournamentRecordList.records)
		{
			OwnerRecords.Add(ownerRecord);
		}
	}
}

FNakamaTournamentRecordList::FNakamaTournamentRecordList()
{
	
}

FNakamaTournamentList::FNakamaTournamentList(const NTournamentList& NakamaNativeTournamentList)
	: Tournaments()
	, Cursor(FNakamaUtils::StdStringToUEString(NakamaNativeTournamentList.cursor))
{
	for (auto& tournament : NakamaNativeTournamentList.tournaments)
	{
		Tournaments.Add(tournament);
	}
}

FNakamaTournamentList::FNakamaTournamentList()
{
	
}
