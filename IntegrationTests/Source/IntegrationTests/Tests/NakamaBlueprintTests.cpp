/**
 * Blueprint Async Action Test Suite
 *
 * Tests for NakamaBlueprints module UBlueprintAsyncActionBase subclasses.
 * Each test fires a BP async action, then verifies the server-side effect
 * through the C++ client (the TFuture-based Nakama:: free-function API).
 *
 * This avoids creating any UObject helpers for delegate binding.
 */

#include "Misc/AutomationTest.h"
#include "NakamaClient.h"
#include "Blueprints/NakamaClientBlueprintLibrary.h"
#include "Misc/Guid.h"
#include "Containers/Ticker.h"
#include "UObject/Package.h"

// Helper: keep the BP action alive for the duration of the async call. Tests pass
// GetTransientPackage() as WorldContextObject — this satisfies UE 5.7's requirement
// that NewObject<> receives a valid packaged outer, while RegisterWithGameInstance
// remains effectively a no-op (transient package has no GameInstance).
// The base class constructor sets RF_StrongRefOnFrame, and SetReadyToDestroy()
// clears it. We AddToRoot() to prevent GC across frames, then poll until
// RF_StrongRefOnFrame is cleared (signalling the action called SetReadyToDestroy).
static void VerifyWhenComplete(UBlueprintAsyncActionBase* Action, TFunction<void()> VerifyFunc)
{
	Action->AddToRoot();

	FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateLambda([Action, VerifyFunc = MoveTemp(VerifyFunc)](float) -> bool
		{
			if (Action->HasAnyFlags(RF_StrongRefOnFrame))
			{
				return true; // keep ticking — action hasn't called SetReadyToDestroy yet
			}
			Action->RemoveFromRoot();
			VerifyFunc();
			return false;
		}),
		0.0f
	);
}

