/**
 * Cursor pagination tests.
 */

#include "NakamaClient.h"
#include "NakamaClientConfig.h"
#include "NakamaSession.h"
#include "Misc/AutomationTest.h"
#include "Misc/Guid.h"

namespace
{
	const FNakamaClientConfig PaginationConfig{TEXT("defaultkey"), TEXT("127.0.0.1"), 7350, false};
}

// ============================================================================
// STORAGE CURSOR PAGINATION
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaStoragePaginationSpec, "IntegrationTests.NakamaTests.Pagination.Storage",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaSession Session;
	FString UserId;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }
	FString GenerateShortId() { return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8); }

END_DEFINE_SPEC(FNakamaStoragePaginationSpec)

void FNakamaStoragePaginationSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(PaginationConfig, true, TEXT(""), GenerateId())
		.Next([this](const FNakamaSession& AuthResult)
		{
			Session = AuthResult;
			return Nakama::GetAccount(PaginationConfig, Session);
		})
		.Next([this, Done](FNakamaAccountResult AccResult)
		{
			if (AccResult.bIsError) { AddError(FString::Printf(TEXT("Setup failed: %s"), *AccResult.Error.Message)); Done.Execute(); return; }
			UserId = AccResult.Value.User.Id;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(PaginationConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("ListStorageObjects", [this]()
	{
		LatentIt("should walk the cursor across two disjoint pages", [this](const FDoneDelegate& Done)
		{
			const FString Collection = FString::Printf(TEXT("page_%s"), *GenerateShortId());
			constexpr int32 TotalObjects = 15;
			constexpr int32 PageSize = 10;

			TArray<FNakamaWriteStorageObject> Objects;
			for (int32 i = 0; i < TotalObjects; ++i)
			{
				FNakamaWriteStorageObject Obj;
				Obj.Collection = Collection;
				Obj.Key = FString::Printf(TEXT("key_%02d"), i);
				Obj.Value = FString::Printf(TEXT("{\"index\": %d}"), i);
				Obj.PermissionRead = 1;
				Obj.PermissionWrite = 1;
				Objects.Add(Obj);
			}

			Nakama::WriteStorageObjects(PaginationConfig, Session, Objects)
			.Next([this, Collection](const FNakamaStorageObjectAcks&)
			{
				return Nakama::ListStorageObjects(PaginationConfig, Session, UserId, Collection, PageSize, TEXT(""));
			})
			.Next([this, Done, Collection](FNakamaStorageObjectListResult Page1)
			{
				if (Page1.bIsError) { AddError(FString::Printf(TEXT("Page 1 failed: %s"), *Page1.Error.Message)); Done.Execute(); return; }

				TestEqual("Page 1 is a full page", Page1.Value.Objects.Num(), PageSize);
				TestFalse("Page 1 returns a next-page cursor", Page1.Value.Cursor.IsEmpty());

				TSet<FString> FirstPageKeys;
				for (const FNakamaStorageObject& Obj : Page1.Value.Objects)
				{
					FirstPageKeys.Add(Obj.Key);
				}

				Nakama::ListStorageObjects(PaginationConfig, Session, UserId, Collection, PageSize, Page1.Value.Cursor)
				.Next([this, Done, FirstPageKeys](FNakamaStorageObjectListResult Page2)
				{
					if (Page2.bIsError) { AddError(FString::Printf(TEXT("Page 2 failed: %s"), *Page2.Error.Message)); Done.Execute(); return; }

					TestEqual("Page 2 holds the remaining objects", Page2.Value.Objects.Num(), TotalObjects - PageSize);

					bool bDisjoint = true;
					for (const FNakamaStorageObject& Obj : Page2.Value.Objects)
					{
						if (FirstPageKeys.Contains(Obj.Key)) { bDisjoint = false; break; }
					}
					TestTrue("Page 2 keys are disjoint from page 1", bDisjoint);
					Done.Execute();
				});
			});
		});
	});
}

// ============================================================================
// FRIENDS CURSOR PAGINATION
// ============================================================================

BEGIN_DEFINE_SPEC(FNakamaFriendsPaginationSpec, "IntegrationTests.NakamaTests.Pagination.Friends",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaSession Session;
	TArray<FNakamaSession> FriendSessions;
	TArray<FString> FriendIds;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

	/** Authenticate one friend account, record its session + user id, then continue. */
	void CreateFriend(int32 Remaining, TFunction<void()> OnComplete)
	{
		if (Remaining <= 0) { OnComplete(); return; }

		Nakama::AuthenticateCustom(PaginationConfig, true, TEXT(""), GenerateId())
		.Next([this](const FNakamaSession& Auth)
		{
			FriendSessions.Add(Auth);
			return Nakama::GetAccount(PaginationConfig, Auth);
		})
		.Next([this, Remaining, OnComplete](FNakamaAccountResult Acc)
		{
			if (!Acc.bIsError) { FriendIds.Add(Acc.Value.User.Id); }
			CreateFriend(Remaining - 1, OnComplete);
		});
	}

	/** Delete each recorded friend session sequentially, then continue. */
	void DeleteFriends(int32 Index, TFunction<void()> OnComplete)
	{
		if (Index >= FriendSessions.Num()) { OnComplete(); return; }
		Nakama::DeleteAccount(PaginationConfig, FriendSessions[Index])
		.Next([this, Index, OnComplete](FNakamaVoidResult)
		{
			DeleteFriends(Index + 1, OnComplete);
		});
	}

END_DEFINE_SPEC(FNakamaFriendsPaginationSpec)

void FNakamaFriendsPaginationSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		FriendSessions.Empty();
		FriendIds.Empty();

		Nakama::AuthenticateCustom(PaginationConfig, true, TEXT(""), GenerateId())
		.Next([this, Done](FNakamaSessionResult AuthResult)
		{
			if (AuthResult.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *AuthResult.Error.Message)); Done.Execute(); return; }
			Session = AuthResult.Value;

			// Create three friend accounts, then invite them all.
			CreateFriend(3, [this, Done]()
			{
				if (FriendIds.Num() < 3) { AddError(TEXT("Failed to create friend accounts")); Done.Execute(); return; }
				Nakama::AddFriends(PaginationConfig, Session, FriendIds, {}, TEXT(""))
				.Next([Done](FNakamaVoidResult) { Done.Execute(); });
			});
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		auto DeleteMain = [this, Done]()
		{
			if (Session.Token.IsEmpty()) { Done.Execute(); return; }
			Nakama::DeleteAccount(PaginationConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
		};
		DeleteFriends(0, DeleteMain);
	});

	Describe("ListFriends", [this]()
	{
		LatentIt("should walk the cursor across two disjoint pages", [this](const FDoneDelegate& Done)
		{
			constexpr int32 PageSize = 2; // 3 invited friends -> pages of 2 + 1

			Nakama::ListFriends(PaginationConfig, Session, PageSize, {}, TEXT(""))
			.Next([this, Done](FNakamaFriendListResult Page1)
			{
				if (Page1.bIsError) { AddError(FString::Printf(TEXT("Page 1 failed: %s"), *Page1.Error.Message)); Done.Execute(); return; }

				TestEqual("Page 1 is a full page", Page1.Value.Friends.Num(), PageSize);
				TestFalse("Page 1 returns a next-page cursor", Page1.Value.Cursor.IsEmpty());

				TSet<FString> FirstPageIds;
				for (const FNakamaFriend& Friend : Page1.Value.Friends)
				{
					FirstPageIds.Add(Friend.User.Id);
				}

				Nakama::ListFriends(PaginationConfig, Session, PageSize, {}, Page1.Value.Cursor)
				.Next([this, Done, FirstPageIds](FNakamaFriendListResult Page2)
				{
					if (Page2.bIsError) { AddError(FString::Printf(TEXT("Page 2 failed: %s"), *Page2.Error.Message)); Done.Execute(); return; }

					TestTrue("Page 2 is non-empty", Page2.Value.Friends.Num() >= 1);

					bool bDisjoint = true;
					for (const FNakamaFriend& Friend : Page2.Value.Friends)
					{
						if (FirstPageIds.Contains(Friend.User.Id)) { bDisjoint = false; break; }
					}
					TestTrue("Page 2 users are disjoint from page 1", bDisjoint);
					Done.Execute();
				});
			});
		});
	});
}
