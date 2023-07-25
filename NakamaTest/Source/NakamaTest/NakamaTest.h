// Copyright 2023 The Nakama Authors.

#pragma once

#include "CoreMinimal.h"

class NakamaTest : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
