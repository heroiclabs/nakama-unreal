#pragma once

//#include "SatoriUnreal.h"
//#include "nonstd/optional.hpp"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSatoriBlueprints, Log, All);


class FSatoriBlueprintsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
