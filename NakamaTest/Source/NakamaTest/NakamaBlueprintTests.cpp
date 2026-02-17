/**
 * Blueprint Async Action Test Suite
 *
 * Tests for NakamaBlueprints module UBlueprintAsyncActionBase subclasses.
 * Each test fires a BP async action, then verifies the server-side effect
 * through the C++ client (which supports lambda callbacks natively).
 *
 * This avoids creating any UObject helpers for delegate binding.
 */

#include "Misc/AutomationTest.h"
#include "NakamaApi.h"
#include "NakamaClientBlueprintLibrary.h"
#include "Misc/Guid.h"
#include "Containers/Ticker.h"

// Delay before verifying server state after a BP action fires.
// This must be long enough for the BP action's HTTP round-trip to complete.
// If the action hasn't finished when the timer fires, RemoveFromRoot() makes
// it eligible for GC while the HTTP callback still holds a raw `this` pointer.
// 1.0s is generous for a local Nakama server (~5-20ms typical RTT).
static constexpr float BP_VERIFY_DELAY = 1.0f;

// Helper: schedule a verification callback after the BP action completes.
// Uses TWeakObjectPtr so that RemoveFromRoot on an already-destroyed action
// is safely skipped. Verification runs before unrooting to maximize the
// window for the action's async work to finish.
static void VerifyAfterDelay(UBlueprintAsyncActionBase* Action, TFunction<void()> VerifyFunc)
{
	TWeakObjectPtr<UBlueprintAsyncActionBase> WeakAction(Action);

	FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateLambda([WeakAction, VerifyFunc = MoveTemp(VerifyFunc)](float) -> bool
		{
			VerifyFunc();
			if (WeakAction.IsValid())
			{
				WeakAction->RemoveFromRoot();
			}
			return false;
		}),
		BP_VERIFY_DELAY
	);
}

// ============================================================================
// HEALTHCHECK TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPHealthcheckSpec, "NakamaTest.BP.Healthcheck",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientRef ClientRef;
	FNakamaSessionPtr Session;
	FNakamaApiConfigPtr Client;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaBPHealthcheckSpec)

const FString FNakamaBPHealthcheckSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaBPHealthcheckSpec::Host = TEXT("127.0.0.1");

