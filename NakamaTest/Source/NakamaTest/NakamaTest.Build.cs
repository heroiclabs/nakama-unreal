// Copyright 2023 The Nakama Authors.

using System;
using System.IO;
using UnrealBuildTool;

public class NakamaTest : ModuleRules
{
	public NakamaTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "FieldNotification", "InputCore", "Json", "NakamaApi", "NakamaUnreal", "NakamaBlueprints", "WebSockets", "Slate", "SlateCore", "UMG", "ModelViewViewModel" });
	}
}
