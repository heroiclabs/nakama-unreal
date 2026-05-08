// Copyright 2026 The Nakama Authors.

using System;
using System.IO;
using UnrealBuildTool;

public class NakamaEditor : ModuleRules
{
	public NakamaEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
	}
}
