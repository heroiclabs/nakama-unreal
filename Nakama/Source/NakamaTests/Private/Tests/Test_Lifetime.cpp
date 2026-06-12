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

// Use-after-free guard for async client callbacks: capture TWeakObjectPtr, bail
// out if the owner was GC'd. Lambdas mirror the capture pattern in NakamaClient.cpp.

#include "NakamaTestBase.h"
#include "NakamaRealtimeClient.h"
#include "NakamaUtils.h"

// Releases Obj and forces a full GC so weak references resolve to null.
static void ReleaseAndCollect(UObject* Obj)
{
	Obj->MarkAsGarbage();
	CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS, /*bPerformFullPurge*/ true);
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(ClientReleasedCallback, FNakamaTestBase, "Nakama.Base.Lifetime.ClientReleasedCallback", NAKAMA_MODULE_TEST_MASK)
inline bool ClientReleasedCallback::RunTest(const FString& Parameters)
{
	UNakamaClient* LocalClient = NewObject<UNakamaClient>();
	LocalClient->bIsActive = true;
	TWeakObjectPtr<UNakamaClient> WeakThis(LocalClient);

	int32 Fired = 0;
	auto Callback = [WeakThis, &Fired]()
	{
		if (!FNakamaUtils::IsClientActive(WeakThis.Get()))
		{
			return;
		}
		++Fired;
	};

	Callback();
	TestEqual(TEXT("fires while the client is alive"), Fired, 1);

	// Alive but deactivated: guard must also block.
	LocalClient->bIsActive = false;
	Callback();
	TestEqual(TEXT("does not fire while inactive"), Fired, 1);
	LocalClient->bIsActive = true;
	Callback();
	TestEqual(TEXT("fires again when reactivated"), Fired, 2);

	LocalClient = nullptr;
	ReleaseAndCollect(WeakThis.Get());

	TestFalse(TEXT("weak pointer is invalid after release"), WeakThis.IsValid());
	TestNull(TEXT("weak.Get() is null after release"), WeakThis.Get());

	Callback(); // must not dereference a dangling pointer
	TestEqual(TEXT("does not fire after the client is released"), Fired, 2);
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RealtimeClientReleasedCallback, FNakamaTestBase, "Nakama.Base.Lifetime.RealtimeClientReleasedCallback", NAKAMA_MODULE_TEST_MASK)
inline bool RealtimeClientReleasedCallback::RunTest(const FString& Parameters)
{
	UNakamaRealtimeClient* LocalClient = NewObject<UNakamaRealtimeClient>();
	LocalClient->bIsActive = true;
	TWeakObjectPtr<UNakamaRealtimeClient> WeakThis(LocalClient);

	int32 Fired = 0;
	auto Callback = [WeakThis, &Fired]()
	{
		if (!FNakamaUtils::IsRealtimeClientActive(WeakThis.Get()))
		{
			return;
		}
		++Fired;
	};

	Callback();
	TestEqual(TEXT("fires while the realtime client is alive"), Fired, 1);

	LocalClient->bIsActive = false;
	Callback();
	TestEqual(TEXT("does not fire while inactive"), Fired, 1);
	LocalClient->bIsActive = true;
	Callback();
	TestEqual(TEXT("fires again when reactivated"), Fired, 2);

	LocalClient = nullptr;
	ReleaseAndCollect(WeakThis.Get());

	TestFalse(TEXT("weak pointer is invalid after release"), WeakThis.IsValid());

	Callback();
	TestEqual(TEXT("does not fire after the realtime client is released"), Fired, 2);
	return true;
}

// SendJsonRequest / WebSocket style: resolve weak to strong, touch members only if non-null.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(ClientReleasedMemberAccess, FNakamaTestBase, "Nakama.Base.Lifetime.ClientReleasedMemberAccess", NAKAMA_MODULE_TEST_MASK)
inline bool ClientReleasedMemberAccess::RunTest(const FString& Parameters)
{
	UNakamaClient* LocalClient = NewObject<UNakamaClient>();
	LocalClient->bIsActive = true;
	TWeakObjectPtr<UNakamaClient> WeakThis(LocalClient);

	int32 TouchedMembers = 0;
	auto Callback = [WeakThis, &TouchedMembers]()
	{
		UNakamaClient* Self = WeakThis.Get();
		if (!Self)
		{
			return;
		}
		(void)Self->bIsActive;
		++TouchedMembers;
	};

	Callback();
	TestEqual(TEXT("accesses members while alive"), TouchedMembers, 1);

	LocalClient = nullptr;
	ReleaseAndCollect(WeakThis.Get());

	Callback(); // Self is null -> no member access, no crash
	TestEqual(TEXT("no member access after release"), TouchedMembers, 1);
	return true;
}
