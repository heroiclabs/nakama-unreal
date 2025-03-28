#include "SatoriUserSession.h"

FSatoriUserSession::FSatoriUserSession(): IsCreated(false), CreateTime(FDateTime::MinValue()), ExpireTime(FDateTime::MinValue()), IsExpired(false), IsRefreshExpired(false)
{
	
}