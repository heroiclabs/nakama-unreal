#pragma once

#include "Modules/ModuleInterface.h"

class FNakamaUnrealModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
