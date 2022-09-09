#pragma once

#include <nakama-cpp/NTypes.h>
#include <nakama-cpp/NHttpTransportInterface.h>

#include "Interfaces/IHttpRequest.h"

namespace Nakama {
namespace Unreal {
class UnrealHttpTransport : public NHttpTransportInterface {
public:
    UnrealHttpTransport();
    virtual ~UnrealHttpTransport() override = default;
    void setBaseUri(const std::string &uri) override { BaseURI = UTF8_TO_TCHAR(uri.c_str()); }
    void tick() override;
    void request(const NHttpRequest &req, const NHttpResponseCallback &callback = nullptr) override;
	void cancelAllRequests() override;
private:
    FHttpRequestPtr PrepareRequest(const NHttpRequest& req) const;
    void RegisterRequest(FHttpRequestPtr Request, const NHttpResponseCallback& callback);
	
	TMap<FHttpRequestPtr, NHttpResponseCallback> PendingRequests;
	FCriticalSection PendingRequestsCS;
	
	TMap<FHttpRequestPtr, NHttpResponse> CompletedRequests;
	FCriticalSection CompletedRequestsCS;

	FString BaseURI;
};
}
}
