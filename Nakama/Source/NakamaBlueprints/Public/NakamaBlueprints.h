// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "NakamaUnreal.h"
//#include "nonstd/optional.hpp"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNakamaBlueprints, Log, All);


class FNakamaBlueprintsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
