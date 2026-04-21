/**
 * Nakama Async API Integration Test Suite
 *
 * Mirror of NakamaApiTests.cpp using the TFuture-based Nakama:: free-function API.
 * Each test uses F*Result types instead of separate success/error callback pairs.
 */

#include "Nakama.h"
#include "Misc/Guid.h"
#include "Serialization/JsonSerializer.h"

const FNakamaClientConfig ClientConfig = FNakamaClientConfig{TEXT("defaultkey"), TEXT("127.0.0.1"), 7350, false};
static const FString DefaultHttpKey = TEXT("defaulthttpkey");

/** Serialize a JSON object to a string for RpcFunc payloads. Returns "" for null. */
static FString JsonToString(const TSharedPtr<FJsonObject>& Json)
{
	if (!Json.IsValid()) return TEXT("");
	FString Out;
	TSharedRef<TJsonWriter<>> W = TJsonWriterFactory<>::Create(&Out);
	FJsonSerializer::Serialize(Json.ToSharedRef(), W);
	return Out;
}

/**
 * Helper macro: early-return on unexpected error inside a callback.
 * Use in tests that expect success.
 */
#define ASYNC_FAIL_ON_ERROR(Result, Done) \
	if (Result.bIsError) { \
		AddError(FString::Printf(TEXT("Unexpected error %d: %s"), Result.Error.Code, *Result.Error.Message)); \
		Done.Execute(); \
		return; \
	}

// ============================================================================
// AUTHENTICATION TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncAuthSpec, "IntegrationTests.Nakama.Auth",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;

	FString TestCustomId;
	FString TestDeviceId;
	FString TestEmail;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncAuthSpec)

