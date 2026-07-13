// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class IntegrationTestsTarget : TargetRules
{
	public IntegrationTestsTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		CppStandard = CppStandardVersion.Cpp20;
		ExtraModuleNames.AddRange( new string[] { "IntegrationTests" } );
		bUseLoggingInShipping = true;
	}
}
