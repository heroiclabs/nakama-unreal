/*
This file purely exists to make Jetbrains Rider  IDE happy and
give us at least somewhat comfortable experience working on Unreal code
*/

using UnrealBuildTool;

public class dummyTarget : TargetRules
{
	public dummyTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		
		ExtraModuleNames.Add("Nakama");
	}
}
