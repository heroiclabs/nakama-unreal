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
#include "SatoriRetryInvoker.h"
#include "Containers/Ticker.h"
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

	// Take ownership of the in-flight set under the lock, then release it before
	// cancelling so a synchronous completion callback can re-enter the lock safely.
	TArray<FHttpRequestPtr> ToCancel;
	{
		FScopeLock Lock(&ActiveRequestsMutex);
		ToCancel = MoveTemp(ActiveRequests);
		ActiveRequests.Empty();
	}

	// Cancel each request. We deliberately do NOT unbind the completion delegate:
	// CancelRequest drives it with bSuccess=false, and since the request is no
	// longer in ActiveRequests the completion handler resolves it as a transport
	// failure, delivering a terminal OnError instead of silently dropping the
	// caller's callback.
	for (const FHttpRequestPtr& Request : ToCancel)
	{
		Request->CancelRequest();
	}
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
	const FOnSatoriAuthUpdate& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](USatoriSession* session)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success, session);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
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
	const TFunction<void(USatoriSession* UserSession)>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

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
	SendJsonRequest(Endpoint, Content, ESatoriRequestMethod::POST, TMultiMap<FString, FString>(), "",
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				SuccessCallback(USatoriSession::SetupSession(ResponseBody));
			}
		},
		ErrorCallback,
		[WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
		{
			USatoriClient* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}
			FSatoriUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
		});
}

void USatoriClient::AuthenticateRefresh(
	USatoriSession* Session,
	const FOnSatoriAuthUpdate& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](USatoriSession* UserSession)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success, UserSession);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	AuthenticateRefresh(Session, successCallback, errorCallback);
}

void USatoriClient::EnsureValidSession(
	USatoriSession* Session,
	const TFunction<void()>& OnReady,
	const TFunction<void(const FSatoriError& Error)>& OnError)
{
	const FDateTime Deadline =
		FDateTime::UtcNow() + FTimespan::FromMinutes(SessionRefreshLeewayMinutes);

	// No refresh needed: disabled, no refresh token, or token still fresh enough.
	if (!bAutoRefreshSession
		|| Session->GetRefreshToken().IsEmpty()
		|| !Session->IsExpiredTime(Deadline))
	{
		OnReady();
		return;
	}

	// Coalesce concurrent refreshes for the same session. A rotating refresh
	// token can only be redeemed once, so a burst of requests on an expiring
	// token must share a single refresh; otherwise all but the first would fail.
	// (Game-thread only: HTTP completions and ticker callbacks both dispatch on
	// the game thread, so InFlightRefreshes needs no external locking.)
	const TWeakObjectPtr<USatoriSession> Key(Session);
	if (TSharedPtr<FPendingRefresh>* Existing = InFlightRefreshes.Find(Key))
	{
		(*Existing)->OnReady.Add(OnReady);
		(*Existing)->OnError.Add(OnError);
		return;
	}

	const TSharedPtr<FPendingRefresh> Pending = MakeShared<FPendingRefresh>();
	Pending->OnReady.Add(OnReady);
	Pending->OnError.Add(OnError);
	InFlightRefreshes.Add(Key, Pending);

	TWeakObjectPtr<USatoriClient> WeakThis(this);

	// Refresh first, then run all deferred requests with the refreshed token.
	// Callbacks are driven from the captured Pending (not a map lookup) so they
	// always fire exactly once, even if the client is torn down mid-refresh.
	AuthenticateRefresh(Session,
		[WeakThis, Key, Pending](USatoriSession* Refreshed)
		{
			if (USatoriClient* Self = WeakThis.Get())
			{
				Self->InFlightRefreshes.Remove(Key);
			}

			USatoriSession* LiveSession = Key.Get();
			if (Refreshed && LiveSession)
			{
				LiveSession->Update(Refreshed);
				for (const TFunction<void()>& Cb : Pending->OnReady)
				{
					if (Cb) { Cb(); }
				}
			}
			else
			{
				// Refresh response could not be parsed into a session (or the
				// session was destroyed); do not proceed with the stale token.
				const FSatoriError Error = FSatoriUtils::CreateRequestFailureError();
				for (const TFunction<void(const FSatoriError&)>& Cb : Pending->OnError)
				{
					if (Cb) { Cb(Error); }
				}
			}
		},
		[WeakThis, Key, Pending](const FSatoriError& Error)
		{
			if (USatoriClient* Self = WeakThis.Get())
			{
				Self->InFlightRefreshes.Remove(Key);
			}
			for (const TFunction<void(const FSatoriError&)>& Cb : Pending->OnError)
			{
				if (Cb) { Cb(Error); }
			}
		});
}

