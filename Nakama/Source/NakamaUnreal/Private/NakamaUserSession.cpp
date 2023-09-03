#include "NakamaUserSession.h"

FNakamaUserSession::FNakamaUserSession(): IsCreated(false), CreateTime(FDateTime::MinValue()), ExpireTime(FDateTime::MinValue()), IsExpired(false), IsRefreshExpired(false)
{
	
}