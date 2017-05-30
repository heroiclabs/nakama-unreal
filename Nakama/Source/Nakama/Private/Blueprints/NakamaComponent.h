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

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NClient.h"
#include "NBPDataClasses.h"
#include "NakamaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisconnect);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnError, UNBPError*, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchDataRcvd, UNBPMatchData*, data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchPresenceRcvd, UNBPMatchPresence*, presence);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTopicMessageRcvd, UNBPTopicMessage*, data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTopicPresenceRcvd, UNBPTopicPresence*, presence);

UCLASS(ClassGroup=(Nakama), meta = (BlueprintSpawnableComponent))
class NAKAMA_API UNakamaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNakamaComponent();
	~UNakamaComponent();

	UPROPERTY(BlueprintAssignable)
		FOnDisconnect OnDisconnect;

	UPROPERTY(BlueprintAssignable)
		FOnMatchDataRcvd OnMatchDataRcvd;

	UPROPERTY(BlueprintAssignable)
		FOnError OnError;

	UPROPERTY(BlueprintAssignable)
		FOnMatchPresenceRcvd OnMatchPresenceRcvd;

	UPROPERTY(BlueprintAssignable)
		FOnTopicMessageRcvd OnTopicMessageRcvd;

	UPROPERTY(BlueprintAssignable)
		FOnTopicPresenceRcvd OnTopicPresenceRcvd;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Nakama|Client")
		void SetupClient(FString serverKey = "defaultkey", FString host = "127.0.0.1", int32 port = 7350, FString lang = "en", bool ssl = false);

	UFUNCTION(BlueprintCallable, Category = "Nakama|Client")
		void ShutdownClient();

	Nakama::NClient* GetClient() { return ClientRef; }

private:
	Nakama::NClient* ClientRef;

};
