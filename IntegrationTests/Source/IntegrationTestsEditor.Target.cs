// Copyright 2023 The Nakama Authors.

using UnrealBuildTool;
using System.Collections.Generic;

public class IntegrationTestsEditorTarget : TargetRules
{
	public IntegrationTestsEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V8;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange( new string[] { "IntegrationTests" } );
		
		bOverrideBuildEnvironment = true;
		if (Target.Version.MajorVersion == 5 && Target.Version.MinorVersion >= 8)
		{
			GlobalDefinitions.Add("UE_JSONOBJECT_LEGACY_STRING_KEYS=1");
		}
	}
}
