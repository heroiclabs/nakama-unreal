// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class NakamaTestTarget : TargetRules
{
	public NakamaTestTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		ExtraModuleNames.AddRange( new string[] { "NakamaTest" } );
		bUseLoggingInShipping = true;
	}
}
