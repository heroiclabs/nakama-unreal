// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class NakamaBlueprintsTestEditorTarget : TargetRules
{
	public NakamaBlueprintsTestEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        //bIWYU = true;
        bEnforceIWYU = true;
		bUseUnityBuild = false;
		bForceUnityBuild = false;
		bUsePCHFiles = false;

		ExtraModuleNames.AddRange( new string[] { "NakamaBlueprintsTest" } );
	}
}
