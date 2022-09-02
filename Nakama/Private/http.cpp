#include "http.h"
#include "HttpModule.h"
#include "Containers/ArrayBuilder.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/ScopeExit.h"


DEFINE_LOG_CATEGORY_STATIC(NakamaHttp, Warning, Warning);


namespace Nakama {
namespace Unreal {
	
UnrealHttpTransport::UnrealHttpTransport() {}

FString NHttpMethodToFString(NHttpReqMethod m)
{
	switch (m)
	{
	case NHttpReqMethod::GET: return TEXT("GET");
	case NHttpReqMethod::POST: return TEXT("POST");
	case NHttpReqMethod::DEL: return TEXT("DELETE");
	case NHttpReqMethod::PUT: return TEXT("PUT");
	}
	checkNoEntry();
	return TEXT("");
}

void UnrealHttpTransport::request(const NHttpRequest& req, const NHttpResponseCallback& callback)
{
	auto HttpRequest = PrepareRequest(req);
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
	{
		NHttpResponse NResponse;
		if (bSuccess)
		{
			NResponse.statusCode = Response->GetResponseCode();
			if (auto& Content = Response->GetContent(); !Content.IsEmpty())
			{
				 NResponse.body = std::string(reinterpret_cast<const char*>(Content.GetData()), Content.Num());
			}
		} else
		{
			NResponse.statusCode = InternalStatusCodes::CONNECTION_ERROR;
			NResponse.errorMessage = "Connection failed";
		}
		
		CompletedRequestsCS.Lock();
		ON_SCOPE_EXIT { CompletedRequestsCS.Unlock(); };
		CompletedRequests.Emplace(std::move(Request), std::move(NResponse));
	});
	
	if (callback) RegisterRequest(HttpRequest, callback);
	HttpRequest->ProcessRequest();
}

FHttpRequestPtr UnrealHttpTransport::PrepareRequest(const NHttpRequest& req) const
{
	auto HttpRequest = FHttpModule::Get().CreateRequest();

	FString URL = BaseURI;
	URL.Append(req.path.data(), req.path.length())
		.Append(req.queryArgs.empty() ? "" : "?");

	for (auto& p: req.queryArgs)
	{
		URL.Append(p.first.data(), p.first.length())
			.Append("=")
			.Append(p.second.data(), p.second.length())
			.Append("&");
	}

	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(NHttpMethodToFString(req.method));

	for (auto& h: req.headers)
	{
		HttpRequest->SetHeader(UTF8_TO_TCHAR(h.first.c_str()), UTF8_TO_TCHAR(h.second.c_str()));
	}

	if (!req.body.empty())
	{
		HttpRequest->SetContent(TArray<uint8>(reinterpret_cast<const uint8*>(req.body.data()), req.body.length()));
	}
	HttpRequest->SetTimeout(5);

	return HttpRequest;
}

void UnrealHttpTransport::RegisterRequest(FHttpRequestPtr Request, const NHttpResponseCallback& callback)
{
	PendingRequestsCS.Lock();
	ON_SCOPE_EXIT { PendingRequestsCS.Unlock(); };
	PendingRequests.Emplace(std::move(Request), std::move(callback));
}

void UnrealHttpTransport::tick()
{
	CompletedRequestsCS.Lock();
	ON_SCOPE_EXIT { CompletedRequestsCS.Unlock(); };
	for (const auto& item: CompletedRequests)
	{
		NHttpResponseCallback callback = nullptr;
		
		{
			PendingRequestsCS.Lock();
			ON_SCOPE_EXIT { PendingRequestsCS.Unlock(); };
			if (!PendingRequests.RemoveAndCopyValue(item.Key, callback))
			{
				UE_LOG(NakamaHttp, Warning, TEXT("Completed request doesn't have matching PendingRequests entry. No callback will be called."));
				continue;
			}
		}
		callback(std::make_shared<NHttpResponse>(std::move(item.Value)));
	}
	CompletedRequests.Reset();
}

void UnrealHttpTransport::cancelAllRequests()
{
	PendingRequestsCS.Lock();
	ON_SCOPE_EXIT { PendingRequestsCS.Unlock(); };
	for (auto& p: PendingRequests)
	{
		auto Request = p.Key.Get();
		Request->OnProcessRequestComplete().Unbind();
		Request->CancelRequest();
		
		NHttpResponsePtr responsePtr(new NHttpResponse{InternalStatusCodes::CANCELLED_BY_USER, std::string() , std::string()});
		(p.Value)(std::move(responsePtr));
	}
	PendingRequests.Reset();
}

	
}
}