void USatoriClient::AuthenticateRefresh(
	USatoriSession* Session,
	const TFunction<void(USatoriSession* UserSession)>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

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
	SendJsonRequest(Endpoint, Content, ESatoriRequestMethod::POST, TMultiMap<FString, FString>(), "",
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				SuccessCallback(USatoriSession::SetupSession(ResponseBody));
			}
		},
		ErrorCallback,
		[WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
		{
			USatoriClient* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}
			FSatoriUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
		});
}

void USatoriClient::AuthenticateLogout(
	USatoriSession* Session,
	const FOnAuthLogoutSent& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	AuthenticateLogout(Session, successCallback, errorCallback);
}

void USatoriClient::AuthenticateLogout(
	USatoriSession* Session,
	const TFunction<void()>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
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
	SendJsonRequest(Endpoint, Content, ESatoriRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		ErrorCallback);
}

void USatoriClient::Identify(
	USatoriSession* Session, 
	const FString& ID, 
	const TMap<FString, FString>& defaultProperties,
	const TMap<FString, FString>& customProperties,
	const FOnSatoriAuthUpdate& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](USatoriSession* UserSession)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success, UserSession);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	Identify(Session, ID, defaultProperties, customProperties, successCallback, errorCallback);
}

void USatoriClient::Identify(
	USatoriSession* Session, 
	const FString& ID, 
	const TMap<FString, FString>& DefaultProperties, 
	const TMap<FString, FString>& CustomProperties,
	const TFunction<void(USatoriSession* UserSession)>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

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

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, Content, ESatoriRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				SuccessCallback(USatoriSession::SetupSession(ResponseBody));
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
}

void USatoriClient::ListIdentityProperties(
	USatoriSession* Session,
	const FOnGetProperties& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FSatoriProperties& Properties)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success, Properties);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	ListIdentityProperties(Session, successCallback, errorCallback);
}

void USatoriClient::ListIdentityProperties(
	USatoriSession* Session,
	const TFunction<void(const FSatoriProperties& Properties)>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/properties");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, TMultiMap<FString, FString>(), Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				const FSatoriProperties Properties = FSatoriProperties(ResponseBody);
						SuccessCallback(Properties);
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
}

void USatoriClient::UpdateProperties(
	USatoriSession* Session,
	const TMap<FString, FString>& DefaultProperties,
	const TMap<FString, FString>& CustomProperties,
	const bool bRecompute,
	const FOnUpdatePropertiesSent& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	UpdateProperties(Session, DefaultProperties, CustomProperties, bRecompute, successCallback, errorCallback);
}

void USatoriClient::UpdateProperties(
	USatoriSession* Session,
	const TMap<FString, FString>& DefaultProperties,
	const TMap<FString, FString>& CustomProperties,
	const bool bRecompute,
	const TFunction<void()>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

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

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, Content, ESatoriRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
}

void USatoriClient::DeleteIdentity(
	USatoriSession* Session,
	const FOnDeleteIdentitySent& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	DeleteIdentity(Session, successCallback, errorCallback);
}

void USatoriClient::DeleteIdentity(
	USatoriSession* Session,
	const TFunction<void()>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/identity");

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, TEXT(""), ESatoriRequestMethod::DEL, TMultiMap<FString, FString>(), Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
}

