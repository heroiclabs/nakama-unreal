#include "NakamaGroup.h"

#include "NakamaUtils.h"
#include "nakama-cpp/Nakama.h"

FNakamaGroup::FNakamaGroup(const NGroup& NakamaNativeGroup)
	: Id(FNakamaUtils::StdStringToUEString(NakamaNativeGroup.id))
	, CreatorId(FNakamaUtils::StdStringToUEString(NakamaNativeGroup.creatorId))
	, Name(FNakamaUtils::StdStringToUEString(NakamaNativeGroup.name))
	, Description(FNakamaUtils::StdStringToUEString(NakamaNativeGroup.description))
	, Language(FNakamaUtils::StdStringToUEString(NakamaNativeGroup.lang))
	, MetaData(FNakamaUtils::StdStringToUEString(NakamaNativeGroup.metadata))
	, AvatarUrl(FNakamaUtils::StdStringToUEString(NakamaNativeGroup.avatarUrl))
	, open(NakamaNativeGroup.open)
	, EdgeCount(NakamaNativeGroup.edgeCount)
	, MaxCount(NakamaNativeGroup.maxCount)
	, CreateTime(FDateTime::FromUnixTimestamp(NakamaNativeGroup.createTime / 1000))
	, UpdateTime(FDateTime::FromUnixTimestamp(NakamaNativeGroup.updateTime / 1000))
{
	
}

FNakamaGroupUser::FNakamaGroupUser(const NGroupUser& NakamaNativeGroupUser)
	: User(NakamaNativeGroupUser.user)
	, State(static_cast<ENakamaGroupState>(NakamaNativeGroupUser.state))
{
	
}

FNakamaGroupUser::FNakamaGroupUser(): State()
{
}

FNakamaGroupUsersList::FNakamaGroupUsersList(const NGroupUserList& NakamaNativeGroupUsersList)
	: GroupUsers()
	, Cursor(FNakamaUtils::StdStringToUEString(NakamaNativeGroupUsersList.cursor))
{
	if(NakamaNativeGroupUsersList.groupUsers.size() > 0)
	{
		for (auto & GroupUser : NakamaNativeGroupUsersList.groupUsers)
		{
			FNakamaGroupUser User = GroupUser;
			GroupUsers.Add(GroupUser); // Auto Convert
		}
	}
	
}

FNakamaGroupList::FNakamaGroupList(const NGroupList& NakamaNativeGroupList)
	: Groups()
	, Cursor(FNakamaUtils::StdStringToUEString(NakamaNativeGroupList.cursor))
{
	for (auto &group : NakamaNativeGroupList.groups)
	{
		Groups.Add(group);
	}
}

FNakamaUserGroup::FNakamaUserGroup(const NUserGroup& NakamaNativeUserGroup)
	: Group(NakamaNativeUserGroup.group)
	, State(static_cast<ENakamaGroupState>(NakamaNativeUserGroup.state))
{
	
}

FNakamaUserGroup::FNakamaUserGroup(): State()
{
	
}

FNakamaUserGroupList::FNakamaUserGroupList(const NUserGroupList& NakamaNativeUserGroupList)
	: UserGroups()
	, Cursor(FNakamaUtils::StdStringToUEString(NakamaNativeUserGroupList.cursor))
{
	for (auto & group : NakamaNativeUserGroupList.userGroups)
	{
		UserGroups.Add(group); // Automatic Convert
	}
}

FNakamaUserGroupList::FNakamaUserGroupList()
{
	
}
