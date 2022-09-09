#include "NakamaAccountDevice.h"

#include "NakamaUtils.h"

FNakamaAccountDevice::FNakamaAccountDevice(const NAccountDevice& NakamaNativeAccountDevice)
	: Id(FNakamaUtils::StdStringToUEString(NakamaNativeAccountDevice.id))
	, Vars(FNakamaUtils::NStringMapToTMap(NakamaNativeAccountDevice.vars))
{

}

FNakamaAccountDevice::FNakamaAccountDevice()
{
	
}
