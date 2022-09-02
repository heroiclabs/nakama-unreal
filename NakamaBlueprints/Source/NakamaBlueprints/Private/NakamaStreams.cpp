#include "NakamaStreams.h"

#include "NakamaUtils.h"


FNakamaStream::FNakamaStream(const NStream& NakamaNativeStream)
	: Mode(NakamaNativeStream.mode)
	, Subject(FNakamaUtils::StdStringToUEString(NakamaNativeStream.subject))
	, SubContext(FNakamaUtils::StdStringToUEString(NakamaNativeStream.subcontext))
	, Label(FNakamaUtils::StdStringToUEString(NakamaNativeStream.label))
{
	
}

FNakamaStream::FNakamaStream()
{
	
}

FNakamaStreamData::FNakamaStreamData(const NStreamData& NakamaNativeStreamData)
	: Stream(NakamaNativeStreamData.stream)
	, Sender(NakamaNativeStreamData.sender)
	, Data(FNakamaUtils::StdStringToUEString(NakamaNativeStreamData.data))
{
	
}

FNakamaStreamData::FNakamaStreamData()
{
	
}

FNakamaStreamPresenceEvent::FNakamaStreamPresenceEvent(const NStreamPresenceEvent NakamaNativeStreamData)
	: Stream(NakamaNativeStreamData.stream)
	, Joins(FNakamaUtils::ConvertUserPresences(NakamaNativeStreamData.joins))
	, Leaves(FNakamaUtils::ConvertUserPresences(NakamaNativeStreamData.leaves))
{
	
}

FNakamaStreamPresenceEvent::FNakamaStreamPresenceEvent()
{
	
}