void USatoriClient::PostServerEvent(
	const TArray<FSatoriEvent>& Events,
	const FOnPostServerEventSent& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FSatoriUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
	{
		FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	PostServerEvent(Events, successCallback, errorCallback);
}

void USatoriClient::PostServerEvent(
	const TArray<FSatoriEvent>& Events,
	const TFunction<void()>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/server-event");

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
		// google rpc requires RFC 3339, let's just hope Unreal's ISO 8601 keeps being compliant with it.
		EventJson->SetStringField(TEXT("timestamp"), Event.Timestamp.ToIso8601());
		
		if (!Event.IdentityId.IsEmpty())
		{
			EventJson->SetStringField(TEXT("identity_id"), Event.IdentityId);
		}
		if (!Event.SessionId.IsEmpty())
		{
			EventJson->SetStringField(TEXT("session_id"), Event.SessionId);
		}
		if (Event.SessionIssuedAt > 0)
		{
			EventJson->SetNumberField(TEXT("session_issued_at"), Event.SessionIssuedAt);
		}
		if (Event.SessionExpiresAt > 0)
		{
			EventJson->SetNumberField(TEXT("session_expires_at"), Event.SessionExpiresAt);
		}
		
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
	SendJsonRequest(Endpoint, Content, ESatoriRequestMethod::POST, TMultiMap<FString, FString>(), "",
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		ErrorCallback,
		[WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
		{
			USatoriClient* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}
			FSatoriUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
		});
}

void USatoriClient::PostEvent(
	USatoriSession* Session,
	const TArray<FSatoriEvent>& Events,
	const FOnPostEventSent& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	PostEvent(Session, Events, successCallback, errorCallback);
}

void USatoriClient::PostEvent(
	USatoriSession* Session,
	const TArray<FSatoriEvent>& Events,
	const TFunction<void()>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

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
		// google rpc requires RFC 3339, let's just hope Unreal's ISO 8601 keeps being compliant with it.
		EventJson->SetStringField(TEXT("timestamp"), Event.Timestamp.ToIso8601());
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

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, Content, ESatoriRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
}

void USatoriClient::GetExperiments(
	USatoriSession* Session,
	const TArray<FString>& Names,
	const FOnGetExperiments& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FSatoriExperimentList& Experiments)
	{
		FSatoriUtils::BroadcastIfActive(WeakThis, Success, Experiments);
	};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
	{
		FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	GetExperiments(Session, Names, successCallback, errorCallback);
}

void USatoriClient::GetExperiments(
	USatoriSession* Session, 
	const TArray<FString>& Names,
	const TFunction<void(const FSatoriExperimentList& Experiments)>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

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

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, QueryParams, Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				const FSatoriExperimentList Experiments = FSatoriExperimentList(ResponseBody);
						SuccessCallback(Experiments);
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
}

void USatoriClient::GetFlags(
	USatoriSession* Session,
	const TArray<FString>& Names,
	const FOnGetFlags& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FSatoriFlagList& Flags)
	{
		FSatoriUtils::BroadcastIfActive(WeakThis, Success, Flags);
	};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
	{
		FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	GetFlags(Session, Names, successCallback, errorCallback);
}

void USatoriClient::GetFlags(
	USatoriSession* Session, 
	const TArray<FString>& Names,
	const TFunction<void(const FSatoriFlagList& Flags)>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

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

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, QueryParams, Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				const FSatoriFlagList Flags = FSatoriFlagList(ResponseBody);
						SuccessCallback(Flags);
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
}

void USatoriClient::GetFlagOverrides(
	USatoriSession* Session, 
	const TArray<FString>& Names,
	const FOnGetFlagOverrides& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FSatoriFlagOverrideList& Flags)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success, Flags);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	GetFlagOverrides(Session, Names, successCallback, errorCallback);
}

