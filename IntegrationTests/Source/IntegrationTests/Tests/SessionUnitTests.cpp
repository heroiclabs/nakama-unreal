/**
 * Session parsing / expiry / update tests.
 */

#include "NakamaClient.h"
#include "NakamaClientConfig.h"
#include "NakamaSession.h"
#include "Misc/AutomationTest.h"
#include "Misc/Guid.h"

namespace
{
	const FNakamaClientConfig SessionUnitConfig{TEXT("defaultkey"), TEXT("127.0.0.1"), 7350, false};
}

BEGIN_DEFINE_SPEC(FNakamaSessionUnitSpec, "IntegrationTests.NakamaTests.SessionUnit",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	FNakamaSession Session;

	FString GenerateId() { return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens); }

END_DEFINE_SPEC(FNakamaSessionUnitSpec)

void FNakamaSessionUnitSpec::Define()
{
	LatentAfterEach([this](const FDoneDelegate& Done)
	{
		if (Session.Token.IsEmpty()) { Done.Execute(); return; }
		Nakama::DeleteAccount(SessionUnitConfig, Session).Next([Done](FNakamaVoidResult) { Done.Execute(); });
	});

	Describe("ParseTokens", [this]()
	{
		LatentIt("should populate JWT claims from a server-issued session", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateCustom(SessionUnitConfig, true, TEXT(""), GenerateId())
			.Next([this, Done](FNakamaSessionResult Result)
			{
				if (Result.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *Result.Error.Message)); Done.Execute(); return; }
				Session = Result.Value;

				TestFalse("Token is set", Session.Token.IsEmpty());
				TestFalse("Refresh token is set", Session.RefreshToken.IsEmpty());
				TestFalse("User ID parsed from JWT", Session.UserId.IsEmpty());
				TestTrue("Issued-at parsed", Session.TokenIssuedAt > 0);
				TestTrue("Auth expiry parsed and after issued-at", Session.TokenExpiresAt > Session.TokenIssuedAt);
				TestTrue("Refresh expiry outlives auth expiry", Session.RefreshTokenExpiresAt >= Session.TokenExpiresAt);
				Done.Execute();
			});
		});

		LatentIt("should parse session variables bundled in the token", [this](const FDoneDelegate& Done)
		{
			TMap<FString, FString> Vars;
			Vars.Add(TEXT("param1"), TEXT("test value"));
			Vars.Add(TEXT("param2"), TEXT("42"));

			Nakama::AuthenticateCustom(SessionUnitConfig, true, TEXT(""), GenerateId(), Vars)
			.Next([this, Done](FNakamaSessionResult Result)
			{
				if (Result.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *Result.Error.Message)); Done.Execute(); return; }
				Session = Result.Value;

				TestEqual("param1 round-trips through the JWT", Session.Vars.FindRef(TEXT("param1")), TEXT("test value"));
				TestEqual("param2 round-trips through the JWT", Session.Vars.FindRef(TEXT("param2")), TEXT("42"));
				Done.Execute();
			});
		});
	});

	Describe("IsExpired", [this]()
	{
		LatentIt("should report a fresh session as valid and honour the buffer", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateCustom(SessionUnitConfig, true, TEXT(""), GenerateId())
			.Next([this, Done](FNakamaSessionResult Result)
			{
				if (Result.bIsError) { AddError(FString::Printf(TEXT("Auth failed: %s"), *Result.Error.Message)); Done.Execute(); return; }
				Session = Result.Value;

				TestFalse("Fresh auth token not expired", Session.IsExpired());
				TestFalse("Fresh refresh token not expired", Session.IsRefreshExpired());

				// A buffer larger than the token lifetime pushes "now" past expiry.
				const int64 HugeBuffer = 100LL * 365LL * 24LL * 60LL * 60LL; // ~100 years
				TestTrue("Considered expired under a huge buffer", Session.IsExpired(HugeBuffer));
				Done.Execute();
			});
		});
	});

	Describe("Update", [this]()
	{
		LatentIt("should replace tokens and re-parse claims while preserving identity", [this](const FDoneDelegate& Done)
		{
			Nakama::AuthenticateCustom(SessionUnitConfig, true, TEXT(""), GenerateId())
			.Next([this](FNakamaSessionResult AuthResult) -> TNakamaFuture<FNakamaSessionResult>
			{
				Session = AuthResult.Value;
				return Nakama::SessionRefresh(SessionUnitConfig, Session.RefreshToken, {});
			})
			.Next([this, Done](FNakamaSessionResult RefreshResult)
			{
				if (RefreshResult.bIsError) { AddError(FString::Printf(TEXT("Refresh failed: %s"), *RefreshResult.Error.Message)); Done.Execute(); return; }

				const FString OriginalUserId = Session.UserId;

				FNakamaSession Updated = Session;
				Updated.Update(RefreshResult.Value.Token, RefreshResult.Value.RefreshToken);

				TestEqual("Token replaced with refreshed token", Updated.Token, RefreshResult.Value.Token);
				TestEqual("Refresh token replaced", Updated.RefreshToken, RefreshResult.Value.RefreshToken);
				TestEqual("User identity preserved across update", Updated.UserId, OriginalUserId);
				TestTrue("Claims re-parsed (expiry present)", Updated.TokenExpiresAt > 0);
				TestFalse("Updated session is valid", Updated.IsExpired());
				Done.Execute();
			});
		});
	});
}
