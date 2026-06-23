// Copyright 2023 The Nakama Authors.

using System;
using System.IO;
using UnrealBuildTool;

public class IntegrationTests : ModuleRules
{
	public IntegrationTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "FieldNotification", "InputCore", "Json", "HTTP", "Nakama", "Satori", "WebSockets", "Slate", "SlateCore", "UMG", "ModelViewViewModel" });
		
		if (Target.Version.MajorVersion == 5 && Target.Version.MinorVersion >= 8)
		{
        	PublicDefinitions.Add("UE_JSONOBJECT_LEGACY_STRING_KEYS=1");
		}
	}
}