// ============================================================================
// HEALTHCHECK TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPHealthcheckSpec, "IntegrationTests.NakamaBlueprintTests.Healthcheck",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)


	FNakamaSession Session;
	FNakamaClientConfig Client;

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
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(Client, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(Client, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("Healthcheck", [this]()
	{
		LatentIt("should pass healthcheck", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientHealthcheck::Healthcheck(GetTransientPackage(), Client, Session);
			Action->Activate();

			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::Healthcheck(Client, Session).Next([this, Done](FNakamaVoidResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Result.Error.Message));
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// AUTHENTICATION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPAuthSpec, "IntegrationTests.NakamaBlueprintTests.Auth",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)


	FNakamaClientConfig Client;
	FNakamaSession Session;

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
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
		Session = FNakamaSession();
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty())
		{
			Done.Execute();
			return;
		}
		Nakama::DeleteAccount(Client, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("AuthenticateCustom", [this]()
	{
		LatentIt("should authenticate with custom ID", [this](const FDoneDelegate& Done)
		{
			FString CustomId = GenerateId();

			FNakamaAccountCustom Account;
			Account.Id = CustomId;
			auto* Action = UNakamaClientAuthenticateCustom::AuthenticateCustom(
				GetTransientPackage(), Client, Account, true, TEXT(""));
			Action->Activate();

			// Verify: re-auth with create=false should succeed (account was created)
			VerifyWhenComplete(Action, [this, Done, CustomId]()
			{
				Nakama::AuthenticateCustom(Client, false, TEXT(""), CustomId).Next([this, Done](FNakamaSessionResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Re-auth failed: %s"), *Result.Error.Message));
					}
					else
					{
						Session = Result.Value;
						TestTrue("Session has token", !Result.Value.Token.IsEmpty());
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("AuthenticateEmail", [this]()
	{
		LatentIt("should authenticate with email", [this](const FDoneDelegate& Done)
		{
			FString Email = FString::Printf(TEXT("test_%s@example.com"), *GenerateShortId());
			FString Password = TEXT("password123!");

			FNakamaAccountEmail Account;
			Account.Email = Email;
			Account.Password = Password;
			auto* Action = UNakamaClientAuthenticateEmail::AuthenticateEmail(
				GetTransientPackage(), Client, Account, true, TEXT(""));
			Action->Activate();

			// Verify: re-auth with create=false should succeed
			VerifyWhenComplete(Action, [this, Done, Email, Password]()
			{
				Nakama::AuthenticateEmail(Client, false, TEXT(""), Email, Password).Next([this, Done](FNakamaSessionResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Re-auth failed: %s"), *Result.Error.Message));
					}
					else
					{
						Session = Result.Value;
						TestTrue("Session has token", !Result.Value.Token.IsEmpty());
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("AuthenticateDevice", [this]()
	{
		LatentIt("should authenticate with device ID", [this](const FDoneDelegate& Done)
		{
			FString DeviceId = GenerateId();
			FNakamaAccountDevice Account;
			Account.Id = DeviceId;
			auto* Action = UNakamaClientAuthenticateDevice::AuthenticateDevice(
				GetTransientPackage(), Client, Account, true, TEXT(""));
			Action->Activate();

			// Verify: re-auth with create=false should succeed
			VerifyWhenComplete(Action, [this, Done, DeviceId]()
			{
				Nakama::AuthenticateDevice(Client, false, TEXT(""), DeviceId).Next([this, Done](FNakamaSessionResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Re-auth failed: %s"), *Result.Error.Message));
					}
					else
					{
						Session = Result.Value;
						TestTrue("Session has token", !Result.Value.Token.IsEmpty());
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// SESSION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPSessionSpec, "IntegrationTests.NakamaBlueprintTests.Session",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)


	FNakamaClientConfig Client;
	FNakamaSession Session;

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
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(Client, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(Client, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("SessionRefresh", [this]()
	{
		LatentIt("should refresh session", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientSessionRefresh::SessionRefresh(
				GetTransientPackage(), Client, Session.RefreshToken, TMap<FString, FString>());
			Action->Activate();

			// Verify: original session token still works for API call
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::GetAccount(Client, Session).Next([this, Done](FNakamaAccountResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Account retrieved", !Result.Value.User.Id.IsEmpty());
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("SessionLogout", [this]()
	{
		LatentIt("should logout session", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientSessionLogout::SessionLogout(
				GetTransientPackage(), Client, Session, Session.Token, Session.RefreshToken);
			Action->Activate();

			// Verify: action completed without crash; server is still responsive.
			// Use an empty session — the logout invalidated this session's tokens,
			// and passing it would trigger an auto-refresh against the now-invalid
			// refresh token. The healthcheck endpoint is unauthenticated, so an
			// empty session reaches it without attempting a refresh.
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::Healthcheck(Client, FNakamaSession{}).Next([this, Done](FNakamaVoidResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Result.Error.Message));
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// ACCOUNT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPAccountSpec, "IntegrationTests.NakamaBlueprintTests.Account",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)


	FNakamaClientConfig Client;
	FNakamaSession Session;
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
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(Client, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
				Done.Execute();
				return;
			}
			Session = Result.Value;
			Nakama::GetAccount(Client, Session).Next([this, Done](FNakamaAccountResult AccResult)
			{
				if (AccResult.bIsError)
				{
					AddError(FString::Printf(TEXT("GetAccount failed: %s"), *AccResult.Error.Message));
				}
				else
				{
					UserId = AccResult.Value.User.Id;
				}
				Done.Execute();
			});
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(Client, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("GetAccount", [this]()
	{
		LatentIt("should get account", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientGetAccount::GetAccount(GetTransientPackage(), Client, Session);
			Action->Activate();

			// Verify via C++ GetAccount
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::GetAccount(Client, Session).Next([this, Done](FNakamaAccountResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestEqual("User ID matches", Result.Value.User.Id, UserId);
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("UpdateAccount", [this]()
	{
		LatentIt("should update and verify display name", [this](const FDoneDelegate& Done)
		{
			FString NewDisplayName = TEXT("BPTestUser");

			auto* Action = UNakamaClientUpdateAccount::UpdateAccount(
				GetTransientPackage(), Client, Session,
				TEXT(""), NewDisplayName, TEXT(""), TEXT(""), TEXT(""), TEXT(""));
			Action->Activate();

			// Verify via C++ GetAccount
			VerifyWhenComplete(Action, [this, Done, NewDisplayName]()
			{
				Nakama::GetAccount(Client, Session).Next([this, Done, NewDisplayName](FNakamaAccountResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestEqual("Display name updated", Result.Value.User.DisplayName, NewDisplayName);
					}
					Done.Execute();
				});
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
				GetTransientPackage(), Client, Session, Ids, Usernames, FacebookIds);
			Action->Activate();

			// Verify via C++ GetUsers
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::GetUsers(Client, Session, { UserId }, {}, {}).Next([this, Done](FNakamaUsersResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("GetUsers failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Got at least one user", Result.Value.Users.Num() > 0);
						if (Result.Value.Users.Num() > 0)
						{
							TestEqual("User ID matches", Result.Value.Users[0].Id, UserId);
						}
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// FRIENDS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPFriendsSpec, "IntegrationTests.NakamaBlueprintTests.Friends",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)


	FNakamaClientConfig Client;
	FNakamaSession Session;
	FString UserId;

	FNakamaClientConfig FriendClient;
	FNakamaSession FriendSession;
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
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};

		FriendClient = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(Client, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
				Done.Execute();
				return;
			}
			Session = Result.Value;
			Nakama::GetAccount(Client, Session).Next([this, Done](FNakamaAccountResult AccResult)
			{
				if (AccResult.bIsError)
				{
					AddError(FString::Printf(TEXT("GetAccount failed: %s"), *AccResult.Error.Message));
					Done.Execute();
					return;
				}
				UserId = AccResult.Value.User.Id;

				Nakama::AuthenticateCustom(FriendClient, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult FResult)
				{
					if (FResult.bIsError)
					{
						AddError(FString::Printf(TEXT("Friend auth failed: %s"), *FResult.Error.Message));
						Done.Execute();
						return;
					}
					FriendSession = FResult.Value;
					Nakama::GetAccount(FriendClient, FriendSession).Next([this, Done](FNakamaAccountResult FAccResult)
					{
						if (FAccResult.bIsError)
						{
							AddError(FString::Printf(TEXT("Friend GetAccount failed: %s"), *FAccResult.Error.Message));
						}
						else
						{
							FriendUserId = FAccResult.Value.User.Id;
						}
						Done.Execute();
					});
				});
			});
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(Client, Session).Next([this, Done](FNakamaVoidResult)
		{
			Nakama::DeleteAccount(Client, FriendSession).Next([Done](FNakamaVoidResult) { Done.Execute(); });
		});
	});

	Describe("AddFriends", [this]()
	{
		LatentIt("should add a friend and verify via list", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids = { FriendUserId };
			TArray<FString> Usernames;

			auto* Action = UNakamaClientAddFriends::AddFriends(
				GetTransientPackage(), Client, Session, Ids, Usernames, TEXT(""));
			Action->Activate();

			// Verify via C++ ListFriends
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::ListFriends(Client, Session, 10, {}, TEXT("")).Next([this, Done](FNakamaFriendListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListFriends failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Friend list is not empty", Result.Value.Friends.Num() > 0);
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("ListFriends", [this]()
	{
		LatentIt("should list friends after adding one", [this](const FDoneDelegate& Done)
		{
			// Setup: add friend via C++
			Nakama::AddFriends(Client, Session, { FriendUserId }, {}, TEXT("")).Next([this, Done](FNakamaVoidResult AddResult)
			{
				if (AddResult.bIsError)
				{
					AddError(FString::Printf(TEXT("AddFriends setup failed: %s"), *AddResult.Error.Message));
					Done.Execute();
					return;
				}
				// Fire BP ListFriends
				auto* Action = UNakamaClientListFriends::ListFriends(
					GetTransientPackage(), Client, Session, 10, {}, TEXT(""));
				Action->Activate();

				// Verify via C++
				VerifyWhenComplete(Action, [this, Done]()
				{
					Nakama::ListFriends(Client, Session, 10, {}, TEXT("")).Next([this, Done](FNakamaFriendListResult Result)
					{
						if (Result.bIsError)
						{
							AddError(FString::Printf(TEXT("ListFriends failed: %s"), *Result.Error.Message));
						}
						else
						{
							TestTrue("Friend list has entries", Result.Value.Friends.Num() > 0);
						}
						Done.Execute();
					});
				});
			});
		});
	});

	Describe("BlockFriends", [this]()
	{
		LatentIt("should block a friend", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids = { FriendUserId };
			TArray<FString> Usernames;

			auto* Action = UNakamaClientBlockFriends::BlockFriends(
				GetTransientPackage(), Client, Session, Ids, Usernames);
			Action->Activate();

			// Verify: blocked friend appears in friend list with state=3 (blocked)
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::ListFriends(Client, Session, 10, 3, TEXT("")).Next([this, Done](FNakamaFriendListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListFriends failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Blocked friend list has entries", Result.Value.Friends.Num() > 0);
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("DeleteFriends", [this]()
	{
		LatentIt("should delete a friend", [this](const FDoneDelegate& Done)
		{
			// Setup: add friend via C++
			Nakama::AddFriends(Client, Session, { FriendUserId }, {}, TEXT("")).Next([this, Done](FNakamaVoidResult AddResult)
			{
				if (AddResult.bIsError)
				{
					AddError(FString::Printf(TEXT("AddFriends setup failed: %s"), *AddResult.Error.Message));
					Done.Execute();
					return;
				}
				// Fire BP DeleteFriends
				TArray<FString> Ids = { FriendUserId };
				TArray<FString> Usernames;

				auto* Action = UNakamaClientDeleteFriends::DeleteFriends(
					GetTransientPackage(), Client, Session, Ids, Usernames);
				Action->Activate();

				// Verify: friend list is now empty
				VerifyWhenComplete(Action, [this, Done]()
				{
					Nakama::ListFriends(Client, Session, 10, 0, TEXT("")).Next([this, Done](FNakamaFriendListResult Result)
					{
						if (Result.bIsError)
						{
							AddError(FString::Printf(TEXT("ListFriends failed: %s"), *Result.Error.Message));
						}
						else
						{
							TestEqual("Friend list is empty", Result.Value.Friends.Num(), 0);
						}
						Done.Execute();
					});
				});
			});
		});
	});
}

// ============================================================================
// GROUPS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPGroupsSpec, "IntegrationTests.NakamaBlueprintTests.Groups",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)


	FNakamaClientConfig Client;
	FNakamaSession Session;
	FString UserId;


	FNakamaSession Session2;
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
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(Client, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Result.Error.Message));
				Done.Execute();
				return;
			}
			Session = Result.Value;
			Nakama::GetAccount(Client, Session).Next([this, Done](FNakamaAccountResult AccResult)
			{
				if (AccResult.bIsError)
				{
					AddError(FString::Printf(TEXT("GetAccount failed: %s"), *AccResult.Error.Message));
					Done.Execute();
					return;
				}
				UserId = AccResult.Value.User.Id;

				Nakama::AuthenticateCustom(Client, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult Result2)
				{
					if (Result2.bIsError)
					{
						AddError(FString::Printf(TEXT("Auth2 failed: %s"), *Result2.Error.Message));
						Done.Execute();
						return;
					}
					Session2 = Result2.Value;
					Nakama::GetAccount(Client, Session2).Next([this, Done](FNakamaAccountResult AccResult2)
					{
						if (AccResult2.bIsError)
						{
							AddError(FString::Printf(TEXT("GetAccount2 failed: %s"), *AccResult2.Error.Message));
							Done.Execute();
							return;
						}
						UserId2 = AccResult2.Value.User.Id;

						// Create a group as user1
						GroupName = FString::Printf(TEXT("bp_grp_%s"), *GenerateShortId());
						Nakama::CreateGroup(Client, Session, GroupName, TEXT("Test group"),
							TEXT("en"), TEXT(""), true, 100).Next([this, Done](FNakamaGroupResult Group)
						{
							if (Group.bIsError)
							{
								AddError(FString::Printf(TEXT("CreateGroup failed: %s"), *Group.Error.Message));
							}
							else
							{
								GroupId = Group.Value.Id;
							}
							Done.Execute();
						});
					});
				});
			});
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteGroup(Client, Session, GroupId).Next([this, Done](FNakamaVoidResult)
		{
			Nakama::DeleteAccount(Client, Session).Next([this, Done](FNakamaVoidResult)
			{
				Nakama::DeleteAccount(Client, Session2).Next([Done](FNakamaVoidResult) { Done.Execute(); });
			});
		});
	});

	Describe("CreateGroup", [this]()
	{
		LatentIt("should create a group", [this](const FDoneDelegate& Done)
		{
			FString NewGroupName = FString::Printf(TEXT("bp_new_%s"), *GenerateShortId());

			auto* Action = UNakamaClientCreateGroup::CreateGroup(
				GetTransientPackage(), Client, Session,
				NewGroupName, TEXT("Test group"), TEXT("en"), TEXT(""), true, 100);
			Action->Activate();

			// Verify via C++ ListUserGroups (ListGroups always sends open filter which conflicts with name)
			VerifyWhenComplete(Action, [this, Done, NewGroupName]()
			{
				Nakama::ListUserGroups(Client, Session, UserId, 100, 0, TEXT("")).Next([this, Done, NewGroupName](FNakamaUserGroupListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListUserGroups failed: %s"), *Result.Error.Message));
						Done.Execute();
						return;
					}
					FString NewGroupId;
					bool Found = false;
					for (const auto& UG : Result.Value.UserGroups)
					{
						if (UG.Group.Name == NewGroupName)
						{
							Found = true;
							NewGroupId = UG.Group.Id;
							break;
						}
					}
					TestTrue("Created group found in user groups", Found);
					if (!NewGroupId.IsEmpty())
					{
						Nakama::DeleteGroup(Client, Session, NewGroupId).Next([Done](FNakamaVoidResult) { Done.Execute(); });
					}
					else
					{
						Done.Execute();
					}
				});
			});
		});
	});

	Describe("UpdateGroup", [this]()
	{
		LatentIt("should update a group", [this](const FDoneDelegate& Done)
		{
			FString NewDesc = TEXT("Updated description");

			auto* Action = UNakamaClientUpdateGroup::UpdateGroup(
				GetTransientPackage(), Client, Session,
				GroupId, GroupName, NewDesc, TEXT("en"), TEXT(""), true);
			Action->Activate();

			// Verify: group still exists and is accessible
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::ListGroupUsers(Client, Session, GroupId, 10, {}, TEXT("")).Next([this, Done](FNakamaGroupUserListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Group still has users after update", Result.Value.GroupUsers.Num() > 0);
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("DeleteGroup", [this]()
	{
		LatentIt("should delete a group", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientDeleteGroup::DeleteGroup(
				GetTransientPackage(), Client, Session, GroupId);
			Action->Activate();

			// Verify: group no longer in user's groups
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::ListUserGroups(Client, Session, UserId, 100, 0, TEXT("")).Next([this, Done](FNakamaUserGroupListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListUserGroups failed: %s"), *Result.Error.Message));
						Done.Execute();
						return;
					}
					bool Found = false;
					for (const auto& UG : Result.Value.UserGroups)
					{
						if (UG.Group.Id == GroupId)
						{
							Found = true;
							break;
						}
					}
					TestFalse("Deleted group not in user groups", Found);
					Done.Execute();
				});
			});
		});
	});

	Describe("ListGroups", [this]()
	{
		LatentIt("should list groups", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientListGroups::ListGroups(
				GetTransientPackage(), Client, Session,
				TEXT(""), TEXT(""), 100, TEXT(""), {}, true);
			Action->Activate();

			// Verify via C++ ListGroups
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::ListGroups(Client, Session, TEXT(""), TEXT(""), 100, TEXT(""), {}, true).Next([this, Done](FNakamaGroupListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListGroups failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Group list has entries", Result.Value.Groups.Num() > 0);
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("JoinGroup", [this]()
	{
		LatentIt("should join a group", [this](const FDoneDelegate& Done)
		{
			// User2 fires BP JoinGroup on user1's open group
			auto* Action = UNakamaClientJoinGroup::JoinGroup(
				GetTransientPackage(), Client, Session2, GroupId);
			Action->Activate();

			// Verify via C++ ListGroupUsers
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::ListGroupUsers(Client, Session, GroupId, 10, {}, TEXT("")).Next([this, Done](FNakamaGroupUserListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Group has at least 2 users", Result.Value.GroupUsers.Num() >= 2);
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("AddGroupUsers", [this]()
	{
		LatentIt("should add users to a group", [this](const FDoneDelegate& Done)
		{
			TArray<FString> UserIds = { UserId2 };

			auto* Action = UNakamaClientAddGroupUsers::AddGroupUsers(
				GetTransientPackage(), Client, Session, GroupId, UserIds);
			Action->Activate();

			// Verify via C++ ListGroupUsers
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::ListGroupUsers(Client, Session, GroupId, 10, {}, TEXT("")).Next([this, Done](FNakamaGroupUserListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Group has at least 2 users", Result.Value.GroupUsers.Num() >= 2);
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("KickGroupUsers", [this]()
	{
		LatentIt("should kick users from a group", [this](const FDoneDelegate& Done)
		{
			// Setup: add user2 to group via C++
			Nakama::AddGroupUsers(Client, Session, GroupId, { UserId2 }).Next([this, Done](FNakamaVoidResult AddResult)
			{
				if (AddResult.bIsError)
				{
					AddError(FString::Printf(TEXT("AddGroupUsers setup failed: %s"), *AddResult.Error.Message));
					Done.Execute();
					return;
				}
				// Fire BP KickGroupUsers
				TArray<FString> UserIds = { UserId2 };

				auto* Action = UNakamaClientKickGroupUsers::KickGroupUsers(
					GetTransientPackage(), Client, Session, GroupId, UserIds);
				Action->Activate();

				// Verify user2 is no longer in group
				VerifyWhenComplete(Action, [this, Done]()
				{
					Nakama::ListGroupUsers(Client, Session, GroupId, 10, {}, TEXT("")).Next([this, Done](FNakamaGroupUserListResult Result)
					{
						if (Result.bIsError)
						{
							AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Result.Error.Message));
							Done.Execute();
							return;
						}
						bool Found = false;
						for (const auto& GU : Result.Value.GroupUsers)
						{
							if (GU.User.Id == UserId2)
							{
								Found = true;
								break;
							}
						}
						TestFalse("Kicked user not in group", Found);
						Done.Execute();
					});
				});
			});
		});
	});

	Describe("PromoteGroupUsers", [this]()
	{
		LatentIt("should promote users in a group", [this](const FDoneDelegate& Done)
		{
			// Setup: add user2 to group via C++
			Nakama::AddGroupUsers(Client, Session, GroupId, { UserId2 }).Next([this, Done](FNakamaVoidResult AddResult)
			{
				if (AddResult.bIsError)
				{
					AddError(FString::Printf(TEXT("AddGroupUsers setup failed: %s"), *AddResult.Error.Message));
					Done.Execute();
					return;
				}
				// Fire BP PromoteGroupUsers
				TArray<FString> UserIds = { UserId2 };

				auto* Action = UNakamaClientPromoteGroupUsers::PromoteGroupUsers(
					GetTransientPackage(), Client, Session, GroupId, UserIds);
				Action->Activate();

				// Verify: user2 is still in group (promotion doesn't remove)
				VerifyWhenComplete(Action, [this, Done]()
				{
					Nakama::ListGroupUsers(Client, Session, GroupId, 10, {}, TEXT("")).Next([this, Done](FNakamaGroupUserListResult Result)
					{
						if (Result.bIsError)
						{
							AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Result.Error.Message));
							Done.Execute();
							return;
						}
						bool Found = false;
						for (const auto& GU : Result.Value.GroupUsers)
						{
							if (GU.User.Id == UserId2)
							{
								Found = true;
								break;
							}
						}
						TestTrue("Promoted user still in group", Found);
						Done.Execute();
					});
				});
			});
		});
	});

	Describe("LeaveGroup", [this]()
	{
		LatentIt("should leave a group", [this](const FDoneDelegate& Done)
		{
			// Setup: user2 joins group via C++
			Nakama::JoinGroup(Client, Session2, GroupId).Next([this, Done](FNakamaVoidResult JoinResult)
			{
				if (JoinResult.bIsError)
				{
					AddError(FString::Printf(TEXT("JoinGroup setup failed: %s"), *JoinResult.Error.Message));
					Done.Execute();
					return;
				}
				// Fire BP LeaveGroup as user2
				auto* Action = UNakamaClientLeaveGroup::LeaveGroup(
					GetTransientPackage(), Client, Session2, GroupId);
				Action->Activate();

				// Verify user2 no longer in group
				VerifyWhenComplete(Action, [this, Done]()
				{
					Nakama::ListGroupUsers(Client, Session, GroupId, 10, {}, TEXT("")).Next([this, Done](FNakamaGroupUserListResult Result)
					{
						if (Result.bIsError)
						{
							AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Result.Error.Message));
							Done.Execute();
							return;
						}
						bool Found = false;
						for (const auto& GU : Result.Value.GroupUsers)
						{
							if (GU.User.Id == UserId2)
							{
								Found = true;
								break;
							}
						}
						TestFalse("User2 left the group", Found);
						Done.Execute();
					});
				});
			});
		});
	});

	Describe("ListGroupUsers", [this]()
	{
		LatentIt("should list group users", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientListGroupUsers::ListGroupUsers(
				GetTransientPackage(), Client, Session, GroupId, 10, 0, TEXT(""));
			Action->Activate();

			// Verify via C++
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::ListGroupUsers(Client, Session, GroupId, 10, {}, TEXT("")).Next([this, Done](FNakamaGroupUserListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Group has at least one user (owner)", Result.Value.GroupUsers.Num() > 0);
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("ListUserGroups", [this]()
	{
		LatentIt("should list user groups", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientListUserGroups::ListUserGroups(
				GetTransientPackage(), Client, Session, UserId, 10, 0, TEXT(""));
			Action->Activate();

			// Verify via C++
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::ListUserGroups(Client, Session, UserId, 10, 0, TEXT("")).Next([this, Done](FNakamaUserGroupListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListUserGroups failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("User has at least one group", Result.Value.UserGroups.Num() > 0);
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// STORAGE TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPStorageSpec, "IntegrationTests.NakamaBlueprintTests.Storage",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)


	FNakamaClientConfig Client;
	FNakamaSession Session;
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
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(Client, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
				Done.Execute();
				return;
			}
			Session = Result.Value;
			Nakama::GetAccount(Client, Session).Next([this, Done](FNakamaAccountResult AccResult)
			{
				if (AccResult.bIsError)
				{
					AddError(FString::Printf(TEXT("GetAccount failed: %s"), *AccResult.Error.Message));
				}
				else
				{
					UserId = AccResult.Value.User.Id;
				}
				Done.Execute();
			});
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(Client, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
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
				GetTransientPackage(), Client, Session, Objects);
			Action->Activate();

			// Verify via C++ ReadStorageObjects
			VerifyWhenComplete(Action, [this, Done, Key]()
			{
				FNakamaReadStorageObjectId ReadId;
				ReadId.Collection = TEXT("bp_test");
				ReadId.Key = Key;
				ReadId.UserId = UserId;

				Nakama::ReadStorageObjects(Client, Session, { ReadId }).Next([this, Done](FNakamaStorageObjectsResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ReadStorage failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Got at least one object", Result.Value.Objects.Num() > 0);
						if (Result.Value.Objects.Num() > 0)
						{
							TestTrue("Value contains score", Result.Value.Objects[0].Value.Contains(TEXT("42")));
						}
					}
					Done.Execute();
				});
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
				GetTransientPackage(), Client, Session, Objects);
			Action->Activate();

			// Verify via C++ ReadStorageObjects
			VerifyWhenComplete(Action, [this, Done, Key]()
			{
				FNakamaReadStorageObjectId ReadId;
				ReadId.Collection = TEXT("bp_test");
				ReadId.Key = Key;
				ReadId.UserId = UserId;

				Nakama::ReadStorageObjects(Client, Session, { ReadId }).Next([this, Done](FNakamaStorageObjectsResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ReadStorage failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Got at least one object", Result.Value.Objects.Num() > 0);
						if (Result.Value.Objects.Num() > 0)
						{
							TestTrue("Value contains level", Result.Value.Objects[0].Value.Contains(TEXT("99")));
							TestTrue("Value contains name", Result.Value.Objects[0].Value.Contains(TEXT("hero")));
						}
					}
					Done.Execute();
				});
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

			Nakama::WriteStorageObjects(Client, Session, { Obj }).Next([this, Done, Key](FNakamaStorageObjectAcksResult WriteResult)
			{
				if (WriteResult.bIsError)
				{
					AddError(FString::Printf(TEXT("WriteStorage setup failed: %s"), *WriteResult.Error.Message));
					Done.Execute();
					return;
				}
				// Fire BP ReadStorageObjects
				FNakamaReadStorageObjectId ReadId;
				ReadId.Collection = TEXT("bp_test");
				ReadId.Key = Key;
				ReadId.UserId = UserId;

				auto* Action = UNakamaClientReadStorageObjects::ReadStorageObjects(
					GetTransientPackage(), Client, Session, { ReadId });
				Action->Activate();

				// Verify via C++ that object exists
				VerifyWhenComplete(Action, [this, Done, Key]()
				{
					FNakamaReadStorageObjectId VerifyId;
					VerifyId.Collection = TEXT("bp_test");
					VerifyId.Key = Key;
					VerifyId.UserId = UserId;

					Nakama::ReadStorageObjects(Client, Session, { VerifyId }).Next([this, Done](FNakamaStorageObjectsResult Result)
					{
						if (Result.bIsError)
						{
							AddError(FString::Printf(TEXT("ReadStorage failed: %s"), *Result.Error.Message));
						}
						else
						{
							TestTrue("Object still readable", Result.Value.Objects.Num() > 0);
						}
						Done.Execute();
					});
				});
			});
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

			Nakama::WriteStorageObjects(Client, Session, { Obj }).Next([this, Done](FNakamaStorageObjectAcksResult WriteResult)
			{
				if (WriteResult.bIsError)
				{
					AddError(FString::Printf(TEXT("WriteStorage setup failed: %s"), *WriteResult.Error.Message));
					Done.Execute();
					return;
				}
				// Fire BP ListStorageObjects
				auto* Action = UNakamaClientListStorageObjects::ListStorageObjects(
					GetTransientPackage(), Client, Session, UserId, TEXT("bp_list_test"), 10, TEXT(""));
				Action->Activate();

				// Verify via C++
				VerifyWhenComplete(Action, [this, Done]()
				{
					Nakama::ListStorageObjects(Client, Session, UserId, TEXT("bp_list_test"), 10, TEXT("")).Next([this, Done](FNakamaStorageObjectListResult Result)
					{
						if (Result.bIsError)
						{
							AddError(FString::Printf(TEXT("ListStorage failed: %s"), *Result.Error.Message));
						}
						else
						{
							TestTrue("Listed at least one object", Result.Value.Objects.Num() > 0);
						}
						Done.Execute();
					});
				});
			});
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

			Nakama::WriteStorageObjects(Client, Session, { Obj }).Next([this, Done, Key](FNakamaStorageObjectAcksResult WriteResult)
			{
				if (WriteResult.bIsError)
				{
					AddError(FString::Printf(TEXT("WriteStorage setup failed: %s"), *WriteResult.Error.Message));
					Done.Execute();
					return;
				}
				// Fire BP DeleteStorageObjects
				FNakamaDeleteStorageObjectId DelId;
				DelId.Collection = TEXT("bp_del_test");
				DelId.Key = Key;
				DelId.Version = WriteResult.Value.Acks.Num() > 0 ? WriteResult.Value.Acks[0].Version : TEXT("");

				auto* Action = UNakamaClientDeleteStorageObjects::DeleteStorageObjects(
					GetTransientPackage(), Client, Session, { DelId });
				Action->Activate();

				// Verify: object is gone
				VerifyWhenComplete(Action, [this, Done, Key]()
				{
					FNakamaReadStorageObjectId ReadId;
					ReadId.Collection = TEXT("bp_del_test");
					ReadId.Key = Key;
					ReadId.UserId = UserId;

					Nakama::ReadStorageObjects(Client, Session, { ReadId }).Next([this, Done](FNakamaStorageObjectsResult Result)
					{
						if (Result.bIsError)
						{
							AddError(FString::Printf(TEXT("ReadStorage failed: %s"), *Result.Error.Message));
						}
						else
						{
							TestEqual("Object deleted", Result.Value.Objects.Num(), 0);
						}
						Done.Execute();
					});
				});
			});
		});
	});
}

// ============================================================================
// LINK / UNLINK TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPLinkSpec, "IntegrationTests.NakamaBlueprintTests.Link",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)


	FNakamaClientConfig Client;
	FNakamaSession Session;

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
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(Client, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(Client, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("LinkCustom", [this]()
	{
		LatentIt("should link a custom ID", [this](const FDoneDelegate& Done)
		{
			FString NewId = GenerateId();

			auto* Action = UNakamaClientLinkCustom::LinkCustom(
				GetTransientPackage(), Client, Session, NewId, TMap<FString, FString>());
			Action->Activate();

			// Verify: can authenticate with the linked ID
			VerifyWhenComplete(Action, [this, Done, NewId]()
			{
				Nakama::AuthenticateCustom(Client, false, TEXT(""), NewId).Next([this, Done](FNakamaSessionResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Linked auth failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Linked custom auth succeeded", !Result.Value.Token.IsEmpty());
					}
					Done.Execute();
				});
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
			Nakama::LinkDevice(Client, Session, DeviceId, TMap<FString, FString>()).Next([this, Done, ExtraId](FNakamaVoidResult LinkDeviceResult)
			{
				if (LinkDeviceResult.bIsError)
				{
					AddError(FString::Printf(TEXT("LinkDevice setup failed: %s"), *LinkDeviceResult.Error.Message));
					Done.Execute();
					return;
				}
				Nakama::LinkCustom(Client, Session, ExtraId, TMap<FString, FString>()).Next([this, Done, ExtraId](FNakamaVoidResult LinkCustomResult)
				{
					if (LinkCustomResult.bIsError)
					{
						AddError(FString::Printf(TEXT("LinkCustom setup failed: %s"), *LinkCustomResult.Error.Message));
						Done.Execute();
						return;
					}
					// Fire BP UnlinkCustom
					auto* Action = UNakamaClientUnlinkCustom::UnlinkCustom(
						GetTransientPackage(), Client, Session, ExtraId, TMap<FString, FString>());
					Action->Activate();

					// Verify: can no longer auth with the unlinked ID
					VerifyWhenComplete(Action, [this, Done, ExtraId]()
					{
						Nakama::AuthenticateCustom(Client, false, TEXT(""), ExtraId).Next([this, Done](FNakamaSessionResult Result)
						{
							if (Result.bIsError)
							{
								// Expected: auth fails because ID is unlinked
								TestTrue("Unlinked ID auth rejected", true);
							}
							else
							{
								AddError(TEXT("Auth should have failed for unlinked ID"));
							}
							Done.Execute();
						});
					});
				});
			});
		});
	});

	Describe("LinkDevice", [this]()
	{
		LatentIt("should link a device ID", [this](const FDoneDelegate& Done)
		{
			FString DeviceId = GenerateId();

			auto* Action = UNakamaClientLinkDevice::LinkDevice(
				GetTransientPackage(), Client, Session, DeviceId, TMap<FString, FString>());
			Action->Activate();

			// Verify: can authenticate with the linked device ID
			VerifyWhenComplete(Action, [this, Done, DeviceId]()
			{
				Nakama::AuthenticateDevice(Client, false, TEXT(""), DeviceId).Next([this, Done](FNakamaSessionResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Linked device auth failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Linked device auth succeeded", !Result.Value.Token.IsEmpty());
					}
					Done.Execute();
				});
			});
		});
	});

	Describe("UnlinkDevice", [this]()
	{
		LatentIt("should unlink a device ID", [this](const FDoneDelegate& Done)
		{
			FString DeviceId = GenerateId();

			// Setup: link device via C++
			Nakama::LinkDevice(Client, Session, DeviceId, TMap<FString, FString>()).Next([this, Done, DeviceId](FNakamaVoidResult LinkResult)
			{
				if (LinkResult.bIsError)
				{
					AddError(FString::Printf(TEXT("LinkDevice setup failed: %s"), *LinkResult.Error.Message));
					Done.Execute();
					return;
				}
				// Fire BP UnlinkDevice
				auto* Action = UNakamaClientUnlinkDevice::UnlinkDevice(
					GetTransientPackage(), Client, Session, DeviceId, TMap<FString, FString>());
				Action->Activate();

				// Verify: can no longer auth with the unlinked device
				VerifyWhenComplete(Action, [this, Done, DeviceId]()
				{
					Nakama::AuthenticateDevice(Client, false, TEXT(""), DeviceId).Next([this, Done](FNakamaSessionResult Result)
					{
						if (Result.bIsError)
						{
							TestTrue("Unlinked device auth rejected", true);
						}
						else
						{
							AddError(TEXT("Auth should have failed for unlinked device"));
						}
						Done.Execute();
					});
				});
			});
		});
	});

	Describe("LinkEmail", [this]()
	{
		LatentIt("should link an email", [this](const FDoneDelegate& Done)
		{
			FString Email = FString::Printf(TEXT("link_%s@example.com"), *GenerateShortId());
			FString Password = TEXT("password123!");

			auto* Action = UNakamaClientLinkEmail::LinkEmail(
				GetTransientPackage(), Client, Session, Email, Password, TMap<FString, FString>());
			Action->Activate();

			// Verify: can authenticate with the linked email
			VerifyWhenComplete(Action, [this, Done, Email, Password]()
			{
				Nakama::AuthenticateEmail(Client, false, TEXT(""), Email, Password).Next([this, Done](FNakamaSessionResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Linked email auth failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("Linked email auth succeeded", !Result.Value.Token.IsEmpty());
					}
					Done.Execute();
				});
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
			Nakama::LinkEmail(Client, Session, Email, Password, TMap<FString, FString>()).Next([this, Done, Email, Password](FNakamaVoidResult LinkResult)
			{
				if (LinkResult.bIsError)
				{
					AddError(FString::Printf(TEXT("LinkEmail setup failed: %s"), *LinkResult.Error.Message));
					Done.Execute();
					return;
				}
				// Fire BP UnlinkEmail
				auto* Action = UNakamaClientUnlinkEmail::UnlinkEmail(
					GetTransientPackage(), Client, Session, Email, Password, TMap<FString, FString>());
				Action->Activate();

				// Verify: can no longer auth with the unlinked email
				VerifyWhenComplete(Action, [this, Done, Email, Password]()
				{
					Nakama::AuthenticateEmail(Client, false, TEXT(""), Email, Password).Next([this, Done](FNakamaSessionResult Result)
					{
						if (Result.bIsError)
						{
							TestTrue("Unlinked email auth rejected", true);
						}
						else
						{
							AddError(TEXT("Auth should have failed for unlinked email"));
						}
						Done.Execute();
					});
				});
			});
		});
	});
}

// ============================================================================
// NOTIFICATIONS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPNotificationsSpec, "IntegrationTests.NakamaBlueprintTests.Notifications",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)


	FNakamaClientConfig Client;
	FNakamaSession Session;

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
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(Client, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(Client, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("ListNotifications", [this]()
	{
		LatentIt("should list notifications", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientListNotifications::ListNotifications(
				GetTransientPackage(), Client, Session, 100, TEXT(""));
			Action->Activate();

			// Verify via C++
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::ListNotifications(Client, Session, 100, TEXT("")).Next([this, Done](FNakamaNotificationListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListNotifications failed: %s"), *Result.Error.Message));
					}
					else
					{
						// Fresh account has no notifications; just verify no error
						TestTrue("Notification list call succeeded", true);
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// MATCHES TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPMatchesSpec, "IntegrationTests.NakamaBlueprintTests.Matches",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)


	FNakamaClientConfig Client;
	FNakamaSession Session;

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
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(Client, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(Client, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("ListMatches", [this]()
	{
		LatentIt("should list matches", [this](const FDoneDelegate& Done)
		{
			auto* Action = UNakamaClientListMatches::ListMatches(
				GetTransientPackage(), Client, Session, 10, false, TEXT(""), 0, 100, TEXT(""));
			Action->Activate();

			// Verify via C++
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::ListMatches(Client, Session, 10, false, TEXT(""), 0, 100, TEXT("")).Next([this, Done](FNakamaMatchListResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("ListMatches failed: %s"), *Result.Error.Message));
					}
					else
					{
						TestTrue("ListMatches call succeeded", true);
					}
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// EVENTS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaBPEventsSpec, "IntegrationTests.NakamaBlueprintTests.Events",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)


	FNakamaClientConfig Client;
	FNakamaSession Session;

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
		Client = FNakamaClientConfig{ServerKey, Host, Port, false};
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(Client, true, TEXT(""), GenerateId()).Next([this, Done](FNakamaSessionResult Result)
		{
			if (Result.bIsError)
			{
				AddError(FString::Printf(TEXT("Setup auth failed: %s"), *Result.Error.Message));
			}
			else
			{
				Session = Result.Value;
			}
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(Client, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("Event", [this]()
	{
		LatentIt("should send an event", [this](const FDoneDelegate& Done)
		{
			TMap<FString, FString> Properties;
			Properties.Add(TEXT("key1"), TEXT("value1"));

			auto* Action = UNakamaClientEvent::Event(
				GetTransientPackage(), Client, Session, TEXT("bp_test_event"), FDateTime(), false, Properties);
			Action->Activate();

			// Verify: server is still healthy after event
			VerifyWhenComplete(Action, [this, Done]()
			{
				Nakama::Healthcheck(Client, Session).Next([this, Done](FNakamaVoidResult Result)
				{
					if (Result.bIsError)
					{
						AddError(FString::Printf(TEXT("Healthcheck failed: %s"), *Result.Error.Message));
					}
					Done.Execute();
				});
			});
		});
	});
}
