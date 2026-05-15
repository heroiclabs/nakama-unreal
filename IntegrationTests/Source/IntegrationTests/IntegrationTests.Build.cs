// Copyright 2023 The Nakama Authors.

using System;
using System.IO;
using UnrealBuildTool;

public class IntegrationTests : ModuleRules
{
	public IntegrationTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "FieldNotification", "InputCore", "Json", "HTTP", "NakamaApi", "Nakama", "NakamaBlueprints", "SatoriApi", "Satori", "SatoriBlueprints", "WebSockets", "Slate", "SlateCore", "UMG", "ModelViewViewModel" });
	}
}
