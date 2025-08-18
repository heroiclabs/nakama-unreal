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

#include "SatoriUtils.h"
#include "SatoriLogger.h"
#include "Dom/JsonObject.h"
#include "Misc/EngineVersionComparison.h"
#include "Interfaces/IHttpResponse.h"

DEFINE_LOG_CATEGORY_STATIC(LogSatoriUtils, Log, Log);

	void FSatoriUtils::ProcessRequestComplete(FHttpRequestPtr Request, const FHttpResponsePtr& Response, bool bSuccess, const TFunction<void(const FString&)>& SuccessCallback, const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
	{
		if (bSuccess && Response.IsValid())
		{
			const int32 ResponseCode = Response->GetResponseCode();
			const FString ResponseBody = Response->GetContentAsString();

			if (ResponseCode == 200)
			{
				SATORI_LOG_DEBUG(FString::Printf(TEXT("Request Successful: %s"), *ResponseBody));
				if (SuccessCallback)
				{
					SuccessCallback(ResponseBody);
				}
			}
			else
			{
				SATORI_LOG_WARN(FString::Printf(TEXT("Response (Code: %d) - Contents: %s"), ResponseCode, *ResponseBody));
				const FSatoriError Error(ResponseBody);
				if (ErrorCallback)
				{
					ErrorCallback(Error);
				}
			}
		}
		else
		{
			// Handle request failure
			SATORI_LOG_ERROR(TEXT("Failed to process request."));

			if (Request.IsValid())
			{
				SATORI_LOG_DEBUG(FString::Printf(TEXT("Request URL: %s"), *(Request->GetURL())));
			}

			FSatoriError Error;
			Error.Code = ESatoriErrorCode::Unknown;
			Error.Message = TEXT("Failed to proccess request. Request failed.");

			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	}

	void FSatoriUtils::HandleJsonSerializationFailure(TFunction<void(const FSatoriError& Error)> ErrorCallback)
	{
		SATORI_LOG_ERROR(TEXT("Failed to generate request content."));
		FSatoriError Error;
		Error.Code = ESatoriErrorCode::Unknown;
		Error.Message = TEXT("Failed to generate request content.");
		ErrorCallback(Error);
	}

	bool FSatoriUtils::IsSessionValid(const USatoriSession* Session, TFunction<void(const FSatoriError& Error)> ErrorCallback)
	{
		if (!Session || Session->SessionData.AuthToken.IsEmpty())
		{
			SATORI_LOG_ERROR("Invalid session or session data.");

			FSatoriError Error;
			Error.Message = "Invalid session or session data.";
			ErrorCallback(Error);
			return false;
		}

		return true;
	}

	bool FSatoriUtils::IsResponseSuccessful(int32 ResponseCode)
	{
		return ResponseCode == 200;
	}

	FSatoriError FSatoriUtils::CreateRequestFailureError()
	{
		SATORI_LOG_ERROR(TEXT("Failed to proccess request. Request failed."));
		FSatoriError Error;
		Error.Code = ESatoriErrorCode::Unknown;
		Error.Message = TEXT("Failed to proccess request. Request failed.");
		return Error;
	}
	
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> FSatoriUtils::MakeRequest(const FString& URL, const FString& Content, ESatoriRequestMethod RequestMethod, const FString& SessionToken, float Timeout)
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

		FString VerbString = ESatoriRequesMethodToFString(RequestMethod);
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

		//SATORI_LOG_INFO(TEXT("..."));
		//SATORI_LOG_INFO(FString::Printf(TEXT("Making Request to %s"), *Endpoint));
		SATORI_LOG_INFO(FString::Printf(TEXT("Making %s request to %s with content: %s"), *VerbString, *URL, *Content));
		return HttpRequest;
	}
