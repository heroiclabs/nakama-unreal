#include "NakamaRPC.h"

#include "NakamaUtils.h"

FNakamaRPC::FNakamaRPC(const NRpc& NakamaNativeRpc)
	: Id(FNakamaUtils::StdStringToUEString(NakamaNativeRpc.id))
	, Payload(FNakamaUtils::StdStringToUEString(NakamaNativeRpc.payload))
	, HttpKey(FNakamaUtils::StdStringToUEString(NakamaNativeRpc.httpKey))
{
	
}

FNakamaRPC::FNakamaRPC()
{
	
}
