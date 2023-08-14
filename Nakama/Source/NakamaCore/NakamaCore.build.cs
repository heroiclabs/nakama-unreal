using System;
using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class NakamaCore : ModuleRules
{
    public NakamaCore(ReadOnlyTargetRules target) : base(target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // Platform -> (buildLib, runtimeLib)
        var libs = new Dictionary<UnrealTargetPlatform, Tuple<string,string>>()
        {
            {UnrealTargetPlatform.Linux, Tuple.Create(Path.Combine("linux-x64", "libnakama-sdk.so"), Path.Combine("linux-x64", "libnakama-sdk.so"))},
        };

        if (target.Platform == UnrealTargetPlatform.Win64)
        {
            string configurationDirectory = null;
            string arch = null;

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

            if (Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT)
            {
                configurationDirectory = "Debug";
                RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "nakama-sdk.pdb"), Path.Combine(ModuleDirectory, "libnakama", arch, configurationDirectory, "nakama-sdk.pdb"));
            }
            else
            {
                configurationDirectory = "Release";
            }

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libnakama", arch, configurationDirectory, "nakama-sdk.lib"));
            RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "nakama-sdk.dll"), Path.Combine(ModuleDirectory, "libnakama", arch, configurationDirectory, "nakama-sdk.dll"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
			string dylibPath;
            if (Target.Architecture == UnrealArch.Arm64)
            {
                dylibPath = Path.Combine(ModuleDirectory, "libnakama", "macosx-arm64", "libnakama-sdk.dylib");
            }
            else if (Target.Architecture == UnrealArch.X64)
            {
                dylibPath = Path.Combine(ModuleDirectory, "libnakama", "macosx-x64", "libnakama-sdk.dylib");
            }
            else
            {
                throw new InvalidOperationException("Unrecognized OSX architecture");
            }

			PublicDelayLoadDLLs.Add(dylibPath);
			RuntimeDependencies.Add(dylibPath);
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            var dylibPath = Path.Combine(ModuleDirectory, "libnakama", "ios-arm64", "libnakama-sdk.dylib");
			PublicDelayLoadDLLs.Add(dylibPath);
			RuntimeDependencies.Add(dylibPath);
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libnakama", "armeabi-v7a", "libnakama-sdk.so"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libnakama", "arm64-v8a", "libnakama-sdk.so"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libnakama", "x86_64", "libnakama-sdk.so"));

            string relAPLPath = Utils.MakePathRelativeTo(Path.Combine(ModuleDirectory, "Nakama_APL.xml"), Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", relAPLPath);
        }
        else
        {
            if (!libs.ContainsKey(Target.Platform))
            {
                throw new BuildException("Unsupported platform");
            }

            var libFiles = libs[Target.Platform];

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libnakama", libFiles.Item1));
            RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", Path.GetFileName(libFiles.Item2)), Path.Combine(ModuleDirectory, "libnakama", libFiles.Item2));
        }

        PrivateDependencyModuleNames.AddRange(new string[]{ "Core", "HTTP" });
		PublicDependencyModuleNames.AddRange(new string[]{ "WebSockets" });
	}
}
