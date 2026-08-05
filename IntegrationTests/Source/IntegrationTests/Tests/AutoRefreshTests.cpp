/**
 * Session auto-refresh behaviour tests.
 */

#include "NakamaClient.h"
#include "NakamaClientConfig.h"
#include "NakamaSession.h"
#include "Misc/AutomationTest.h"
#include "Misc/Guid.h"
#include "Containers/Ticker.h"

namespace
{
	const FNakamaClientConfig AutoRefreshConfig{TEXT("defaultkey"), TEXT("127.0.0.1"), 7350, false};

	// Far larger than any token lifetime, so a fresh session reads as expiring soon.
	constexpr int64 ForceRefreshBufferSeconds = 100LL * 365LL * 24LL * 60LL * 60LL; // ~100 years
}

BEGIN_DEFINE_SPEC(FNakamaAutoRefreshSpec, "IntegrationTests.NakamaTests.AutoRefresh",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaSession Session;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaAutoRefreshSpec)

void FNakamaAutoRefreshSpec::Define()
{
	LatentBeforeEach([this](const FDoneDelegate& Done)
	{
		Nakama::AuthenticateCustom(AutoRefreshConfig, true, TEXT(""), GenerateId())
		.Next([this, Done](FNakamaSessionResult Result)
		{
			if (Result.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *Result.Error.Message)); Done.Execute(); return; }
			Session = Result.Value;
			Done.Execute();
		});
	});

	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(AutoRefreshConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("Enabled", [this]()
	{
		LatentIt("should refresh an about-to-expire session before the request and report the new token", [this](const FDoneDelegate& Done)
		{
			const FString OriginalToken = Session.Token;
			TSharedRef<TAtomic<bool>> bRefreshed = MakeShared<TAtomic<bool>>(false);
			TSharedRef<FNakamaSession> RefreshedSession = MakeShared<FNakamaSession>();

			FNakamaRetryConfig Config;
			Config.bAutoRefreshSession = true;
			Config.AutoRefreshBufferSeconds = ForceRefreshBufferSeconds;
			Config.OnSessionRefreshed = [bRefreshed, RefreshedSession](const FNakamaSession& Updated)
			{
				*bRefreshed = true;
				*RefreshedSession = Updated;
			};

			// Need to wait for some time to ensure we don't generate the same token.
			FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda(
				[this, Done, OriginalToken, bRefreshed, RefreshedSession, Config](float) -> bool
			{
				Nakama::GetAccount(AutoRefreshConfig, Session, Config)
				.Next([this, Done, OriginalToken, bRefreshed, RefreshedSession](FNakamaAccountResult Result)
				{
					if (Result.bIsError) { AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Result.Error.Message)); Done.Execute(); return; }

					TestTrue("Auto-refresh callback fired", bRefreshed->Load());
					TestFalse("Refreshed token is set", RefreshedSession->Token.IsEmpty());
					TestNotEqual("Token was rotated by the refresh", RefreshedSession->Token, OriginalToken);

					// Persist the rotated session so AfterEach deletes the live account.
					Session.Update(RefreshedSession->Token, RefreshedSession->RefreshToken);
					Done.Execute();
				});
				return false;
			}), 1.5f);
		});
	});

	Describe("Disabled", [this]()
	{
		LatentIt("should not refresh when auto-refresh is opted out, even inside the buffer window", [this](const FDoneDelegate& Done)
		{
			TSharedRef<TAtomic<bool>> bRefreshed = MakeShared<TAtomic<bool>>(false);

			FNakamaRetryConfig Config;
			Config.bAutoRefreshSession = false;
			Config.AutoRefreshBufferSeconds = ForceRefreshBufferSeconds;
			Config.OnSessionRefreshed = [bRefreshed](const FNakamaSession&) { *bRefreshed = true; };

			Nakama::GetAccount(AutoRefreshConfig, Session, Config)
			.Next([this, Done, bRefreshed](FNakamaAccountResult Result)
			{
				// The token is actually still valid, so the request succeeds using it untouched.
				if (Result.bIsError) { AddError(FString::Printf(TEXT("GetAccount failed: %s"), *Result.Error.Message)); Done.Execute(); return; }
				TestFalse("Auto-refresh callback did not fire", bRefreshed->Load());
				Done.Execute();
			});
		});
	});
}
