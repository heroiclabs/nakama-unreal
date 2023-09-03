// Copyright Epic Games, Inc. All Rights Reserved.



#include "NakamaBlueprints.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FNakamaBlueprintsModule"

DEFINE_LOG_CATEGORY(LogNakamaBlueprints);


void FNakamaBlueprintsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//NLogger::init(std::make_shared<NUnrealLogSink>(), NLogLevel::Debug);

}

void FNakamaBlueprintsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNakamaBlueprintsModule, NakamaBlueprints)
