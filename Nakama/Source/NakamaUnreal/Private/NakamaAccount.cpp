#include "NakamaAccount.h"
#include "NakamaUtils.h"

FNakamaAccount::FNakamaAccount(const NAccount& NakamaNativeAccount)
	: User(NakamaNativeAccount.user)
	, Wallet(FNakamaUtils::StdStringToUEString(NakamaNativeAccount.wallet))
	, Email(FNakamaUtils::StdStringToUEString(NakamaNativeAccount.email))
	, CustomId(FNakamaUtils::StdStringToUEString(NakamaNativeAccount.customId))
	, VerifyTime(FDateTime::FromUnixTimestamp(NakamaNativeAccount.verifyTime / 1000))
	, DisableTime(FDateTime::FromUnixTimestamp(NakamaNativeAccount.verifyTime / 1000))

{
	for (const auto& NativeAccountDevice : NakamaNativeAccount.devices)
	{
		Devices.Add(FNakamaAccountDevice(NativeAccountDevice));
	}
}

FNakamaAccount::FNakamaAccount(): VerifyTime(FDateTime::MinValue()), DisableTime(FDateTime::MinValue())
{
	
}