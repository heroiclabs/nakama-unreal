// Copyright 2023 The Nakama Authors.

using System;
using System.IO;
using UnrealBuildTool;

public class NakamaTest : ModuleRules
{
	public NakamaTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NakamaCore"});
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "libnakamatest"));

		if (Target.Platform == UnrealTargetPlatform.Mac)
        {
			string dylibPath;
            if (Target.Architecture == UnrealArch.Arm64)
            {
                dylibPath = Path.Combine(ModuleDirectory, "libnakamatest", "libnakama-test.dylib");
            }
            else
            {
                throw new InvalidOperationException("Unrecognized OSX architecture");
            }

			System.Console.WriteLine("DYLIB PATH IS " + dylibPath);
			PublicDelayLoadDLLs.Add(dylibPath);
			RuntimeDependencies.Add(dylibPath);
        }
		else if (Target.Platform == UnrealTargetPlatform.Win64)
		{
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libnakamatest", "windows", "nakama-test.lib"));
			RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", Path.GetFileName("nakama-test.dll")), Path.Combine(ModuleDirectory, "libnakamatest", "windows", "nakama-test.dll"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libnakamatest", "linux", "libnakama-test.so"));
			RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", Path.GetFileName("libnakama-test.so")), Path.Combine(ModuleDirectory, "libnakamatest", "linux", "libnakama-test.so"));
		}
		else
		{
			throw new BuildException("Unsupported platform");
		}
	}
}
