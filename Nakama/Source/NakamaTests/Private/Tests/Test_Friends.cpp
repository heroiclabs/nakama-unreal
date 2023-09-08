#include "Tests/Test_Friends.h"

#include "NakamaLogger.h"
#include "NakamaLoggingMacros.h"
#include "NakamaTestBase.h"

// List friends and testing cursor
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(ListFriends, FNakamaFriendsTestBase, "Nakama.Base.Friends.ListFriends", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool ListFriends::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();

	auto AuthenticateSuccess = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		UE_LOG( LogTemp, Display, TEXT("Session: %s"), *Session->GetAuthToken() );

		for (int i = 0; i < FriendsToAdd; i++)
		{
			auto FriendAuthenticateSuccess = [&](UNakamaSession* friendSession)
			{
				FriendIds.Add(friendSession->GetUserId());

				// Done with authentication of friends
				if (FriendIds.Num() == FriendsToAdd)
				{
					// Add Friends
					auto FriendsAddedSuccess = [&]()
					{
						auto ListFriendsSuccess = [&] (const FNakamaFriendList& Friends)
						{
							FNakamaFriendList InvitedList = Friends;
							
							if(InvitedList.NakamaUsers.IsEmpty())
							{
								NAKAMA_LOG_ERROR("empty invited list 1");
								TestFalse("empty invited list 1", true);
								StopTest();
							}
							
							FString ReturnedFriendId1 = Friends.NakamaUsers[0].NakamaUser.Id;

							auto ListFriends2Success = [&] (const FNakamaFriendList& Friends2)
							{
								if(Friends2.NakamaUsers.IsEmpty())
								{
									NAKAMA_LOG_ERROR("Empty invited list 2");
									TestFalse("Empty invited list 2", true);
									StopTest();
								}
								
								FString ReturnedFriendId2 = Friends2.NakamaUsers[0].NakamaUser.Id;
								TestTrue("List Friends Test Passed", ReturnedFriendId1 != ReturnedFriendId2);
								StopTest();
							};

							auto ListFriends2Error = [&] (const FNakamaError& error)
							{
								// If this is reached then the cursor is most likely invalid
								UE_LOG(LogTemp, Display, TEXT("ListFriends2Error: %s"), *FString(error.Message));
								TestFalse("ListFriends2Error", true);
								StopTest();
							};

							// Passing cursor into function
							Client->ListFriends(Session, ListFriendsLimit, ENakamaFriendState::INVITE_SENT, InvitedList.Cursor, ListFriends2Success, ListFriends2Error);
							
						};
						
						Client->ListFriends(Session, ListFriendsLimit, ENakamaFriendState::INVITE_SENT, "", ListFriendsSuccess, {});
						
					};
					
					// Test that using cursor gives a different friend.
					Client->AddFriends(Session, FriendIds, {}, FriendsAddedSuccess, {});
				}
			};

			Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, FriendAuthenticateSuccess, {});
		}
		
	};

	// Define error callback
	auto AuthenticateError = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("List Friends Test Failed", true);
		StopTest();
	};
	
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, AuthenticateSuccess, AuthenticateError);
	
	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}