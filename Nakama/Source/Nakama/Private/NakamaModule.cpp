#include "NakamaPrivatePCH.h"

#include "Engine.h"
#include "Engine/EngineTypes.h"

#include "NakamaModule.h"
#include "ModuleManager.h"

IMPLEMENT_MODULE(UNakamaModule, Nakama)

DEFINE_LOG_CATEGORY(LogNakama);

void UNakamaModule::StartupModule()
{
	UE_LOG(LogNakama, Verbose, TEXT("Nakama::StartupModule"));
}

void UNakamaModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	isInitialised = false;
}

UNakamaModule* UNakamaModule::GetModulePtr()
{
	return FModuleManager::GetModulePtr<UNakamaModule>("Nakama");
}
