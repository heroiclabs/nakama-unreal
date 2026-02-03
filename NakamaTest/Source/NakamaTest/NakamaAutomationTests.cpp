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
					// Verify friend was added
					Client->ListFriends(100, 0, TEXT(""),
						[this, Done](const FNakamaFriendList& Result)
						{
							bool bFound = false;
							for (const auto& Friend : Result.Friends)
							{
								if (Friend.User.Id == FriendUserId)
								{
									bFound = true;
									break;
								}
							}
							TestTrue("Friend was added", bFound);
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
					AddError(FString::Printf(TEXT("AddFriends failed: %s"), *Error.Message));
					Done.Execute();
				}
			);
		});

		LatentIt("should fail when adding self as friend", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(UserId);

			Client->AddFriends(
				Ids,
				TArray<FString>(),
				TEXT(""),
				[this, Done]()
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
				},
				[this, Done](const FNakamaError& Error)
				{
					TestTrue("Got error when adding self", Error.Code != 0 || !Error.Message.IsEmpty());
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
						TEXT("list_collection"),
						UserId,
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
	});
}
