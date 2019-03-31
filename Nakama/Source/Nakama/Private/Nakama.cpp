// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Nakama.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "nakama-cpp/Nakama.h"
#include "NUnrealLogSink.h"

#define LOCTEXT_NAMESPACE "FNakamaModule"

DEFINE_LOG_CATEGORY(LogNakama);

using namespace Nakama;

void FNakamaModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	UE_LOG(LogTemp, Log, TEXT("Nakama module loaded"));

	NLogger::init(std::make_shared<NUnrealLogSink>(), NLogLevel::Debug);
}

void FNakamaModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNakamaModule, Nakama)
