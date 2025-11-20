/*
* Copyright 2025 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "NakamaUtils.h"
#include "NakamaUser.h"
#include "NakamaLogger.h"
#include "Dom/JsonObject.h"
#include "Misc/EngineVersionComparison.h"
#include "Interfaces/IHttpResponse.h"

DEFINE_LOG_CATEGORY_STATIC(LogNakamaUtils, Log, Log);

void FNakamaUtils::ProcessRequestComplete(FHttpRequestPtr Request, const FHttpResponsePtr& Response, bool bSuccess, const TFunction<void(const FString&)>& SuccessCallback, const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
	if (bSuccess && Response.IsValid())
	{
		const int32 ResponseCode = Response->GetResponseCode();
		const FString ResponseBody = Response->GetContentAsString();

		if (ResponseCode == 200)
		{
			NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Request Successful: %s"), *ResponseBody));
			if (SuccessCallback)
			{
				SuccessCallback(ResponseBody);
			}
		}
		else
		{
			NAKAMA_LOG_WARN(FString::Printf(TEXT("Response (Code: %d) - Contents: %s"), ResponseCode, *ResponseBody));
			const FNakamaError Error(ResponseBody);
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	}
	else
	{
		// Handle request failure
		NAKAMA_LOG_ERROR(TEXT("Failed to process request."));

		if (Request.IsValid())
		{
			NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Request URL: %s"), *(Request->GetURL())));
		}

		FNakamaError Error;
		Error.Code = ENakamaErrorCode::Unknown;
		Error.Message = TEXT("Failed to proccess request. Request failed.");

		if (ErrorCallback)
		{
			ErrorCallback(Error);
		}
	}
}

void FNakamaUtils::ProcessRequestCompleteMove(FHttpRequestPtr Request, const FHttpResponsePtr& Response, bool bSuccess,
	const TFunction<void(FString&&)>& SuccessCallback, const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
	if (bSuccess && Response.IsValid())
	{
		const int32 ResponseCode = Response->GetResponseCode();
		FString ResponseBody = Response->GetContentAsString();

		if (ResponseCode == 200)
		{
			NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Request Successful: %s"), *ResponseBody));
			if (SuccessCallback)
			{
				SuccessCallback(MoveTemp(ResponseBody));
			}
		}
		else
		{
			NAKAMA_LOG_WARN(FString::Printf(TEXT("Response (Code: %d) - Contents: %s"), ResponseCode, *ResponseBody));
			const FNakamaError Error(ResponseBody);
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	}
	else
	{
		// Handle request failure
		NAKAMA_LOG_ERROR(TEXT("Failed to process request."));

		if (Request.IsValid())
		{
			NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Request URL: %s"), *(Request->GetURL())));
		}

		FNakamaError Error;
		Error.Code = ENakamaErrorCode::Unknown;
		Error.Message = TEXT("Failed to proccess request. Request failed.");

		if (ErrorCallback)
		{
			ErrorCallback(Error);
		}
	}
}

void FNakamaUtils::HandleJsonSerializationFailure(TFunction<void(const FNakamaError& Error)> ErrorCallback)
	{
		NAKAMA_LOG_ERROR(TEXT("Failed to generate request content."));
		FNakamaError Error;
		Error.Code = ENakamaErrorCode::Unknown;
		Error.Message = TEXT("Failed to generate request content.");
		ErrorCallback(Error);
	}

	bool FNakamaUtils::IsSessionValid(const UNakamaSession* Session, TFunction<void(const FNakamaError& Error)> ErrorCallback)
	{
		if (!Session || Session->SessionData.AuthToken.IsEmpty())
		{
			NAKAMA_LOG_ERROR("Invalid session or session data.");

			FNakamaError Error;
			Error.Message = "Invalid session or session data.";
			ErrorCallback(Error);
			return false;
		}

		return true;
	}

	bool FNakamaUtils::IsResponseSuccessful(int32 ResponseCode)
	{
		return ResponseCode == 200;
	}

	FNakamaError FNakamaUtils::CreateRequestFailureError()
	{
		NAKAMA_LOG_ERROR(TEXT("Failed to proccess request. Request failed."));
		FNakamaError Error;
		Error.Code = ENakamaErrorCode::Unknown;
		Error.Message = TEXT("Failed to proccess request. Request failed.");
		return Error;
	}
	
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> FNakamaUtils::MakeRequest(const FString& URL, const FString& Content, ENakamaRequestMethod RequestMethod, const FString& SessionToken, float Timeout)
	{
		FHttpModule* HttpModule = &FHttpModule::Get();

		// Create the HttpRequest
#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <= 25
		TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = HttpModule->CreateRequest();
#endif

		HttpRequest->SetURL(URL);
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
		HttpRequest->SetTimeout(Timeout); // Exposed to end user

		FString VerbString = ENakamaRequesMethodToFString(RequestMethod);
		if (!VerbString.IsEmpty())
		{
			HttpRequest->SetVerb(VerbString);
		}

		// Set the content if it is not empty
		if (!Content.IsEmpty())
		{
			HttpRequest->SetContentAsString(Content);
		}

		// Add authorization header if session token is provided
		if (!SessionToken.IsEmpty())
		{
			FString AuthorizationHeader = FString::Printf(TEXT("Bearer %s"), *SessionToken);
			HttpRequest->SetHeader(TEXT("Authorization"), AuthorizationHeader);
		}

		//NAKAMA_LOG_INFO(TEXT("..."));
		//NAKAMA_LOG_INFO(FString::Printf(TEXT("Making Request to %s"), *Endpoint));
		NAKAMA_LOG_INFO(FString::Printf(TEXT("Making %s request to %s with content: %s"), *VerbString, *URL, *Content));
		return HttpRequest;
	}
