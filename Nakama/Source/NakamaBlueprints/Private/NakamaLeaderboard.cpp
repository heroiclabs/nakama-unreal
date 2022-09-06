#include "NakamaLeaderboard.h"

#include "NakamaUtils.h"

FNakamaLeaderboardRecord::FNakamaLeaderboardRecord(const NLeaderboardRecord& NakamaNativeLeaderboardRecord)
	: LeaderboardId(FNakamaUtils::StdStringToUEString(NakamaNativeLeaderboardRecord.leaderboardId))
	, OwnerId(FNakamaUtils::StdStringToUEString(NakamaNativeLeaderboardRecord.ownerId))
	, Username(FNakamaUtils::StdStringToUEString(NakamaNativeLeaderboardRecord.username))
	, Score(NakamaNativeLeaderboardRecord.score)
	, SubScore(NakamaNativeLeaderboardRecord.subscore)
	, NumScore(NakamaNativeLeaderboardRecord.numScore)
	, Metadata(FNakamaUtils::StdStringToUEString(NakamaNativeLeaderboardRecord.metadata))
	, CreateTime(FDateTime::FromUnixTimestamp(NakamaNativeLeaderboardRecord.createTime / 1000))
	, UpdateTime(FDateTime::FromUnixTimestamp(NakamaNativeLeaderboardRecord.updateTime / 1000))
	, ExpiryTime(FDateTime::FromUnixTimestamp(NakamaNativeLeaderboardRecord.expiryTime / 1000))
	, Rank(NakamaNativeLeaderboardRecord.rank)
{
	
}

FNakamaLeaderboardRecord::FNakamaLeaderboardRecord()
{
	
}

FNakamaLeaderboardRecordList::FNakamaLeaderboardRecordList(const NLeaderboardRecordList& NakamaNativeLeaderboardRecordList)
	: Records()
	, OwnerRecords()
	, NextCursor(FNakamaUtils::StdStringToUEString(NakamaNativeLeaderboardRecordList.nextCursor))
	, PrevCursor(FNakamaUtils::StdStringToUEString(NakamaNativeLeaderboardRecordList.prevCursor))
{
	if(NakamaNativeLeaderboardRecordList.records.size() > 0 )
	{
		for (auto& record : NakamaNativeLeaderboardRecordList.records)
		{
			Records.Add(record);
		}
	}

	if(NakamaNativeLeaderboardRecordList.ownerRecords.size() > 0 )
	{
		for (auto& ownerRecord : NakamaNativeLeaderboardRecordList.records)
		{
			OwnerRecords.Add(ownerRecord);
		}
	}
	
}

FNakamaLeaderboardRecordList::FNakamaLeaderboardRecordList()
{
	
}
