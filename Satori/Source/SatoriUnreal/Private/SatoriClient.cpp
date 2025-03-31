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

#include "SatoriClient.h"
#include "SatoriUtils.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Interfaces/IHttpResponse.h"

void USatoriClient::InitializeClient(
	const FString& InHostname,
	int32 InPort, 
	const FString& InServerKey,
	bool bInUseSSL, 
	bool EnableDebug)
{
	Hostname = InHostname;
	Port = InPort;
	ServerKey = InServerKey;
	bUseSSL = bInUseSSL;
	bEnableDebug = EnableDebug;
}

void USatoriClient::InitializeSystem(
	const FString& InServerKey,
	const FString& Host,
	int32 InPort,
	bool UseSSL,
	bool EnableDebug)
{
	InitializeClient(Host, InPort, InServerKey, UseSSL, EnableDebug);
	bIsActive = true;
}

void USatoriClient::Disconnect()
{
	if (IsValidLowLevel())
	{
		CancelAllRequests();
	}
}

void USatoriClient::CancelAllRequests()
{
	if (!IsValidLowLevel())
	{
		return;
	}

	// Lock the mutex to protect access to ActiveRequests
	FScopeLock Lock(&ActiveRequestsMutex);

	// Iterate over the active requests and cancel each one
	for (const FHttpRequestPtr& Request : ActiveRequests)
	{
		Request->OnProcessRequestComplete().Unbind();
		Request->CancelRequest();
	}

	// Clear the ActiveRequests array
	ActiveRequests.Empty();
}

void USatoriClient::Destroy()
{
	bIsActive = false;
	ConditionalBeginDestroy();
}

void USatoriClient::SetTimeout(float InTimeout)
{
	Timeout = InTimeout;
}

float USatoriClient::GetTimeout()
{
	return Timeout;
}

void USatoriClient::BeginDestroy()
{
	UObject::BeginDestroy();
	bIsActive = false;
}

USatoriClient* USatoriClient::CreateDefaultClient(
	const FString& ServerKey, 
	const FString& Host, 
	int32 Port, 
	bool UseSSL, 
	bool EnableDebug)
{
	USatoriClient* NewClient = NewObject<USatoriClient>();
	NewClient->InitializeSystem(ServerKey, Host, Port, UseSSL, EnableDebug);

	if (EnableDebug)
	{
		USatoriLogger::EnableLogging(true);
		USatoriLogger::SetLogLevel(ESatoriLogLevel::Debug);
	}

	return NewClient;
}

void USatoriClient::Authenticate(
	const FString& ID,
	const TMap<FString, FString>& DefaultProperties,
	const TMap<FString, FString>& CustomProperties,
	const bool bNoSession,
	FOnSatoriAuthUpdate Success,
	FOnSatoriError Error)
{
	auto successCallback = [this, Success](USatoriSession* session)
		{
			if (!IsClientActive(this))
				return;

			Success.Broadcast(session);
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
				return;

			Error.Broadcast(error);
		};

	// A custom identifier must contain alphanumeric
	// characters with dashesand be between 6 and 128 bytes.

	Authenticate(ID, DefaultProperties, CustomProperties, bNoSession, successCallback, errorCallback);
}

