// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class NakamaBlueprintsTest : ModuleRules
{
	public NakamaBlueprintsTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Json", "JsonUtilities" });

		PrivateDependencyModuleNames.AddRange(new string[] { "NakamaUnreal" });
	}
}
