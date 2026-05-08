// Copyright 2026 The Nakama Authors.

#pragma once

#include "CoreMinimal.h"

class NakamaEditor : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