void FNakamaBPHealthcheckSpec::Define()
{
	BeforeEach([this]()
	{
		Client = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client->Timeout = 10.0f;
		ClientRef = FNakamaClientRef(Client);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = MakeShared<FNakamaSession>(Result);
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	Describe("Healthcheck", [this]()
	{
		LatentIt("should pass healthcheck", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientHealthcheck::Healthcheck(nullptr, ClientRef, *Session);
			Action->AddToRoot();
			Action->Activate();

			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::Healthcheck(Client, Session,
					[Done]() { Done.Execute(); },
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// AUTHENTICATION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPAuthSpec, "NakamaTest.BP.Auth",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientRef ClientRef;
	FNakamaApiConfigPtr Client;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaBPAuthSpec)

const FString FNakamaBPAuthSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaBPAuthSpec::Host = TEXT("127.0.0.1");

void FNakamaBPAuthSpec::Define()
{
	BeforeEach([this]()
	{
		Client = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client->Timeout = 10.0f;
		ClientRef = FNakamaClientRef(Client);
	});

	Describe("AuthenticateCustom", [this]()
	{
		LatentIt("should authenticate with custom ID", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = GenerateId();

			auto* Action = UNakamaClientAuthenticateCustom::AuthenticateCustom(
				nullptr, ClientRef, Account, true, TEXT(""));
			Action->AddToRoot();
			Action->Activate();

			// Verify: re-auth with create=false should succeed (account was created)
			VerifyAfterDelay(Action, [this, Done, Account]()
			{
				NakamaApi::AuthenticateCustom(Client, Account, false, TEXT(""),
					[this, Done](const FNakamaSession& Result)
					{
						TestTrue("Session has token", !Result.Token.IsEmpty());
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("Re-auth failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("AuthenticateEmail", [this]()
	{
		LatentIt("should authenticate with email", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountEmail Account;
			Account.Email = FString::Printf(TEXT("test_%s@example.com"), *GenerateShortId());
			Account.Password = TEXT("password123!");

			auto* Action = UNakamaClientAuthenticateEmail::AuthenticateEmail(
				nullptr, ClientRef, Account, true, TEXT(""));
			Action->AddToRoot();
			Action->Activate();

			// Verify: re-auth with create=false should succeed
			VerifyAfterDelay(Action, [this, Done, Account]()
			{
				NakamaApi::AuthenticateEmail(Client, Account, false, TEXT(""),
					[this, Done](const FNakamaSession& Result)
					{
						TestTrue("Session has token", !Result.Token.IsEmpty());
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("Re-auth failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("AuthenticateDevice", [this]()
	{
		LatentIt("should authenticate with device ID", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountDevice Account;
			Account.Id = GenerateId();

			auto* Action = UNakamaClientAuthenticateDevice::AuthenticateDevice(
				nullptr, ClientRef, Account, true, TEXT(""));
			Action->AddToRoot();
			Action->Activate();

			// Verify: re-auth with create=false should succeed
			VerifyAfterDelay(Action, [this, Done, Account]()
			{
				NakamaApi::AuthenticateDevice(Client, Account, false, TEXT(""),
					[this, Done](const FNakamaSession& Result)
					{
						TestTrue("Session has token", !Result.Token.IsEmpty());
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("Re-auth failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// SESSION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPSessionSpec, "NakamaTest.BP.Session",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientRef ClientRef;
	FNakamaApiConfigPtr Client;
	FNakamaSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaBPSessionSpec)

const FString FNakamaBPSessionSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaBPSessionSpec::Host = TEXT("127.0.0.1");

void FNakamaBPSessionSpec::Define()
{
	BeforeEach([this]()
	{
		Client = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client->Timeout = 10.0f;
		ClientRef = FNakamaClientRef(Client);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = MakeShared<FNakamaSession>(Result);
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	Describe("SessionRefresh", [this]()
	{
		LatentIt("should refresh session", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientSessionRefresh::SessionRefresh(
				nullptr, ClientRef, Session->RefreshToken, TMap<FString, FString>());
			Action->AddToRoot();
			Action->Activate();

			// Verify: original session token still works for API call
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::GetAccount(Client, Session,
					[this, Done](const FNakamaAccount& Result)
					{
						TestTrue("Account retrieved", !Result.User.Id.IsEmpty());
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("SessionLogout", [this]()
	{
		LatentIt("should logout session", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientSessionLogout::SessionLogout(
				nullptr, ClientRef, *Session, Session->Token, Session->RefreshToken);
			Action->AddToRoot();
			Action->Activate();

			// Verify: action completed without crash; server is still responsive
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::Healthcheck(Client, Session,
					[Done]() { Done.Execute(); },
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// ACCOUNT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPAccountSpec, "NakamaTest.BP.Account",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientRef ClientRef;
	FNakamaApiConfigPtr Client;
	FNakamaSessionPtr Session;
	FString UserId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaBPAccountSpec)

const FString FNakamaBPAccountSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaBPAccountSpec::Host = TEXT("127.0.0.1");

void FNakamaBPAccountSpec::Define()
{
	BeforeEach([this]()
	{
		Client = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client->Timeout = 10.0f;
		ClientRef = FNakamaClientRef(Client);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = MakeShared<FNakamaSession>(Result);
				NakamaApi::GetAccount(Client, Session,
					[this, Done](const FNakamaAccount& AccResult)
					{
						UserId = AccResult.User.Id;
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	Describe("GetAccount", [this]()
	{
		LatentIt("should get account", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientGetAccount::GetAccount(nullptr, ClientRef, *Session);
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++ GetAccount
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::GetAccount(Client, Session,
					[this, Done](const FNakamaAccount& Result)
					{
						TestEqual("User ID matches", Result.User.Id, UserId);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("UpdateAccount", [this]()
	{
		LatentIt("should update and verify display name", [this](const FDoneDelegate& Done)
		{
			FString NewDisplayName = TEXT("BPTestUser");

			auto* Action = UNakamaClientUpdateAccount::UpdateAccount(
				nullptr, ClientRef, *Session,
				TEXT(""), NewDisplayName, TEXT(""), TEXT(""), TEXT(""), TEXT(""));
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++ GetAccount
			VerifyAfterDelay(Action, [this, Done, NewDisplayName]()
			{
				NakamaApi::GetAccount(Client, Session,
					[this, Done, NewDisplayName](const FNakamaAccount& Result)
					{
						TestEqual("Display name updated", Result.User.DisplayName, NewDisplayName);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("GetUsers", [this]()
	{
		LatentIt("should get users by ID", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids = { UserId };
			TArray<FString> Usernames;
			TArray<FString> FacebookIds;

			auto* Action = UNakamaClientGetUsers::GetUsers(
				nullptr, ClientRef, *Session, Ids, Usernames, FacebookIds);
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++ GetUsers
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::GetUsers(Client, Session, { UserId }, {}, {},
					[this, Done](const FNakamaUsers& Result)
					{
						TestTrue("Got at least one user", Result.Users.Num() > 0);
						if (Result.Users.Num() > 0)
						{
							TestEqual("User ID matches", Result.Users[0].Id, UserId);
						}
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("GetUsers failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// FRIENDS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPFriendsSpec, "NakamaTest.BP.Friends",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientRef ClientRef;
	FNakamaApiConfigPtr Client;
	FNakamaSessionPtr Session;
	FString UserId;

	FNakamaApiConfigPtr FriendClient;
	FNakamaSessionPtr FriendSession;
	FString FriendUserId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaBPFriendsSpec)

const FString FNakamaBPFriendsSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaBPFriendsSpec::Host = TEXT("127.0.0.1");

void FNakamaBPFriendsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client->Timeout = 10.0f;
		ClientRef = FNakamaClientRef(Client);

		FriendClient = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		FriendClient->Timeout = 10.0f;
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = MakeShared<FNakamaSession>(Result);
				NakamaApi::GetAccount(Client, Session,
					[this, Done](const FNakamaAccount& AccResult)
					{
						UserId = AccResult.User.Id;

						FNakamaAccountCustom FriendAccount;
						FriendAccount.Id = GenerateId();

						NakamaApi::AuthenticateCustom(FriendClient, FriendAccount, true, TEXT(""),
							[this, Done](const FNakamaSession& FResult)
							{
								FriendSession = MakeShared<FNakamaSession>(FResult);
								NakamaApi::GetAccount(FriendClient, FriendSession,
									[this, Done](const FNakamaAccount& FAccResult)
									{
										FriendUserId = FAccResult.User.Id;
										Done.Execute();
									},
									[this, Done](const FNakamaError& Error)
									{
										AddError(FString::Printf(TEXT("Friend GetAccount failed: %s"), *Error.Message));
										Done.Execute();
									}
								);
							},
							[this, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("Friend auth failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	Describe("AddFriends", [this]()
	{
		LatentIt("should add a friend and verify via list", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids = { FriendUserId };
			TArray<FString> Usernames;

			auto* Action = UNakamaClientAddFriends::AddFriends(
				nullptr, ClientRef, *Session, Ids, Usernames, TEXT(""));
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++ ListFriends
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::ListFriends(Client, Session, 10, 0, TEXT(""),
					[this, Done](const FNakamaFriendList& Result)
					{
						TestTrue("Friend list is not empty", Result.Friends.Num() > 0);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListFriends failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("ListFriends", [this]()
	{
		LatentIt("should list friends after adding one", [this](const FDoneDelegate& Done)
		{
			// Setup: add friend via C++
			NakamaApi::AddFriends(Client, Session, { FriendUserId }, {}, TEXT(""),
				[this, Done]()
				{
					// Fire BP ListFriends
					auto* Action = UNakamaClientListFriends::ListFriends(
						nullptr, ClientRef, *Session, 10, 0, TEXT(""));
					Action->AddToRoot();
					Action->Activate();

					// Verify via C++
					VerifyAfterDelay(Action, [this, Done]()
					{
						NakamaApi::ListFriends(Client, Session, 10, 0, TEXT(""),
							[this, Done](const FNakamaFriendList& Result)
							{
								TestTrue("Friend list has entries", Result.Friends.Num() > 0);
								Done.Execute();
							},
							[this, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("ListFriends failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("AddFriends setup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("BlockFriends", [this]()
	{
		LatentIt("should block a friend", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids = { FriendUserId };
			TArray<FString> Usernames;

			auto* Action = UNakamaClientBlockFriends::BlockFriends(
				nullptr, ClientRef, *Session, Ids, Usernames);
			Action->AddToRoot();
			Action->Activate();

			// Verify: blocked friend appears in friend list with state=3 (blocked)
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::ListFriends(Client, Session, 10, 3, TEXT(""),
					[this, Done](const FNakamaFriendList& Result)
					{
						TestTrue("Blocked friend list has entries", Result.Friends.Num() > 0);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListFriends failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("DeleteFriends", [this]()
	{
		LatentIt("should delete a friend", [this](const FDoneDelegate& Done)
		{
			// Setup: add friend via C++
			NakamaApi::AddFriends(Client, Session, { FriendUserId }, {}, TEXT(""),
				[this, Done]()
				{
					// Fire BP DeleteFriends
					TArray<FString> Ids = { FriendUserId };
					TArray<FString> Usernames;

					auto* Action = UNakamaClientDeleteFriends::DeleteFriends(
						nullptr, ClientRef, *Session, Ids, Usernames);
					Action->AddToRoot();
					Action->Activate();

					// Verify: friend list is now empty
					VerifyAfterDelay(Action, [this, Done]()
					{
						NakamaApi::ListFriends(Client, Session, 10, 0, TEXT(""),
							[this, Done](const FNakamaFriendList& Result)
							{
								TestEqual("Friend list is empty", Result.Friends.Num(), 0);
								Done.Execute();
							},
							[this, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("ListFriends failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("AddFriends setup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// GROUPS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPGroupsSpec, "NakamaTest.BP.Groups",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientRef ClientRef;
	FNakamaApiConfigPtr Client;
	FNakamaSessionPtr Session;
	FString UserId;

	FNakamaClientRef ClientRef2;
	FNakamaApiConfigPtr Client2;
	FNakamaSessionPtr Session2;
	FString UserId2;

	FString GroupId;
	FString GroupName;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaBPGroupsSpec)

const FString FNakamaBPGroupsSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaBPGroupsSpec::Host = TEXT("127.0.0.1");

void FNakamaBPGroupsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client->Timeout = 10.0f;
		ClientRef = FNakamaClientRef(Client);

		Client2 = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client2->Timeout = 10.0f;
		ClientRef2 = FNakamaClientRef(Client2);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account1;
		Account1.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account1, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = MakeShared<FNakamaSession>(Result);
				NakamaApi::GetAccount(Client, Session,
					[this, Done](const FNakamaAccount& AccResult)
					{
						UserId = AccResult.User.Id;

						FNakamaAccountCustom Account2;
						Account2.Id = GenerateId();

						NakamaApi::AuthenticateCustom(Client2, Account2, true, TEXT(""),
							[this, Done](const FNakamaSession& Result2)
							{
								Session2 = MakeShared<FNakamaSession>(Result2);
								NakamaApi::GetAccount(Client2, Session2,
									[this, Done](const FNakamaAccount& AccResult2)
									{
										UserId2 = AccResult2.User.Id;

										// Create a group as user1
										GroupName = FString::Printf(TEXT("bp_grp_%s"), *GenerateShortId());
										NakamaApi::CreateGroup(Client, Session, GroupName, TEXT("Test group"),
											TEXT("en"), TEXT(""), true, 100,
											[this, Done](const FNakamaGroup& Group)
											{
												GroupId = Group.Id;
												Done.Execute();
											},
											[this, Done](const FNakamaError& Error)
											{
												AddError(FString::Printf(TEXT("CreateGroup failed: %s"), *Error.Message));
												Done.Execute();
											}
										);
									},
									[this, Done](const FNakamaError& Error)
									{
										AddError(FString::Printf(TEXT("GetAccount2 failed: %s"), *Error.Message));
										Done.Execute();
									}
								);
							},
							[this, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("Auth2 failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	Describe("CreateGroup", [this]()
	{
		LatentIt("should create a group", [this](const FDoneDelegate& Done)
		{
			FString NewGroupName = FString::Printf(TEXT("bp_new_%s"), *GenerateShortId());

			auto* Action = UNakamaClientCreateGroup::CreateGroup(
				nullptr, ClientRef, *Session,
				NewGroupName, TEXT("Test group"), TEXT("en"), TEXT(""), true, 100);
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++ ListGroups (open=true to match our created group)
			VerifyAfterDelay(Action, [this, Done, NewGroupName]()
			{
				NakamaApi::ListGroups(Client, Session,
					TEXT(""), TEXT(""), 100, TEXT(""), 0, true,
					[this, Done, NewGroupName](const FNakamaGroupList& Result)
					{
						bool Found = false;
						for (const auto& Group : Result.Groups)
						{
							if (Group.Name == NewGroupName)
							{
								Found = true;
								break;
							}
						}
						TestTrue("Created group found in list", Found);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListGroups failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("UpdateGroup", [this]()
	{
		LatentIt("should update a group", [this](const FDoneDelegate& Done)
		{
			FString NewDesc = TEXT("Updated description");

			auto* Action = UNakamaClientUpdateGroup::UpdateGroup(
				nullptr, ClientRef, *Session,
				GroupId, GroupName, NewDesc, TEXT("en"), TEXT(""), true);
			Action->AddToRoot();
			Action->Activate();

			// Verify: group still exists and is accessible
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::ListGroupUsers(Client, Session, GroupId, 10, 0, TEXT(""),
					[this, Done](const FNakamaGroupUserList& Result)
					{
						TestTrue("Group still has users after update", Result.GroupUsers.Num() > 0);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("DeleteGroup", [this]()
	{
		LatentIt("should delete a group", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientDeleteGroup::DeleteGroup(
				nullptr, ClientRef, *Session, GroupId);
			Action->AddToRoot();
			Action->Activate();

			// Verify: group no longer in user's groups
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::ListUserGroups(Client, Session, UserId, 100, 0, TEXT(""),
					[this, Done](const FNakamaUserGroupList& Result)
					{
						bool Found = false;
						for (const auto& UG : Result.UserGroups)
						{
							if (UG.Group.Id == GroupId)
							{
								Found = true;
								break;
							}
						}
						TestFalse("Deleted group not in user groups", Found);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListUserGroups failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("ListGroups", [this]()
	{
		LatentIt("should list groups", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientListGroups::ListGroups(
				nullptr, ClientRef, *Session,
				TEXT(""), TEXT(""), 100, TEXT(""), 0, true);
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++ ListGroups
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::ListGroups(Client, Session, TEXT(""), TEXT(""), 100, TEXT(""), 0, true,
					[this, Done](const FNakamaGroupList& Result)
					{
						TestTrue("Group list has entries", Result.Groups.Num() > 0);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListGroups failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("JoinGroup", [this]()
	{
		LatentIt("should join a group", [this](const FDoneDelegate& Done)
		{
			// User2 fires BP JoinGroup on user1's open group
			auto* Action = UNakamaClientJoinGroup::JoinGroup(
				nullptr, ClientRef2, *Session2, GroupId);
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++ ListGroupUsers
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::ListGroupUsers(Client, Session, GroupId, 10, 0, TEXT(""),
					[this, Done](const FNakamaGroupUserList& Result)
					{
						TestTrue("Group has at least 2 users", Result.GroupUsers.Num() >= 2);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("AddGroupUsers", [this]()
	{
		LatentIt("should add users to a group", [this](const FDoneDelegate& Done)
		{
			TArray<FString> UserIds = { UserId2 };

			auto* Action = UNakamaClientAddGroupUsers::AddGroupUsers(
				nullptr, ClientRef, *Session, GroupId, UserIds);
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++ ListGroupUsers
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::ListGroupUsers(Client, Session, GroupId, 10, 0, TEXT(""),
					[this, Done](const FNakamaGroupUserList& Result)
					{
						TestTrue("Group has at least 2 users", Result.GroupUsers.Num() >= 2);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("KickGroupUsers", [this]()
	{
		LatentIt("should kick users from a group", [this](const FDoneDelegate& Done)
		{
			// Setup: add user2 to group via C++
			NakamaApi::AddGroupUsers(Client, Session, GroupId, { UserId2 },
				[this, Done]()
				{
					// Fire BP KickGroupUsers
					TArray<FString> UserIds = { UserId2 };

					auto* Action = UNakamaClientKickGroupUsers::KickGroupUsers(
						nullptr, ClientRef, *Session, GroupId, UserIds);
					Action->AddToRoot();
					Action->Activate();

					// Verify user2 is no longer in group
					VerifyAfterDelay(Action, [this, Done]()
					{
						NakamaApi::ListGroupUsers(Client, Session, GroupId, 10, 0, TEXT(""),
							[this, Done](const FNakamaGroupUserList& Result)
							{
								bool Found = false;
								for (const auto& GU : Result.GroupUsers)
								{
									if (GU.User.Id == UserId2)
									{
										Found = true;
										break;
									}
								}
								TestFalse("Kicked user not in group", Found);
								Done.Execute();
							},
							[this, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("AddGroupUsers setup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("PromoteGroupUsers", [this]()
	{
		LatentIt("should promote users in a group", [this](const FDoneDelegate& Done)
		{
			// Setup: add user2 to group via C++
			NakamaApi::AddGroupUsers(Client, Session, GroupId, { UserId2 },
				[this, Done]()
				{
					// Fire BP PromoteGroupUsers
					TArray<FString> UserIds = { UserId2 };

					auto* Action = UNakamaClientPromoteGroupUsers::PromoteGroupUsers(
						nullptr, ClientRef, *Session, GroupId, UserIds);
					Action->AddToRoot();
					Action->Activate();

					// Verify: user2 is still in group (promotion doesn't remove)
					VerifyAfterDelay(Action, [this, Done]()
					{
						NakamaApi::ListGroupUsers(Client, Session, GroupId, 10, 0, TEXT(""),
							[this, Done](const FNakamaGroupUserList& Result)
							{
								bool Found = false;
								for (const auto& GU : Result.GroupUsers)
								{
									if (GU.User.Id == UserId2)
									{
										Found = true;
										break;
									}
								}
								TestTrue("Promoted user still in group", Found);
								Done.Execute();
							},
							[this, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("AddGroupUsers setup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("LeaveGroup", [this]()
	{
		LatentIt("should leave a group", [this](const FDoneDelegate& Done)
		{
			// Setup: user2 joins group via C++
			NakamaApi::JoinGroup(Client2, Session2, GroupId,
				[this, Done]()
				{
					// Fire BP LeaveGroup as user2
					auto* Action = UNakamaClientLeaveGroup::LeaveGroup(
						nullptr, ClientRef2, *Session2, GroupId);
					Action->AddToRoot();
					Action->Activate();

					// Verify user2 no longer in group
					VerifyAfterDelay(Action, [this, Done]()
					{
						NakamaApi::ListGroupUsers(Client, Session, GroupId, 10, 0, TEXT(""),
							[this, Done](const FNakamaGroupUserList& Result)
							{
								bool Found = false;
								for (const auto& GU : Result.GroupUsers)
								{
									if (GU.User.Id == UserId2)
									{
										Found = true;
										break;
									}
								}
								TestFalse("User2 left the group", Found);
								Done.Execute();
							},
							[this, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("JoinGroup setup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("ListGroupUsers", [this]()
	{
		LatentIt("should list group users", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientListGroupUsers::ListGroupUsers(
				nullptr, ClientRef, *Session, GroupId, 10, 0, TEXT(""));
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::ListGroupUsers(Client, Session, GroupId, 10, 0, TEXT(""),
					[this, Done](const FNakamaGroupUserList& Result)
					{
						TestTrue("Group has at least one user (owner)", Result.GroupUsers.Num() > 0);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("ListUserGroups", [this]()
	{
		LatentIt("should list user groups", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientListUserGroups::ListUserGroups(
				nullptr, ClientRef, *Session, UserId, 10, 0, TEXT(""));
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::ListUserGroups(Client, Session, UserId, 10, 0, TEXT(""),
					[this, Done](const FNakamaUserGroupList& Result)
					{
						TestTrue("User has at least one group", Result.UserGroups.Num() > 0);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListUserGroups failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// STORAGE TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPStorageSpec, "NakamaTest.BP.Storage",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientRef ClientRef;
	FNakamaApiConfigPtr Client;
	FNakamaSessionPtr Session;
	FString UserId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaBPStorageSpec)

const FString FNakamaBPStorageSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaBPStorageSpec::Host = TEXT("127.0.0.1");

void FNakamaBPStorageSpec::Define()
{
	BeforeEach([this]()
	{
		Client = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client->Timeout = 10.0f;
		ClientRef = FNakamaClientRef(Client);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = MakeShared<FNakamaSession>(Result);
				NakamaApi::GetAccount(Client, Session,
					[this, Done](const FNakamaAccount& AccResult)
					{
						UserId = AccResult.User.Id;
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	Describe("WriteStorageObjects", [this]()
	{
		LatentIt("should write and read back storage objects", [this](const FDoneDelegate& Done)
		{
			FString Key = FString::Printf(TEXT("key_%s"), *GenerateId());

			FNakamaWriteStorageObject Obj;
			Obj.Collection = TEXT("bp_test");
			Obj.Key = Key;
			Obj.Value = TEXT("{\"score\":42}");
			Obj.PermissionRead = 1;
			Obj.PermissionWrite = 1;

			TArray<FNakamaWriteStorageObject> Objects = { Obj };

			auto* Action = UNakamaClientWriteStorageObjects::WriteStorageObjects(
				nullptr, ClientRef, *Session, Objects);
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++ ReadStorageObjects
			VerifyAfterDelay(Action, [this, Done, Key]()
			{
				FNakamaReadStorageObjectId ReadId;
				ReadId.Collection = TEXT("bp_test");
				ReadId.Key = Key;
				ReadId.UserId = UserId;

				NakamaApi::ReadStorageObjects(Client, Session, { ReadId },
					[this, Done](const FNakamaStorageObjects& Result)
					{
						TestTrue("Got at least one object", Result.Objects.Num() > 0);
						if (Result.Objects.Num() > 0)
						{
							TestTrue("Value contains score", Result.Objects[0].Value.Contains(TEXT("42")));
						}
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ReadStorage failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});

		LatentIt("should write then verify value content", [this](const FDoneDelegate& Done)
		{
			FString Key = FString::Printf(TEXT("key_%s"), *GenerateId());

			FNakamaWriteStorageObject Obj;
			Obj.Collection = TEXT("bp_test");
			Obj.Key = Key;
			Obj.Value = TEXT("{\"level\":99,\"name\":\"hero\"}");
			Obj.PermissionRead = 1;
			Obj.PermissionWrite = 1;

			TArray<FNakamaWriteStorageObject> Objects = { Obj };

			auto* Action = UNakamaClientWriteStorageObjects::WriteStorageObjects(
				nullptr, ClientRef, *Session, Objects);
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++ ReadStorageObjects
			VerifyAfterDelay(Action, [this, Done, Key]()
			{
				FNakamaReadStorageObjectId ReadId;
				ReadId.Collection = TEXT("bp_test");
				ReadId.Key = Key;
				ReadId.UserId = UserId;

				NakamaApi::ReadStorageObjects(Client, Session, { ReadId },
					[this, Done](const FNakamaStorageObjects& Result)
					{
						TestTrue("Got at least one object", Result.Objects.Num() > 0);
						if (Result.Objects.Num() > 0)
						{
							TestTrue("Value contains level", Result.Objects[0].Value.Contains(TEXT("99")));
							TestTrue("Value contains name", Result.Objects[0].Value.Contains(TEXT("hero")));
						}
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ReadStorage failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("ReadStorageObjects", [this]()
	{
		LatentIt("should read storage objects", [this](const FDoneDelegate& Done)
		{
			FString Key = FString::Printf(TEXT("key_%s"), *GenerateId());

			// Setup: write via C++
			FNakamaWriteStorageObject Obj;
			Obj.Collection = TEXT("bp_test");
			Obj.Key = Key;
			Obj.Value = TEXT("{\"data\":true}");
			Obj.PermissionRead = 1;
			Obj.PermissionWrite = 1;

			NakamaApi::WriteStorageObjects(Client, Session, { Obj },
				[this, Done, Key](const FNakamaStorageObjectAcks& Acks)
				{
					// Fire BP ReadStorageObjects
					FNakamaReadStorageObjectId ReadId;
					ReadId.Collection = TEXT("bp_test");
					ReadId.Key = Key;
					ReadId.UserId = UserId;

					auto* Action = UNakamaClientReadStorageObjects::ReadStorageObjects(
						nullptr, ClientRef, *Session, { ReadId });
					Action->AddToRoot();
					Action->Activate();

					// Verify via C++ that object exists
					VerifyAfterDelay(Action, [this, Done, Key]()
					{
						FNakamaReadStorageObjectId VerifyId;
						VerifyId.Collection = TEXT("bp_test");
						VerifyId.Key = Key;
						VerifyId.UserId = UserId;

						NakamaApi::ReadStorageObjects(Client, Session, { VerifyId },
							[this, Done](const FNakamaStorageObjects& Result)
							{
								TestTrue("Object still readable", Result.Objects.Num() > 0);
								Done.Execute();
							},
							[this, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("ReadStorage failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("WriteStorage setup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("ListStorageObjects", [this]()
	{
		LatentIt("should list storage objects", [this](const FDoneDelegate& Done)
		{
			// Setup: write an object via C++
			FNakamaWriteStorageObject Obj;
			Obj.Collection = TEXT("bp_list_test");
			Obj.Key = FString::Printf(TEXT("key_%s"), *GenerateId());
			Obj.Value = TEXT("{\"x\":1}");
			Obj.PermissionRead = 1;
			Obj.PermissionWrite = 1;

			NakamaApi::WriteStorageObjects(Client, Session, { Obj },
				[this, Done](const FNakamaStorageObjectAcks& Acks)
				{
					// Fire BP ListStorageObjects
					auto* Action = UNakamaClientListStorageObjects::ListStorageObjects(
						nullptr, ClientRef, *Session, UserId, TEXT("bp_list_test"), 10, TEXT(""));
					Action->AddToRoot();
					Action->Activate();

					// Verify via C++
					VerifyAfterDelay(Action, [this, Done]()
					{
						NakamaApi::ListStorageObjects(Client, Session, UserId, TEXT("bp_list_test"), 10, TEXT(""),
							[this, Done](const FNakamaStorageObjectList& Result)
							{
								TestTrue("Listed at least one object", Result.Objects.Num() > 0);
								Done.Execute();
							},
							[this, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("ListStorage failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("WriteStorage setup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("DeleteStorageObjects", [this]()
	{
		LatentIt("should delete storage objects", [this](const FDoneDelegate& Done)
		{
			FString Key = FString::Printf(TEXT("key_%s"), *GenerateId());

			// Setup: write an object via C++
			FNakamaWriteStorageObject Obj;
			Obj.Collection = TEXT("bp_del_test");
			Obj.Key = Key;
			Obj.Value = TEXT("{\"del\":true}");
			Obj.PermissionRead = 1;
			Obj.PermissionWrite = 1;

			NakamaApi::WriteStorageObjects(Client, Session, { Obj },
				[this, Done, Key](const FNakamaStorageObjectAcks& Acks)
				{
					// Fire BP DeleteStorageObjects
					FNakamaDeleteStorageObjectId DelId;
					DelId.Collection = TEXT("bp_del_test");
					DelId.Key = Key;
					DelId.Version = Acks.Acks.Num() > 0 ? Acks.Acks[0].Version : TEXT("");

					auto* Action = UNakamaClientDeleteStorageObjects::DeleteStorageObjects(
						nullptr, ClientRef, *Session, { DelId });
					Action->AddToRoot();
					Action->Activate();

					// Verify: object is gone
					VerifyAfterDelay(Action, [this, Done, Key]()
					{
						FNakamaReadStorageObjectId ReadId;
						ReadId.Collection = TEXT("bp_del_test");
						ReadId.Key = Key;
						ReadId.UserId = UserId;

						NakamaApi::ReadStorageObjects(Client, Session, { ReadId },
							[this, Done](const FNakamaStorageObjects& Result)
							{
								TestEqual("Object deleted", Result.Objects.Num(), 0);
								Done.Execute();
							},
							[this, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("ReadStorage failed: %s"), *Error.Message));
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("WriteStorage setup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// LINK / UNLINK TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPLinkSpec, "NakamaTest.BP.Link",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientRef ClientRef;
	FNakamaApiConfigPtr Client;
	FNakamaSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaBPLinkSpec)

const FString FNakamaBPLinkSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaBPLinkSpec::Host = TEXT("127.0.0.1");

void FNakamaBPLinkSpec::Define()
{
	BeforeEach([this]()
	{
		Client = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client->Timeout = 10.0f;
		ClientRef = FNakamaClientRef(Client);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = MakeShared<FNakamaSession>(Result);
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	Describe("LinkCustom", [this]()
	{
		LatentIt("should link a custom ID", [this](const FDoneDelegate& Done)
		{
			FString NewId = GenerateId();

			auto* Action = UNakamaClientLinkCustom::LinkCustom(
				nullptr, ClientRef, *Session, NewId, TMap<FString, FString>());
			Action->AddToRoot();
			Action->Activate();

			// Verify: can authenticate with the linked ID
			VerifyAfterDelay(Action, [this, Done, NewId]()
			{
				FNakamaAccountCustom LinkedAccount;
				LinkedAccount.Id = NewId;

				NakamaApi::AuthenticateCustom(Client, LinkedAccount, false, TEXT(""),
					[this, Done](const FNakamaSession& Result)
					{
						TestTrue("Linked custom auth succeeded", !Result.Token.IsEmpty());
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("Linked auth failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("UnlinkCustom", [this]()
	{
		LatentIt("should unlink a custom ID", [this](const FDoneDelegate& Done)
		{
			FString ExtraId = GenerateId();
			FString DeviceId = GenerateId();

			// Setup: link a device first (so there's a fallback auth method),
			// then link an extra custom ID (replaces original)
			NakamaApi::LinkDevice(Client, Session, DeviceId, TMap<FString, FString>(),
				[this, Done, ExtraId]()
				{
					NakamaApi::LinkCustom(Client, Session, ExtraId, TMap<FString, FString>(),
						[this, Done, ExtraId]()
						{
							// Fire BP UnlinkCustom
							auto* Action = UNakamaClientUnlinkCustom::UnlinkCustom(
								nullptr, ClientRef, *Session, ExtraId, TMap<FString, FString>());
							Action->AddToRoot();
							Action->Activate();

							// Verify: can no longer auth with the unlinked ID
							VerifyAfterDelay(Action, [this, Done, ExtraId]()
							{
								FNakamaAccountCustom UnlinkedAccount;
								UnlinkedAccount.Id = ExtraId;

								NakamaApi::AuthenticateCustom(Client, UnlinkedAccount, false, TEXT(""),
									[this, Done](const FNakamaSession& Result)
									{
										AddError(TEXT("Auth should have failed for unlinked ID"));
										Done.Execute();
									},
									[this, Done](const FNakamaError& Error)
									{
										// Expected: auth fails because ID is unlinked
										TestTrue("Unlinked ID auth rejected", true);
										Done.Execute();
									}
								);
							});
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("LinkCustom setup failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("LinkDevice setup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("LinkDevice", [this]()
	{
		LatentIt("should link a device ID", [this](const FDoneDelegate& Done)
		{
			FString DeviceId = GenerateId();

			auto* Action = UNakamaClientLinkDevice::LinkDevice(
				nullptr, ClientRef, *Session, DeviceId, TMap<FString, FString>());
			Action->AddToRoot();
			Action->Activate();

			// Verify: can authenticate with the linked device ID
			VerifyAfterDelay(Action, [this, Done, DeviceId]()
			{
				FNakamaAccountDevice LinkedDevice;
				LinkedDevice.Id = DeviceId;

				NakamaApi::AuthenticateDevice(Client, LinkedDevice, false, TEXT(""),
					[this, Done](const FNakamaSession& Result)
					{
						TestTrue("Linked device auth succeeded", !Result.Token.IsEmpty());
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("Linked device auth failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("UnlinkDevice", [this]()
	{
		LatentIt("should unlink a device ID", [this](const FDoneDelegate& Done)
		{
			FString DeviceId = GenerateId();

			// Setup: link device via C++
			NakamaApi::LinkDevice(Client, Session, DeviceId, TMap<FString, FString>(),
				[this, Done, DeviceId]()
				{
					// Fire BP UnlinkDevice
					auto* Action = UNakamaClientUnlinkDevice::UnlinkDevice(
						nullptr, ClientRef, *Session, DeviceId, TMap<FString, FString>());
					Action->AddToRoot();
					Action->Activate();

					// Verify: can no longer auth with the unlinked device
					VerifyAfterDelay(Action, [this, Done, DeviceId]()
					{
						FNakamaAccountDevice UnlinkedDevice;
						UnlinkedDevice.Id = DeviceId;

						NakamaApi::AuthenticateDevice(Client, UnlinkedDevice, false, TEXT(""),
							[this, Done](const FNakamaSession& Result)
							{
								AddError(TEXT("Auth should have failed for unlinked device"));
								Done.Execute();
							},
							[this, Done](const FNakamaError& Error)
							{
								TestTrue("Unlinked device auth rejected", true);
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("LinkDevice setup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("LinkEmail", [this]()
	{
		LatentIt("should link an email", [this](const FDoneDelegate& Done)
		{
			FString Email = FString::Printf(TEXT("link_%s@example.com"), *GenerateShortId());
			FString Password = TEXT("password123!");

			auto* Action = UNakamaClientLinkEmail::LinkEmail(
				nullptr, ClientRef, *Session, Email, Password, TMap<FString, FString>());
			Action->AddToRoot();
			Action->Activate();

			// Verify: can authenticate with the linked email
			VerifyAfterDelay(Action, [this, Done, Email, Password]()
			{
				FNakamaAccountEmail LinkedEmail;
				LinkedEmail.Email = Email;
				LinkedEmail.Password = Password;

				NakamaApi::AuthenticateEmail(Client, LinkedEmail, false, TEXT(""),
					[this, Done](const FNakamaSession& Result)
					{
						TestTrue("Linked email auth succeeded", !Result.Token.IsEmpty());
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("Linked email auth failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});

	Describe("UnlinkEmail", [this]()
	{
		LatentIt("should unlink an email", [this](const FDoneDelegate& Done)
		{
			FString Email = FString::Printf(TEXT("unlink_%s@example.com"), *GenerateShortId());
			FString Password = TEXT("password123!");

			// Setup: link email via C++
			NakamaApi::LinkEmail(Client, Session, Email, Password, TMap<FString, FString>(),
				[this, Done, Email, Password]()
				{
					// Fire BP UnlinkEmail
					auto* Action = UNakamaClientUnlinkEmail::UnlinkEmail(
						nullptr, ClientRef, *Session, Email, Password, TMap<FString, FString>());
					Action->AddToRoot();
					Action->Activate();

					// Verify: can no longer auth with the unlinked email
					VerifyAfterDelay(Action, [this, Done, Email, Password]()
					{
						FNakamaAccountEmail UnlinkedEmail;
						UnlinkedEmail.Email = Email;
						UnlinkedEmail.Password = Password;

						NakamaApi::AuthenticateEmail(Client, UnlinkedEmail, false, TEXT(""),
							[this, Done](const FNakamaSession& Result)
							{
								AddError(TEXT("Auth should have failed for unlinked email"));
								Done.Execute();
							},
							[this, Done](const FNakamaError& Error)
							{
								TestTrue("Unlinked email auth rejected", true);
								Done.Execute();
							}
						);
					});
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("LinkEmail setup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// NOTIFICATIONS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPNotificationsSpec, "NakamaTest.BP.Notifications",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientRef ClientRef;
	FNakamaApiConfigPtr Client;
	FNakamaSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaBPNotificationsSpec)

const FString FNakamaBPNotificationsSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaBPNotificationsSpec::Host = TEXT("127.0.0.1");

void FNakamaBPNotificationsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client->Timeout = 10.0f;
		ClientRef = FNakamaClientRef(Client);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = MakeShared<FNakamaSession>(Result);
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	Describe("ListNotifications", [this]()
	{
		LatentIt("should list notifications", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientListNotifications::ListNotifications(
				nullptr, ClientRef, *Session, 100, TEXT(""));
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::ListNotifications(Client, Session, 100, TEXT(""),
					[this, Done](const FNakamaNotificationList& Result)
					{
						// Fresh account has no notifications; just verify no error
						TestTrue("Notification list call succeeded", true);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListNotifications failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// MATCHES TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPMatchesSpec, "NakamaTest.BP.Matches",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientRef ClientRef;
	FNakamaApiConfigPtr Client;
	FNakamaSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaBPMatchesSpec)

const FString FNakamaBPMatchesSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaBPMatchesSpec::Host = TEXT("127.0.0.1");

void FNakamaBPMatchesSpec::Define()
{
	BeforeEach([this]()
	{
		Client = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client->Timeout = 10.0f;
		ClientRef = FNakamaClientRef(Client);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = MakeShared<FNakamaSession>(Result);
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	Describe("ListMatches", [this]()
	{
		LatentIt("should list matches", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientListMatches::ListMatches(
				nullptr, ClientRef, *Session, 10, false, TEXT(""), 0, 100, TEXT(""));
			Action->AddToRoot();
			Action->Activate();

			// Verify via C++
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::ListMatches(Client, Session, 10, false, TEXT(""), 0, 100, TEXT(""),
					[this, Done](const FNakamaMatchList& Result)
					{
						TestTrue("ListMatches call succeeded", true);
						Done.Execute();
					},
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("ListMatches failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}

// ============================================================================
// EVENTS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPEventsSpec, "NakamaTest.BP.Events",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaClientRef ClientRef;
	FNakamaApiConfigPtr Client;
	FNakamaSessionPtr Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaBPEventsSpec)

const FString FNakamaBPEventsSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaBPEventsSpec::Host = TEXT("127.0.0.1");

void FNakamaBPEventsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
		Client->Timeout = 10.0f;
		ClientRef = FNakamaClientRef(Client);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		NakamaApi::AuthenticateCustom(Client, Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = MakeShared<FNakamaSession>(Result);
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	Describe("Event", [this]()
	{
		LatentIt("should send an event", [this](const FDoneDelegate& Done)
		{
			TMap<FString, FString> Properties;
			Properties.Add(TEXT("key1"), TEXT("value1"));

			auto* Action = UNakamaClientEvent::Event(
				nullptr, ClientRef, *Session, TEXT("bp_test_event"), TEXT(""), false, Properties);
			Action->AddToRoot();
			Action->Activate();

			// Verify: server is still healthy after event
			VerifyAfterDelay(Action, [this, Done]()
			{
				NakamaApi::Healthcheck(Client, Session,
					[Done]() { Done.Execute(); },
					[this, Done](const FNakamaError& Error)
					{
						AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Error.Message));
						Done.Execute();
					}
				);
			});
		});
	});
}
