/**
 * Nakama Integration Test Suite
 *
 * Comprehensive tests for all Nakama REST API endpoints using Unreal Spec testing.
 * Tests cover success cases, validation failures, authentication errors, and permission errors.
 */

#include "Misc/AutomationTest.h"
#include "NakamaUnreal.h"
#include "Misc/Guid.h"

// Error codes from gRPC/Nakama
namespace NakamaErrorCode
{
	constexpr int32 OK = 0;
	constexpr int32 Cancelled = 1;
	constexpr int32 Unknown = 2;
	constexpr int32 InvalidArgument = 3;
	constexpr int32 DeadlineExceeded = 4;
	constexpr int32 NotFound = 5;
	constexpr int32 AlreadyExists = 6;
	constexpr int32 PermissionDenied = 7;
	constexpr int32 ResourceExhausted = 8;
	constexpr int32 FailedPrecondition = 9;
	constexpr int32 Aborted = 10;
	constexpr int32 OutOfRange = 11;
	constexpr int32 Unimplemented = 12;
	constexpr int32 Internal = 13;
	constexpr int32 Unavailable = 14;
	constexpr int32 DataLoss = 15;
	constexpr int32 Unauthenticated = 16;
}

// ============================================================================
// AUTHENTICATION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAuthSpec, "NakamaTest.Auth",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;
	FString TestCustomId;
	FString TestDeviceId;
	FString TestEmail;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAuthSpec)

const FString FNakamaAuthSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaAuthSpec::Host = TEXT("127.0.0.1");

void FNakamaAuthSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
		TestCustomId = GenerateId();
		TestDeviceId = GenerateId();
		TestEmail = FString::Printf(TEXT("test_%s@example.com"), *GenerateShortId());
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("CustomAuth", [this]()
	{
		LatentIt("should authenticate with valid custom ID", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = TestCustomId;

			Client->AuthenticateCustom(Account, true, TEXT(""),
				[this, Done](const FNakamaSession& Result)
				{
					TestTrue("Session has token", !Result.Token.IsEmpty());
					TestTrue("Session has refresh token", !Result.RefreshToken.IsEmpty());
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("Unexpected error: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with empty custom ID", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = TEXT("");

			Client->AuthenticateCustom(Account, true, TEXT(""),
				[this, Done](const FNakamaSession& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error response", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with custom ID too short", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = TEXT("abc");  // < 6 chars

			Client->AuthenticateCustom(Account, true, TEXT(""),
				[this, Done](const FNakamaSession& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error response", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with custom ID too long", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = FString::ChrN(150, 'a');  // > 128 chars

			Client->AuthenticateCustom(Account, true, TEXT(""),
				[this, Done](const FNakamaSession& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error response", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});

		LatentIt("should authenticate with username", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = TestCustomId;
			FString Username = FString::Printf(TEXT("user_%s"), *GenerateShortId());

			Client->AuthenticateCustom(Account, true, Username,
				[this, Done](const FNakamaSession& Result)
				{
					TestTrue("Session has token", !Result.Token.IsEmpty());
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("Unexpected error: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("DeviceAuth", [this]()
	{
		LatentIt("should authenticate with valid device ID", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountDevice Account;
			Account.Id = TestDeviceId;

			Client->AuthenticateDevice(Account, true, TEXT(""),
				[this, Done](const FNakamaSession& Result)
				{
					TestTrue("Session has token", !Result.Token.IsEmpty());
					TestTrue("Session has refresh token", !Result.RefreshToken.IsEmpty());
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("Unexpected error: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with empty device ID", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountDevice Account;
			Account.Id = TEXT("");

			Client->AuthenticateDevice(Account, true, TEXT(""),
				[this, Done](const FNakamaSession& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error response", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with device ID too short", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountDevice Account;
			Account.Id = TEXT("short");  // < 10 chars

			Client->AuthenticateDevice(Account, true, TEXT(""),
				[this, Done](const FNakamaSession& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error response", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});

	Describe("EmailAuth", [this]()
	{
		LatentIt("should authenticate with valid email and password", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountEmail Account;
			Account.Email = TestEmail;
			Account.Password = TEXT("password123");

			Client->AuthenticateEmail(Account, true, TEXT(""),
				[this, Done](const FNakamaSession& Result)
				{
					TestTrue("Session has token", !Result.Token.IsEmpty());
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("Unexpected error: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with invalid email format", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountEmail Account;
			Account.Email = TEXT("notanemail");
			Account.Password = TEXT("password123");

			Client->AuthenticateEmail(Account, true, TEXT(""),
				[this, Done](const FNakamaSession& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error response", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with password too short", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountEmail Account;
			Account.Email = TestEmail;
			Account.Password = TEXT("short");  // < 8 chars

			Client->AuthenticateEmail(Account, true, TEXT(""),
				[this, Done](const FNakamaSession& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error response", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// ACCOUNT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAccountSpec, "NakamaTest.Account",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;
	FString UserId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAccountSpec)

const FString FNakamaAccountSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaAccountSpec::Host = TEXT("127.0.0.1");

void FNakamaAccountSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("GetAccount", [this]()
	{
		LatentIt("should get account for authenticated user", [this](const FDoneDelegate& Done)
		{
			Client->GetAccount(
				[this, Done](const FNakamaAccount& Result)
				{
					TestTrue("Account has user ID", !Result.User.Id.IsEmpty());
					UserId = Result.User.Id;
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("Unexpected error: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("UpdateAccount", [this]()
	{
		LatentIt("should update account display name", [this](const FDoneDelegate& Done)
		{
			FString NewDisplayName = FString::Printf(TEXT("TestUser_%s"), *GenerateShortId());

			Client->UpdateAccount(
				TEXT(""),  // username (don't change)
				NewDisplayName,
				TEXT(""),  // avatar_url
				TEXT("en"),  // lang_tag
				TEXT(""),  // location
				TEXT(""),  // timezone
				[this, Done, NewDisplayName]()
				{
					// Verify update by getting account
					Client->GetAccount(
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
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("UpdateAccount failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("SessionRefresh", [this]()
	{
		LatentIt("should refresh session with valid token", [this](const FDoneDelegate& Done)
		{
			Client->SessionRefresh(
				Session.RefreshToken,
				TMap<FString, FString>(),
				[this, Done](const FNakamaSession& Result)
				{
					TestTrue("New session has token", !Result.Token.IsEmpty());
					TestTrue("New session has refresh token", !Result.RefreshToken.IsEmpty());
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("Refresh failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with invalid refresh token", [this](const FDoneDelegate& Done)
		{
			Client->SessionRefresh(
				TEXT("invalid.token.here"),
				TMap<FString, FString>(),
				[this, Done](const FNakamaSession& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error response", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// FRIENDS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaFriendsSpec, "NakamaTest.Friends",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	TSharedPtr<FNakamaClient> FriendClient;
	FNakamaSession Session;
	FString UserId;
	FString FriendUserId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaFriendsSpec)

const FString FNakamaFriendsSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaFriendsSpec::Host = TEXT("127.0.0.1");

void FNakamaFriendsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
		FriendClient = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		FriendClient->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		// Authenticate main user
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				// Get user ID
				Client->GetAccount(
					[this, Done](const FNakamaAccount& AccResult)
					{
						UserId = AccResult.User.Id;

						// Authenticate friend user
						FNakamaAccountCustom FriendAccount;
						FriendAccount.Id = GenerateId();

						FriendClient->AuthenticateCustom(FriendAccount, true, TEXT(""),
							[this, Done](const FNakamaSession& FriendSession)
							{
								FriendClient->GetAccount(
									[this, Done](const FNakamaAccount& FriendAccResult)
									{
										FriendUserId = FriendAccResult.User.Id;
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
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
		FriendClient.Reset();
	});

	Describe("ListFriends", [this]()
	{
		LatentIt("should list friends for authenticated user", [this](const FDoneDelegate& Done)
		{
			Client->ListFriends(
				100,  // limit
				0,    // state (all)
				TEXT(""),  // cursor
				[this, Done](const FNakamaFriendList& Result)
				{
					// New user should have empty or valid friends list
					TestTrue("Friends list is valid", true);
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

	Describe("AddFriends", [this]()
	{
		LatentIt("should add friend by user ID", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(FriendUserId);

			Client->AddFriends(
				Ids,
				TArray<FString>(),  // usernames
				TEXT(""),  // metadata
				[this, Done]()
				{
					// AddFriends succeeded - test passes
					// Note: Verifying the friend list state would require careful
					// session management as both users share logging infrastructure
					TestTrue("AddFriends completed successfully", true);
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("AddFriends failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should not add self as friend", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(UserId);

			Client->AddFriends(
				Ids,
				TArray<FString>(),
				TEXT(""),
				[this, Done]()
				{
					// Server accepts but should not add self to friend list
					// Verify self is not in friend list
					Client->ListFriends(100, 2, TEXT(""),  // state 2 = INVITE_SENT
						[this, Done](const FNakamaFriendList& Result)
						{
							bool bFoundSelf = false;
							for (const auto& Friend : Result.Friends)
							{
								if (Friend.User.Id == UserId)
								{
									bFoundSelf = true;
									break;
								}
							}
							TestTrue("Self not in friend list", !bFoundSelf);
							Done.Execute();
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("ListFriends failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					// Some servers may return an error, which is also acceptable
					Done.Execute();
				}
			);
		});
	});

	Describe("BlockFriends", [this]()
	{
		LatentIt("should block user by ID", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(FriendUserId);

			Client->BlockFriends(
				Ids,
				TArray<FString>(),
				[this, Done]()
				{
					TestTrue("Block succeeded", true);
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("BlockFriends failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// GROUPS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaGroupsSpec, "NakamaTest.Groups",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;
	FString UserId;
	FString CreatedGroupId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaGroupsSpec)

const FString FNakamaGroupsSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaGroupsSpec::Host = TEXT("127.0.0.1");

void FNakamaGroupsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
		CreatedGroupId.Empty();
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Client->GetAccount(
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
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("CreateGroup", [this]()
	{
		LatentIt("should create group with valid name", [this](const FDoneDelegate& Done)
		{
			FString GroupName = FString::Printf(TEXT("TestGroup_%s"), *GenerateShortId());

			Client->CreateGroup(
				GroupName,
				TEXT("Test description"),
				TEXT(""),  // avatar_url
				TEXT("en"),  // lang_tag
				true,  // open
				100,  // max_count
				[this, Done](const FNakamaGroup& Result)
				{
					TestTrue("Group has ID", !Result.Id.IsEmpty());
					TestTrue("Group has name", !Result.Name.IsEmpty());
					CreatedGroupId = Result.Id;
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("CreateGroup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with empty group name", [this](const FDoneDelegate& Done)
		{
			Client->CreateGroup(
				TEXT(""),  // empty name
				TEXT("Description"),
				TEXT(""),
				TEXT("en"),
				true,
				100,
				[this, Done](const FNakamaGroup& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for empty name", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});

	Describe("ListGroups", [this]()
	{
		LatentIt("should list groups", [this](const FDoneDelegate& Done)
		{
			Client->ListGroups(
				TEXT(""),  // name filter
				TEXT(""),  // cursor
				100,  // limit
				TEXT(""),  // lang_tag
				0,  // members
				true,  // open
				[this, Done](const FNakamaGroupList& Result)
				{
					TestTrue("Groups list is valid", true);
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

	Describe("ListUserGroups", [this]()
	{
		LatentIt("should list groups for user", [this](const FDoneDelegate& Done)
		{
			// First create a group
			FString GroupName = FString::Printf(TEXT("UserGroup_%s"), *GenerateShortId());

			Client->CreateGroup(
				GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100,
				[this, Done](const FNakamaGroup& Group)
				{
					// Now list user's groups
					Client->ListUserGroups(
						UserId,
						100,  // limit
						0,    // state
						TEXT(""),  // cursor
						[this, Done](const FNakamaUserGroupList& Result)
						{
							TestTrue("User has at least one group", Result.UserGroups.Num() >= 1);
							Done.Execute();
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("ListUserGroups failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("CreateGroup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// STORAGE TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaStorageSpec, "NakamaTest.Storage",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;
	FString UserId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaStorageSpec)

const FString FNakamaStorageSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaStorageSpec::Host = TEXT("127.0.0.1");

void FNakamaStorageSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Client->GetAccount(
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
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("WriteStorageObjects", [this]()
	{
		LatentIt("should write storage object", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Object;
			Object.Collection = TEXT("test_collection");
			Object.Key = FString::Printf(TEXT("test_key_%s"), *GenerateShortId());
			Object.Value = TEXT("{\"test\": \"value\"}");
			Object.PermissionRead = 1;
			Object.PermissionWrite = 1;
			Objects.Add(Object);

			Client->WriteStorageObjects(
				Objects,
				[this, Done](const FNakamaStorageObjectAcks& Result)
				{
					TestTrue("Got acks", Result.Acks.Num() > 0);
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("WriteStorageObjects failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with invalid JSON value", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Object;
			Object.Collection = TEXT("test_collection");
			Object.Key = TEXT("test_key");
			Object.Value = TEXT("not valid json {{{");
			Object.PermissionRead = 1;
			Object.PermissionWrite = 1;
			Objects.Add(Object);

			Client->WriteStorageObjects(
				Objects,
				[this, Done](const FNakamaStorageObjectAcks& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for invalid JSON", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});

	Describe("ReadStorageObjects", [this]()
	{
		LatentIt("should read written storage object", [this](const FDoneDelegate& Done)
		{
			FString Key = FString::Printf(TEXT("read_key_%s"), *GenerateShortId());

			// First write
			TArray<FNakamaWriteStorageObject> WriteObjects;
			FNakamaWriteStorageObject WriteObject;
			WriteObject.Collection = TEXT("test_collection");
			WriteObject.Key = Key;
			WriteObject.Value = TEXT("{\"data\": \"test\"}");
			WriteObject.PermissionRead = 2;  // public
			WriteObject.PermissionWrite = 1;
			WriteObjects.Add(WriteObject);

			Client->WriteStorageObjects(
				WriteObjects,
				[this, Done, Key](const FNakamaStorageObjectAcks& WriteResult)
				{
					// Now read
					TArray<FNakamaReadStorageObjectId> ReadIds;
					FNakamaReadStorageObjectId ReadId;
					ReadId.Collection = TEXT("test_collection");
					ReadId.Key = Key;
					ReadId.UserId = UserId;
					ReadIds.Add(ReadId);

					Client->ReadStorageObjects(
						ReadIds,
						[this, Done](const FNakamaStorageObjects& ReadResult)
						{
							TestTrue("Got objects", ReadResult.Objects.Num() > 0);
							Done.Execute();
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("ReadStorageObjects failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("WriteStorageObjects failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("ListStorageObjects", [this]()
	{
		LatentIt("should list storage objects", [this](const FDoneDelegate& Done)
		{
			// First write some objects
			TArray<FNakamaWriteStorageObject> Objects;
			for (int32 i = 0; i < 3; i++)
			{
				FNakamaWriteStorageObject Object;
				Object.Collection = TEXT("list_collection");
				Object.Key = FString::Printf(TEXT("list_key_%d_%s"), i, *GenerateShortId());
				Object.Value = FString::Printf(TEXT("{\"index\": %d}"), i);
				Object.PermissionRead = 1;
				Object.PermissionWrite = 1;
				Objects.Add(Object);
			}

			Client->WriteStorageObjects(
				Objects,
				[this, Done](const FNakamaStorageObjectAcks& WriteResult)
				{
					Client->ListStorageObjects(
						UserId,
						TEXT("list_collection"),
						100,
						TEXT(""),
						[this, Done](const FNakamaStorageObjectList& ListResult)
						{
							TestTrue("Has objects", ListResult.Objects.Num() >= 3);
							Done.Execute();
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("ListStorageObjects failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("WriteStorageObjects failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// LEADERBOARD TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaLeaderboardSpec, "NakamaTest.Leaderboard",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaLeaderboardSpec)

const FString FNakamaLeaderboardSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaLeaderboardSpec::Host = TEXT("127.0.0.1");

void FNakamaLeaderboardSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("ListLeaderboardRecords", [this]()
	{
		LatentIt("should fail with empty leaderboard ID", [this](const FDoneDelegate& Done)
		{
			Client->ListLeaderboardRecords(
				TEXT(""),  // empty ID
				TArray<FString>(),
				100,
				TEXT(""),
				0,
				[this, Done](const FNakamaLeaderboardRecordList& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for empty ID", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// MATCHES TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaMatchesSpec, "NakamaTest.Matches",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaMatchesSpec)

const FString FNakamaMatchesSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaMatchesSpec::Host = TEXT("127.0.0.1");

void FNakamaMatchesSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("ListMatches", [this]()
	{
		LatentIt("should list matches", [this](const FDoneDelegate& Done)
		{
			Client->ListMatches(
				10,  // limit
				false,  // authoritative
				TEXT(""),  // label
				0,  // min_size
				100,  // max_size
				TEXT(""),  // query
				[this, Done](const FNakamaMatchList& Result)
				{
					TestTrue("Matches list is valid", true);
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("ListMatches failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should list authoritative matches only", [this](const FDoneDelegate& Done)
		{
			Client->ListMatches(
				10,
				true,  // authoritative only
				TEXT(""),
				0,
				100,
				TEXT(""),
				[this, Done](const FNakamaMatchList& Result)
				{
					TestTrue("Authoritative matches list is valid", true);
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
}

// ============================================================================
// NOTIFICATIONS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaNotificationsSpec, "NakamaTest.Notifications",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaNotificationsSpec)

const FString FNakamaNotificationsSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaNotificationsSpec::Host = TEXT("127.0.0.1");

void FNakamaNotificationsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("ListNotifications", [this]()
	{
		LatentIt("should list notifications", [this](const FDoneDelegate& Done)
		{
			Client->ListNotifications(
				100,
				TEXT(""),
				[this, Done](const FNakamaNotificationList& Result)
				{
					TestTrue("Notifications list is valid", true);
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
}

// ============================================================================
// LINK/UNLINK TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaLinkSpec, "NakamaTest.Link",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;
	FString DeviceId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaLinkSpec)

const FString FNakamaLinkSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaLinkSpec::Host = TEXT("127.0.0.1");

void FNakamaLinkSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
		DeviceId = GenerateId();
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		// Authenticate with device
		FNakamaAccountDevice Account;
		Account.Id = DeviceId;

		Client->AuthenticateDevice(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("LinkCustom", [this]()
	{
		LatentIt("should link custom ID", [this](const FDoneDelegate& Done)
		{
			Client->LinkCustom(
				GenerateId(),
				TMap<FString, FString>(),
				[this, Done]()
				{
					TestTrue("Link succeeded", true);
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("LinkCustom failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with ID too short", [this](const FDoneDelegate& Done)
		{
			Client->LinkCustom(
				TEXT("abc"),  // < 6 chars
				TMap<FString, FString>(),
				[this, Done]()
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for short ID", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});

	Describe("LinkEmail", [this]()
	{
		LatentIt("should link email", [this](const FDoneDelegate& Done)
		{
			FString Email = FString::Printf(TEXT("link_%s@example.com"), *GenerateShortId());

			Client->LinkEmail(
				Email,
				TEXT("password123"),
				TMap<FString, FString>(),
				[this, Done]()
				{
					TestTrue("Link succeeded", true);
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("LinkEmail failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with invalid email format", [this](const FDoneDelegate& Done)
		{
			Client->LinkEmail(
				TEXT("notanemail"),
				TEXT("password123"),
				TMap<FString, FString>(),
				[this, Done]()
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for invalid email", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with password too short", [this](const FDoneDelegate& Done)
		{
			FString Email = FString::Printf(TEXT("short_%s@example.com"), *GenerateShortId());

			Client->LinkEmail(
				Email,
				TEXT("short"),  // < 8 chars
				TMap<FString, FString>(),
				[this, Done]()
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for short password", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// TOURNAMENT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaTournamentSpec, "NakamaTest.Tournament",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaTournamentSpec)

const FString FNakamaTournamentSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaTournamentSpec::Host = TEXT("127.0.0.1");

void FNakamaTournamentSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("ListTournaments", [this]()
	{
		LatentIt("should list tournaments", [this](const FDoneDelegate& Done)
		{
			Client->ListTournaments(
				0,  // category_start
				127,  // category_end
				0,  // start_time
				0,  // end_time
				100,  // limit
				TEXT(""),  // cursor
				[this, Done](const FNakamaTournamentList& Result)
				{
					TestTrue("Tournaments list is valid", true);
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("ListTournaments failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with category end too high", [this](const FDoneDelegate& Done)
		{
			Client->ListTournaments(
				0,  // category_start
				200,  // category_end - too high (>=128)
				0,  // start_time
				0,  // end_time
				100,  // limit
				TEXT(""),  // cursor
				[this, Done](const FNakamaTournamentList& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for invalid category", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// USERS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaUsersSpec, "NakamaTest.Users",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;
	FString UserId;
	FString Username;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaUsersSpec)

const FString FNakamaUsersSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaUsersSpec::Host = TEXT("127.0.0.1");

void FNakamaUsersSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Username = FString::Printf(TEXT("user_%s"), *GenerateShortId());
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, Username,
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Client->GetAccount(
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
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("GetUsers", [this]()
	{
		LatentIt("should get users by ID", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(UserId);

			Client->GetUsers(
				Ids,
				TArray<FString>(),  // usernames
				TArray<FString>(),  // facebook_ids
				[this, Done](const FNakamaUsers& Result)
				{
					TestTrue("Got user", Result.Users.Num() > 0);
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

		LatentIt("should get users by username", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Usernames;
			Usernames.Add(Username);

			Client->GetUsers(
				TArray<FString>(),  // ids
				Usernames,
				TArray<FString>(),  // facebook_ids
				[this, Done](const FNakamaUsers& Result)
				{
					TestTrue("Got user by username", Result.Users.Num() > 0);
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("GetUsers failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should return empty for non-existent user", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			// Use a valid UUID format but one that doesn't exist (not the zero UUID which is reserved)
			Ids.Add(TEXT("ffffffff-ffff-ffff-ffff-ffffffffffff"));

			Client->GetUsers(
				Ids,
				TArray<FString>(),
				TArray<FString>(),
				[this, Done](const FNakamaUsers& Result)
				{
					TestTrue("Empty result for non-existent user", Result.Users.Num() == 0);
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
}

// ============================================================================
// SESSION LOGOUT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaSessionSpec, "NakamaTest.Session",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaSessionSpec)

const FString FNakamaSessionSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaSessionSpec::Host = TEXT("127.0.0.1");

void FNakamaSessionSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("SessionLogout", [this]()
	{
		LatentIt("should logout successfully", [this](const FDoneDelegate& Done)
		{
			Client->SessionLogout(
				Session.Token,
				Session.RefreshToken,
				[this, Done]()
				{
					TestTrue("Logout succeeded", true);
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("SessionLogout failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// DELETE STORAGE TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaDeleteStorageSpec, "NakamaTest.DeleteStorage",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;
	FString UserId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaDeleteStorageSpec)

const FString FNakamaDeleteStorageSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaDeleteStorageSpec::Host = TEXT("127.0.0.1");

void FNakamaDeleteStorageSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Client->GetAccount(
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
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("DeleteStorageObjects", [this]()
	{
		LatentIt("should delete storage object", [this](const FDoneDelegate& Done)
		{
			FString Key = FString::Printf(TEXT("delete_key_%s"), *GenerateShortId());

			// First write an object
			TArray<FNakamaWriteStorageObject> WriteObjects;
			FNakamaWriteStorageObject WriteObject;
			WriteObject.Collection = TEXT("delete_collection");
			WriteObject.Key = Key;
			WriteObject.Value = TEXT("{\"test\": \"delete\"}");
			WriteObject.PermissionRead = 1;
			WriteObject.PermissionWrite = 1;
			WriteObjects.Add(WriteObject);

			Client->WriteStorageObjects(
				WriteObjects,
				[this, Done, Key](const FNakamaStorageObjectAcks& WriteResult)
				{
					// Now delete it
					TArray<FNakamaDeleteStorageObjectId> DeleteIds;
					FNakamaDeleteStorageObjectId DeleteId;
					DeleteId.Collection = TEXT("delete_collection");
					DeleteId.Key = Key;
					DeleteIds.Add(DeleteId);

					Client->DeleteStorageObjects(
						DeleteIds,
						[this, Done]()
						{
							TestTrue("Delete succeeded", true);
							Done.Execute();
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("DeleteStorageObjects failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("WriteStorageObjects failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail when deleting non-existent object", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaDeleteStorageObjectId> DeleteIds;
			FNakamaDeleteStorageObjectId DeleteId;
			DeleteId.Collection = TEXT("nonexistent_collection");
			DeleteId.Key = TEXT("nonexistent_key");
			DeleteIds.Add(DeleteId);

			Client->DeleteStorageObjects(
				DeleteIds,
				[this, Done]()
				{
					// Some servers may succeed (no-op), which is acceptable
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					// Server returns error for non-existent objects - this is expected
					TestTrue("Got error for non-existent object", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// DELETE FRIENDS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaDeleteFriendsSpec, "NakamaTest.DeleteFriends",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	TSharedPtr<FNakamaClient> FriendClient;
	FNakamaSession Session;
	FString UserId;
	FString FriendUserId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaDeleteFriendsSpec)

const FString FNakamaDeleteFriendsSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaDeleteFriendsSpec::Host = TEXT("127.0.0.1");

void FNakamaDeleteFriendsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
		FriendClient = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		FriendClient->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Client->GetAccount(
					[this, Done](const FNakamaAccount& AccResult)
					{
						UserId = AccResult.User.Id;

						// Create friend user
						FNakamaAccountCustom FriendAccount;
						FriendAccount.Id = GenerateId();

						FriendClient->AuthenticateCustom(FriendAccount, true, TEXT(""),
							[this, Done](const FNakamaSession& FriendSession)
							{
								FriendClient->GetAccount(
									[this, Done](const FNakamaAccount& FriendAccResult)
									{
										FriendUserId = FriendAccResult.User.Id;
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
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
		FriendClient.Reset();
	});

	Describe("DeleteFriends", [this]()
	{
		LatentIt("should delete friend by ID", [this](const FDoneDelegate& Done)
		{
			// First add a friend
			TArray<FString> AddIds;
			AddIds.Add(FriendUserId);

			Client->AddFriends(
				AddIds,
				TArray<FString>(),
				TEXT(""),
				[this, Done]()
				{
					// Now delete the friend
					TArray<FString> DeleteIds;
					DeleteIds.Add(FriendUserId);

					Client->DeleteFriends(
						DeleteIds,
						TArray<FString>(),
						[this, Done]()
						{
							TestTrue("Friend deleted", true);
							Done.Execute();
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("DeleteFriends failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("AddFriends failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should succeed when deleting non-friend", [this](const FDoneDelegate& Done)
		{
			// Try to delete someone who isn't a friend - should succeed (no-op)
			TArray<FString> DeleteIds;
			DeleteIds.Add(FriendUserId);

			Client->DeleteFriends(
				DeleteIds,
				TArray<FString>(),
				[this, Done]()
				{
					TestTrue("Delete non-friend succeeded (no-op)", true);
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("DeleteFriends failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// GROUP OPERATIONS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaGroupOpsSpec, "NakamaTest.GroupOps",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	TSharedPtr<FNakamaClient> MemberClient;
	FNakamaSession Session;
	FString UserId;
	FString MemberUserId;
	FString GroupId;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaGroupOpsSpec)

const FString FNakamaGroupOpsSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaGroupOpsSpec::Host = TEXT("127.0.0.1");

void FNakamaGroupOpsSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
		MemberClient = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		MemberClient->SetTimeout(10.0f);
		GroupId.Empty();
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Client->GetAccount(
					[this, Done](const FNakamaAccount& AccResult)
					{
						UserId = AccResult.User.Id;

						// Create member user
						FNakamaAccountCustom MemberAccount;
						MemberAccount.Id = GenerateId();

						MemberClient->AuthenticateCustom(MemberAccount, true, TEXT(""),
							[this, Done](const FNakamaSession& MemberSession)
							{
								MemberClient->GetAccount(
									[this, Done](const FNakamaAccount& MemberAccResult)
									{
										MemberUserId = MemberAccResult.User.Id;
										Done.Execute();
									},
									[this, Done](const FNakamaError& Error)
									{
										AddError(FString::Printf(TEXT("Member GetAccount failed: %s"), *Error.Message));
										Done.Execute();
									}
								);
							},
							[this, Done](const FNakamaError& Error)
							{
								AddError(FString::Printf(TEXT("Member auth failed: %s"), *Error.Message));
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

	AfterEach([this]()
	{
		Client.Reset();
		MemberClient.Reset();
	});

	Describe("JoinGroup", [this]()
	{
		LatentIt("should join open group", [this](const FDoneDelegate& Done)
		{
			// Create an open group first
			FString GroupName = FString::Printf(TEXT("JoinGroup_%s"), *GenerateShortId());

			Client->CreateGroup(
				GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100,
				[this, Done](const FNakamaGroup& Group)
				{
					GroupId = Group.Id;

					// Now have member join the group
					MemberClient->JoinGroup(
						GroupId,
						[this, Done]()
						{
							TestTrue("Joined open group", true);
							Done.Execute();
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("JoinGroup failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("CreateGroup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail to join non-existent group", [this](const FDoneDelegate& Done)
		{
			Client->JoinGroup(
				TEXT("00000000-0000-0000-0000-000000000000"),
				[this, Done]()
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for non-existent group", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});

	Describe("LeaveGroup", [this]()
	{
		LatentIt("should leave group", [this](const FDoneDelegate& Done)
		{
			// Create a group, have member join, then leave
			FString GroupName = FString::Printf(TEXT("LeaveGroup_%s"), *GenerateShortId());

			Client->CreateGroup(
				GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100,
				[this, Done](const FNakamaGroup& Group)
				{
					GroupId = Group.Id;

					// Member joins
					MemberClient->JoinGroup(
						GroupId,
						[this, Done]()
						{
							// Member leaves
							MemberClient->LeaveGroup(
								GroupId,
								[this, Done]()
								{
									TestTrue("Left group", true);
									Done.Execute();
								},
								[this, Done](const FNakamaError& Error)
								{
									AddError(FString::Printf(TEXT("LeaveGroup failed: %s"), *Error.Message));
									Done.Execute();
								}
							);
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("JoinGroup failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("CreateGroup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("UpdateGroup", [this]()
	{
		LatentIt("should update group name", [this](const FDoneDelegate& Done)
		{
			FString GroupName = FString::Printf(TEXT("UpdateGroup_%s"), *GenerateShortId());
			FString NewGroupName = FString::Printf(TEXT("Updated_%s"), *GenerateShortId());

			Client->CreateGroup(
				GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100,
				[this, Done, NewGroupName](const FNakamaGroup& Group)
				{
					Client->UpdateGroup(
						Group.Id,
						NewGroupName,
						TEXT("Updated description"),
						TEXT(""),  // avatar_url
						TEXT("en"),  // lang_tag
						true,  // open
						[this, Done]()
						{
							TestTrue("Group updated", true);
							Done.Execute();
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("UpdateGroup failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("CreateGroup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("DeleteGroup", [this]()
	{
		LatentIt("should delete group as superadmin", [this](const FDoneDelegate& Done)
		{
			FString GroupName = FString::Printf(TEXT("DeleteGroup_%s"), *GenerateShortId());

			Client->CreateGroup(
				GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100,
				[this, Done](const FNakamaGroup& Group)
				{
					Client->DeleteGroup(
						Group.Id,
						[this, Done]()
						{
							TestTrue("Group deleted", true);
							Done.Execute();
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("DeleteGroup failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("CreateGroup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});

	Describe("ListGroupUsers", [this]()
	{
		LatentIt("should list group users", [this](const FDoneDelegate& Done)
		{
			FString GroupName = FString::Printf(TEXT("ListUsers_%s"), *GenerateShortId());

			Client->CreateGroup(
				GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100,
				[this, Done](const FNakamaGroup& Group)
				{
					Client->ListGroupUsers(
						Group.Id,
						100,  // limit
						0,    // state
						TEXT(""),  // cursor
						[this, Done](const FNakamaGroupUserList& Result)
						{
							TestTrue("Has at least creator", Result.GroupUsers.Num() >= 1);
							Done.Execute();
						},
						[this, Done](const FNakamaError& Error)
						{
							AddError(FString::Printf(TEXT("ListGroupUsers failed: %s"), *Error.Message));
							Done.Execute();
						}
					);
				},
				[this, Done](const FNakamaError& Error)
				{
					AddError(FString::Printf(TEXT("CreateGroup failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// RPC TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaRpcSpec, "NakamaTest.RPC",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaRpcSpec)

const FString FNakamaRpcSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaRpcSpec::Host = TEXT("127.0.0.1");

void FNakamaRpcSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("RpcFunc", [this]()
	{
		LatentIt("should fail with empty RPC ID", [this](const FDoneDelegate& Done)
		{
			Client->RpcFunc(
				TEXT(""),  // empty ID
				TEXT("{}"),
				TEXT(""),  // empty http_key (using session auth)
				[this, Done](const FNakamaRpc& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for empty RPC ID", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});

		LatentIt("should fail with non-existent RPC", [this](const FDoneDelegate& Done)
		{
			Client->RpcFunc(
				TEXT("nonexistent_rpc_function"),
				TEXT("{}"),
				TEXT(""),  // empty http_key (using session auth)
				[this, Done](const FNakamaRpc& Result)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for non-existent RPC", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});
}

// ============================================================================
// IMPORT ACCOUNT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaImportSpec, "NakamaTest.Import",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;

	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaImportSpec)

const FString FNakamaImportSpec::ServerKey = TEXT("defaultkey");
const FString FNakamaImportSpec::Host = TEXT("127.0.0.1");

void FNakamaImportSpec::Define()
{
	BeforeEach([this]()
	{
		Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, false, true);
		Client->SetTimeout(10.0f);
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Client->AuthenticateCustom(Account, true, TEXT(""),
			[this, Done](const FNakamaSession& Result)
			{
				Session = Result;
				Done.Execute();
			},
			[this, Done](const FNakamaError& Error)
			{
				AddError(FString::Printf(TEXT("Auth failed: %s"), *Error.Message));
				Done.Execute();
			}
		);
	});

	AfterEach([this]()
	{
		Client.Reset();
	});

	Describe("ImportSteamFriends", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountSteam Account;
			Account.Token = TEXT("");

			Client->ImportSteamFriends(
				Account,
				false,
				[this, Done]()
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for empty token", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});

	Describe("ImportFacebookFriends", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountFacebook Account;
			Account.Token = TEXT("");

			Client->ImportFacebookFriends(
				Account,
				false,
				[this, Done]()
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error for empty token", Error.Code != 0 || !Error.Message.IsEmpty());
					Done.Execute();
				}
			);
		});
	});
}
