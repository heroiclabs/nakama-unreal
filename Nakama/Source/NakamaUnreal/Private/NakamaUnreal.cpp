#include "NakamaUnreal.h"
#include "Modules/ModuleManager.h"

void FNakamaUnrealModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//NLogger::init(std::make_shared<NUnrealLogSink>(), NLogLevel::Debug);

}

void FNakamaUnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNakamaUnrealModule, NakamaUnreal)
