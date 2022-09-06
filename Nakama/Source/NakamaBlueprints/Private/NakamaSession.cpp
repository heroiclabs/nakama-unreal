// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaSession.h"

#include "NakamaUtils.h"

NSessionPtr UNakamaSession::UserSession;

void UNakamaSession::RestoreSession(FString Token, FString RefreshToken)
{
	UserSession = restoreSession(FNakamaUtils::UEStringToStdString(Token), FNakamaUtils::UEStringToStdString(RefreshToken));
	SessionData = UserSession; // Converts and sets readable data
}

FString UNakamaSession::GetVariable(FString Name)
{
	FString *Value = SessionData.Variables.Find(Name);
	return *Value;
}

bool UNakamaSession::IsRefreshExpired(FDateTime Time)
{
	//FDateTime::FromUnixTimestamp(NakamaNativeUser.createdAt / 1000)
	const bool IsRefreshExpired = UserSession->isRefreshExpired(Time.ToUnixTimestamp());
	return  IsRefreshExpired;
}

bool UNakamaSession::IsExpired(FDateTime Time)
{
	//FDateTime::FromUnixTimestamp(NakamaNativeUser.createdAt / 1000)
	const bool IsExpired = UserSession->isExpired(Time.ToUnixTimestamp());
	return  IsExpired;
}

bool UNakamaSession::IsCreated()
{
	return UserSession->isCreated();
}
