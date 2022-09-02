using UnrealBuildTool;
using System.IO;

//  UE4 and UE5 use different imports , uncomment one you want

//UE5
using EpicGames.Core;
//UE4
//using Tools.DotNETCommon;


using System;
using System.Reflection;

/*
Shim module which compiles and runs libnakama test suite from within Unreal, linking
to libnakama shared lib dynamically.

It expects test code to be copied into `Intermediate/Source/src` dir and any
header only dependencies, like rapidjson, to be copied to `Intermediate/Source`
*/

public class NakamaTest : ModuleRules
{
	public NakamaTest(ReadOnlyTargetRules Target) : base(Target)
	{

	    ConditionalAddModuleDirectory(DirectoryReference.Combine(Target.ProjectFile.Directory, new string[]{"Intermediate", "Source", "src"}));
	    PrivateIncludePaths.Add(DirectoryReference.Combine(Target.ProjectFile.Directory, new string[]{"Intermediate", "Source", "src"}).FullName);
        PrivateIncludePathModuleNames.Add("Launch");
		PrivateDependencyModuleNames.AddRange(new string[]{ "Core", "Projects", "Nakama" });
	}
}