#include "NakamaFriend.h"

#include "NakamaUtils.h"
#include "nakama-cpp/data/NFriend.h"
#include "nakama-cpp/data/NFriendList.h"

FNakamaFriend::FNakamaFriend(const NFriend& NakamaNativeFriend)
	: NakamaUser(NakamaNativeFriend.user)
	, UserState(static_cast<ENakamaFriendState>(NakamaNativeFriend.state))
	, UpdateTime(FDateTime::FromUnixTimestamp(NakamaNativeFriend.updateTime / 1000))
{
	
}

FNakamaFriend::FNakamaFriend(): UserState(ENakamaFriendState::FRIEND), UpdateTime(FDateTime::MinValue())
{
	
}

FNakamaFriendList::FNakamaFriendList(const NFriendList& NakamaNativeFriendList)
	: NakamaUsers()
	, Cursor(FNakamaUtils::StdStringToUEString(NakamaNativeFriendList.cursor))
{
	for (auto& Friend : NakamaNativeFriendList.friends)
	{
		NakamaUsers.Add(Friend);
	}
}

FNakamaFriendList::FNakamaFriendList()
{
	
}