void USatoriClient::GetFlagOverrides(
	USatoriSession* Session, 
	const TArray<FString>& Names,
	const TFunction<void(const FSatoriFlagOverrideList& Flags)>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

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

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, QueryParams, Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				const FSatoriFlagOverrideList FlagOverrides = FSatoriFlagOverrideList(ResponseBody);
						SuccessCallback(FlagOverrides);
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
}

void USatoriClient::GetLiveEvents(
	USatoriSession* Session, 
	const TArray<FString>& LiveEventNames,
	const FOnGetLiveEvents& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FSatoriLiveEventList& LiveEvents)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success, LiveEvents);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	GetLiveEvents(Session, LiveEventNames, successCallback, errorCallback);
}

void USatoriClient::GetLiveEvents(
	USatoriSession* Session,
	const TArray<FString>& LiveEventNames,
	const TFunction<void(const FSatoriLiveEventList& LiveEvents)>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

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

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, QueryParams, Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				const FSatoriLiveEventList LiveEvents = FSatoriLiveEventList(ResponseBody);
						SuccessCallback(LiveEvents);
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
}

void USatoriClient::GetMessages(
	USatoriSession* Session, 
	int32 Limit,
	bool Forward, 
	const FString& Cursor,
	const FOnGetMessages& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FSatoriMessageList& Messages)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success, Messages);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	GetMessages(Session, Limit, Forward, Cursor, successCallback, errorCallback);
}

void USatoriClient::GetMessages(
	USatoriSession* Session, 
	int32 Limit, 
	bool Forward,
	const FString& Cursor,
	const TFunction<void(const FSatoriMessageList& Messages)>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

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

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, TEXT(""), ESatoriRequestMethod::GET, QueryParams, Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				const FSatoriMessageList Messages = FSatoriMessageList(ResponseBody);
						SuccessCallback(Messages);
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
}

void USatoriClient::UpdateMessage(
	USatoriSession* Session, 
	const FString& MessageId, 
	const FDateTime ReadTime, 
	const FDateTime ConsumeTime,
	const FOnUpdateMessageSent& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	UpdateMessage(Session, MessageId, ReadTime, ConsumeTime, successCallback, errorCallback);
}

void USatoriClient::UpdateMessage(
	USatoriSession* Session, 
	const FString& MessageId, 
	const FDateTime ReadTime, 
	const FDateTime ConsumeTime,
	const TFunction<void()>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

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

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, Content, ESatoriRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
}

void USatoriClient::DeleteMessage(
	USatoriSession* Session, 
	const FString& MessageId,
	const FOnDeleteMessageSent& Success,
	const FOnSatoriError& Error)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Success);
		};

	auto errorCallback = [WeakThis, Error](const FSatoriError& error)
		{
			FSatoriUtils::BroadcastIfActive(WeakThis, Error, error);
		};

	DeleteMessage(Session, MessageId, successCallback, errorCallback);
}

