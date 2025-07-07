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

#include "Tests/Test_Groups.h"
#include "Misc/AutomationTest.h"

// List Groups
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(ListGroups, FNakamaGroupsTestBase, "Nakama.Base.Groups.List", NAKAMA_MODULE_TEST_MASK)
inline bool ListGroups::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();

	// Auth Success
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;
		UE_LOG(LogTemp, Display, TEXT("Session Token: %s"), *Session->GetAuthToken());

		// List Groups
		DoListGroups();
	};

	// Call the AuthenticateEmail functions
	Client->AuthenticateDevice("mytestdevice0000", true, {}, {}, successCallback, {});

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

void FNakamaGroupsTestBase::DoListGroups()
{
	auto successCallback = [this](const FNakamaGroupList& Groups)
	{
		UE_LOG(LogTemp, Display, TEXT("List Groups Success. Groups: %d"), Groups.Groups.Num());

		if (Groups.Groups.Num() > 0)
		{
			// Group exists, update it
			UpdateGroup(Groups.Groups[0].Id);
		}
		else
		{
			// Group does not exist, create it
			CreateGroup();
		}
	};

	auto errorCallback = [this](const FNakamaError& Error)
	{
		UE_LOG(LogTemp, Error, TEXT("List Groups Error: %s"), *Error.Message);
		TestFalse("List Groups Test Failed", true);
		StopTest();
	};

	Client->ListGroups(Session, GroupName, 0, "", successCallback, errorCallback);
}

void FNakamaGroupsTestBase::CreateGroup()
{

	auto successCallback = [this] (const FNakamaGroup& Group)
	{
		UpdateGroup(Group.Id);
	};

	auto errorCallback = [this] (const FNakamaError& Error)
	{
		UE_LOG(LogTemp, Error, TEXT("Create Group Error: %s"), *Error.Message);
		TestFalse("Create Group Test Failed", true);
		StopTest();
	};

	FString Description = TEXT("Nakama is cool!");

	Client->CreateGroup(
		Session,
		GroupName,
		Description,
		"", // Avatar URL
		"", 
		true, // Open
		{},
		successCallback,
		errorCallback
	);
}

void FNakamaGroupsTestBase::UpdateGroup(const FString& GroupId)
{
	auto successCallback = [this, GroupId]()
	{
		UE_LOG(LogTemp, Display, TEXT("Group Updated. Group ID: %s"), *GroupId);
		// Proceed to list group users
		ListGroupUsers(GroupId);
	};

	auto errorCallback = [this](const FNakamaError& Error)
	{
		UE_LOG(LogTemp, Error, TEXT("Update Group Error: %s"), *Error.Message);
		TestFalse("Update Group Test Failed", true);
		StopTest();
	};

	FString Description = TEXT("Nakama is cool!");

	Client->UpdateGroup(
		Session,
		GroupId,
		{},
		Description,
		{},
		{}, // LangTag
		{},
		successCallback,
		errorCallback
	);
}

void FNakamaGroupsTestBase::ListGroupUsers(const FString& GroupId)
{
	auto successCallback = [this](const FNakamaGroupUsersList& GroupUsers)
	{
		UE_LOG(LogTemp, Display, TEXT("List Group Users Success. GroupUsers: %d"), GroupUsers.GroupUsers.Num());

		if (GroupUsers.GroupUsers.Num() <= 0)
		{
			UE_LOG(LogTemp, Display, TEXT("List Group Users Error. No GroupUsers Found"));
			TestFalse("List Group Users Error. No GroupUsers Found", true);
			StopTest();
			return;
		}

		TestTrue("List Group Users Test Passed", GroupUsers.GroupUsers.Num() >= 1 && !GroupUsers.GroupUsers[0].User.Id.IsEmpty());
		StopTest();
	};

	auto errorCallback = [this](const FNakamaError& Error)
	{
		UE_LOG(LogTemp, Error, TEXT("List Group Users Error: %s"), *Error.Message);
		TestFalse("List Group Users Test Failed", true);
		StopTest();
	};

	Client->ListGroupUsers(Session, GroupId, 30, ENakamaGroupState::SUPERADMIN, "", successCallback, errorCallback);
}