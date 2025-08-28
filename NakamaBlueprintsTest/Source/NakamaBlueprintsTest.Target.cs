// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class NakamaBlueprintsTestTarget : TargetRules
{
	public NakamaBlueprintsTestTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
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
