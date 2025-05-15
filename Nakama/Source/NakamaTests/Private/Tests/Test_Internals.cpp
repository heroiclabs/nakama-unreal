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

#include "GenericPlatform/GenericPlatformHttp.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(Test_Internals, "Nakama.Base.Internals.UriEncode",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

// It is important to use TEXT macro, otherwise this test would fail!
bool Test_Internals::RunTest(const FString& Parameters)
{
	FString Input = TEXT("βσκαταη3");
	FString Expected = TEXT("%CE%B2%CF%83%CE%BA%CE%B1%CF%84%CE%B1%CE%B73");

	const FString EncodedString = FGenericPlatformHttp::UrlEncode(Input);

	if( EncodedString != Expected )
	{
		UE_LOG(LogTemp, Display, TEXT("EncodedString: %s"), *EncodedString);
		UE_LOG(LogTemp, Display, TEXT("Expected: %s"), *Expected);
		TestFalse("UriEncode Test Failed", true);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("EncodedString: %s"), *EncodedString);
		UE_LOG(LogTemp, Display, TEXT("Expected: %s"), *Expected);
		TestTrue("UriEncode Test Passed", true);
	}
	
	// Make the test pass by returning true, or fail by returning false.
	return true;
}
