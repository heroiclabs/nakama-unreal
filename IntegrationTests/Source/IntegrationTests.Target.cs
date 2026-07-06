// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class IntegrationTestsTarget : TargetRules
{
	public IntegrationTestsTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.AddRange( new string[] { "IntegrationTests" } );
		bUseLoggingInShipping = true;
		
#if UE_5_8_OR_LATER
		bOverrideBuildEnvironment = true;
		CppStandard = CppStandardVersion.Cpp20;
		GlobalDefinitions.Add("UE_JSONOBJECT_LEGACY_STRING_KEYS=1");
#endif
	}
}