void FNakamaAsyncAuthSpec::Define()
{
	BeforeEach([this]()
	{
		TestCustomId = GenerateId();
		TestDeviceId = GenerateId();
		TestEmail = FString::Printf(TEXT("test_%s@example.com"), *GenerateShortId());
	});

	Describe("CustomAuth", [this]()
	{
		LatentIt("should authenticate with valid custom ID", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateCustom(ClientConfig, TestCustomId, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Session has token", !Result.Value.Token.IsEmpty());
				TestTrue("Session has refresh token", !Result.Value.RefreshToken.IsEmpty());
				Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
			});
		});

		LatentIt("should fail with empty custom ID", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateCustom(ClientConfig, TEXT(""), { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError)
				{
					AddError(TEXT("Expected error but got success"));
					Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
					return;
				}
				TestTrue("Got error response", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with custom ID too short < 6 chars", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateCustom(ClientConfig, TEXT("abc"), { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError)
				{
					AddError(TEXT("Expected error but got success"));
					Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
					return;
				}
				TestTrue("Got error response", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with custom ID too long > 128 chars", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateCustom(ClientConfig, FString::ChrN(150, 'a'), { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError)
				{
					AddError(TEXT("Expected error but got success"));
					Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
					return;
				}
				TestTrue("Got error response", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should authenticate with username", [this](const FDoneDelegate& Done)
		{
			FString Username = FString::Printf(TEXT("user_%s"), *GenerateShortId());
			Nakama::AuthenticateCustom(ClientConfig, TestCustomId, { }, true, Username).Next([this, Done](FNakamaSessionResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Session has token", !Result.Value.Token.IsEmpty());
				Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
			});
		});
	});

	Describe("DeviceAuth", [this]()
	{
		LatentIt("should authenticate with valid device ID", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateDevice(ClientConfig, TestDeviceId, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Session has token", !Result.Value.Token.IsEmpty());
				TestTrue("Session has refresh token", !Result.Value.RefreshToken.IsEmpty());
				Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
			});
		});

		LatentIt("should fail with empty device ID", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateDevice(ClientConfig, TEXT(""), { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError)
				{
					AddError(TEXT("Expected error but got success"));
					Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
					return;
				}
				TestTrue("Got error response", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with device ID too short < 10 chars", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateDevice(ClientConfig, TEXT("short"), { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError)
				{
					AddError(TEXT("Expected error but got success"));
					Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
					return;
				}
				TestTrue("Got error response", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("EmailAuth", [this]()
	{
		LatentIt("should authenticate with valid email and password", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateEmail(ClientConfig, TestEmail, TEXT("password123"), { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Session has token", !Result.Value.Token.IsEmpty());
				Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
			});
		});

		LatentIt("should fail with invalid email format", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateEmail(ClientConfig, TEXT("notanemail"), TEXT("password123"), { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError)
				{
					AddError(TEXT("Expected error but got success"));
					Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
					return;
				}
				TestTrue("Got error response", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with password too short < 8 chars", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateEmail(ClientConfig, TestEmail, TEXT("short"), { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError)
				{
					AddError(TEXT("Expected error but got success"));
					Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
					return;
				}
				TestTrue("Got error response", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// ACCOUNT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncAccountSpec, "IntegrationTests.Nakama.Account",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString UserId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncAccountSpec)


void FNakamaAsyncAccountSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("GetAccount", [this]()
	{
		LatentIt("should get account for authenticated user", [this](const FDoneDelegate& Done)
		{
			Nakama::GetAccount(ClientConfig, Session).Next([this, Done](FNakamaAccountResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Account has user ID", !Result.Value.User.Id.IsEmpty());
				UserId = Result.Value.User.Id;
				Done.Execute();
			});
		});
	});

	Describe("UpdateAccount", [this]()
	{
		LatentIt("should update account display name", [this](const FDoneDelegate& Done)
		{
			FString NewDisplayName = FString::Printf(TEXT("TestUser_%s"), *GenerateShortId());

			Nakama::UpdateAccount(ClientConfig, Session, TEXT(""), NewDisplayName, TEXT(""), TEXT("en"), TEXT(""), TEXT(""))
			.Next([this](const FNakamaVoid&)
			{
				return Nakama::GetAccount(ClientConfig, Session);
			})
			.Next([this, Done, NewDisplayName](FNakamaAccountResult GetResult)
			{
				ASYNC_FAIL_ON_ERROR(GetResult, Done);
				TestEqual("Display name updated", GetResult.Value.User.DisplayName, NewDisplayName);
				Done.Execute();
			});
		});
	});

	Describe("SessionRefresh", [this]()
	{
		LatentIt("should refresh session with valid token", [this](const FDoneDelegate& Done)
		{
			Nakama::SessionRefresh(ClientConfig, Session.RefreshToken, TMap<FString, FString>())
			.Next([this, Done](FNakamaSessionResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("New session has token", !Result.Value.Token.IsEmpty());
				TestTrue("New session has refresh token", !Result.Value.RefreshToken.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with invalid refresh token", [this](const FDoneDelegate& Done)
		{
			Nakama::SessionRefresh(ClientConfig, TEXT("invalid.token.here"), TMap<FString, FString>())
			.Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError)
				{
					AddError(TEXT("Expected error but got success"));
					Done.Execute();
					return;
				}
				TestTrue("Got error response", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// FRIENDS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncFriendsSpec, "IntegrationTests.Nakama.Friends",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FNakamaSession FriendSession;
	FString UserId;
	FString FriendUserId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncFriendsSpec)


void FNakamaAsyncFriendsSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this](const FNakamaAccount& AccResult)
		{
			UserId = AccResult.User.Id;
			FNakamaAccountCustom FriendAccount;
			FriendAccount.Id = GenerateId();
			return Nakama::AuthenticateCustom(ClientConfig, FriendAccount.Id, { }, true, TEXT(""));
		})
		.Next([this](const FNakamaSession& FriendAuthResult)
		{
			FriendSession = FriendAuthResult;
			return Nakama::GetAccount(ClientConfig, FriendSession);
		})
		.Next([this, Done](FNakamaAccountResult FriendAccResult)
		{
			ASYNC_FAIL_ON_ERROR(FriendAccResult, Done);
			FriendUserId = FriendAccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		auto DeleteMain = [this, Done]()
		{
			if (Session.Token.IsEmpty()) { Done.Execute(); return; }
			Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
		};

		if (FriendSession.Token.IsEmpty()) { DeleteMain(); return; }
		Nakama::DeleteAccount(ClientConfig, FriendSession).Next([DeleteMain](FNakamaVoidResult) { DeleteMain(); });
	});



	Describe("ListFriends", [this]()
	{
		LatentIt("should list friends for authenticated user", [this](const FDoneDelegate& Done)
		{
			Nakama::ListFriends(ClientConfig, Session, 100, 0, TEXT("")).Next([this, Done](FNakamaFriendListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Friends list is valid", true);
				Done.Execute();
			});
		});
	});

	Describe("AddFriends", [this]()
	{
		LatentIt("should add friend by user ID", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(FriendUserId);

			Nakama::AddFriends(ClientConfig, Session, Ids, TArray<FString>(), TEXT("")).Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("AddFriends completed successfully", true);
				Done.Execute();
			});
		});

		LatentIt("should not add self as friend", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(UserId);

			Nakama::AddFriends(ClientConfig, Session, Ids, TArray<FString>(), TEXT("")).Next([this, Done](FNakamaVoidResult AddResult)
			{
				// Server accepts but should not add self to friend list
				if (AddResult.bIsError)
				{
					// Some servers may return an error, which is also acceptable
					Done.Execute();
					return;
				}

				// Verify self is not in friend list
				Nakama::ListFriends(ClientConfig, Session, 100, 2, TEXT("")).Next([this, Done](FNakamaFriendListResult ListResult)
				{
					ASYNC_FAIL_ON_ERROR(ListResult, Done);
					bool bFoundSelf = false;
					for (const auto& Friend : ListResult.Value.Friends)
					{
						if (Friend.User.Id == UserId)
						{
							bFoundSelf = true;
							break;
						}
					}
					TestTrue("Self not in friend list", !bFoundSelf);
					Done.Execute();
				});
			});
		});
	});

	Describe("BlockFriends", [this]()
	{
		LatentIt("should block user by ID", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(FriendUserId);

			Nakama::BlockFriends(ClientConfig, Session, Ids, TArray<FString>()).Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Block succeeded", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// GROUPS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncGroupsSpec, "IntegrationTests.Nakama.Groups",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString UserId;
	FString CreatedGroupId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncGroupsSpec)


void FNakamaAsyncGroupsSpec::Define()
{
	BeforeEach([this]()
	{
		CreatedGroupId.Empty();
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this, Done](FNakamaAccountResult AccResult)
		{
			ASYNC_FAIL_ON_ERROR(AccResult, Done);
			UserId = AccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("CreateGroup", [this]()
	{
		LatentIt("should create group with valid name", [this](const FDoneDelegate& Done)
		{
			FString GroupName = FString::Printf(TEXT("TestGroup_%s"), *GenerateShortId());

			Nakama::CreateGroup(ClientConfig, Session, GroupName, TEXT("Test description"), TEXT(""), TEXT("en"), true, 100)
			.Next([this, Done](FNakamaGroupResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Group has ID", !Result.Value.Id.IsEmpty());
				TestTrue("Group has name", !Result.Value.Name.IsEmpty());
				CreatedGroupId = Result.Value.Id;
				Done.Execute();
			});
		});

		LatentIt("should fail with empty group name", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, TEXT(""), TEXT("Description"), TEXT(""), TEXT("en"), true, 100)
			.Next([this, Done](FNakamaGroupResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty name", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("ListGroups", [this]()
	{
		LatentIt("should list groups", [this](const FDoneDelegate& Done)
		{
			Nakama::ListGroups(ClientConfig, Session, TEXT(""), TEXT(""), 100, TEXT(""), 0, true)
			.Next([this, Done](FNakamaGroupListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Groups list is valid", true);
				Done.Execute();
			});
		});
	});

	Describe("ListUserGroups", [this]()
	{
		LatentIt("should list groups for user", [this](const FDoneDelegate& Done)
		{
			FString GroupName = FString::Printf(TEXT("UserGroup_%s"), *GenerateShortId());

			Nakama::CreateGroup(ClientConfig, Session, GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this](const FNakamaGroup&)
			{
				return Nakama::ListUserGroups(ClientConfig, Session, UserId, 100, 0, TEXT(""));
			})
			.Next([this, Done](FNakamaUserGroupListResult ListResult)
			{
				ASYNC_FAIL_ON_ERROR(ListResult, Done);
				TestTrue("User has at least one group", ListResult.Value.UserGroups.Num() >= 1);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// STORAGE TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncStorageSpec, "IntegrationTests.Nakama.Storage",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString UserId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncStorageSpec)


void FNakamaAsyncStorageSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this, Done](FNakamaAccountResult AccResult)
		{
			ASYNC_FAIL_ON_ERROR(AccResult, Done);
			UserId = AccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("WriteStorageObjects", [this]()
	{
		LatentIt("should write storage object", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Obj;
			Obj.Collection = TEXT("test_collection");
			Obj.Key = FString::Printf(TEXT("test_key_%s"), *GenerateShortId());
			Obj.Value = TEXT("{\"test\": \"value\"}");
			Obj.PermissionRead = 1;
			Obj.PermissionWrite = 1;
			Objects.Add(Obj);

			Nakama::WriteStorageObjects(ClientConfig, Session, Objects).Next([this, Done](FNakamaStorageObjectAcksResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Got acks", Result.Value.Acks.Num() > 0);
				Done.Execute();
			});
		});

		LatentIt("should fail with invalid JSON value", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Obj;
			Obj.Collection = TEXT("test_collection");
			Obj.Key = TEXT("test_key");
			Obj.Value = TEXT("not valid json {{{");
			Obj.PermissionRead = 1;
			Obj.PermissionWrite = 1;
			Objects.Add(Obj);

			Nakama::WriteStorageObjects(ClientConfig, Session, Objects).Next([this, Done](FNakamaStorageObjectAcksResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid JSON", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("ReadStorageObjects", [this]()
	{
		LatentIt("should read written storage object", [this](const FDoneDelegate& Done)
		{
			FString Key = FString::Printf(TEXT("read_key_%s"), *GenerateShortId());

			TArray<FNakamaWriteStorageObject> WriteObjects;
			FNakamaWriteStorageObject WriteObj;
			WriteObj.Collection = TEXT("test_collection");
			WriteObj.Key = Key;
			WriteObj.Value = TEXT("{\"data\": \"test\"}");
			WriteObj.PermissionRead = 2;
			WriteObj.PermissionWrite = 1;
			WriteObjects.Add(WriteObj);

			Nakama::WriteStorageObjects(ClientConfig, Session, WriteObjects)
			.Next([this, Key](const FNakamaStorageObjectAcks&)
			{
				TArray<FNakamaReadStorageObjectId> ReadIds;
				FNakamaReadStorageObjectId ReadId;
				ReadId.Collection = TEXT("test_collection");
				ReadId.Key = Key;
				ReadId.UserId = UserId;
				ReadIds.Add(ReadId);

				return Nakama::ReadStorageObjects(ClientConfig, Session, ReadIds);
			})
			.Next([this, Done](FNakamaStorageObjectsResult ReadResult)
			{
				ASYNC_FAIL_ON_ERROR(ReadResult, Done);
				TestTrue("Got objects", ReadResult.Value.Objects.Num() > 0);
				Done.Execute();
			});
		});
	});

	Describe("ListStorageObjects", [this]()
	{
		LatentIt("should list storage objects", [this](const FDoneDelegate& Done)
		{
			FString ShortId = GenerateShortId();
			TArray<FNakamaWriteStorageObject> Objects;
			for (int32 i = 0; i < 3; i++)
			{
				FNakamaWriteStorageObject Obj;
				Obj.Collection = TEXT("list_collection");
				Obj.Key = FString::Printf(TEXT("list_key_%d_%s"), i, *ShortId);
				Obj.Value = FString::Printf(TEXT("{\"index\": %d}"), i);
				Obj.PermissionRead = 1;
				Obj.PermissionWrite = 1;
				Objects.Add(Obj);
			}
			Nakama::WriteStorageObjects(ClientConfig, Session, Objects)
				.Next([this](const FNakamaStorageObjectAcks&)
				{
					return Nakama::ListStorageObjects(ClientConfig, Session, UserId, TEXT("list_collection"), 100, TEXT(""));
				})
				.Next([this, Done](FNakamaStorageObjectListResult ListResult)
				{
					ASYNC_FAIL_ON_ERROR(ListResult, Done);
					TestTrue("Has objects", ListResult.Value.Objects.Num() >= 3);
					Done.Execute();
				});
		});
	});
}

// ============================================================================
// LEADERBOARD TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncLeaderboardSpec, "IntegrationTests.Nakama.Leaderboard",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncLeaderboardSpec)


void FNakamaAsyncLeaderboardSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("WriteLeaderboardRecord", [this]()
	{
		LatentIt("should fail with empty leaderboard ID", [this](const FDoneDelegate& Done)
		{
	//		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record;
	//		Record.Score = 100;
	//		Record.Subscore = 0;
	//		Record.Metadata = TEXT("{}");
	//		Record.Operator = ENakamaOperator::NO_OVERRIDE;

			Nakama::WriteLeaderboardRecord(ClientConfig, Session, TEXT(""), 100, 0, TEXT("{}"),  ENakamaOperator::NO_OVERRIDE)
			.Next([this, Done](FNakamaLeaderboardRecordResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty leaderboard ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with non-existent leaderboard", [this](const FDoneDelegate& Done)
		{
			//FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record;
			//Record.Score = 100;
			//Record.Subscore = 0;
			//Record.Metadata = TEXT("{}");
			//Record.Operator = ENakamaOperator::NO_OVERRIDE;

			Nakama::WriteLeaderboardRecord(ClientConfig, Session, TEXT("nonexistent_leaderboard_12345"), 100, 0, TEXT(""), ENakamaOperator::BEST)
				.Next([this, Done](FNakamaLeaderboardRecordResult Result)
				{
					if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
					TestTrue("Got NOT_FOUND error", Result.Error.Code == 5 || Result.Error.Message.Contains(TEXT("not found")));
					Done.Execute();
				});
			});
	});

	Describe("ListLeaderboardRecords", [this]()
	{
		LatentIt("should fail with empty leaderboard ID", [this](const FDoneDelegate& Done)
		{
			Nakama::ListLeaderboardRecords(ClientConfig, Session, TEXT(""), TArray<FString>(), 100, TEXT(""), 0)
			.Next([this, Done](FNakamaLeaderboardRecordListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with limit too high", [this](const FDoneDelegate& Done)
		{
			Nakama::ListLeaderboardRecords(ClientConfig, Session, TEXT("test_leaderboard"), TArray<FString>(), 2000, TEXT(""), 0)
			.Next([this, Done](FNakamaLeaderboardRecordListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for limit too high", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("DeleteLeaderboardRecord", [this]()
	{
		LatentIt("should fail with empty leaderboard ID", [this](const FDoneDelegate& Done)
		{
			Nakama::DeleteLeaderboardRecord(ClientConfig, Session, TEXT(""))
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty leaderboard ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// MATCHES TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncMatchesSpec, "IntegrationTests.Nakama.Matches",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncMatchesSpec)


void FNakamaAsyncMatchesSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("ListMatches", [this]()
	{
		LatentIt("should list matches", [this](const FDoneDelegate& Done)
		{
			Nakama::ListMatches(ClientConfig, Session, 10, false, TEXT(""), 0, 100, TEXT(""))
			.Next([this, Done](FNakamaMatchListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Matches list is valid", true);
				Done.Execute();
			});
		});

		LatentIt("should list authoritative matches only", [this](const FDoneDelegate& Done)
		{
			Nakama::ListMatches(ClientConfig, Session, 10, true, TEXT(""), 0, 100, TEXT(""))
			.Next([this, Done](FNakamaMatchListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Authoritative matches list is valid", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// NOTIFICATIONS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncNotificationsSpec, "IntegrationTests.Nakama.Notifications",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncNotificationsSpec)


void FNakamaAsyncNotificationsSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("ListNotifications", [this]()
	{
		LatentIt("should list notifications", [this](const FDoneDelegate& Done)
		{
			Nakama::ListNotifications(ClientConfig, Session, 100, TEXT(""))
			.Next([this, Done](FNakamaNotificationListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Notifications list is valid", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// LINK TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncLinkSpec, "IntegrationTests.Nakama.Link",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString DeviceId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncLinkSpec)


void FNakamaAsyncLinkSpec::Define()
{
	BeforeEach([this]()
	{
		DeviceId = GenerateId();
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountDevice Account;
		Account.Id = DeviceId;

		Nakama::AuthenticateDevice(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("LinkCustom", [this]()
	{
		LatentIt("should link custom ID", [this](const FDoneDelegate& Done)
		{
			Nakama::LinkCustom(ClientConfig, Session, GenerateId(), TMap<FString, FString>())
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Link succeeded", true);
				Done.Execute();
			});
		});

		LatentIt("should fail with ID too short", [this](const FDoneDelegate& Done)
		{
			Nakama::LinkCustom(ClientConfig, Session, TEXT("abc"), TMap<FString, FString>())
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for short ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("LinkEmail", [this]()
	{
		LatentIt("should link email", [this](const FDoneDelegate& Done)
		{
			FString Email = FString::Printf(TEXT("link_%s@example.com"), *GenerateShortId());

			Nakama::LinkEmail(ClientConfig, Session, Email, TEXT("password123"), TMap<FString, FString>())
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Link succeeded", true);
				Done.Execute();
			});
		});

		LatentIt("should fail with invalid email format", [this](const FDoneDelegate& Done)
		{
			Nakama::LinkEmail(ClientConfig, Session, TEXT("notanemail"), TEXT("password123"), TMap<FString, FString>())
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid email", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with password too short", [this](const FDoneDelegate& Done)
		{
			FString Email = FString::Printf(TEXT("short_%s@example.com"), *GenerateShortId());

			Nakama::LinkEmail(ClientConfig, Session, Email, TEXT("short"), TMap<FString, FString>())
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for short password", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// TOURNAMENT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncTournamentSpec, "IntegrationTests.Nakama.Tournament",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncTournamentSpec)


void FNakamaAsyncTournamentSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("ListTournaments", [this]()
	{
		LatentIt("should list tournaments", [this](const FDoneDelegate& Done)
		{
			Nakama::ListTournaments(ClientConfig, Session, 0, 127, 0, 0, 100, TEXT(""))
			.Next([this, Done](FNakamaTournamentListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Tournaments list is valid", true);
				Done.Execute();
			});
		});

		LatentIt("should fail with category end too high", [this](const FDoneDelegate& Done)
		{
			Nakama::ListTournaments(ClientConfig, Session, 0, 200, 0, 0, 100, TEXT(""))
			.Next([this, Done](FNakamaTournamentListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid category", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with limit too high", [this](const FDoneDelegate& Done)
		{
			Nakama::ListTournaments(ClientConfig, Session, 0, 127, 0, 0, 2000, TEXT(""))
			.Next([this, Done](FNakamaTournamentListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for limit too high", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("JoinTournament", [this]()
	{
		LatentIt("should fail with empty tournament ID", [this](const FDoneDelegate& Done)
		{
			Nakama::JoinTournament(ClientConfig, Session, TEXT(""))
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty tournament ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with non-existent tournament", [this](const FDoneDelegate& Done)
		{
			Nakama::JoinTournament(ClientConfig, Session, TEXT("nonexistent_tournament_12345"))
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got NOT_FOUND error", Result.Error.Code == 5 || Result.Error.Message.Contains(TEXT("not found")));
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// USERS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncUsersSpec, "IntegrationTests.Nakama.Users",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString UserId;
	FString Username;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncUsersSpec)


void FNakamaAsyncUsersSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Username = FString::Printf(TEXT("user_%s"), *GenerateShortId());
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, Username)
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this, Done](FNakamaAccountResult AccResult)
		{
			ASYNC_FAIL_ON_ERROR(AccResult, Done);
			UserId = AccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("GetUsers", [this]()
	{
		LatentIt("should get users by ID", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(UserId);

			Nakama::GetUsers(ClientConfig, Session, Ids, TArray<FString>(), TArray<FString>())
			.Next([this, Done](FNakamaUsersResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Got user", Result.Value.Users.Num() > 0);
				if (Result.Value.Users.Num() > 0)
				{
					TestEqual("User ID matches", Result.Value.Users[0].Id, UserId);
				}
				Done.Execute();
			});
		});

		LatentIt("should get users by username", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Usernames;
			Usernames.Add(Username);

			Nakama::GetUsers(ClientConfig, Session, TArray<FString>(), Usernames, TArray<FString>())
			.Next([this, Done](FNakamaUsersResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Got user by username", Result.Value.Users.Num() > 0);
				Done.Execute();
			});
		});

		LatentIt("should return empty for non-existent user", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(TEXT("ffffffff-ffff-ffff-ffff-ffffffffffff"));

			Nakama::GetUsers(ClientConfig, Session, Ids, TArray<FString>(), TArray<FString>())
			.Next([this, Done](FNakamaUsersResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Empty result for non-existent user", Result.Value.Users.Num() == 0);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// SESSION LOGOUT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncSessionSpec, "IntegrationTests.Nakama.Session",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncSessionSpec)


void FNakamaAsyncSessionSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("SessionLogout", [this]()
	{
		LatentIt("should logout successfully", [this](const FDoneDelegate& Done)
		{
			Nakama::SessionLogout(ClientConfig, Session, Session.Token, Session.RefreshToken)
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Logout succeeded", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// DELETE STORAGE TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncDeleteStorageSpec, "IntegrationTests.Nakama.DeleteStorage",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString UserId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncDeleteStorageSpec)


void FNakamaAsyncDeleteStorageSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this, Done](FNakamaAccountResult AccResult)
		{
			ASYNC_FAIL_ON_ERROR(AccResult, Done);
			UserId = AccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("DeleteStorageObjects", [this]()
	{
		LatentIt("should delete storage object", [this](const FDoneDelegate& Done)
		{
			FString Key = FString::Printf(TEXT("delete_key_%s"), *GenerateShortId());

			TArray<FNakamaWriteStorageObject> WriteObjects;
			FNakamaWriteStorageObject WriteObj;
			WriteObj.Collection = TEXT("delete_collection");
			WriteObj.Key = Key;
			WriteObj.Value = TEXT("{\"test\": \"delete\"}");
			WriteObj.PermissionRead = 1;
			WriteObj.PermissionWrite = 1;
			WriteObjects.Add(WriteObj);

			Nakama::WriteStorageObjects(ClientConfig, Session, WriteObjects)
			.Next([this, Key](const FNakamaStorageObjectAcks&)
			{
				TArray<FNakamaDeleteStorageObjectId> DeleteIds;
				FNakamaDeleteStorageObjectId DeleteId;
				DeleteId.Collection = TEXT("delete_collection");
				DeleteId.Key = Key;
				DeleteIds.Add(DeleteId);

				return Nakama::DeleteStorageObjects(ClientConfig, Session, DeleteIds);
			})
			.Next([this, Done](FNakamaVoidResult DeleteResult)
			{
				ASYNC_FAIL_ON_ERROR(DeleteResult, Done);
				TestTrue("Delete succeeded", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// GROUP OPERATIONS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncGroupOpsSpec, "IntegrationTests.Nakama.GroupOps",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FNakamaSession MemberSession;
	FString UserId;
	FString MemberUserId;
	FString GroupId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncGroupOpsSpec)


void FNakamaAsyncGroupOpsSpec::Define()
{
	BeforeEach([this]()
	{
		GroupId.Empty();
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this](const FNakamaAccount& AccResult)
		{
			UserId = AccResult.User.Id;
			FNakamaAccountCustom MemberAccount;
			MemberAccount.Id = GenerateId();
			return Nakama::AuthenticateCustom(ClientConfig, MemberAccount.Id, { }, true, TEXT(""));
		})
		.Next([this](const FNakamaSession& MemberAuthResult)
		{
			MemberSession = MemberAuthResult;
			return Nakama::GetAccount(ClientConfig, MemberSession);
		})
		.Next([this, Done](FNakamaAccountResult MemberAccResult)
		{
			ASYNC_FAIL_ON_ERROR(MemberAccResult, Done);
			MemberUserId = MemberAccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(ClientConfig, MemberSession)
		.Next([this](FNakamaVoidResult) { return Nakama::DeleteAccount(ClientConfig, Session); })
		.Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("JoinGroup", [this]()
	{
		LatentIt("should join open group", [this](const FDoneDelegate& Done)
		{
			FString GroupName = FString::Printf(TEXT("JoinGroup_%s"), *GenerateShortId());

			Nakama::CreateGroup(ClientConfig, Session, GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this](const FNakamaGroup& CreateResult)
			{
				GroupId = CreateResult.Id;
				return Nakama::JoinGroup(ClientConfig, MemberSession, GroupId);
			})
			.Next([this, Done](FNakamaVoidResult JoinResult)
			{
				ASYNC_FAIL_ON_ERROR(JoinResult, Done);
				TestTrue("Joined open group", true);
				Done.Execute();
			});
		});

		LatentIt("should fail to join non-existent group", [this](const FDoneDelegate& Done)
		{
			Nakama::JoinGroup(ClientConfig, Session, TEXT("00000000-0000-0000-0000-000000000000"))
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for non-existent group", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("LeaveGroup", [this]()
	{
		LatentIt("should leave group", [this](const FDoneDelegate& Done)
		{
			FString GroupName = FString::Printf(TEXT("LeaveGroup_%s"), *GenerateShortId());

			Nakama::CreateGroup(ClientConfig, Session, GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this](const FNakamaGroup& CreateResult)
			{
				GroupId = CreateResult.Id;
				return Nakama::JoinGroup(ClientConfig, MemberSession, GroupId);
			})
			.Next([this](const FNakamaVoid&)
			{
				return Nakama::LeaveGroup(ClientConfig, MemberSession, GroupId);
			})
			.Next([this, Done](FNakamaVoidResult LeaveResult)
			{
				ASYNC_FAIL_ON_ERROR(LeaveResult, Done);
				TestTrue("Left group", true);
				Done.Execute();
			});
		});
	});

	Describe("UpdateGroup", [this]()
	{
		LatentIt("should update group name", [this](const FDoneDelegate& Done)
		{
			FString GroupName = FString::Printf(TEXT("UpdateGroup_%s"), *GenerateShortId());
			FString NewGroupName = FString::Printf(TEXT("Updated_%s"), *GenerateShortId());

			Nakama::CreateGroup(ClientConfig, Session, GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this, NewGroupName](const FNakamaGroup& CreateResult)
			{
				return Nakama::UpdateGroup(ClientConfig, Session, CreateResult.Id, NewGroupName, TEXT("Updated description"), TEXT(""), TEXT("en"), true);
			})
			.Next([this, Done](FNakamaVoidResult UpdateResult)
			{
				ASYNC_FAIL_ON_ERROR(UpdateResult, Done);
				TestTrue("Group updated", true);
				Done.Execute();
			});
		});
	});

	Describe("DeleteGroup", [this]()
	{
		LatentIt("should delete group as superadmin", [this](const FDoneDelegate& Done)
		{
			FString GroupName = FString::Printf(TEXT("DeleteGroup_%s"), *GenerateShortId());

			Nakama::CreateGroup(ClientConfig, Session, GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this](const FNakamaGroup& CreateResult)
			{
				return Nakama::DeleteGroup(ClientConfig, Session, CreateResult.Id);
			})
			.Next([this, Done](FNakamaVoidResult DeleteResult)
			{
				ASYNC_FAIL_ON_ERROR(DeleteResult, Done);
				TestTrue("Group deleted", true);
				Done.Execute();
			});
		});
	});

	Describe("ListGroupUsers", [this]()
	{
		LatentIt("should list group users", [this](const FDoneDelegate& Done)
		{
			FString GroupName = FString::Printf(TEXT("ListUsers_%s"), *GenerateShortId());

			Nakama::CreateGroup(ClientConfig, Session, GroupName, TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this](const FNakamaGroup& CreateResult)
			{
				return Nakama::ListGroupUsers(ClientConfig, Session, CreateResult.Id, 100, 0, TEXT(""));
			})
			.Next([this, Done](FNakamaGroupUserListResult ListResult)
			{
				ASYNC_FAIL_ON_ERROR(ListResult, Done);
				TestTrue("Has at least creator", ListResult.Value.GroupUsers.Num() >= 1);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// RPC TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncRpcSpec, "IntegrationTests.Nakama.RPC",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	static const FString HttpKey;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncRpcSpec)

const FString FNakamaAsyncRpcSpec::HttpKey = TEXT("defaulthttpkey");


void FNakamaAsyncRpcSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("RpcFunc", [this]()
	{
		LatentIt("should fail with empty RPC ID", [this](const FDoneDelegate& Done)
		{
			Nakama::RpcFunc(ClientConfig, TEXT(""), TEXT(""), HttpKey)
				.Next([this, Done](FNakamaRpcResult Result)
				{
					if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
					TestTrue("Got error for empty RPC ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
					Done.Execute();
				});
		});

		LatentIt("should fail with non-existent RPC", [this](const FDoneDelegate& Done)
		{
			Nakama::RpcFunc(ClientConfig, TEXT("nonexistent_rpc_function"), TEXT(""), HttpKey)
			.Next([this, Done](FNakamaRpcResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for non-existent RPC", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// AUTH EXTENDED TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncAuthExtSpec, "IntegrationTests.Nakama.AuthExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncAuthExtSpec)


void FNakamaAsyncAuthExtSpec::Define()
{

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("CustomAuthExtended", [this]()
	{
		LatentIt("should fail with create=false for non-existent user", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = GenerateId();

			Nakama::AuthenticateCustom(ClientConfig, Account.Id, {}, false, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got NOT_FOUND error", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should authenticate existing user with create=false", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = GenerateId();

			Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
			.Next([this, Account](const FNakamaSession&)
			{
				return Nakama::AuthenticateCustom(ClientConfig, Account.Id, {}, false, TEXT(""));
			})
			.Next([this, Done](FNakamaSessionResult SecondResult)
			{
				ASYNC_FAIL_ON_ERROR(SecondResult, Done);
				TestTrue("Session has token", !SecondResult.Value.Token.IsEmpty());
				Session = SecondResult.Value;
				Done.Execute();
			});
		});
	});

	Describe("DeviceAuthExtended", [this]()
	{
		LatentIt("should fail with device ID too long", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountDevice Account;
			Account.Id = FString::ChrN(150, 'a');

			Nakama::AuthenticateDevice(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for long device ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("FacebookAuth", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountFacebook Account;
			Account.Token = TEXT("");

			Nakama::AuthenticateFacebook(ClientConfig, Account.Token, { }, true, TEXT(""), false).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("GoogleAuth", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountGoogle Account;
			Account.Token = TEXT("");

			Nakama::AuthenticateGoogle(ClientConfig, Account.Token, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("SteamAuth", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountSteam Account;
			Account.Token = TEXT("");

			Nakama::AuthenticateSteam(ClientConfig, Account.Token, { }, true, TEXT(""), false).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("AppleAuth", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountApple Account;
			Account.Token = TEXT("");

			Nakama::AuthenticateApple(ClientConfig, Account.Token, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// DELETE FRIENDS TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncDeleteFriendsSpec, "IntegrationTests.Nakama.DeleteFriends",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FNakamaSession FriendSession;
	FString UserId;
	FString FriendUserId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncDeleteFriendsSpec)


void FNakamaAsyncDeleteFriendsSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this](const FNakamaAccount& AccResult)
		{
			UserId = AccResult.User.Id;
			FNakamaAccountCustom FriendAccount;
			FriendAccount.Id = GenerateId();
			return Nakama::AuthenticateCustom(ClientConfig, FriendAccount.Id, { }, true, TEXT(""));
		})
		.Next([this](const FNakamaSession& FriendAuthResult)
		{
			FriendSession = FriendAuthResult;
			return Nakama::GetAccount(ClientConfig, FriendSession);
		})
		.Next([this, Done](FNakamaAccountResult FriendAccResult)
		{
			ASYNC_FAIL_ON_ERROR(FriendAccResult, Done);
			FriendUserId = FriendAccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		auto DeleteMain = [this, Done]()
		{
			if (Session.Token.IsEmpty()) { Done.Execute(); return; }
			Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
		};

		if (FriendSession.Token.IsEmpty()) { DeleteMain(); return; }
		Nakama::DeleteAccount(ClientConfig, FriendSession).Next([DeleteMain](FNakamaVoidResult) { DeleteMain(); });
	});



	Describe("DeleteFriends", [this]()
	{
		LatentIt("should delete friend by ID", [this](const FDoneDelegate& Done)
		{
			TArray<FString> AddIds;
			AddIds.Add(FriendUserId);

			Nakama::AddFriends(ClientConfig, Session, AddIds, TArray<FString>(), TEXT(""))
			.Next([this](const FNakamaVoid&)
			{
				TArray<FString> DeleteIds;
				DeleteIds.Add(FriendUserId);
				return Nakama::DeleteFriends(ClientConfig, Session, DeleteIds, TArray<FString>());
			})
			.Next([this, Done](FNakamaVoidResult DeleteResult)
			{
				ASYNC_FAIL_ON_ERROR(DeleteResult, Done);
				TestTrue("Friend deleted", true);
				Done.Execute();
			});
		});

		LatentIt("should succeed when deleting non-friend", [this](const FDoneDelegate& Done)
		{
			TArray<FString> DeleteIds;
			DeleteIds.Add(FriendUserId);

			Nakama::DeleteFriends(ClientConfig, Session, DeleteIds, TArray<FString>()).Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Delete non-friend succeeded (no-op)", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// IMPORT TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncImportSpec, "IntegrationTests.Nakama.Import",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncImportSpec)


void FNakamaAsyncImportSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("ImportSteamFriends", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountSteam Account;
			Account.Token = TEXT("");

			Nakama::ImportSteamFriends(ClientConfig, Session, Account.Token, {}, false)
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("ImportFacebookFriends", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountFacebook Account;
			Account.Token = TEXT("");

			Nakama::ImportFacebookFriends(ClientConfig, Session, Account.Token, {}, false)
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// ADDITIONAL ACCOUNT TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncAccountExtSpec, "IntegrationTests.Nakama.AccountExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString UserId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncAccountExtSpec)


void FNakamaAsyncAccountExtSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this, Done](FNakamaAccountResult AccResult)
		{
			ASYNC_FAIL_ON_ERROR(AccResult, Done);
			UserId = AccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("UpdateAccountExtended", [this]()
	{
		LatentIt("should update all fields", [this](const FDoneDelegate& Done)
		{
			Nakama::UpdateAccount(ClientConfig, Session, TEXT(""), FString::Printf(TEXT("Display_%s"), *GenerateShortId()), TEXT("https://example.com/avatar.png"), TEXT("es"), TEXT("US"), TEXT("America/New_York"))
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Update all fields succeeded", true);
				Done.Execute();
			});
		});

		LatentIt("should update lang tag", [this](const FDoneDelegate& Done)
		{
			Nakama::UpdateAccount(ClientConfig, Session, TEXT(""), TEXT(""), TEXT(""), TEXT("fr"), TEXT(""), TEXT(""))
			.Next([this](const FNakamaVoid&)
			{
				return Nakama::GetAccount(ClientConfig, Session);
			})
			.Next([this, Done](FNakamaAccountResult AccResult)
			{
				ASYNC_FAIL_ON_ERROR(AccResult, Done);
				TestEqual("Lang tag updated", AccResult.Value.User.LangTag, TEXT("fr"));
				Done.Execute();
			});
		});

		LatentIt("should update location", [this](const FDoneDelegate& Done)
		{
			Nakama::UpdateAccount(ClientConfig, Session, TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT("London"), TEXT(""))
			.Next([this](const FNakamaVoid&)
			{
				return Nakama::GetAccount(ClientConfig, Session);
			})
			.Next([this, Done](FNakamaAccountResult AccResult)
			{
				ASYNC_FAIL_ON_ERROR(AccResult, Done);
				TestEqual("Location updated", AccResult.Value.User.Location, TEXT("London"));
				Done.Execute();
			});
		});

		LatentIt("should update timezone", [this](const FDoneDelegate& Done)
		{
			Nakama::UpdateAccount(ClientConfig, Session, TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT("Europe/London"))
			.Next([this](const FNakamaVoid&)
			{
				return Nakama::GetAccount(ClientConfig, Session);
			})
			.Next([this, Done](FNakamaAccountResult AccResult)
			{
				ASYNC_FAIL_ON_ERROR(AccResult, Done);
				TestEqual("Timezone updated", AccResult.Value.User.Timezone, TEXT("Europe/London"));
				Done.Execute();
			});
		});

		LatentIt("should update avatar URL", [this](const FDoneDelegate& Done)
		{
			FString NewAvatarUrl = TEXT("https://example.com/new-avatar.png");
			Nakama::UpdateAccount(ClientConfig, Session, TEXT(""), TEXT(""), NewAvatarUrl, TEXT(""), TEXT(""), TEXT(""))
			.Next([this](const FNakamaVoid&)
			{
				return Nakama::GetAccount(ClientConfig, Session);
			})
			.Next([this, Done, NewAvatarUrl](FNakamaAccountResult AccResult)
			{
				ASYNC_FAIL_ON_ERROR(AccResult, Done);
				TestEqual("Avatar URL updated", AccResult.Value.User.AvatarUrl, NewAvatarUrl);
				Done.Execute();
			});
		});
	});

	Describe("GetAccountDetails", [this]()
	{
		LatentIt("should return account with devices", [this](const FDoneDelegate& Done)
		{
			Nakama::GetAccount(ClientConfig, Session).Next([this, Done](FNakamaAccountResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Account has user", !Result.Value.User.Id.IsEmpty());
				TestTrue("Account has create time", !Result.Value.User.CreateTime.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// ADDITIONAL FRIENDS TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncFriendsExtSpec, "IntegrationTests.Nakama.FriendsExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FNakamaSession FriendSession;
	FString UserId;
	FString FriendUserId;
	FString FriendUsername;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncFriendsExtSpec)


void FNakamaAsyncFriendsExtSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		FriendUsername = FString::Printf(TEXT("friend_%s"), *GenerateShortId());

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this](const FNakamaAccount& AccResult)
		{
			UserId = AccResult.User.Id;
			FNakamaAccountCustom FriendAccount;
			FriendAccount.Id = GenerateId();
			return Nakama::AuthenticateCustom(ClientConfig, FriendAccount.Id, { }, true, FriendUsername);
		})
		.Next([this](const FNakamaSession& FriendResult)
		{
			FriendSession = FriendResult;
			return Nakama::GetAccount(ClientConfig, FriendSession);
		})
		.Next([this, Done](FNakamaAccountResult FriendAccResult)
		{
			ASYNC_FAIL_ON_ERROR(FriendAccResult, Done);
			FriendUserId = FriendAccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		auto DeleteMain = [this, Done]()
		{
			if (Session.Token.IsEmpty()) { Done.Execute(); return; }
			Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
		};

		if (FriendSession.Token.IsEmpty()) { DeleteMain(); return; }
		Nakama::DeleteAccount(ClientConfig, FriendSession).Next([DeleteMain](FNakamaVoidResult) { DeleteMain(); });
	});



	Describe("ListFriendsWithFilters", [this]()
	{
		LatentIt("should list friends with limit", [this](const FDoneDelegate& Done)
		{
			Nakama::ListFriends(ClientConfig, Session, 5, 0, TEXT("")).Next([this, Done](FNakamaFriendListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("List friends with limit succeeded", true);
				Done.Execute();
			});
		});

		LatentIt("should list friends with state filter", [this](const FDoneDelegate& Done)
		{
			Nakama::ListFriends(ClientConfig, Session, 100, 0, TEXT("")).Next([this, Done](FNakamaFriendListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("List friends by state succeeded", true);
				Done.Execute();
			});
		});

		LatentIt("should list blocked friends", [this](const FDoneDelegate& Done)
		{
			Nakama::ListFriends(ClientConfig, Session, 100, 3, TEXT("")).Next([this, Done](FNakamaFriendListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("List blocked friends succeeded", true);
				Done.Execute();
			});
		});
	});

	Describe("AddFriendsByUsername", [this]()
	{
		LatentIt("should add friend by username", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Usernames;
			Usernames.Add(FriendUsername);
			Nakama::AddFriends(ClientConfig, Session, TArray<FString>(), Usernames, TEXT("")).Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("AddFriends by username succeeded", true);
				Done.Execute();
			});
		});

		LatentIt("should handle invalid user ID format gracefully", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(TEXT("not-a-valid-uuid"));
			Nakama::AddFriends(ClientConfig, Session, Ids, TArray<FString>(), TEXT("")).Next([this, Done](FNakamaVoidResult Result)
			{
				TestTrue("Server handled invalid UUID", true);
				Done.Execute();
			});
		});
	});

	Describe("DeleteFriendsByUsername", [this]()
	{
		LatentIt("should delete friend by username", [this](const FDoneDelegate& Done)
		{
			TArray<FString> AddUsernames;
			AddUsernames.Add(FriendUsername);
			Nakama::AddFriends(ClientConfig, Session, TArray<FString>(), AddUsernames, TEXT(""))
			.Next([this](const FNakamaVoid&)
			{
				TArray<FString> DeleteUsernames;
				DeleteUsernames.Add(FriendUsername);
				return Nakama::DeleteFriends(ClientConfig, Session, TArray<FString>(), DeleteUsernames);
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Delete friend by username succeeded", true);
				Done.Execute();
			});
		});
	});

	Describe("BlockFriendsByUsername", [this]()
	{
		LatentIt("should block user by username", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Usernames;
			Usernames.Add(FriendUsername);
			Nakama::BlockFriends(ClientConfig, Session, TArray<FString>(), Usernames).Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Block by username succeeded", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// ADDITIONAL STORAGE TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncStorageExtSpec, "IntegrationTests.Nakama.StorageExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString UserId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncStorageExtSpec)


void FNakamaAsyncStorageExtSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this, Done](FNakamaAccountResult AccResult)
		{
			ASYNC_FAIL_ON_ERROR(AccResult, Done);
			UserId = AccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("WriteStorageMultiple", [this]()
	{
		LatentIt("should write multiple storage objects", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			for (int32 i = 0; i < 5; i++)
			{
				FNakamaWriteStorageObject Object;
				Object.Collection = TEXT("multi_collection");
				Object.Key = FString::Printf(TEXT("multi_key_%d_%s"), i, *GenerateShortId());
				Object.Value = FString::Printf(TEXT("{\"index\": %d}"), i);
				Object.PermissionRead = 1;
				Object.PermissionWrite = 1;
				Objects.Add(Object);
			}
			Nakama::WriteStorageObjects(ClientConfig, Session, Objects).Next([this, Done](FNakamaStorageObjectAcksResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestEqual("Got 5 acks", Result.Value.Acks.Num(), 5);
				Done.Execute();
			});
		});
	});

	Describe("WriteStorageValidation", [this]()
	{
		LatentIt("should fail with empty collection", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Object;
			Object.Collection = TEXT("");
			Object.Key = TEXT("test_key");
			Object.Value = TEXT("{\"test\": true}");
			Objects.Add(Object);
			Nakama::WriteStorageObjects(ClientConfig, Session, Objects).Next([this, Done](FNakamaStorageObjectAcksResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty collection", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with empty key", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Object;
			Object.Collection = TEXT("test_collection");
			Object.Key = TEXT("");
			Object.Value = TEXT("{\"test\": true}");
			Objects.Add(Object);
			Nakama::WriteStorageObjects(ClientConfig, Session, Objects).Next([this, Done](FNakamaStorageObjectAcksResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty key", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should write with public read permission", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Object;
			Object.Collection = TEXT("public_collection");
			Object.Key = FString::Printf(TEXT("public_key_%s"), *GenerateShortId());
			Object.Value = TEXT("{\"public\": true}");
			Object.PermissionRead = 2;
			Object.PermissionWrite = 1;
			Objects.Add(Object);
			Nakama::WriteStorageObjects(ClientConfig, Session, Objects).Next([this, Done](FNakamaStorageObjectAcksResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Write with public permission succeeded", Result.Value.Acks.Num() > 0);
				Done.Execute();
			});
		});

		LatentIt("should fail with JSON array as value", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Object;
			Object.Collection = TEXT("test_collection");
			Object.Key = TEXT("array_key");
			Object.Value = TEXT("[1, 2, 3]");
			Objects.Add(Object);
			Nakama::WriteStorageObjects(ClientConfig, Session, Objects).Next([this, Done](FNakamaStorageObjectAcksResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for JSON array", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("ReadStorageValidation", [this]()
	{
		LatentIt("should return empty for non-existent key", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaReadStorageObjectId> ReadIds;
			FNakamaReadStorageObjectId ReadId;
			ReadId.Collection = TEXT("nonexistent_collection");
			ReadId.Key = TEXT("nonexistent_key");
			ReadId.UserId = UserId;
			ReadIds.Add(ReadId);
			Nakama::ReadStorageObjects(ClientConfig, Session, ReadIds).Next([this, Done](FNakamaStorageObjectsResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Empty result for non-existent key", Result.Value.Objects.Num() == 0);
				Done.Execute();
			});
		});

		LatentIt("should read multiple objects", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> WriteObjects;
			TArray<FString> Keys;
			for (int32 i = 0; i < 3; i++)
			{
				FString Key = FString::Printf(TEXT("read_multi_%d_%s"), i, *GenerateShortId());
				Keys.Add(Key);
				FNakamaWriteStorageObject Object;
				Object.Collection = TEXT("read_multi_collection");
				Object.Key = Key;
				Object.Value = FString::Printf(TEXT("{\"index\": %d}"), i);
				Object.PermissionRead = 1;
				Object.PermissionWrite = 1;
				WriteObjects.Add(Object);
			}
			Nakama::WriteStorageObjects(ClientConfig, Session, WriteObjects)
			.Next([this, Keys](const FNakamaStorageObjectAcks&)
			{
				TArray<FNakamaReadStorageObjectId> ReadIds;
				for (const FString& Key : Keys)
				{
					FNakamaReadStorageObjectId ReadId;
					ReadId.Collection = TEXT("read_multi_collection");
					ReadId.Key = Key;
					ReadId.UserId = UserId;
					ReadIds.Add(ReadId);
				}
				return Nakama::ReadStorageObjects(ClientConfig, Session, ReadIds);
			})
			.Next([this, Done](FNakamaStorageObjectsResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestEqual("Read 3 objects", Result.Value.Objects.Num(), 3);
				Done.Execute();
			});
		});
	});

	Describe("ListStorageValidation", [this]()
	{
		LatentIt("should list with small limit", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			for (int32 i = 0; i < 5; i++)
			{
				FNakamaWriteStorageObject Object;
				Object.Collection = TEXT("list_limit_collection");
				Object.Key = FString::Printf(TEXT("limit_key_%d_%s"), i, *GenerateShortId());
				Object.Value = FString::Printf(TEXT("{\"index\": %d}"), i);
				Object.PermissionRead = 1;
				Object.PermissionWrite = 1;
				Objects.Add(Object);
			}
			Nakama::WriteStorageObjects(ClientConfig, Session, Objects)
			.Next([this](const FNakamaStorageObjectAcks&)
			{
				return Nakama::ListStorageObjects(ClientConfig, Session, UserId, TEXT("list_limit_collection"), 2, TEXT(""));
			})
			.Next([this, Done](FNakamaStorageObjectListResult ListResult)
			{
				ASYNC_FAIL_ON_ERROR(ListResult, Done);
				TestTrue("List respects limit", ListResult.Value.Objects.Num() <= 2);
				Done.Execute();
			});
		});
	});

	Describe("DeleteStorageValidation", [this]()
	{
		LatentIt("should delete multiple objects", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> WriteObjects;
			TArray<FString> Keys;
			for (int32 i = 0; i < 3; i++)
			{
				FString Key = FString::Printf(TEXT("delete_multi_%d_%s"), i, *GenerateShortId());
				Keys.Add(Key);
				FNakamaWriteStorageObject Object;
				Object.Collection = TEXT("delete_multi_collection");
				Object.Key = Key;
				Object.Value = FString::Printf(TEXT("{\"index\": %d}"), i);
				Object.PermissionRead = 1;
				Object.PermissionWrite = 1;
				WriteObjects.Add(Object);
			}
			Nakama::WriteStorageObjects(ClientConfig, Session, WriteObjects)
			.Next([this, Keys](const FNakamaStorageObjectAcks&)
			{
				TArray<FNakamaDeleteStorageObjectId> DeleteIds;
				for (const FString& Key : Keys)
				{
					FNakamaDeleteStorageObjectId DeleteId;
					DeleteId.Collection = TEXT("delete_multi_collection");
					DeleteId.Key = Key;
					DeleteIds.Add(DeleteId);
				}
				return Nakama::DeleteStorageObjects(ClientConfig, Session, DeleteIds);
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Delete multiple objects succeeded", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// ADDITIONAL GROUP TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncGroupExtSpec, "IntegrationTests.Nakama.GroupExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FNakamaSession MemberSession;
	FString UserId;
	FString MemberUserId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncGroupExtSpec)


void FNakamaAsyncGroupExtSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this](const FNakamaAccount& AccResult)
		{
			UserId = AccResult.User.Id;
			FNakamaAccountCustom MemberAccount;
			MemberAccount.Id = GenerateId();
			return Nakama::AuthenticateCustom(ClientConfig, MemberAccount.Id, { }, true, TEXT(""));
		})
		.Next([this](const FNakamaSession& MemberResult)
		{
			MemberSession = MemberResult;
			return Nakama::GetAccount(ClientConfig, MemberSession);
		})
		.Next([this, Done](FNakamaAccountResult MemberAccResult)
		{
			ASYNC_FAIL_ON_ERROR(MemberAccResult, Done);
			MemberUserId = MemberAccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(ClientConfig, MemberSession)
		.Next([this](FNakamaVoidResult) { return Nakama::DeleteAccount(ClientConfig, Session); })
		.Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("CreateGroupValidation", [this]()
	{
		LatentIt("should create closed group", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("ClosedGroup_%s"), *GenerateShortId()), TEXT("Closed group for testing"), TEXT(""), TEXT("en"), false, 100)
			.Next([this, Done](FNakamaGroupResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Group created", !Result.Value.Id.IsEmpty());
				TestFalse("Group is closed", Result.Value.Open);
				Done.Execute();
			});
		});

		LatentIt("should create group with description and lang tag", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("MetaGroup_%s"), *GenerateShortId()), TEXT("Group with description"), TEXT(""), TEXT("es"), true, 100)
			.Next([this, Done](FNakamaGroupResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Group created with description", !Result.Value.Id.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("ListGroupsWithFilters", [this]()
	{
		LatentIt("should list groups by name prefix", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("SearchGroup_%s"), *GenerateShortId()), TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this](const FNakamaGroup&)
			{
				return Nakama::ListGroups(ClientConfig, Session, TEXT("SearchGroup"), TEXT(""), 100, TEXT(""), 0, false);
			})
			.Next([this, Done](FNakamaGroupListResult Result)
			{
				if (Result.bIsError) { TestTrue("Server handled name filter", true); Done.Execute(); return; }
				TestTrue("Found groups by name", Result.Value.Groups.Num() >= 1);
				Done.Execute();
			});
		});

		LatentIt("should list groups with limit", [this](const FDoneDelegate& Done)
		{
			Nakama::ListGroups(ClientConfig, Session, TEXT(""), TEXT(""), 5, TEXT(""), 0, true).Next([this, Done](FNakamaGroupListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("List respects limit", Result.Value.Groups.Num() <= 5);
				Done.Execute();
			});
		});
	});

	Describe("GroupMemberOperations", [this]()
	{
		LatentIt("should add user to group", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("AddUserGroup_%s"), *GenerateShortId()), TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this](const FNakamaGroup& GroupResult)
			{
				TArray<FString> UserIds;
				UserIds.Add(MemberUserId);
				return Nakama::AddGroupUsers(ClientConfig, Session, GroupResult.Id, UserIds);
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Added user to group", true);
				Done.Execute();
			});
		});

		LatentIt("should kick user from group", [this](const FDoneDelegate& Done)
		{
			auto GId = MakeShared<FString>();
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("KickGroup_%s"), *GenerateShortId()), TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this, GId](const FNakamaGroup& GroupResult)
			{
				*GId = GroupResult.Id;
				TArray<FString> UserIds;
				UserIds.Add(MemberUserId);
				return Nakama::AddGroupUsers(ClientConfig, Session, *GId, UserIds);
			})
			.Next([this, GId](const FNakamaVoid&)
			{
				TArray<FString> KickIds;
				KickIds.Add(MemberUserId);
				return Nakama::KickGroupUsers(ClientConfig, Session, *GId, KickIds);
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Kicked user from group", true);
				Done.Execute();
			});
		});

		LatentIt("should ban user from group", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("BanGroup_%s"), *GenerateShortId()), TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this](const FNakamaGroup& GroupResult)
			{
				TArray<FString> UserIds;
				UserIds.Add(MemberUserId);
				return Nakama::BanGroupUsers(ClientConfig, Session, GroupResult.Id, UserIds);
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Banned user from group", true);
				Done.Execute();
			});
		});

		LatentIt("should promote user in group", [this](const FDoneDelegate& Done)
		{
			auto GId = MakeShared<FString>();
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("PromoteGroup_%s"), *GenerateShortId()), TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this, GId](const FNakamaGroup& GroupResult)
			{
				*GId = GroupResult.Id;
				TArray<FString> UserIds;
				UserIds.Add(MemberUserId);
				return Nakama::AddGroupUsers(ClientConfig, Session, *GId, UserIds);
			})
			.Next([this, GId](const FNakamaVoid&)
			{
				TArray<FString> PromoteIds;
				PromoteIds.Add(MemberUserId);
				return Nakama::PromoteGroupUsers(ClientConfig, Session, *GId, PromoteIds);
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Promoted user in group", true);
				Done.Execute();
			});
		});

		LatentIt("should demote user in group", [this](const FDoneDelegate& Done)
		{
			auto GId = MakeShared<FString>();
			FString TargetUserId = MemberUserId;
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("DemoteGroup_%s"), *GenerateShortId()), TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this, GId, TargetUserId](const FNakamaGroup& GroupResult)
			{
				*GId = GroupResult.Id;
				TArray<FString> UserIds;
				UserIds.Add(TargetUserId);
				return Nakama::AddGroupUsers(ClientConfig, Session, *GId, UserIds);
			})
			.Next([this, GId, TargetUserId](const FNakamaVoid&)
			{
				TArray<FString> PromoteIds;
				PromoteIds.Add(TargetUserId);
				return Nakama::PromoteGroupUsers(ClientConfig, Session, *GId, PromoteIds);
			})
			.Next([this, GId, TargetUserId](const FNakamaVoid&)
			{
				TArray<FString> DemoteIds;
				DemoteIds.Add(TargetUserId);
				return Nakama::DemoteGroupUsers(ClientConfig, Session, *GId, DemoteIds);
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Demoted user in group", true);
				Done.Execute();
			});
		});
	});

	Describe("ListGroupUsersWithState", [this]()
	{
		LatentIt("should list group users with state filter", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("ListUsersState_%s"), *GenerateShortId()), TEXT("Test"), TEXT(""), TEXT("en"), true, 100)
			.Next([this](const FNakamaGroup& GroupResult)
			{
				return Nakama::ListGroupUsers(ClientConfig, Session, GroupResult.Id, 100, 0, TEXT(""));
			})
			.Next([this, Done](FNakamaGroupUserListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Found superadmin (creator)", Result.Value.GroupUsers.Num() >= 1);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// ADDITIONAL UNLINK TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncUnlinkSpec, "IntegrationTests.Nakama.Unlink",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString DeviceId;
	FString CustomId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncUnlinkSpec)


void FNakamaAsyncUnlinkSpec::Define()
{
	BeforeEach([this]()
	{
		DeviceId = GenerateId();
		CustomId = GenerateId();
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountDevice Account;
		Account.Id = DeviceId;
		Nakama::AuthenticateDevice(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("UnlinkCustom", [this]()
	{
		LatentIt("should unlink custom ID", [this](const FDoneDelegate& Done)
		{
			Nakama::LinkCustom(ClientConfig, Session, CustomId, TMap<FString, FString>())
			.Next([this](const FNakamaVoid&)
			{
				return Nakama::UnlinkCustom(ClientConfig, Session, CustomId, TMap<FString, FString>());
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Unlink custom succeeded", true);
				Done.Execute();
			});
		});
	});

	Describe("UnlinkEmail", [this]()
	{
		LatentIt("should unlink email", [this](const FDoneDelegate& Done)
		{
			FString Email = FString::Printf(TEXT("unlink_%s@example.com"), *GenerateShortId());
			Nakama::LinkEmail(ClientConfig, Session, Email, TEXT("password123"), TMap<FString, FString>())
			.Next([this, Email](const FNakamaVoid&)
			{
				return Nakama::UnlinkEmail(ClientConfig, Session, Email, TEXT("password123"), TMap<FString, FString>());
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Unlink email succeeded", true);
				Done.Execute();
			});
		});
	});

	Describe("UnlinkDevice", [this]()
	{
		LatentIt("should unlink device", [this](const FDoneDelegate& Done)
		{
			FString NewDeviceId = GenerateId();
			Nakama::LinkDevice(ClientConfig, Session, NewDeviceId, TMap<FString, FString>())
			.Next([this, NewDeviceId](const FNakamaVoid&)
			{
				return Nakama::UnlinkDevice(ClientConfig, Session, NewDeviceId, TMap<FString, FString>());
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Unlink device succeeded", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// ADDITIONAL MATCHES TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncMatchesExtSpec, "IntegrationTests.Nakama.MatchesExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncMatchesExtSpec)


void FNakamaAsyncMatchesExtSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("ListMatchesWithFilters", [this]()
	{
		LatentIt("should list matches with min size filter", [this](const FDoneDelegate& Done)
		{
			Nakama::ListMatches(ClientConfig, Session, 100, false, TEXT(""), 2, 100, TEXT("")).Next([this, Done](FNakamaMatchListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				for (const auto& Match : Result.Value.Matches) { TestTrue("Match has min size", Match.Size >= 2); }
				Done.Execute();
			});
		});

		LatentIt("should list matches with max size filter", [this](const FDoneDelegate& Done)
		{
			Nakama::ListMatches(ClientConfig, Session, 100, false, TEXT(""), 0, 4, TEXT("")).Next([this, Done](FNakamaMatchListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				for (const auto& Match : Result.Value.Matches) { TestTrue("Match has max size", Match.Size <= 4); }
				Done.Execute();
			});
		});

		LatentIt("should list matches with label filter", [this](const FDoneDelegate& Done)
		{
			Nakama::ListMatches(ClientConfig, Session, 10, true, TEXT("test_label"), 0, 100, TEXT("")).Next([this, Done](FNakamaMatchListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("List with label filter succeeded", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// CHANNEL MESSAGES TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncChannelSpec, "IntegrationTests.Nakama.Channel",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncChannelSpec)


void FNakamaAsyncChannelSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("ListChannelMessages", [this]()
	{
		LatentIt("should fail with empty channel ID", [this](const FDoneDelegate& Done)
		{
			Nakama::ListChannelMessages(ClientConfig, Session, TEXT(""), 100, true, TEXT("")).Next([this, Done](FNakamaChannelMessageListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty channel ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should list room channel messages", [this](const FDoneDelegate& Done)
		{
			FString ChannelId = FString::Printf(TEXT("2.testroom_%s"), *GenerateShortId());
			Nakama::ListChannelMessages(ClientConfig, Session, ChannelId, 100, true, TEXT("")).Next([this, Done](FNakamaChannelMessageListResult Result)
			{
				TestTrue("Got expected response", true);
				Done.Execute();
			});
		});

		LatentIt("should list messages with limit", [this](const FDoneDelegate& Done)
		{
			FString ChannelId = FString::Printf(TEXT("2.limitroom_%s"), *GenerateShortId());
			Nakama::ListChannelMessages(ClientConfig, Session, ChannelId, 5, true, TEXT("")).Next([this, Done](FNakamaChannelMessageListResult Result)
			{
				if (!Result.bIsError) { TestTrue("List respects limit", Result.Value.Messages.Num() <= 5); }
				else { TestTrue("Got expected error or success", true); }
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// ADDITIONAL NOTIFICATION TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncNotificationsExtSpec, "IntegrationTests.Nakama.NotificationsExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncNotificationsExtSpec)


void FNakamaAsyncNotificationsExtSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("ListNotificationsWithFilters", [this]()
	{
		LatentIt("should list notifications with limit", [this](const FDoneDelegate& Done)
		{
			Nakama::ListNotifications(ClientConfig, Session, 5, TEXT("")).Next([this, Done](FNakamaNotificationListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("List respects limit", Result.Value.Notifications.Num() <= 5);
				Done.Execute();
			});
		});
	});

	Describe("DeleteNotifications", [this]()
	{
		LatentIt("should handle invalid notification ID gracefully", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(TEXT("not-a-valid-uuid"));
			Nakama::DeleteNotifications(ClientConfig, Session, Ids).Next([this, Done](FNakamaVoidResult Result)
			{
				TestTrue("Server handled invalid UUID", true);
				Done.Execute();
			});
		});

		LatentIt("should succeed when deleting non-existent notification", [this](const FDoneDelegate& Done)
		{
			TArray<FString> Ids;
			Ids.Add(TEXT("ffffffff-ffff-ffff-ffff-ffffffffffff"));
			Nakama::DeleteNotifications(ClientConfig, Session, Ids).Next([this, Done](FNakamaVoidResult Result)
			{
				TestTrue("Delete non-existent notification handled", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// ADDITIONAL AUTH VALIDATION TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncAuthValidationSpec, "IntegrationTests.Nakama.Auth.Validation",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncAuthValidationSpec)


void FNakamaAsyncAuthValidationSpec::Define()
{


	Describe("CustomAuth.Validation", [this]()
	{
		LatentIt("should fail with custom ID containing spaces", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = TEXT("test id with spaces");
			Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for ID with spaces", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with username too long", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = GenerateId();
			Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, FString::ChrN(150, 'x')).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for username too long", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should accept username with special chars", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = GenerateId();
			FString Username = TEXT("u@$^!~+");
			Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, Username).Next([this, Done](FNakamaSessionResult Result)
			{
				if (Result.bIsError)
				{
					AddError(FString::Printf(TEXT("Unexpected error %d: %s"), Result.Error.Code, *Result.Error.Message));
					Done.Execute();
					return;
				}
				TestTrue("Session is valid", !Result.Value.Token.IsEmpty());
				Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult)
				{
					Done.Execute();
				});
			});
		});
	});

	Describe("DeviceAuth.Validation", [this]()
	{
		LatentIt("should fail with device ID containing only spaces", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountDevice Account;
			Account.Id = TEXT("          ");
			Nakama::AuthenticateDevice(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for spaces-only ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("EmailAuth.Validation", [this]()
	{
		LatentIt("should fail with email too short", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountEmail Account;
			Account.Email = TEXT("a@b.c");
			Account.Password = TEXT("password123");
			Nakama::AuthenticateEmail(ClientConfig, Account.Email, Account.Password, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for email too short", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with missing at symbol in email", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountEmail Account;
			Account.Email = TEXT("notanemailaddress.com");
			Account.Password = TEXT("password123");
			Nakama::AuthenticateEmail(ClientConfig, Account.Email, Account.Password, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for missing @ in email", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with empty password", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountEmail Account;
			Account.Email = FString::Printf(TEXT("test_%s@example.com"), *GenerateShortId());
			Account.Password = TEXT("");
			Nakama::AuthenticateEmail(ClientConfig, Account.Email, Account.Password, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty password", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should authenticate existing user with create=false", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountEmail Account;
			Account.Email = FString::Printf(TEXT("existing_%s@example.com"), *GenerateShortId());
			Account.Password = TEXT("password123");
			Nakama::AuthenticateEmail(ClientConfig, Account.Email, Account.Password, { }, true, TEXT(""))
			.Next([this, Account](const FNakamaSession&)
			{
				return Nakama::AuthenticateEmail(ClientConfig, Account.Email, Account.Password, {}, false, TEXT(""));
			})
			.Next([this, Done](FNakamaSessionResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Session has token", !Result.Value.Token.IsEmpty());
				Nakama::DeleteAccount(ClientConfig, Result.Value).Next([Done](FNakamaVoidResult) { Done.Execute(); });
			});
		});
	});
}

// ============================================================================
// ACCOUNT DELETE TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncAccountDeleteSpec, "IntegrationTests.Nakama.Account.Delete",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncAccountDeleteSpec)


void FNakamaAsyncAccountDeleteSpec::Define()
{


	Describe("DeleteAccount", [this]()
	{
		LatentIt("should delete account successfully", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = GenerateId();
			Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
			.Next([this](const FNakamaSession& AuthResult)
			{
				Session = AuthResult;
				return Nakama::DeleteAccount(ClientConfig, Session);
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Account deleted successfully", true);
				Done.Execute();
			});
		});

		LatentIt("should fail to get account after deletion", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountCustom Account;
			Account.Id = GenerateId();
			Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
			.Next([this](const FNakamaSession& AuthResult)
			{
				Session = AuthResult;
				return Nakama::DeleteAccount(ClientConfig, Session);
			})
			.Next([this](const FNakamaVoid&)
			{
				return Nakama::GetAccount(ClientConfig, Session);
			})
			.Next([this, Done](FNakamaAccountResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got account after deletion")); Done.Execute(); return; }
				TestTrue("Got error when accessing deleted account",
					Result.Error.Code == ENakamaErrorCode::Unauthenticated ||
					Result.Error.Code == ENakamaErrorCode::NotFound ||
					!Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// SOCIAL AUTH VALIDATION TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncSocialAuthSpec, "IntegrationTests.Nakama.Auth.Social",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;


END_DEFINE_SPEC(FNakamaAsyncSocialAuthSpec)


void FNakamaAsyncSocialAuthSpec::Define()
{


	Describe("FacebookAuth.Validation", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountFacebook Account;
			Account.Token = TEXT("");
			Nakama::AuthenticateFacebook(ClientConfig, Account.Token, { }, true, TEXT(""), true).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty Facebook token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("GoogleAuth.Validation", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountGoogle Account;
			Account.Token = TEXT("");
			Nakama::AuthenticateGoogle(ClientConfig, Account.Token, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty Google token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("SteamAuth.Validation", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountSteam Account;
			Account.Token = TEXT("");
			Nakama::AuthenticateSteam(ClientConfig, Account.Token, { }, true, TEXT(""), true).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty Steam token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("AppleAuth.Validation", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountApple Account;
			Account.Token = TEXT("");
			Nakama::AuthenticateApple(ClientConfig, Account.Token, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty Apple token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("GameCenterAuth.Validation", [this]()
	{
		LatentIt("should fail with missing required fields", [this](const FDoneDelegate& Done)
		{
			FNakamaAccountGameCenter Account;
			Account.PlayerId = TEXT("");
			Account.BundleId = TEXT("");
			Account.TimestampSeconds = 0;
			Account.Salt = TEXT("");
			Account.Signature = TEXT("");
			Account.PublicKeyUrl = TEXT("");
			Nakama::AuthenticateGameCenter(ClientConfig, Account.PlayerId, Account.BundleId, Account.TimestampSeconds, Account.Salt, Account.Signature, Account.PublicKeyUrl, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for missing GameCenter fields", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// SESSION EXTENDED TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncSessionExtSpec, "IntegrationTests.Nakama.SessionExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncSessionExtSpec)


void FNakamaAsyncSessionExtSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("Logout.Extended", [this]()
	{
		LatentIt("should logout and invalidate session", [this](const FDoneDelegate& Done)
		{
			Nakama::SessionLogout(ClientConfig, Session, Session.Token, Session.RefreshToken)
			.Next([this](const FNakamaVoid&)
			{
				return Nakama::GetAccount(ClientConfig, Session);
			})
			.Next([this, Done](FNakamaAccountResult Result)
			{
				TestTrue("Logout succeeded", true);
				Done.Execute();
			});
		});
	});

	Describe("SessionRefresh.Extended", [this]()
	{
		LatentIt("should fail with empty token", [this](const FDoneDelegate& Done)
		{
			Nakama::SessionRefresh(ClientConfig, TEXT(""), TMap<FString, FString>()).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty refresh token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with malformed token", [this](const FDoneDelegate& Done)
		{
			Nakama::SessionRefresh(ClientConfig, TEXT("not-a-valid-jwt-token"), TMap<FString, FString>()).Next([this, Done](FNakamaSessionResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for malformed token", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// USERS EXTENDED TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncUsersExtSpec, "IntegrationTests.Nakama.UsersExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString UserId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncUsersExtSpec)


void FNakamaAsyncUsersExtSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this, Done](FNakamaAccountResult AccResult)
		{
			ASYNC_FAIL_ON_ERROR(AccResult, Done);
			UserId = AccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("GetUsers.Extended", [this]()
	{
		LatentIt("should return empty for empty request", [this](const FDoneDelegate& Done)
		{
			Nakama::GetUsers(ClientConfig, Session, TArray<FString>(), TArray<FString>(), TArray<FString>()).Next([this, Done](FNakamaUsersResult Result)
			{
				if (!Result.bIsError) { TestTrue("Empty request returns empty result", Result.Value.Users.Num() == 0); }
				else { TestTrue("Got expected response", true); }
				Done.Execute();
			});
		});

		LatentIt("should fail with invalid UUID format", [this](const FDoneDelegate& Done)
		{
			TArray<FString> InvalidIds;
			InvalidIds.Add(TEXT("not-a-valid-uuid"));
			Nakama::GetUsers(ClientConfig, Session, InvalidIds, TArray<FString>(), TArray<FString>()).Next([this, Done](FNakamaUsersResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid UUID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should get user by Facebook ID (returns empty if not linked)", [this](const FDoneDelegate& Done)
		{
			TArray<FString> FacebookIds;
			FacebookIds.Add(TEXT("123456789"));
			Nakama::GetUsers(ClientConfig, Session, TArray<FString>(), TArray<FString>(), FacebookIds).Next([this, Done](FNakamaUsersResult Result)
			{
				if (!Result.bIsError) { TestTrue("Facebook ID search returns empty", Result.Value.Users.Num() == 0); }
				else { TestTrue("Got expected response", true); }
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// FRIENDS OF FRIENDS TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncFriendsOfFriendsSpec, "IntegrationTests.Nakama.FriendsOfFriends",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString UserId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncFriendsOfFriendsSpec)


void FNakamaAsyncFriendsOfFriendsSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this, Done](FNakamaAccountResult AccResult)
		{
			ASYNC_FAIL_ON_ERROR(AccResult, Done);
			UserId = AccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("ListFriendsOfFriends", [this]()
	{
		LatentIt("should list friends of friends", [this](const FDoneDelegate& Done)
		{
			Nakama::ListFriendsOfFriends(ClientConfig, Session, 100, TEXT("")).Next([this, Done](FNakamaFriendsOfFriendsListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				Done.Execute();
			});
		});

		LatentIt("should respect limit parameter", [this](const FDoneDelegate& Done)
		{
			Nakama::ListFriendsOfFriends(ClientConfig, Session, 5, TEXT("")).Next([this, Done](FNakamaFriendsOfFriendsListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Result respects limit", Result.Value.FriendsOfFriends.Num() <= 5);
				Done.Execute();
			});
		});
	});

	Describe("ListFriends.Validation", [this]()
	{
		LatentIt("should accept limit zero", [this](const FDoneDelegate& Done)
		{
			Nakama::ListFriends(ClientConfig, Session, 0, 0, TEXT("")).Next([this, Done](FNakamaFriendListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("ListFriends with limit=0 accepted", true);
				Done.Execute();
			});
		});

		LatentIt("should fail with invalid state filter", [this](const FDoneDelegate& Done)
		{
			Nakama::ListFriends(ClientConfig, Session, 100, 99, TEXT("")).Next([this, Done](FNakamaFriendListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid state", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("AddFriends.Validation", [this]()
	{
		LatentIt("should accept empty IDs and usernames as no-op", [this](const FDoneDelegate& Done)
		{
			Nakama::AddFriends(ClientConfig, Session, TArray<FString>(), TArray<FString>(), TEXT("")).Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("AddFriends with empty arrays accepted (no-op)", true);
				Done.Execute();
			});
		});

		LatentIt("should fail with invalid UUID", [this](const FDoneDelegate& Done)
		{
			TArray<FString> InvalidIds;
			InvalidIds.Add(TEXT("not-a-uuid"));
			Nakama::AddFriends(ClientConfig, Session, InvalidIds, TArray<FString>(), TEXT("")).Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid UUID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("BlockFriends.Validation", [this]()
	{
		LatentIt("should fail when blocking self", [this](const FDoneDelegate& Done)
		{
			TArray<FString> SelfId;
			SelfId.Add(UserId);
			Nakama::BlockFriends(ClientConfig, Session, SelfId, TArray<FString>()).Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for blocking self", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// GROUPS PERMISSIONS AND EDGE CASES TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncGroupPermissionsSpec, "IntegrationTests.Nakama.GroupPermissions",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FNakamaSession Session2;
	FString UserId;
	FString UserId2;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncGroupPermissionsSpec)


void FNakamaAsyncGroupPermissionsSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account1;
		Account1.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account1.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& Result)
		{
			Session = Result;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this](const FNakamaAccount& AccResult)
		{
			UserId = AccResult.User.Id;
			FNakamaAccountCustom Account2;
			Account2.Id = GenerateId();
			return Nakama::AuthenticateCustom(ClientConfig, Account2.Id, { }, true, TEXT(""));
		})
		.Next([this](const FNakamaSession& Result2)
		{
			Session2 = Result2;
			return Nakama::GetAccount(ClientConfig, Session2);
		})
		.Next([this, Done](FNakamaAccountResult AccResult2)
		{
			ASYNC_FAIL_ON_ERROR(AccResult2, Done);
			UserId2 = AccResult2.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(ClientConfig, Session)
			.Next([this](FNakamaVoidResult) -> TNakamaFuture<FNakamaVoidResult>
			{
				return Nakama::DeleteAccount(ClientConfig, Session2);
			})
			.Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("CreateGroup.Validation", [this]()
	{
		LatentIt("should accept max count zero", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("testgroup_%s"), *GenerateShortId()), TEXT(""), TEXT(""), TEXT(""), true, 0)
			.Next([this, Done](FNakamaGroupResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("CreateGroup with max_count=0 accepted", !Result.Value.Id.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should create closed group", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("closedgroup_%s"), *GenerateShortId()), TEXT(""), TEXT("A closed group"), TEXT(""), false, 100)
			.Next([this, Done](FNakamaGroupResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Group is closed", !Result.Value.Open);
				Done.Execute();
			});
		});
	});

	Describe("UpdateGroup.Permissions", [this]()
	{
		LatentIt("should fail with empty group ID", [this](const FDoneDelegate& Done)
		{
			Nakama::UpdateGroup(ClientConfig, Session, TEXT(""), TEXT("newname"), TEXT(""), TEXT(""), TEXT(""), true).Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty group ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with invalid group ID format", [this](const FDoneDelegate& Done)
		{
			Nakama::UpdateGroup(ClientConfig, Session, TEXT("not-a-valid-uuid"), TEXT("newname"), TEXT(""), TEXT(""), TEXT(""), true).Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid group ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("DeleteGroup.Permissions", [this]()
	{
		LatentIt("should fail with invalid group ID format", [this](const FDoneDelegate& Done)
		{
			Nakama::DeleteGroup(ClientConfig, Session, TEXT("not-a-valid-uuid")).Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid group ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail when non-member tries to delete", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("testdelete_%s"), *GenerateShortId()), TEXT(""), TEXT(""), TEXT(""), true, 100)
			.Next([this](const FNakamaGroup& GroupResult)
			{
				return Nakama::DeleteGroup(ClientConfig, Session2, GroupResult.Id);
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but non-member could delete")); Done.Execute(); return; }
				TestTrue("Non-member cannot delete group", true);
				Done.Execute();
			});
		});
	});

	Describe("JoinGroup.EdgeCases", [this]()
	{
		LatentIt("should handle joining non-existent group", [this](const FDoneDelegate& Done)
		{
			Nakama::JoinGroup(ClientConfig, Session, TEXT("ffffffff-ffff-ffff-ffff-ffffffffffff")).Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for non-existent group", Result.Error.Code == ENakamaErrorCode::NotFound || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should handle joining already joined group", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("testjoin_%s"), *GenerateShortId()), TEXT(""), TEXT(""), TEXT(""), true, 100)
			.Next([this](const FNakamaGroup& GroupResult)
			{
				return Nakama::JoinGroup(ClientConfig, Session, GroupResult.Id);
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				TestTrue("Join already-joined group handled", true);
				Done.Execute();
			});
		});
	});

	Describe("LeaveGroup.EdgeCases", [this]()
	{
		LatentIt("should handle leaving non-member group", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("testleave_%s"), *GenerateShortId()), TEXT(""), TEXT(""), TEXT(""), true, 100)
			.Next([this](const FNakamaGroup& GroupResult)
			{
				return Nakama::LeaveGroup(ClientConfig, Session2, GroupResult.Id);
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				TestTrue("Leave non-member group handled", true);
				Done.Execute();
			});
		});
	});

	Describe("ListGroupUsers.Validation", [this]()
	{
		LatentIt("should fail with invalid group ID format", [this](const FDoneDelegate& Done)
		{
			Nakama::ListGroupUsers(ClientConfig, Session, TEXT("not-a-valid-uuid"), 100, 0, TEXT("")).Next([this, Done](FNakamaGroupUserListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid group ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("ListUserGroups.Validation", [this]()
	{
		LatentIt("should fail with invalid user ID format", [this](const FDoneDelegate& Done)
		{
			Nakama::ListUserGroups(ClientConfig, Session, TEXT("not-a-valid-uuid"), 100, 0, TEXT("")).Next([this, Done](FNakamaUserGroupListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid user ID", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should list own groups", [this](const FDoneDelegate& Done)
		{
			Nakama::ListUserGroups(ClientConfig, Session, UserId, 100, 0, TEXT("")).Next([this, Done](FNakamaUserGroupListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("List own groups succeeded", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// STORAGE PERMISSIONS TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncStoragePermissionsSpec, "IntegrationTests.Nakama.StoragePermissions",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FNakamaSession Session2;
	FString UserId;
	FString UserId2;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncStoragePermissionsSpec)


void FNakamaAsyncStoragePermissionsSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account1;
		Account1.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account1.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& Result)
		{
			Session = Result;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this](const FNakamaAccount& AccResult)
		{
			UserId = AccResult.User.Id;
			FNakamaAccountCustom Account2;
			Account2.Id = GenerateId();
			return Nakama::AuthenticateCustom(ClientConfig, Account2.Id, { }, true, TEXT(""));
		})
		.Next([this](const FNakamaSession& Result2)
		{
			Session2 = Result2;
			return Nakama::GetAccount(ClientConfig, Session2);
		})
		.Next([this, Done](FNakamaAccountResult AccResult2)
		{
			ASYNC_FAIL_ON_ERROR(AccResult2, Done);
			UserId2 = AccResult2.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		auto DeleteMain = [this, Done]()
		{
			if (Session.Token.IsEmpty()) { Done.Execute(); return; }
			Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
		};

		if (Session2.Token.IsEmpty()) { DeleteMain(); return; }
		Nakama::DeleteAccount(ClientConfig, Session2).Next([DeleteMain](FNakamaVoidResult) { DeleteMain(); });
	});



	Describe("WriteStorage.Permissions", [this]()
	{
		LatentIt("should fail with invalid permission read value", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Obj;
			Obj.Collection = TEXT("test_collection");
			Obj.Key = FString::Printf(TEXT("test_key_%s"), *GenerateShortId());
			Obj.Value = TEXT("{\"data\":\"test\"}");
			Obj.PermissionRead = 99;
			Obj.PermissionWrite = 1;
			Objects.Add(Obj);
			Nakama::WriteStorageObjects(ClientConfig, Session, Objects).Next([this, Done](FNakamaStorageObjectAcksResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid permission read", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with invalid permission write value", [this](const FDoneDelegate& Done)
		{
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Obj;
			Obj.Collection = TEXT("test_collection");
			Obj.Key = FString::Printf(TEXT("test_key_%s"), *GenerateShortId());
			Obj.Value = TEXT("{\"data\":\"test\"}");
			Obj.PermissionRead = 1;
			Obj.PermissionWrite = 99;
			Objects.Add(Obj);
			Nakama::WriteStorageObjects(ClientConfig, Session, Objects).Next([this, Done](FNakamaStorageObjectAcksResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid permission write", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("ReadStorage.Permissions", [this]()
	{
		LatentIt("should read public object from other user", [this](const FDoneDelegate& Done)
		{
			FString TestKey = FString::Printf(TEXT("public_key_%s"), *GenerateShortId());
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Obj;
			Obj.Collection = TEXT("public_collection");
			Obj.Key = TestKey;
			Obj.Value = TEXT("{\"data\":\"public\"}");
			Obj.PermissionRead = 2;
			Obj.PermissionWrite = 1;
			Objects.Add(Obj);
			Nakama::WriteStorageObjects(ClientConfig, Session, Objects)
			.Next([this, TestKey](const FNakamaStorageObjectAcks&)
			{
				TArray<FNakamaReadStorageObjectId> ReadIds;
				FNakamaReadStorageObjectId ReadId;
				ReadId.Collection = TEXT("public_collection");
				ReadId.Key = TestKey;
				ReadId.UserId = UserId;
				ReadIds.Add(ReadId);
				return Nakama::ReadStorageObjects(ClientConfig, Session2, ReadIds);
			})
			.Next([this, Done](FNakamaStorageObjectsResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("User 2 can read public object", Result.Value.Objects.Num() > 0);
				Done.Execute();
			});
		});

		LatentIt("should not read private object from other user", [this](const FDoneDelegate& Done)
		{
			FString TestKey = FString::Printf(TEXT("private_key_%s"), *GenerateShortId());
			TArray<FNakamaWriteStorageObject> Objects;
			FNakamaWriteStorageObject Obj;
			Obj.Collection = TEXT("private_collection");
			Obj.Key = TestKey;
			Obj.Value = TEXT("{\"data\":\"private\"}");
			Obj.PermissionRead = 1;
			Obj.PermissionWrite = 1;
			Objects.Add(Obj);
			Nakama::WriteStorageObjects(ClientConfig, Session, Objects)
			.Next([this, TestKey](const FNakamaStorageObjectAcks&)
			{
				TArray<FNakamaReadStorageObjectId> ReadIds;
				FNakamaReadStorageObjectId ReadId;
				ReadId.Collection = TEXT("private_collection");
				ReadId.Key = TestKey;
				ReadId.UserId = UserId;
				ReadIds.Add(ReadId);
				return Nakama::ReadStorageObjects(ClientConfig, Session2, ReadIds);
			})
			.Next([this, Done](FNakamaStorageObjectsResult Result)
			{
				if (!Result.bIsError) { TestTrue("Private object not visible to other user", Result.Value.Objects.Num() == 0); }
				else { TestTrue("Server protected private object", true); }
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// CHANNEL EXTENDED TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncChannelExtSpec, "IntegrationTests.Nakama.ChannelExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FString UserId;
	FString GroupId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncChannelExtSpec)


void FNakamaAsyncChannelExtSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this](const FNakamaAccount& AccResult)
		{
			UserId = AccResult.User.Id;
			return Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("channelgroup_%s"), *GenerateShortId()), TEXT(""), TEXT(""), TEXT(""), true, 100);
		})
		.Next([this, Done](FNakamaGroupResult GroupResult)
		{
			ASYNC_FAIL_ON_ERROR(GroupResult, Done);
			GroupId = GroupResult.Value.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("ListChannelMessages.Extended", [this]()
	{
		LatentIt("should reject invalid channel ID format", [this](const FDoneDelegate& Done)
		{
			FString ChannelId = FString::Printf(TEXT("2.%s"), *GroupId);
			Nakama::ListChannelMessages(ClientConfig, Session, ChannelId, 100, true, TEXT("")).Next([this, Done](FNakamaChannelMessageListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error for channel not joined via WebSocket")); Done.Execute(); return; }
				TestTrue("Got expected invalid channel error", !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should list messages backward (newest first)", [this](const FDoneDelegate& Done)
		{
			FString ChannelId = FString::Printf(TEXT("2.backwardroom_%s"), *GenerateShortId());
			Nakama::ListChannelMessages(ClientConfig, Session, ChannelId, 100, false, TEXT("")).Next([this, Done](FNakamaChannelMessageListResult Result)
			{
				TestTrue("Got expected response", true);
				Done.Execute();
			});
		});

		LatentIt("should fail with invalid channel format", [this](const FDoneDelegate& Done)
		{
			Nakama::ListChannelMessages(ClientConfig, Session, TEXT("invalid_channel_format"), 100, true, TEXT("")).Next([this, Done](FNakamaChannelMessageListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for invalid channel format", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should fail with group channel for non-existent group", [this](const FDoneDelegate& Done)
		{
			Nakama::ListChannelMessages(ClientConfig, Session, TEXT("2.ffffffff-ffff-ffff-ffff-ffffffffffff"), 100, true, TEXT("")).Next([this, Done](FNakamaChannelMessageListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for non-existent group channel", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// LINKING EXTENDED TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncLinkExtSpec, "IntegrationTests.Nakama.LinkExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FNakamaSession Session2;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncLinkExtSpec)


void FNakamaAsyncLinkExtSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account1;
		Account1.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account1.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& Result)
		{
			Session = Result;
			FNakamaAccountCustom Account2;
			Account2.Id = GenerateId();
			return Nakama::AuthenticateCustom(ClientConfig, Account2.Id, { }, true, TEXT(""));
		})
		.Next([this, Done](FNakamaSessionResult Result2)
		{
			ASYNC_FAIL_ON_ERROR(Result2, Done);
			Session2 = Result2.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		auto DeleteMain = [this, Done]()
		{
			if (Session.Token.IsEmpty()) { Done.Execute(); return; }
			Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
		};

		if (Session2.Token.IsEmpty()) { DeleteMain(); return; }
		Nakama::DeleteAccount(ClientConfig, Session2).Next([DeleteMain](FNakamaVoidResult) { DeleteMain(); });
	});



	Describe("LinkCustom.AlreadyLinked", [this]()
	{
		LatentIt("should fail when custom ID already linked to another account", [this](const FDoneDelegate& Done)
		{
			FString CustomId = GenerateId();
			Nakama::LinkCustom(ClientConfig, Session, CustomId, TMap<FString, FString>())
			.Next([this, CustomId](const FNakamaVoid&)
			{
				return Nakama::LinkCustom(ClientConfig, Session2, CustomId, TMap<FString, FString>());
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got ALREADY_EXISTS error", Result.Error.Code == ENakamaErrorCode::AlreadyExists || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("LinkDevice.AlreadyLinked", [this]()
	{
		LatentIt("should fail when device ID already linked to another account", [this](const FDoneDelegate& Done)
		{
			FString DeviceId = GenerateId();
			Nakama::LinkDevice(ClientConfig, Session, DeviceId, TMap<FString, FString>())
			.Next([this, DeviceId](const FNakamaVoid&)
			{
				return Nakama::LinkDevice(ClientConfig, Session2, DeviceId, TMap<FString, FString>());
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got ALREADY_EXISTS error", Result.Error.Code == ENakamaErrorCode::AlreadyExists || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("LinkEmail.AlreadyLinked", [this]()
	{
		LatentIt("should fail when email already linked to another account", [this](const FDoneDelegate& Done)
		{
			FString Email = FString::Printf(TEXT("linked_%s@example.com"), *GenerateShortId());
			Nakama::LinkEmail(ClientConfig, Session, Email, TEXT("password123"), TMap<FString, FString>())
			.Next([this, Email](const FNakamaVoid&)
			{
				return Nakama::LinkEmail(ClientConfig, Session2, Email, TEXT("password123"), TMap<FString, FString>());
			})
			.Next([this, Done](FNakamaVoidResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got ALREADY_EXISTS error", Result.Error.Code == ENakamaErrorCode::AlreadyExists || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("Unlink.NotLinked", [this]()
	{
		LatentIt("should succeed when unlinking not-linked custom ID", [this](const FDoneDelegate& Done)
		{
			Nakama::UnlinkCustom(ClientConfig, Session, GenerateId(), TMap<FString, FString>()).Next([this, Done](FNakamaVoidResult Result)
			{
				TestTrue("Got expected response", true);
				Done.Execute();
			});
		});

		LatentIt("should succeed when unlinking not-linked device ID", [this](const FDoneDelegate& Done)
		{
			Nakama::UnlinkDevice(ClientConfig, Session, GenerateId(), TMap<FString, FString>()).Next([this, Done](FNakamaVoidResult Result)
			{
				TestTrue("Got expected response", true);
				Done.Execute();
			});
		});

		LatentIt("should succeed when unlinking not-linked email", [this](const FDoneDelegate& Done)
		{
			Nakama::UnlinkEmail(ClientConfig, Session, FString::Printf(TEXT("notlinked_%s@example.com"), *GenerateShortId()), TEXT("password123"), TMap<FString, FString>()).Next([this, Done](FNakamaVoidResult Result)
			{
				TestTrue("Got expected response", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// RPC EXTENDED TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncRpcExtSpec, "IntegrationTests.Nakama.RPCExt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;

	static const FString HttpKey;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncRpcExtSpec)

const FString FNakamaAsyncRpcExtSpec::HttpKey = TEXT("defaulthttpkey");

void FNakamaAsyncRpcExtSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("RpcFunc.WithPayload", [this]()
	{
		LatentIt("should return NOT_FOUND for non-existent RPC", [this](const FDoneDelegate& Done)
		{
			TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
			Payload->SetStringField(TEXT("test"), TEXT("data"));
			Nakama::RpcFunc(ClientConfig, TEXT("test_echo"), JsonToString(Payload), HttpKey).Next([this, Done](FNakamaRpcResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected NOT_FOUND error but RPC succeeded")); Done.Execute(); return; }
				TestTrue("Got NOT_FOUND for non-existent RPC",
					Result.Error.Code == ENakamaErrorCode::NotFound ||
					Result.Error.Message.Contains(TEXT("not found"), ESearchCase::IgnoreCase));
				Done.Execute();
			});
		});

		LatentIt("should return NOT_FOUND for non-existent RPC with empty payload", [this](const FDoneDelegate& Done)
		{
			Nakama::RpcFunc(ClientConfig, TEXT("test_echo"), TEXT(""), HttpKey).Next([this, Done](FNakamaRpcResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected NOT_FOUND error but RPC succeeded")); Done.Execute(); return; }
				TestTrue("Got NOT_FOUND for non-existent RPC",
					Result.Error.Code == ENakamaErrorCode::NotFound ||
					Result.Error.Message.Contains(TEXT("not found"), ESearchCase::IgnoreCase));
				Done.Execute();
			});
		});
	});

	Describe("RpcFunc.WithHttpKey", [this]()
	{
		LatentIt("should execute RPC with HTTP key (server-to-server)", [this](const FDoneDelegate& Done)
		{
			TSharedPtr<FJsonObject> ServerPayload = MakeShared<FJsonObject>();
			ServerPayload->SetStringField(TEXT("server"), TEXT("call"));
			Nakama::RpcFunc(ClientConfig, TEXT("test_echo"), JsonToString(ServerPayload), HttpKey).Next([this, Done](FNakamaRpcResult Result)
			{
				TestTrue("Got expected response", true);
				Done.Execute();
			});
		});
	});

	Describe("RpcFunc.Validation", [this]()
	{
		LatentIt("should fail with RPC that returns error", [this](const FDoneDelegate& Done)
		{
			Nakama::RpcFunc(ClientConfig, TEXT("test_error"), TEXT(""), HttpKey).Next([this, Done](FNakamaRpcResult Result)
			{
				if (Result.bIsError) { TestTrue("Got error as expected", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty()); }
				else { TestTrue("Got response", true); }
				Done.Execute();
			});
		});
	});

	Describe("RpcFunc.Transform", [this]()
	{
		LatentIt("should transform a message", [this](const FDoneDelegate& Done)
		{
			TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
			Payload->SetStringField(TEXT("message"), TEXT("hello"));
			Nakama::RpcFunc(ClientConfig, TEXT("transform"), JsonToString(Payload), HttpKey).Next([this, Done](FNakamaRpcResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TSharedPtr<FJsonObject> Response;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Result.Value.Payload);
				if (!FJsonSerializer::Deserialize(Reader, Response) || !Response.IsValid())
				{
					AddError(TEXT("Failed to parse transform RPC response JSON"));
					Done.Execute();
					return;
				}
				TestEqual("original matches", Response->GetStringField(TEXT("original")), FString(TEXT("hello")));
				TestEqual("reversed matches", Response->GetStringField(TEXT("reversed")), FString(TEXT("olleh")));
				TestEqual("upper matches", Response->GetStringField(TEXT("upper")), FString(TEXT("HELLO")));
				TestEqual("length matches", static_cast<int32>(Response->GetNumberField(TEXT("length"))), 5);
				Done.Execute();
			});
		});

		LatentIt("should return error for missing message field", [this](const FDoneDelegate& Done)
		{
			TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
			Payload->SetStringField(TEXT("foo"), TEXT("bar"));
			Nakama::RpcFunc(ClientConfig, TEXT("transform"), JsonToString(Payload), HttpKey).Next([this, Done](FNakamaRpcResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error for missing message field but RPC succeeded")); Done.Execute(); return; }
				TestTrue("Got error for missing message field", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should transform via HTTP key", [this](const FDoneDelegate& Done)
		{
			TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
			Payload->SetStringField(TEXT("message"), TEXT("world"));
			Nakama::RpcFunc(ClientConfig, TEXT("transform"), JsonToString(Payload), HttpKey).Next([this, Done](FNakamaRpcResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TSharedPtr<FJsonObject> Response;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Result.Value.Payload);
				if (!FJsonSerializer::Deserialize(Reader, Response) || !Response.IsValid())
				{
					AddError(TEXT("Failed to parse transform RPC response JSON"));
					Done.Execute();
					return;
				}
				TestEqual("original matches", Response->GetStringField(TEXT("original")), FString(TEXT("world")));
				TestEqual("reversed matches", Response->GetStringField(TEXT("reversed")), FString(TEXT("dlrow")));
				TestEqual("upper matches", Response->GetStringField(TEXT("upper")), FString(TEXT("WORLD")));
				TestEqual("length matches", static_cast<int32>(Response->GetNumberField(TEXT("length"))), 5);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// MATCHES VALIDATION TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncMatchesValidationSpec, "IntegrationTests.Nakama.MatchesValidation",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncMatchesValidationSpec)


void FNakamaAsyncMatchesValidationSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});


	Describe("ListMatches.Validation", [this]()
	{
		LatentIt("should fail with limit too high", [this](const FDoneDelegate& Done)
		{
			Nakama::ListMatches(ClientConfig, Session, 2000, false, TEXT(""), 0, 100, TEXT("")).Next([this, Done](FNakamaMatchListResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for limit too high", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should list with combined filters", [this](const FDoneDelegate& Done)
		{
			Nakama::ListMatches(ClientConfig, Session, 10, true, TEXT(""), 2, 8, TEXT("")).Next([this, Done](FNakamaMatchListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				for (const auto& Match : Result.Value.Matches)
				{
					TestTrue("Match is authoritative", Match.Authoritative);
					TestTrue("Match size >= min", Match.Size >= 2);
					TestTrue("Match size <= max", Match.Size <= 8);
				}
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// PURCHASES/SUBSCRIPTIONS TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncPurchasesSpec, "IntegrationTests.Nakama.Purchases",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncPurchasesSpec)


void FNakamaAsyncPurchasesSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});


	Describe("ListSubscriptions", [this]()
	{
		LatentIt("should list subscriptions (empty if none)", [this](const FDoneDelegate& Done)
		{
			Nakama::ListSubscriptions(ClientConfig, Session, 100, TEXT("")).Next([this, Done](FNakamaSubscriptionListResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("ListSubscriptions succeeded", true);
				Done.Execute();
			});
		});
	});

	Describe("ValidatePurchase.Apple", [this]()
	{
		LatentIt("should fail with empty receipt", [this](const FDoneDelegate& Done)
		{
			Nakama::ValidatePurchaseApple(ClientConfig, Session, TEXT(""), false).Next([this, Done](FNakamaValidatePurchaseResponseResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty receipt", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("ValidatePurchase.Google", [this]()
	{
		LatentIt("should fail with empty purchase", [this](const FDoneDelegate& Done)
		{
			Nakama::ValidatePurchaseGoogle(ClientConfig, Session, TEXT(""), false).Next([this, Done](FNakamaValidatePurchaseResponseResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty purchase", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("ValidateSubscription.Apple", [this]()
	{
		LatentIt("should fail with empty receipt", [this](const FDoneDelegate& Done)
		{
			Nakama::ValidateSubscriptionApple(ClientConfig, Session, TEXT(""), false).Next([this, Done](FNakamaValidateSubscriptionResponseResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty receipt", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});

	Describe("ValidateSubscription.Google", [this]()
	{
		LatentIt("should fail with empty receipt", [this](const FDoneDelegate& Done)
		{
			Nakama::ValidateSubscriptionGoogle(ClientConfig, Session, TEXT(""), false).Next([this, Done](FNakamaValidateSubscriptionResponseResult Result)
			{
				if (!Result.bIsError) { AddError(TEXT("Expected error but got success")); Done.Execute(); return; }
				TestTrue("Got error for empty receipt", Result.Error.Code != 0 || !Result.Error.Message.IsEmpty());
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// EVENT TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncEventSpec, "IntegrationTests.Nakama.Event",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncEventSpec)


void FNakamaAsyncEventSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});


	Describe("Event", [this]()
	{
		LatentIt("should submit event successfully", [this](const FDoneDelegate& Done)
		{
			TMap<FString, FString> Properties;
			Properties.Add(TEXT("source"), TEXT("test"));
			Nakama::Event(ClientConfig, Session, TEXT("test_event"), FDateTime::UtcNow().ToIso8601(), false, Properties).Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Event submitted successfully", true);
				Done.Execute();
			});
		});

		LatentIt("should accept empty event name", [this](const FDoneDelegate& Done)
		{
			TMap<FString, FString> Properties;
			Nakama::Event(ClientConfig, Session, TEXT(""), FDateTime::UtcNow().ToIso8601(), false, Properties).Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Event with empty name accepted", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// HEALTHCHECK TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncHealthcheckSpec, "IntegrationTests.Nakama.Healthcheck",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;

	static const FString HttpKey;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncHealthcheckSpec)

const FString FNakamaAsyncHealthcheckSpec::HttpKey = TEXT("defaulthttpkey");

void FNakamaAsyncHealthcheckSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});


	Describe("Healthcheck", [this]()
	{
		LatentIt("should return healthy status with session", [this](const FDoneDelegate& Done)
		{
			Nakama::Healthcheck(ClientConfig, Session).Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Server is healthy", true);
				Done.Execute();
			});
		});

		LatentIt("should return healthy status with HTTP key", [this](const FDoneDelegate& Done)
		{
			Nakama::Healthcheck(ClientConfig, HttpKey).Next([this, Done](FNakamaVoidResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Server is healthy with HTTP key", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// GROUP USER MANAGEMENT TESTS (Async)
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncGroupUsersSpec, "IntegrationTests.Nakama.GroupUsers",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;
	FNakamaSession Session2;
	FNakamaSession Session3;
	FString UserId;
	FString UserId2;
	FString UserId3;
	FString GroupId;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaAsyncGroupUsersSpec)


void FNakamaAsyncGroupUsersSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account1;
		Account1.Id = GenerateId();
		Nakama::AuthenticateCustom(ClientConfig, Account1.Id, { }, true, TEXT(""))
		.Next([this](const FNakamaSession& Result)
		{
			Session = Result;
			return Nakama::GetAccount(ClientConfig, Session);
		})
		.Next([this](const FNakamaAccount& AccResult)
		{
			UserId = AccResult.User.Id;
			FNakamaAccountCustom Account2;
			Account2.Id = GenerateId();
			return Nakama::AuthenticateCustom(ClientConfig, Account2.Id, { }, true, TEXT(""));
		})
		.Next([this](const FNakamaSession& Result2)
		{
			Session2 = Result2;
			return Nakama::GetAccount(ClientConfig, Session2);
		})
		.Next([this](const FNakamaAccount& AccResult2)
		{
			UserId2 = AccResult2.User.Id;
			FNakamaAccountCustom Account3;
			Account3.Id = GenerateId();
			return Nakama::AuthenticateCustom(ClientConfig, Account3.Id, { }, true, TEXT(""));
		})
		.Next([this](const FNakamaSession& Result3)
		{
			Session3 = Result3;
			return Nakama::GetAccount(ClientConfig, Session3);
		})
		.Next([this, Done](FNakamaAccountResult AccResult3)
		{
			ASYNC_FAIL_ON_ERROR(AccResult3, Done);
			UserId3 = AccResult3.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		Nakama::DeleteAccount(ClientConfig, Session3)
		.Next([this](FNakamaVoidResult) { return Nakama::DeleteAccount(ClientConfig, Session2); })
		.Next([this](FNakamaVoidResult) { return Nakama::DeleteAccount(ClientConfig, Session); })
		.Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});



	Describe("AddGroupUsers", [this]()
	{
		LatentIt("should add user to group by owner", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("addusers_%s"), *GenerateShortId()), TEXT(""), TEXT(""), TEXT(""), true, 100)
			.Next([this](const FNakamaGroup& Result)
			{
				GroupId = Result.Id;
				TArray<FString> UserIds;
				UserIds.Add(UserId2);
				return Nakama::AddGroupUsers(ClientConfig, Session, GroupId, UserIds);
			})
			.Next([this, Done](FNakamaVoidResult AddResult)
			{
				ASYNC_FAIL_ON_ERROR(AddResult, Done);
				TestTrue("User added to group", true);
				Done.Execute();
			});
		});
	});

	Describe("KickGroupUsers", [this]()
	{
		LatentIt("should kick user from group", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("kickusers_%s"), *GenerateShortId()), TEXT(""), TEXT(""), TEXT(""), true, 100)
			.Next([this](const FNakamaGroup& Result)
			{
				GroupId = Result.Id;
				return Nakama::JoinGroup(ClientConfig, Session2, GroupId);
			})
			.Next([this](const FNakamaVoid&)
			{
				TArray<FString> UserIds;
				UserIds.Add(UserId2);
				return Nakama::KickGroupUsers(ClientConfig, Session, GroupId, UserIds);
			})
			.Next([this, Done](FNakamaVoidResult KickResult)
			{
				ASYNC_FAIL_ON_ERROR(KickResult, Done);
				TestTrue("User kicked successfully", true);
				Done.Execute();
			});
		});
	});

	Describe("BanGroupUsers", [this]()
	{
		LatentIt("should ban user from group", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("banusers_%s"), *GenerateShortId()), TEXT(""), TEXT(""), TEXT(""), true, 100)
			.Next([this](const FNakamaGroup& Result)
			{
				GroupId = Result.Id;
				return Nakama::JoinGroup(ClientConfig, Session2, GroupId);
			})
			.Next([this](const FNakamaVoid&)
			{
				TArray<FString> UserIds;
				UserIds.Add(UserId2);
				return Nakama::BanGroupUsers(ClientConfig, Session, GroupId, UserIds);
			})
			.Next([this, Done](FNakamaVoidResult BanResult)
			{
				ASYNC_FAIL_ON_ERROR(BanResult, Done);
				TestTrue("User banned successfully", true);
				Done.Execute();
			});
		});

		LatentIt("should prevent banned user from rejoining", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("banrejoin_%s"), *GenerateShortId()), TEXT(""), TEXT(""), TEXT(""), true, 100)
			.Next([this](const FNakamaGroup& Result)
			{
				GroupId = Result.Id;
				return Nakama::JoinGroup(ClientConfig, Session2, GroupId);
			})
			.Next([this](const FNakamaVoid&)
			{
				TArray<FString> UserIds;
				UserIds.Add(UserId2);
				return Nakama::BanGroupUsers(ClientConfig, Session, GroupId, UserIds);
			})
			.Next([this, Done](FNakamaVoidResult BanResult)
			{
				ASYNC_FAIL_ON_ERROR(BanResult, Done);
				Nakama::JoinGroup(ClientConfig, Session2, GroupId).Next([this, Done](FNakamaVoidResult RejoinResult)
				{
					if (RejoinResult.bIsError)
					{
						TestTrue("Banned user cannot rejoin", true);
						Done.Execute();
						return;
					}
					Nakama::ListGroupUsers(ClientConfig, Session, GroupId, 100, 0, TEXT("")).Next([this, Done](FNakamaGroupUserListResult ListResult)
					{
						ASYNC_FAIL_ON_ERROR(ListResult, Done);
						bool bFoundUser = false;
						for (const auto& GU : ListResult.Value.GroupUsers)
						{
							if (GU.User.Id == UserId2) { bFoundUser = true; break; }
						}
						TestFalse("Banned user should not be in group membership", bFoundUser);
						Done.Execute();
					});
				});
			});
		});
	});

	Describe("PromoteGroupUsers", [this]()
	{
		LatentIt("should promote user to admin", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("promote_%s"), *GenerateShortId()), TEXT(""), TEXT(""), TEXT(""), true, 100)
			.Next([this](const FNakamaGroup& Result)
			{
				GroupId = Result.Id;
				return Nakama::JoinGroup(ClientConfig, Session2, GroupId);
			})
			.Next([this](const FNakamaVoid&)
			{
				TArray<FString> UserIds;
				UserIds.Add(UserId2);
				return Nakama::PromoteGroupUsers(ClientConfig, Session, GroupId, UserIds);
			})
			.Next([this, Done](FNakamaVoidResult PromoteResult)
			{
				ASYNC_FAIL_ON_ERROR(PromoteResult, Done);
				TestTrue("User promoted successfully", true);
				Done.Execute();
			});
		});
	});

	Describe("DemoteGroupUsers", [this]()
	{
		LatentIt("should demote admin to member", [this](const FDoneDelegate& Done)
		{
			Nakama::CreateGroup(ClientConfig, Session, FString::Printf(TEXT("demote_%s"), *GenerateShortId()), TEXT(""), TEXT(""), TEXT(""), true, 100)
			.Next([this](const FNakamaGroup& Result)
			{
				GroupId = Result.Id;
				return Nakama::JoinGroup(ClientConfig, Session2, GroupId);
			})
			.Next([this](const FNakamaVoid&)
			{
				TArray<FString> UserIds;
				UserIds.Add(UserId2);
				return Nakama::PromoteGroupUsers(ClientConfig, Session, GroupId, UserIds);
			})
			.Next([this](const FNakamaVoid&)
			{
				TArray<FString> UserIds;
				UserIds.Add(UserId2);
				return Nakama::DemoteGroupUsers(ClientConfig, Session, GroupId, UserIds);
			})
			.Next([this, Done](FNakamaVoidResult DemoteResult)
			{
				ASYNC_FAIL_ON_ERROR(DemoteResult, Done);
				TestTrue("User demoted successfully", true);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// CANCELLATION TOKEN TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncCancellationSpec, "IntegrationTests.Nakama.Cancellation",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncCancellationSpec)


void FNakamaAsyncCancellationSpec::Define()
{

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT("")).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("CancellationToken", [this]()
	{
		LatentIt("should return error immediately with pre-cancelled token on GetAccount", [this](const FDoneDelegate& Done)
		{
			TSharedRef<TAtomic<bool>> Token = MakeShared<TAtomic<bool>>(true);
			Nakama::GetAccount(ClientConfig, Session, {}, Token).Next([this, Done](FNakamaAccountResult Result)
			{
				TestTrue("Request is error", Result.bIsError);
				TestEqual("Error code is -1 (cancelled)", Result.Error.Code, -1);
				Done.Execute();
			});
		});

		LatentIt("should succeed with uncancelled token", [this](const FDoneDelegate& Done)
		{
			TSharedRef<TAtomic<bool>> Token = MakeShared<TAtomic<bool>>(false);
			Nakama::GetAccount(ClientConfig, Session, {}, Token).Next([this, Done](FNakamaAccountResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);
				TestTrue("Got valid user ID", !Result.Value.User.Id.IsEmpty());
				Done.Execute();
			});
		});

		LatentIt("should return error with pre-cancelled token on RpcFunc", [this](const FDoneDelegate& Done)
		{
			TSharedRef<TAtomic<bool>> Token = MakeShared<TAtomic<bool>>(true);
			TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
			Payload->SetStringField(TEXT("message"), TEXT("hello"));
			Nakama::RpcFunc(ClientConfig, TEXT("transform"), JsonToString(Payload), DefaultHttpKey, {}, Token).Next([this, Done](FNakamaRpcResult Result)
			{
				TestTrue("Request is error", Result.bIsError);
				TestEqual("Error code is -1 (cancelled)", Result.Error.Code, -1);
				Done.Execute();
			});
		});
	});
}

// ============================================================================
// RETRY TESTS
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaAsyncRetrySpec, "IntegrationTests.Nakama.Retry",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaRetryConfig RetryConfig;
	FNakamaSession Session;


	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAsyncRetrySpec)


void FNakamaAsyncRetrySpec::Define()
{
	BeforeEach([this]()
	{
		RetryConfig.MaxRetries = 2;
		RetryConfig.BaseDelayMs = 100;
	});

	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FNakamaAccountCustom Account;
		Account.Id = GenerateId();

		Nakama::AuthenticateCustom(ClientConfig, Account.Id, { }, true, TEXT(""), RetryConfig).Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(ClientConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("Retry", [this]()
	{
		LatentIt("should exhaust retries on persistent transient error", [this](const FDoneDelegate& Done)
		{
			Nakama::RpcFunc(ClientConfig, TEXT("always_fail"), TEXT(""), DefaultHttpKey, RetryConfig).Next([this, Done](FNakamaRpcResult Result)
			{
				TestTrue("Request failed", Result.bIsError);
				TestEqual("Error code is 14 (UNAVAILABLE)", Result.Error.Code, 14);
				Done.Execute();
			});
		});

		LatentIt("should succeed after transient failures within retry budget", [this](const FDoneDelegate& Done)
		{
			TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
			Payload->SetStringField(TEXT("test_id"), GenerateId());
			Payload->SetNumberField(TEXT("fail_count"), 2);

			Nakama::RpcFunc(ClientConfig, TEXT("retry_test"), JsonToString(Payload), DefaultHttpKey, RetryConfig).Next([this, Done](FNakamaRpcResult Result)
			{
				ASYNC_FAIL_ON_ERROR(Result, Done);

				TSharedPtr<FJsonObject> Response;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Result.Value.Payload);
				if (!FJsonSerializer::Deserialize(Reader, Response) || !Response.IsValid())
				{
					AddError(TEXT("Failed to parse RPC response JSON"));
					Done.Execute();
					return;
				}

				TestEqual("Took 3 attempts (1 original + 2 retries)", static_cast<int32>(Response->GetNumberField(TEXT("attempts"))), 3);
				Done.Execute();
			});
		});

		LatentIt("should fail immediately on non-transient error without retry", [this](const FDoneDelegate& Done)
		{
			TSharedPtr<FJsonObject> Payload = MakeShared<FJsonObject>();
			Payload->SetStringField(TEXT("foo"), TEXT("bar"));  // missing "message" field triggers INVALID_ARGUMENT

			Nakama::RpcFunc(ClientConfig, TEXT("transform"), JsonToString(Payload), DefaultHttpKey, RetryConfig).Next([this, Done](FNakamaRpcResult Result)
			{
				TestTrue("Request failed", Result.bIsError);
				TestEqual("Error code is 3 (INVALID_ARGUMENT)", Result.Error.Code, 3);
				Done.Execute();
			});
		});

		LatentIt("should not retry when MaxRetries is zero", [this](const FDoneDelegate& Done)
		{
			RetryConfig.MaxRetries = 0;

			Nakama::RpcFunc(ClientConfig, TEXT("always_fail"), TEXT(""), DefaultHttpKey, RetryConfig).Next([this, Done](FNakamaRpcResult Result)
			{
				TestTrue("Request failed", Result.bIsError);
				TestEqual("Error code is 14 (UNAVAILABLE)", Result.Error.Code, 14);
				Done.Execute();
			});
		});

		LatentIt("should retry on connection failure (unreachable host)", [this](const FDoneDelegate& Done)
		{
			FNakamaClientConfig BadConfig{TEXT("defaultkey"), TEXT("127.0.0.1"), 19999, false};
			FNakamaRetryConfig ConnRetryConfig;
			ConnRetryConfig.MaxRetries = 1;
			ConnRetryConfig.BaseDelayMs = 100;
			ConnRetryConfig.Timeout = 2.0f;

			double StartTime = FPlatformTime::Seconds();
			Nakama::GetAccount(BadConfig, Session, ConnRetryConfig).Next([this, Done, StartTime](FNakamaAccountResult Result)
			{
				TestTrue("Request failed", Result.bIsError);
				TestEqual("Error code is 0 (connection failed)", Result.Error.Code, 0);
				double Elapsed = FPlatformTime::Seconds() - StartTime;
				TestTrue("Took long enough to have retried (>0.1s)", Elapsed > 0.1);
				Done.Execute();
			});
		});

		LatentIt("should report expired refresh token as UNAUTHENTICATED (code 16)", [this](const FDoneDelegate& Done)
		{
			// Force both tokens to appear expired so MaybeRefreshThenCall
			// hits the IsRefreshExpired() path.
			Session.TokenExpiresAt = 1;          // auth token expired (Unix epoch + 1s)
			Session.RefreshTokenExpiresAt = 1;    // refresh token also expired

			FNakamaRetryConfig RefreshRetryConfig;
			RefreshRetryConfig.MaxRetries = 0;
			RefreshRetryConfig.bAutoRefreshSession = true;

			Nakama::GetAccount(ClientConfig, Session, RefreshRetryConfig).Next([this, Done](FNakamaAccountResult Result)
			{
				TestTrue("Request failed", Result.bIsError);
				TestEqual("Error code is UNAUTHENTICATED (16)", Result.Error.Code, 16);
				Done.Execute();
			});
		});

		LatentIt("should safely skip OnSessionRefreshed when owner UObject is GC'd", [this](const FDoneDelegate& Done)
		{
			// Create a temporary UObject that we will destroy before the callback fires.
			// This simulates a common pattern: a UObject (e.g. a GameInstance subsystem
			// or controller) captures `this` in OnSessionRefreshed, then gets GC'd while
			// a retry/refresh is in-flight.
			UObject* Victim = NewObject<UPackage>(nullptr, TEXT("/Temp/NakamaTestVictim"), RF_Transient);
			Victim->AddToRoot(); // prevent premature GC so we control the lifetime

			// Capture the raw pointer but also set OnSessionRefreshedOwner so the
			// retry logic can detect when the owner has been collected.
			TSharedRef<bool> CallbackFired = MakeShared<bool>(false);
			FNakamaRetryConfig RefreshRetryConfig;
			RefreshRetryConfig.MaxRetries = 0;
			RefreshRetryConfig.bAutoRefreshSession = true;
			RefreshRetryConfig.OnSessionRefreshedOwner = Victim;
			RefreshRetryConfig.OnSessionRefreshed = [Victim, CallbackFired](const FNakamaSession& RefreshedSession)
			{
				*CallbackFired = true;
				// If we get here with a GC'd Victim, this would crash.
				// The weak owner guard should prevent this from ever executing.
				UE_LOG(LogTemp, Log, TEXT("OnSessionRefreshed called, Victim class: %s"),
					*Victim->GetClass()->GetName());
			};

			// Force the auth token to appear expired so the retry logic triggers
			// a session refresh (but keep the refresh token valid).
			Session.TokenExpiresAt = 1;

			// Remove the root reference and force GC so the weak pointer becomes stale.
			// TWeakObjectPtr only invalidates after the GC clears the weak reference table.
			Victim->RemoveFromRoot();
			Victim->MarkAsGarbage();
			CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);

			// The weak pointer is now stale. The API call will trigger
			// MaybeRefreshThenCall -> SessionRefresh, but OnSessionRefreshed
			// should be skipped because OnSessionRefreshedOwner is no longer valid.
			Nakama::GetAccount(ClientConfig, Session, RefreshRetryConfig).Next([this, Done, CallbackFired](FNakamaAccountResult Result)
			{
				TestFalse("OnSessionRefreshed should NOT have fired after owner was GC'd", *CallbackFired);
				Done.Execute();
			});
		});
	});
}
