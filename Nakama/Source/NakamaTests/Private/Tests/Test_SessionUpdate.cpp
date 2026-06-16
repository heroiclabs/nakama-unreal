#include "NakamaTestBase.h"

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(SessionUpdate, FNakamaTestBase, "Nakama.Base.Sessions.SessionUpdate", NAKAMA_MODULE_TEST_MASK)
inline bool SessionUpdate::RunTest(const FString& Parameters)
{
    const FString TokenA = TEXT("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE1MTY5MTA5NzMsInVpZCI6ImY0MTU4ZjJiLTgwZjMtNDkyNi05NDZiLWE4Y2NmYzE2NTQ5MCIsInVzbiI6InZUR2RHSHl4dmwifQ.gzLaMQPaj5wEKoskOSALIeJLOYXEVFoPx3KY0Jm1EVU");
    const FString TokenB = TEXT("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE1MTY5MTA5NzMsInVpZCI6ImY0MTU4ZjJiLTgwZjMtNDkyNi05NDZiLWE4Y2NmYzE2NTQ5MCIsInVzbiI6InZUR2RHSHl4dmwiLCJ2cnMiOnsiazEiOiJ2MSIsImsyIjoidjIifX0.Hs9ltsNmtrTJXi2U21jjuXcd-3DMsyv4W6u1vyDBMTo");

    UNakamaSession* A = UNakamaSession::RestoreSession(TokenA, TEXT("refreshA"));
    UNakamaSession* B = UNakamaSession::RestoreSession(TokenB, TEXT("refreshB"));

    TestTrue("A has no variables before update", A->GetVariable(TEXT("k1")).IsEmpty());

    A->Update(B);

    TestEqual("AuthToken copied", A->GetAuthToken(), TokenB);
    TestEqual("RefreshToken copied", A->GetRefreshToken(), FString(TEXT("refreshB")));
    TestEqual("Username copied", A->GetUsername(), B->GetUsername());
    TestEqual("UserId copied", A->GetUserId(), B->GetUserId());
    TestEqual("IsCreated copied", A->IsCreated(), B->IsCreated());
    TestEqual("ExpireTime copied", A->GetExpireTime(), B->GetExpireTime());
    TestEqual("IsExpired copied", A->IsExpired(), B->IsExpired());
    TestEqual("Variable k1 copied", A->GetVariable(TEXT("k1")), FString(TEXT("v1")));
    TestEqual("Variable k2 copied", A->GetVariable(TEXT("k2")), FString(TEXT("v2")));

    A->Update(nullptr);

    TestEqual("null source: AuthToken unchanged", A->GetAuthToken(), TokenB);
    TestEqual("null source: RefreshToken unchanged", A->GetRefreshToken(), FString(TEXT("refreshB")));
    TestEqual("null source: variables unchanged", A->GetVariable(TEXT("k1")), FString(TEXT("v1")));

    StopTest();
    ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));
    return true;
}

// Pointers held by other systems stay valid across Update() and read new values.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(SessionUpdateHolders, FNakamaTestBase, "Nakama.Base.Sessions.SessionUpdateHolders", NAKAMA_MODULE_TEST_MASK)
inline bool SessionUpdateHolders::RunTest(const FString& Parameters)
{
    const FString TokenA = TEXT("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE1MTY5MTA5NzMsInVpZCI6ImY0MTU4ZjJiLTgwZjMtNDkyNi05NDZiLWE4Y2NmYzE2NTQ5MCIsInVzbiI6InZUR2RHSHl4dmwifQ.gzLaMQPaj5wEKoskOSALIeJLOYXEVFoPx3KY0Jm1EVU");
    const FString TokenB = TEXT("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE1MTY5MTA5NzMsInVpZCI6ImY0MTU4ZjJiLTgwZjMtNDkyNi05NDZiLWE4Y2NmYzE2NTQ5MCIsInVzbiI6InZUR2RHSHl4dmwiLCJ2cnMiOnsiazEiOiJ2MSIsImsyIjoidjIifX0.Hs9ltsNmtrTJXi2U21jjuXcd-3DMsyv4W6u1vyDBMTo");

    UNakamaSession* A = UNakamaSession::RestoreSession(TokenA, TEXT("refreshA"));
    UNakamaSession* B = UNakamaSession::RestoreSession(TokenB, TEXT("refreshB"));

    // References taken BEFORE the update, the ways game code typically holds one.
    UNakamaSession* RawHolder = A;
    TWeakObjectPtr<UNakamaSession> WeakHolder(A);
    TArray<UNakamaSession*> ContainerHolder;
    ContainerHolder.Add(A);
    auto CallbackHolder = [RawHolder]() { return RawHolder->GetAuthToken(); };

    A->Update(B);

    TestTrue("raw pointer identity stable", RawHolder == A);
    TestTrue("weak pointer identity stable", WeakHolder.Get() == A);
    TestTrue("weak pointer still valid", WeakHolder.IsValid());

    TestEqual("raw holder reads refreshed token", RawHolder->GetAuthToken(), TokenB);
    TestEqual("weak holder reads refreshed token", WeakHolder->GetAuthToken(), TokenB);
    TestEqual("container holder reads refreshed token", ContainerHolder[0]->GetAuthToken(), TokenB);
    TestEqual("captured-in-callback holder reads refreshed token", CallbackHolder(), TokenB);
    TestEqual("holder reads refreshed refresh token", RawHolder->GetRefreshToken(), FString(TEXT("refreshB")));
    TestEqual("holder reads refreshed variables", RawHolder->GetVariable(TEXT("k2")), FString(TEXT("v2")));

    StopTest();
    ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));
    return true;
}
