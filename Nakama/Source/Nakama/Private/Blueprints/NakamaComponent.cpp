/**
* Copyright 2017 The Nakama Authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "NakamaComponent.h"
#include "NakamaSDK/NClient.h"

using namespace Nakama;

UNakamaComponent::UNakamaComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

UNakamaComponent::~UNakamaComponent() {
	delete ClientRef;
	ClientRef = nullptr;
}

void UNakamaComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (ClientRef != nullptr) {
		ClientRef->Tick(DeltaTime);
	}
}

void UNakamaComponent::SetupClient(FString serverKey, FString host, int32 port, FString lang, bool ssl) {
	auto client = &NClient::Builder(TCHAR_TO_UTF8(*serverKey))
		.Host(TCHAR_TO_UTF8(*host))
		.Port(port)
		.Lang(TCHAR_TO_UTF8(*lang))
		.SSL(ssl)
		.Build();
	this->ClientRef = client;
	this->ClientRef->OnDisconnect.push_back([=]() {
		OnDisconnect.Broadcast();
	});
	this->ClientRef->OnError.push_back([=](NError error) {
		OnError.Broadcast(UNBPError::From(error));
	});
	this->ClientRef->OnMatchData.push_back([=](NMatchData data) {
		OnMatchDataRcvd.Broadcast(UNBPMatchData::From(data));
	});
	this->ClientRef->OnMatchPresence.push_back([=](NMatchPresence presence) {
		OnMatchPresenceRcvd.Broadcast(UNBPMatchPresence::From(presence));
	});
	this->ClientRef->OnTopicMessage.push_back([=](NTopicMessage message) {
		OnTopicMessageRcvd.Broadcast(UNBPTopicMessage::From(message));
	});
	this->ClientRef->OnTopicPresence.push_back([=](NTopicPresence presence) {
		OnTopicPresenceRcvd.Broadcast(UNBPTopicPresence::From(presence));
	});
}

void UNakamaComponent::ShutdownClient()
{
	if (ClientRef != nullptr) {
		ClientRef->Disconnect();
	}

	this->UnregisterComponent();
}