void USatoriClient::DeleteMessage(
	USatoriSession* Session,
	const FString& MessageId,
	const TFunction<void()>& SuccessCallback,
	const TFunction<void(const FSatoriError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<USatoriClient> WeakThis(this);

	// Setup the endpoint
	const FString Endpoint = TEXT("/v1/message/") + FGenericPlatformHttp::UrlEncode(MessageId);

	// Verify the session
	if (!FSatoriUtils::IsSessionValid(Session, ErrorCallback))
	{
		return;
	}

	// Refresh the session token first if it is about to expire, then send.
	EnsureValidSession(Session,
		[WeakThis, Session, Endpoint, SuccessCallback, ErrorCallback]()
	{
	USatoriClient* Self = WeakThis.Get();
	if (!Self)
	{
		if (ErrorCallback) { ErrorCallback(FSatoriUtils::CreateRequestFailureError()); }
		return;
	}

	// Make the request
	Self->SendJsonRequest(Endpoint, TEXT(""), ESatoriRequestMethod::DEL, TMultiMap<FString, FString>(), Session->GetAuthToken(),
		[SuccessCallback](const FString& ResponseBody)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		ErrorCallback);
	},
	ErrorCallback);
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

FSatoriRetryConfiguration USatoriClient::BuildRetryConfiguration() const
{
	FSatoriRetryConfiguration Config;
	Config.BaseDelayMs = RetryBaseDelayMs;
	// bEnableRetries == false means zero retries (single attempt).
	Config.MaxRetries = bEnableRetries ? RetryMaxAttempts : 0;
	// Jitter defaults to DecorrelatedJitter; Listener stays null in production.
	return Config;
}

void USatoriClient::SendJsonRequest(
	const FString& Endpoint,
	const FString& Content,
	ESatoriRequestMethod Method,
	const TMultiMap<FString, FString>& QueryParams,
	const FString& SessionToken,
	const TFunction<void(const FString& Body)>& OnSuccess,
	const TFunction<void(const FSatoriError& Error)>& OnError,
	const TFunction<void(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>&)>& PrepareRequest)
{
	// One attempt: build a FRESH request (UE requests are single-use), bind, fire.
	TWeakObjectPtr<USatoriClient> WeakThis(this);
	FSatoriSendFn Send =
		[WeakThis, Endpoint, Content, Method, QueryParams, SessionToken, PrepareRequest]
		(TFunction<void(bool, int32, const FString&)> OnComplete)
	{
		USatoriClient* Self = WeakThis.Get();
		if (!Self)
		{
			OnComplete(false, -1, FString());
			return;
		}

		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest =
			Self->MakeRequest(Endpoint, Content, Method, QueryParams, SessionToken);
		if (PrepareRequest)
		{
			PrepareRequest(HttpRequest);
		}

		{
			FScopeLock Lock(&Self->ActiveRequestsMutex);
			Self->ActiveRequests.Add(HttpRequest);
		}

		HttpRequest->OnProcessRequestComplete().BindLambda(
			[WeakThis, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			// Always deliver exactly one terminal outcome to OnComplete so the retry
			// chain (and the caller's success/error callback) can never be silently
			// dropped. A response is only forwarded when the request was still active;
			// a cancelled request (removed from ActiveRequests) or a dead client both
			// resolve to a transport failure, which ends the chain via OnError.
			bool bDeliverResponse = bSuccess && Response.IsValid();
			if (USatoriClient* Self = WeakThis.Get())
			{
				if (Self->IsValidLowLevel())
				{
					FScopeLock Lock(&Self->ActiveRequestsMutex);
					if (Self->ActiveRequests.Contains(Request))
					{
						Self->ActiveRequests.Remove(Request);
					}
					else
					{
						bDeliverResponse = false; // cancelled or already reaped
					}
				}
				else
				{
					bDeliverResponse = false;
				}
			}
			else
			{
				bDeliverResponse = false; // client gone
			}

			if (bDeliverResponse)
			{
				OnComplete(true, Response->GetResponseCode(), Response->GetContentAsString());
			}
			else
			{
				OnComplete(false, -1, FString());
			}
		});

		HttpRequest->ProcessRequest();
	};

	// FTSTicker-based delay: schedule Work after Seconds, once. Work is run
	// unconditionally (even if the client has since been destroyed) so the
	// retry attempt always executes and self-terminates through the null-client
	// path in Send, guaranteeing the caller's OnError fires instead of hanging.
	FSatoriDelayFn Delay = [](float Seconds, TFunction<void()> Work)
	{
		FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda(
			[Work](float /*DeltaTime*/) -> bool
			{
				Work();
				return false; // one-shot: unregister after firing
			}), Seconds);
	};

	// Seed the RNG from the auth token (or endpoint+content for auth calls).
	const int32 Seed = SessionToken.IsEmpty()
		? static_cast<int32>(GetTypeHash(Endpoint + Content))
		: static_cast<int32>(GetTypeHash(SessionToken));

	FSatoriRetryInvoker::InvokeWithRetry(
		Send, BuildRetryConfiguration(), Seed, Delay, OnSuccess, OnError);
}