void USatoriClient::Authenticate(
	const FString& ID,
	const TMap<FString, FString>& DefaultProperties,
	const TMap<FString, FString>& CustomProperties,
	const bool bNoSession,
	TFunction<void(USatoriSession* UserSession)> SuccessCallback,
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/authenticate");

	// Setup the request content
	const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();

	ContentJson->SetStringField(TEXT("id"), ID);
	if (bNoSession)
	{
		ContentJson->SetBoolField(TEXT("no_session"), bNoSession);
	}

	if(!DefaultProperties.IsEmpty())
	{
		TSharedPtr<FJsonObject> DefaultPropertiesJson = MakeShared<FJsonObject>();
		for (const TPair<FString, FString>& Pair : DefaultProperties)
		{
			DefaultPropertiesJson->SetStringField(Pair.Key, Pair.Value);
		}
		ContentJson->SetObjectField(TEXT("default"), DefaultPropertiesJson);
	}

	if (!CustomProperties.IsEmpty())
	{
		TSharedPtr<FJsonObject> CustomPropertiesJson = MakeShared<FJsonObject>();
		for (const TPair<FString, FString>& Pair : CustomProperties)
		{
			CustomPropertiesJson->SetStringField(Pair.Key, Pair.Value);
		}
		ContentJson->SetObjectField(TEXT("custom"), CustomPropertiesJson);
	}

	// Serialize the request content
	FString Content;
	if (!FSatoriUtils::SerializeJsonObject(ContentJson, Content))
	{
		// Handle JSON serialization failure
		FSatoriUtils::HandleJsonSerializationFailure(ErrorCallback);
		return;
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, Content, ESatoriRequestMethod::POST, TMultiMap<FString, FString>(), "");

	// Set the basic authorization header
	FSatoriUtils::SetBasicAuthorizationHeader(HttpRequest, ServerKey);

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						USatoriSession* ResultSession = NewObject<USatoriSession>();
						ResultSession->SetupSession(ResponseBody);
						SuccessCallback(ResultSession);
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::AuthenticateRefresh(
	USatoriSession* Session, 
	FOnSatoriAuthUpdate Success, 
	FOnSatoriError Error)
{
	auto successCallback = [this, Success](USatoriSession* UserSession)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast(UserSession);
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	AuthenticateRefresh(Session, successCallback, errorCallback);
}

void USatoriClient::AuthenticateRefresh(
	USatoriSession* Session, 
	TFunction<void(USatoriSession* UserSession)> SuccessCallback,
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/authenticate/refresh");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Setup the request content
	TSharedPtr<FJsonObject> ContentJson = MakeShareable(new FJsonObject);
	ContentJson->SetStringField(TEXT("refresh_token"), Session->GetRefreshToken());

	// Serialize the request content
	FString Content;
	if (!FSatoriUtils::SerializeJsonObject(ContentJson, Content))
	{
		// Handle JSON serialization failure
		FSatoriUtils::HandleJsonSerializationFailure(ErrorCallback);
		return;
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, Content, ESatoriRequestMethod::POST, TMultiMap<FString, FString>(), "");

	// Set the basic authorization header
	FSatoriUtils::SetBasicAuthorizationHeader(HttpRequest, ServerKey);

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						USatoriSession* ResultSession = NewObject<USatoriSession>();
						ResultSession->SetupSession(ResponseBody);
						SuccessCallback(ResultSession);
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
	});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::AuthenticateLogout(
	USatoriSession* Session,
	FOnAuthLogoutSent Success, 
	FOnSatoriError Error)
{
	auto successCallback = [this, Success]()
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast();
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	AuthenticateLogout(Session, successCallback, errorCallback);
}

