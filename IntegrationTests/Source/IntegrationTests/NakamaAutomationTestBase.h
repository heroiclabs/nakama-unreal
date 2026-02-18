#pragma once

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "NakamaApi.h"
#include "Templates/Function.h"

/**
 * Latent command that waits until a condition is true or times out
 */
class FNakamaWaitCommand : public IAutomationLatentCommand
{
public:
	FNakamaWaitCommand(TFunction<bool()> InCondition, TFunction<bool()> InOnTimeout, float InTimeout = 10.0f)
		: Condition(InCondition)
		, OnTimeout(InOnTimeout)
		, Timeout(InTimeout)
		, ElapsedTime(0.0f)
	{
	}

	virtual bool Update() override
	{
		ElapsedTime += FApp::GetDeltaTime();

		if (Condition())
		{
			return true;
		}

		if (ElapsedTime >= Timeout)
		{
			return OnTimeout();
		}

		return false;
	}

private:
	TFunction<bool()> Condition;
	TFunction<bool()> OnTimeout;
	float Timeout;
	float ElapsedTime;
};

/**
 * Base class for all Nakama automation tests.
 * Provides common utilities for testing Nakama API endpoints.
 */
class FNakamaAutomationTestBase : public FAutomationTestBase
{
public:
	FNakamaAutomationTestBase(const FString& InName, const bool bInComplexTask);

	/** Initialize the test client */
	void Initialize();

	/** Generate a unique ID for test isolation */
	static FString GenerateUniqueId();

	/** Generate a short unique ID (for usernames) */
	static FString GenerateShortId();

protected:
	FNakamaApiConfig NakamaClient;
	FNakamaSessionPtr Session;

	// Test configuration
	static constexpr float DefaultTimeout = 10.0f;
	static const FString ServerKey;
	static const FString Host;
	static constexpr int32 Port = 7350;
};

/**
 * Macro to define a Nakama test with standard flags
 */
#define IMPLEMENT_NAKAMA_TEST(TestClass, TestName) \
	IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(TestClass, FNakamaAutomationTestBase, TestName, \
		EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

/**
 * Helper macro to create async test with success/error callbacks
 */
#define NAKAMA_TEST_BEGIN() \
	Initialize(); \
	TSharedPtr<bool> bDone = MakeShared<bool>(false); \
	TSharedPtr<bool> bSuccess = MakeShared<bool>(false);

#define NAKAMA_TEST_END() \
	ADD_LATENT_AUTOMATION_COMMAND(FNakamaWaitCommand([bDone]() -> bool { return *bDone; }, \
		[this]() -> bool { AddError(TEXT("Test timed out")); return true; }, DefaultTimeout)); \
	return true;

/**
 * Helper for tests expecting success
 */
#define NAKAMA_ON_SUCCESS(Code) \
	[this, bDone, bSuccess](const auto& Result) { \
		Code; \
		*bSuccess = true; \
		*bDone = true; \
	}

#define NAKAMA_ON_SUCCESS_VOID() \
	[this, bDone, bSuccess]() { \
		*bSuccess = true; \
		*bDone = true; \
	}

/**
 * Helper for tests expecting specific error
 */
#define NAKAMA_ON_ERROR_EXPECTED(ExpectedCode) \
	[this, bDone, bSuccess](const FNakamaError& Error) { \
		if (Error.Code == ExpectedCode) { \
			*bSuccess = true; \
		} else { \
			AddError(FString::Printf(TEXT("Expected error code %d but got %d: %s"), ExpectedCode, Error.Code, *Error.Message)); \
		} \
		*bDone = true; \
	}

/**
 * Helper for tests expecting success but getting error
 */
#define NAKAMA_ON_ERROR_FAIL() \
	[this, bDone](const FNakamaError& Error) { \
		AddError(FString::Printf(TEXT("Unexpected error %d: %s"), Error.Code, *Error.Message)); \
		*bDone = true; \
	}

