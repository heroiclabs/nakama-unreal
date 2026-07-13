// Copyright 2023 The Nakama Authors.

using UnrealBuildTool;
using System.Collections.Generic;

public class IntegrationTestsEditorTarget : TargetRules
{
	public IntegrationTestsEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		CppStandard = CppStandardVersion.Cpp20;
		DefaultBuildSettings = BuildSettingsVersion.V8;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange( new string[] { "IntegrationTests" } );
	}
}