void USatoriClient::AuthenticateLogout(
	USatoriSession* Session,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/authenticate/logout");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Setup the request content
	TSharedPtr<FJsonObject> ContentJson = MakeShareable(new FJsonObject);
	ContentJson->SetStringField(TEXT("token"), Session->GetAuthToken());
	ContentJson->SetStringField(TEXT("refresh_token"), Session->GetRefreshToken());

	// Serialize the request content
	FString Content;
	if (!FSatoriUtils::SerializeJsonObject(ContentJson, Content))
	{
		// Handle JSON serialization failure
		FSatoriUtils::HandleJsonSerializationFailure(ErrorCallback);
		return;
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, Content, ESatoriRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						SuccessCallback();
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::Identify(
	USatoriSession* Session, 
	const FString& ID, 
	const TMap<FString, FString>& defaultProperties,
	const TMap<FString, FString>& customProperties, 
	FOnSatoriAuthUpdate Success, 
	FOnSatoriError Error)
{
	auto successCallback = [this, Success](USatoriSession* UserSession)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast(UserSession);
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	Identify(Session, ID, defaultProperties, customProperties, successCallback, errorCallback);
}

void USatoriClient::Identify(
	USatoriSession* Session, 
	const FString& ID, 
	const TMap<FString, FString>& DefaultProperties, 
	const TMap<FString, FString>& CustomProperties, 
	TFunction<void(USatoriSession* UserSession)> SuccessCallback, 
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/identify");

	// Setup the request content
	const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();

	ContentJson->SetStringField(TEXT("id"), ID);

	if(!DefaultProperties.IsEmpty())
	{
		TSharedPtr<FJsonObject> DefaultPropertiesJson = MakeShared<FJsonObject>();
		for (const TPair<FString, FString>& Pair : DefaultProperties)
		{
			DefaultPropertiesJson->SetStringField(Pair.Key, Pair.Value);
		}
		ContentJson->SetObjectField(TEXT("default"), DefaultPropertiesJson);
	}

	if (!CustomProperties.IsEmpty())
	{
		TSharedPtr<FJsonObject> CustomPropertiesJson = MakeShared<FJsonObject>();
		for (const TPair<FString, FString>& Pair : CustomProperties)
		{
			CustomPropertiesJson->SetStringField(Pair.Key, Pair.Value);
		}
		ContentJson->SetObjectField(TEXT("custom"), CustomPropertiesJson);
	}

	// Serialize the request content
	FString Content;
	if (!FSatoriUtils::SerializeJsonObject(ContentJson, Content))
	{
		// Handle JSON serialization failure
		FSatoriUtils::HandleJsonSerializationFailure(ErrorCallback);
		return;
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, Content, ESatoriRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						USatoriSession* ResultSession = NewObject<USatoriSession>();
						ResultSession->SetupSession(ResponseBody);
						SuccessCallback(ResultSession);
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::ListIdentityProperties(
	USatoriSession* Session,
	FOnGetProperties Success,
	FOnSatoriError Error)
{
	auto successCallback = [this, Success](const FSatoriProperties& Properties)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast(Properties);
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	ListIdentityProperties(Session, successCallback, errorCallback);
}

void USatoriClient::ListIdentityProperties(
	USatoriSession* Session,
	TFunction<void(const FSatoriProperties& Properties)> SuccessCallback,
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/properties");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, TMultiMap<FString, FString>(), Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						const FSatoriProperties Properties = FSatoriProperties(ResponseBody);
						SuccessCallback(Properties);
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::UpdateProperties(
	USatoriSession* Session,
	const TMap<FString, FString>& DefaultProperties,
	const TMap<FString, FString>& CustomProperties,
	const bool bRecompute,
	FOnUpdatePropertiesSent Success,
	FOnSatoriError Error)
{
	auto successCallback = [this, Success]()
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast();
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	UpdateProperties(Session, DefaultProperties, CustomProperties, bRecompute, successCallback, errorCallback);
}

void USatoriClient::UpdateProperties(
	USatoriSession* Session,
	const TMap<FString, FString>& DefaultProperties,
	const TMap<FString, FString>& CustomProperties,
	const bool bRecompute,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/properties");

	// Setup the request content
	const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();

	if (!DefaultProperties.IsEmpty())
	{
		TSharedPtr<FJsonObject> DefaultPropertiesJson = MakeShared<FJsonObject>();
		for (const TPair<FString, FString>& Pair : DefaultProperties)
		{
			DefaultPropertiesJson->SetStringField(Pair.Key, Pair.Value);
		}
		ContentJson->SetObjectField(TEXT("default"), DefaultPropertiesJson);
	}

	if (!CustomProperties.IsEmpty())
	{
		TSharedPtr<FJsonObject> CustomPropertiesJson = MakeShared<FJsonObject>();
		for (const TPair<FString, FString>& Pair : CustomProperties)
		{
			CustomPropertiesJson->SetStringField(Pair.Key, Pair.Value);
		}
		ContentJson->SetObjectField(TEXT("custom"), CustomPropertiesJson);
	}

	ContentJson->SetBoolField(TEXT("recompute"), bRecompute);

	// Serialize the request content
	FString Content;
	if (!FSatoriUtils::SerializeJsonObject(ContentJson, Content))
	{
		// Handle JSON serialization failure
		FSatoriUtils::HandleJsonSerializationFailure(ErrorCallback);
		return;
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, Content, ESatoriRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						SuccessCallback();
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::DeleteIdentity(
	USatoriSession* Session,
	FOnDeleteIdentitySent Success,
	FOnSatoriError Error)
{
	auto successCallback = [this, Success]()
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast();
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	DeleteIdentity(Session, successCallback, errorCallback);
}

void USatoriClient::DeleteIdentity(
	USatoriSession* Session,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/identity");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ESatoriRequestMethod::DEL, TMultiMap<FString, FString>(), Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						SuccessCallback();
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::PostEvent(
	USatoriSession* Session,
	const TArray<FSatoriEvent>& events, 
	FOnPostEventSent Success, 
	FOnSatoriError Error)
{
	auto successCallback = [this, Success]()
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast();
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	PostEvent(Session, events, successCallback, errorCallback);
}

void USatoriClient::PostEvent(
	USatoriSession* Session,
	const TArray<FSatoriEvent>& Events,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/event");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Setup the request content
	TSharedPtr<FJsonObject> ContentJson = MakeShareable(new FJsonObject);

	// Setup the request body
	TArray<TSharedPtr<FJsonValue>> EventsJson;
	for (const FSatoriEvent& Event : Events)
	{
		TSharedPtr<FJsonObject> EventJson = MakeShareable(new FJsonObject());
		EventJson->SetStringField(TEXT("name"), Event.Name);
		if (!Event.ID.IsEmpty())
		{
			EventJson->SetStringField(TEXT("id"), Event.ID);
		}
		FSatoriUtils::AddVarsToJson(EventJson, Event.Metadata, TEXT("metadata"));
		if (!Event.Value.IsEmpty())
		{
			EventJson->SetStringField(TEXT("value"), Event.Value);
		}
		EventJson->SetStringField(TEXT("timestamp"), Event.Timestamp.ToIso8601());// google rpc requires RFC 3339, let's just hope Unreal's ISO 8601 keeps being copliant with it.
		EventsJson.Add(MakeShareable(new FJsonValueObject(EventJson)));
	}

	ContentJson->SetArrayField(TEXT("events"), EventsJson);

	// Serialize the request content
	FString Content;
	if (!FSatoriUtils::SerializeJsonObject(ContentJson, Content))
	{
		// Handle JSON serialization failure
		FSatoriUtils::HandleJsonSerializationFailure(ErrorCallback);
		return;
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, Content, ESatoriRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						SuccessCallback();
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::GetExperiments(
	USatoriSession* Session,
	const TArray<FString>& Names, 
	FOnGetExperiments Success, 
	FOnSatoriError Error)
{
	auto successCallback = [this, Success](const FSatoriExperimentList& Experiments)
	{
		if (!IsClientActive(this))
		{
			return;
		}

		Success.Broadcast(Experiments);
	};

	auto errorCallback = [this, Error](const FSatoriError& error)
	{
		if (!IsClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	GetExperiments(Session, Names, successCallback, errorCallback);
}

void USatoriClient::GetExperiments(
	USatoriSession* Session, 
	const TArray<FString>& Names, 
	TFunction<void(const FSatoriExperimentList& Experiments)> SuccessCallback, 
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/experiment");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Setup the query parameters
	TMultiMap<FString, FString> QueryParams;
	for (const FString& Name : Names)
	{
		QueryParams.Add(TEXT("names"), Name);
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, QueryParams, Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						const FSatoriExperimentList Experiments = FSatoriExperimentList(ResponseBody);
						SuccessCallback(Experiments);
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
	});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::GetFlags(
	USatoriSession* Session,
	const TArray<FString>& Names,
	FOnGetFlags Success,
	FOnSatoriError Error)
{
	auto successCallback = [this, Success](const FSatoriFlagList& Flags)
	{
		if (!IsClientActive(this))
		{
			return;
		}

		Success.Broadcast(Flags);
	};

	auto errorCallback = [this, Error](const FSatoriError& error)
	{
		if (!IsClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	GetFlags(Session, Names, successCallback, errorCallback);
}

void USatoriClient::GetFlags(
	USatoriSession* Session, 
	const TArray<FString>& Names, 
	TFunction<void(const FSatoriFlagList& Flags)> SuccessCallback, 
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/flag");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Setup the query parameters
	TMultiMap<FString, FString> QueryParams;
	for (const FString& Name : Names)
	{
		QueryParams.Add(TEXT("names"), Name);
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, QueryParams, Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {
		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						const FSatoriFlagList Flags = FSatoriFlagList(ResponseBody);
						SuccessCallback(Flags);
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
	});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::GetFlagOverrides(
	USatoriSession* Session, 
	const TArray<FString>& Names, 
	FOnGetFlagOverrides Success,
	FOnSatoriError Error)
{
	auto successCallback = [this, Success](const FSatoriFlagOverrideList& Flags)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast(Flags);
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	GetFlagOverrides(Session, Names, successCallback, errorCallback);
}

void USatoriClient::GetFlagOverrides(
	USatoriSession* Session, 
	const TArray<FString>& Names, 
	TFunction<void(const FSatoriFlagOverrideList& Flags)> SuccessCallback, 
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/flag/override");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Setup the query parameters
	TMultiMap<FString, FString> QueryParams;
	for (const FString& Name : Names)
	{
		QueryParams.Add(TEXT("names"), Name);
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, QueryParams, Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {
		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						const FSatoriFlagOverrideList FlagOverrides = FSatoriFlagOverrideList(ResponseBody);
						SuccessCallback(FlagOverrides);
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::GetLiveEvents(
	USatoriSession* Session, 
	const TArray<FString>& LiveEventNames, 
	FOnGetLiveEvents Success, 
	FOnSatoriError Error)
{
	auto successCallback = [this, Success](const FSatoriLiveEventList& LiveEvents)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast(LiveEvents);
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	GetLiveEvents(Session, LiveEventNames, successCallback, errorCallback);
}

void USatoriClient::GetLiveEvents(
	USatoriSession* Session,
	const TArray<FString>& LiveEventNames, 
	TFunction<void(const FSatoriLiveEventList& LiveEvents)> SuccessCallback, 
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/live-event");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Setup the query parameters
	TMultiMap<FString, FString> QueryParams;
	for (const FString& Name : LiveEventNames)
	{
		QueryParams.Add(TEXT("names"), Name);
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, QueryParams, Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						const FSatoriLiveEventList LiveEvents = FSatoriLiveEventList(ResponseBody);
						SuccessCallback(LiveEvents);
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::GetMessages(
	USatoriSession* Session, 
	int32 Limit,
	bool Forward, 
	const FString& Cursor, 
	FOnGetMessages Success, 
	FOnSatoriError Error)
{
	auto successCallback = [this, Success](const FSatoriMessageList& Messages)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast(Messages);
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	GetMessages(Session, Limit, Forward, Cursor, successCallback, errorCallback);
}

void USatoriClient::GetMessages(
	USatoriSession* Session, 
	int32 Limit, 
	bool Forward,
	const FString& Cursor, 
	TFunction<void(const FSatoriMessageList& Messages)> SuccessCallback, 
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/message");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Setup the query parameters
	TMultiMap<FString, FString> QueryParams;
	QueryParams.Add(TEXT("limit"), FString::FromInt(Limit));
	QueryParams.Add(TEXT("forward"), FSatoriUtils::BoolToString(Forward));
	if (!Cursor.IsEmpty()) { QueryParams.Add(TEXT("cursor"), FGenericPlatformHttp::UrlEncode(Cursor)); }

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, QueryParams, Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						const FSatoriMessageList Messages = FSatoriMessageList(ResponseBody);
						SuccessCallback(Messages);
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::UpdateMessage(
	USatoriSession* Session, 
	const FString& MessageId, 
	const FDateTime ReadTime, 
	const FDateTime ConsumeTime, 
	FOnUpdateMessageSent Success, 
	FOnSatoriError Error)
{
	auto successCallback = [this, Success]()
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast();
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	UpdateMessage(Session, MessageId, ReadTime, ConsumeTime, successCallback, errorCallback);
}

void USatoriClient::UpdateMessage(
	USatoriSession* Session, 
	const FString& MessageId, 
	const FDateTime ReadTime, 
	const FDateTime ConsumeTime,
	TFunction<void()> SuccessCallback, 
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/message/") + FGenericPlatformHttp::UrlEncode(MessageId);

	// Setup the request content
	const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();

	ContentJson->SetNumberField(TEXT("read_time"), ReadTime.ToUnixTimestamp());
	ContentJson->SetNumberField(TEXT("consume_time"), ConsumeTime.ToUnixTimestamp());

	// Serialize the request content
	FString Content;
	if (!FSatoriUtils::SerializeJsonObject(ContentJson, Content))
	{
		// Handle JSON serialization failure
		FSatoriUtils::HandleJsonSerializationFailure(ErrorCallback);
		return;
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, Content, ESatoriRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						SuccessCallback();
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

void USatoriClient::DeleteMessage(
	USatoriSession* Session, 
	const FString& MessageId,
	FOnDeleteMessageSent Success, 
	FOnSatoriError Error)
{
	auto successCallback = [this, Success]()
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Success.Broadcast();
		};

	auto errorCallback = [this, Error](const FSatoriError& error)
		{
			if (!IsClientActive(this))
			{
				return;
			}

			Error.Broadcast(error);
		};

	DeleteMessage(Session, MessageId, successCallback, errorCallback);
}

void USatoriClient::DeleteMessage(
	USatoriSession* Session,
	const FString& MessageId, 
	TFunction<void()> SuccessCallback,
	TFunction<void(const FSatoriError& Error)> ErrorCallback)
{
	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/message/") + FGenericPlatformHttp::UrlEncode(MessageId);

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Make the request
	const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ESatoriRequestMethod::DEL, TMultiMap<FString, FString>(), Session->GetAuthToken());

	// Lock the ActiveRequests mutex to protect concurrent access
	FScopeLock Lock(&ActiveRequestsMutex);

	// Add the HttpRequest to ActiveRequests
	ActiveRequests.Add(HttpRequest);

	// Bind the response callback and handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

		if (!IsValidLowLevel())
		{
			return;
		}

		// Lock the ActiveRequests mutex to protect concurrent access
		FScopeLock Lock(&ActiveRequestsMutex);

		if (ActiveRequests.Contains(Request))
		{
			if (bSuccess && Response.IsValid())
			{
				const FString ResponseBody = Response->GetContentAsString();

				// Check if Request was successful
				if (FSatoriUtils::IsResponseSuccessful(Response->GetResponseCode()))
				{
					// Check for Success Callback
					if (SuccessCallback)
					{
						SuccessCallback();
					}
				}
				else
				{
					// Check for Error Callback
					if (ErrorCallback)
					{
						const FSatoriError Error(ResponseBody);
						ErrorCallback(Error);
					}
				}
			}
			else
			{
				// Handle Invalid Response
				if (ErrorCallback)
				{
					const FSatoriError RequestError = FSatoriUtils::CreateRequestFailureError();
					ErrorCallback(RequestError);
				}
			}

			// Remove the HttpRequest from ActiveRequests
			ActiveRequests.Remove(Request);
		}
		});

	// Process the request
	HttpRequest->ProcessRequest();
}

bool USatoriClient::IsClientActive(const USatoriClient* Client)
{
	return IsValid(Client) && Client->bIsActive == true;
}

FString USatoriClient::ConstructURL(const FString& Endpoint)
{
	FString Protocol = bUseSSL ? TEXT("https") : TEXT("http");
	FString URL = FString::Printf(TEXT("%s://%s:%d%s"), *Protocol, *Hostname, Port, *Endpoint);

	return URL;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> USatoriClient::MakeRequest(
	const FString& Endpoint, 
	const FString& Content, 
	ESatoriRequestMethod RequestMethod, 
	const TMultiMap<FString, FString>& QueryParams, 
	const FString& SessionToken)
{
	// Append query parameters to the endpoint
	FString ModifiedEndpoint = Endpoint;
	if (QueryParams.Num() > 0)
	{
		FString QueryString = FSatoriUtils::BuildQueryString(QueryParams);
		ModifiedEndpoint += "?" + QueryString;
	}

	// Construct the URL
	FString URL = ConstructURL(ModifiedEndpoint);

	return FSatoriUtils::MakeRequest(URL, Content, RequestMethod, SessionToken, Timeout);
}
