// Copyright 2023 The Nakama Authors.

using System;
using System.IO;
using UnrealBuildTool;

public class NakamaTest : ModuleRules
{
	public NakamaTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NakamaCore", "WebSockets" });
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

			PublicDelayLoadDLLs.Add(dylibPath);
			RuntimeDependencies.Add(dylibPath);
        }
		else if (Target.Platform == UnrealTargetPlatform.Win64)
		{
            string configurationDirectory = null;
            string arch = null;

            if (Target.Configuration == UnrealTargetConfiguration.Debug)
            {
                configurationDirectory = "Debug";
            }
            else
            {
                configurationDirectory = "Release";
            }

            if (Target.Architecture == UnrealArch.X64)
            {
                arch = "win-x64";
            }
            else if (Target.Architecture == UnrealArch.Arm64)
            {
                arch = "win-arm64";
            }
            else
            {
                throw new InvalidOperationException("Unrecognized Windows architecture");
            }

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libnakamatest", arch, configurationDirectory, "nakama-test.lib"));
            RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "nakama-test.dll"), Path.Combine(ModuleDirectory, "libnakamatest", arch, configurationDirectory, "nakama-test.dll"));
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
