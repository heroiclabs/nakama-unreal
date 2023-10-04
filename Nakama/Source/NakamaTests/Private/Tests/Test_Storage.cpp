
#include "Tests/Test_Storage.h"

#include "NakamaTestBase.h"

// Write Storage Invalid Argument
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(WriteStorageInvalidArgument, FNakamaTestBase, "Nakama.Base.Storage.InvalidArgument", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool WriteStorageInvalidArgument::RunTest(const FString& Parameters)
{
	// TODO: This test ends up being quite slow
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		auto errorCallback = [this](const FNakamaError& Error)
		{
			UE_LOG(LogTemp, Display, TEXT("WriteStorageInvalidArgument. ErrorMessage: %s"), *Error.Message);
			UE_LOG(LogTemp, Display, TEXT("WriteStorageInvalidArgument. ErrorCode: %d"), Error.Code);
			TestTrue("Write Storage Invalid Argument Passed.", Error.Code == ENakamaErrorCode::InvalidArgument);
			StopTest();
		};

		// Object to write
		TArray<FNakamaStoreObjectWrite> Objects;

		FNakamaStoreObjectWrite Object1;
		Object1.Collection = TEXT("candies");
		Object1.Key = TEXT("test");
		Object1.Value = TEXT("25"); // Invalid Json!
		Objects.Add(Object1);

		// Only want to check error?
		Client->WriteStorageObjects(Session, Objects, {}, errorCallback);
	};
	
	Client->AuthenticateDevice("mytestdevice0000", true, {}, {}, successCallback, {});

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

// Write Storage Object then verify read
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(WriteStorage, FNakamaTestBase, "Nakama.Base.Storage.Write", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool WriteStorage::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		auto WriteErrorCallback = [this](const FNakamaError& Error)
		{
			UE_LOG(LogTemp, Display, TEXT("Write Storage Object Failed. ErrorMessage: %s"), *Error.Message);
			TestFalse("Write Storage Object Failed.", true);
			StopTest();
		};

		auto WriteSuccessCallback = [this](const FNakamaStoreObjectAcks& Acks)
		{
			if(Acks.StorageObjects.Num() == 1)
			{
				UE_LOG(LogTemp, Display, TEXT("Write Ok. Version: %s"), *Acks.StorageObjects[0].Version);

				auto ListErrorCallback = [this](const FNakamaError& Error)
				{
					UE_LOG(LogTemp, Display, TEXT("List Storage Object Failed. ErrorMessage: %s"), *Error.Message);
					TestFalse("List Storage Object Failed.", true);
					StopTest();
				};

				auto ListSuccessCallback = [this](const FNakamaStorageObjectList& ObjectList)
				{
					UE_LOG(LogTemp, Display, TEXT("List Storage Object Success. Objects: %d"), ObjectList.Objects.Num());
					TestTrue("List Storage Object Success.", ObjectList.Objects.Num() > 0);
					StopTest();
				};
				
				Client->ListUsersStorageObjects(Session, "candies", Session->GetUserId(), {}, {}, ListSuccessCallback, ListErrorCallback);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("Write Storage Object Failed."));
				TestFalse("Write Storage Object Failed.", true);
				StopTest();
			}
		};

		// Object to write
		TArray<FNakamaStoreObjectWrite> Objects;

		FNakamaStoreObjectWrite Object1;
		Object1.Collection = TEXT("candies");
		Object1.Key = TEXT("Ice cream");
		Object1.Value = TEXT("{ \"price\": 25 }");
		Object1.PermissionRead = ENakamaStoragePermissionRead::OWNER_READ;
		Object1.PermissionWrite = ENakamaStoragePermissionWrite::OWNER_WRITE;
		Objects.Add(Object1);

		// Only want to check error?
		Client->WriteStorageObjects(Session, Objects, WriteSuccessCallback, WriteErrorCallback);
	};
	
	Client->AuthenticateDevice("mytestdevice0000", true, {}, {}, successCallback, {});

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

// Write Storage Object then verify cursor
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(WriteStorageCursor, FNakamaStorageTestBase, "Nakama.Base.Storage.WriteCursor", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool WriteStorageCursor::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		auto WriteErrorCallback = [this](const FNakamaError& Error)
		{
			UE_LOG(LogTemp, Display, TEXT("Write Storage Object Failed. ErrorMessage: %s"), *Error.Message);
			TestFalse("Write Storage Object Failed.", true);
			StopTest();
		};

		auto WriteSuccessCallback = [this](const FNakamaStoreObjectAcks& Acks)
		{
			if(Acks.StorageObjects.Num() == NumCandies)
			{
				UE_LOG(LogTemp, Display, TEXT("Write Ok. Version: %s"), *Acks.StorageObjects[0].Version);

				auto ListErrorCallback = [this](const FNakamaError& Error)
				{
					UE_LOG(LogTemp, Display, TEXT("List Storage Object Failed. ErrorMessage: %s"), *Error.Message);
					TestFalse("List Storage Object Failed.", true);
					StopTest();
				};

				auto ListFirstSuccessCallback = [this](const FNakamaStorageObjectList& FirstObjectList)
				{
					UE_LOG(LogTemp, Display, TEXT("Cursor: %d"), FirstObjectList.Objects.Num());

					// Second:
					auto ListSecondSuccessCallback = [this](const FNakamaStorageObjectList& SecondObjectList)
					{
						UE_LOG(LogTemp, Display, TEXT("List Second Storage Object Success. Objects: %d"), SecondObjectList.Objects.Num());
						TestTrue("Storage Object Cursor Passed.", SecondObjectList.Objects.Num() > 0);
						StopTest();
					};

					auto ListSecondErrorCallback = [this](const FNakamaError& Error)
					{
						// This typically means the cursor is invalid
						UE_LOG(LogTemp, Display, TEXT("List Storage Object Second Failed. ErrorMessage: %s"), *Error.Message);
						TestFalse("List Storage Object Second Failed.", true);
						StopTest();
					};

					Client->ListUsersStorageObjects(Session, "candies", Session->GetUserId(), 10, FirstObjectList.Cursor, ListSecondSuccessCallback, ListSecondErrorCallback);
				};
				
				Client->ListUsersStorageObjects(Session, "candies", Session->GetUserId(), {}, {}, ListFirstSuccessCallback, ListErrorCallback);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("Write Storage Object Failed."));
				TestFalse("Write Storage Object Failed.", true);
				StopTest();
			}
		};

		// Object to write
		TArray<FNakamaStoreObjectWrite> Objects;
		
		for (int i = 0; i < NumCandies; i++)
		{
			FNakamaStoreObjectWrite Object;
			Object.Collection = TEXT("candies");
			Object.Key = FString::Printf(TEXT("Ice cream%d"), i);
			Object.Value = TEXT("{ \"price\": 25 }");
			Object.PermissionRead = ENakamaStoragePermissionRead::OWNER_READ;
			Object.PermissionWrite = ENakamaStoragePermissionWrite::OWNER_WRITE;
			Objects.Add(Object);
		}
		
		// Only want to check error?
		Client->WriteStorageObjects(Session, Objects, WriteSuccessCallback, WriteErrorCallback);
	};
	
	Client->AuthenticateDevice("mytestdevice0000", true, {}, {}, successCallback, {});

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}