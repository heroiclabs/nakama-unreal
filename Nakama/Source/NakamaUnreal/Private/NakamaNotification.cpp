#include "NakamaNotification.h"

#include "NakamaUtils.h"
#include "nakama-cpp/data/NNotification.h"
#include "nakama-cpp/data/NNotificationList.h"


FNakamaNotification::FNakamaNotification(const NNotification& NakamaNativeNotification)
	: Id(FNakamaUtils::StdStringToUEString(NakamaNativeNotification.id))
	, Subject(FNakamaUtils::StdStringToUEString(NakamaNativeNotification.subject))
	, Content(FNakamaUtils::StdStringToUEString(NakamaNativeNotification.content))
	, Code(NakamaNativeNotification.code)
	, SenderId(FNakamaUtils::StdStringToUEString(NakamaNativeNotification.senderId))
	, CreateTime(FDateTime::FromUnixTimestamp(NakamaNativeNotification.createTime / 1000))
	, Persistent(NakamaNativeNotification.persistent)
{
	
}

FNakamaNotification::FNakamaNotification()
{
	
}

FNakamaNotificationList::FNakamaNotificationList(const NNotificationList& NakamaNativeNotificationList)
	: Notifications()
	, CacheableCursor(FNakamaUtils::StdStringToUEString(NakamaNativeNotificationList.cacheableCursor))
{
	for (auto &notification : NakamaNativeNotificationList.notifications)
	{
		Notifications.Add(notification);
	}
}

FNakamaNotificationList::FNakamaNotificationList()
{
	
}
	