// Copyright 2023 The Nakama Authors.

using UnrealBuildTool;
using System.Collections.Generic;

public class IntegrationTestsEditorTarget : TargetRules
{
	public IntegrationTestsEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange( new string[] { "IntegrationTests" } );
		#if UE_5_8_OR_LATER
			bOverrideBuildEnvironment = true;
			CppStandard = CppStandardVersion.Cpp20;
			GlobalDefinitions.Add("UE_JSONOBJECT_LEGACY_STRING_KEYS=1");
		#endif
	}
}
