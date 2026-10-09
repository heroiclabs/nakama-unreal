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

// Models the real async RPC ordering: a slow RPC is in flight, the owning client
// is released, then the response arrives. Mirrors the WeakThis guard shipped in
// UNakamaClient::SendJsonRequest's OnProcessRequestComplete lambda - a late
// response with a dead client must resolve to the "client gone" path and never
// dereference a dangling 'this' nor invoke the user's success callback.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(ClientReleasedDeferredRPCCallback, FNakamaTestBase, "Nakama.Base.Lifetime.ClientReleasedDeferredRPCCallback", NAKAMA_MODULE_TEST_MASK)
inline bool ClientReleasedDeferredRPCCallback::RunTest(const FString& Parameters)
{
	UNakamaClient* LocalClient = NewObject<UNakamaClient>();
	LocalClient->bIsActive = true;
	TWeakObjectPtr<UNakamaClient> WeakThis(LocalClient);

	int32 SuccessFired = 0;
	int32 FailurePath = 0;

	// The user's success callback. Touches a client member so a dangling deref
	// would surface under ASan/GC-validation if the guard ever let it run.
	auto UserSuccess = [WeakThis, &SuccessFired]()
	{
		(void)WeakThis.Get()->bIsActive;
		++SuccessFired;
	};

	// The deferred HTTP completion, mirroring SendJsonRequest's guard exactly:
	// resolve the weak client to a strong pointer and only deliver the response
	// when it is still valid; a null resolve is the "client gone" terminal path.
	auto DeliverResponse = [WeakThis, UserSuccess, &FailurePath]()
	{
		if (WeakThis.Get())
		{
			UserSuccess();
		}
		else
		{
			++FailurePath; // client gone -> terminal failure, no user callback
		}
	};

	// Positive control: response arrives while the client is alive.
	DeliverResponse();
	TestEqual(TEXT("success callback fires when the response beats release"), SuccessFired, 1);
	TestEqual(TEXT("no failure path while alive"), FailurePath, 0);

	// Now the slow-RPC scenario: free the caller before the response returns.
	LocalClient = nullptr;
	ReleaseAndCollect(WeakThis.Get());
	TestFalse(TEXT("weak pointer is invalid after release"), WeakThis.IsValid());

	// The response "returns" late, after the owning UObject was released.
	DeliverResponse(); // must not dereference a dangling pointer

	TestEqual(TEXT("success callback does not fire after release"), SuccessFired, 1);
	TestEqual(TEXT("late response routes to the client-gone path"), FailurePath, 1);
	return true;
}
