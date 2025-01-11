#pragma once

#include "Modules/ModuleInterface.h"

class FSatoriUnrealModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
