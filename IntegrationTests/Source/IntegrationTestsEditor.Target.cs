// Copyright 2023 The Nakama Authors.

using UnrealBuildTool;
using System.Collections.Generic;

public class IntegrationTestsEditorTarget : TargetRules
{
	public IntegrationTestsEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
#if UE_5_8_OR_LATER
		DefaultBuildSettings = BuildSettingsVersion.V8;
#else
		DefaultBuildSettings = BuildSettingsVersion.V6;
#endif
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange( new string[] { "IntegrationTests" } );
	}
}
