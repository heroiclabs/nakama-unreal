// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NakamaModule.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
//#include "Interfaces/IPluginManager.h" // "Projects" module required
#include "NUnrealLogSink.h"
#include "NOnlineSubsystem/NOnlineSubsystem.h"

#define LOCTEXT_NAMESPACE "FNakamaModule"

//DEFINE_LOG_CATEGORY(LogNakama);

using namespace NAKAMA_NAMESPACE;

void FNakamaModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	UE_LOG(LogTemp, Log, TEXT("Nakama module loaded"));
}

void FNakamaModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

Nakama::INakamaOnlineSubsystem& FNakamaModule::getOnlineSubsystem()
{
    return _onlineSubsystem;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNakamaModule, Nakama)
