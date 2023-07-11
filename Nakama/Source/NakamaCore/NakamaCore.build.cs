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
            {UnrealTargetPlatform.Win64, Tuple.Create(Path.Combine("win-x64", "nakama-sdk.lib"), Path.Combine("win-x64", "nakama-sdk.dll"))},
            {UnrealTargetPlatform.Linux, Tuple.Create(Path.Combine("linux-amd64", "libnakama-sdk.so"), Path.Combine("linux-amd64", "libnakama-sdk.so"))},
        };

        if (Target.Platform == UnrealTargetPlatform.Mac)
        {
			string dylibPath;
            if (Target.Architecture == UnrealArch.Arm64)
            {
                dylibPath = Path.Combine(ModuleDirectory, "libnakama", "macosx-arm64", "nakama-sdk.dylib");
            }
            else if (Target.Architecture == UnrealArch.X64)
            {
                dylibPath = Path.Combine(ModuleDirectory, "libnakama", "macosx-x64", "nakama-sdk.dylib");
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
            var dylibPath = Path.Combine(ModuleDirectory, "libnakama", "ios-arm64", "nakama-sdk.dylib");
			PublicDelayLoadDLLs.Add(dylibPath);
			RuntimeDependencies.Add(dylibPath);
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            var androidDir = Path.Combine(ModuleDirectory, "libnakama", "android");
            PublicIncludePaths.Add(Path.Combine(androidDir,"include"));

            PublicAdditionalLibraries.Add(Path.Combine(androidDir,"libs","armeabi-v7a","libnakama-sdk.so"));
            PublicAdditionalLibraries.Add(Path.Combine(androidDir,"libs","arm64-v8a","libnakama-sdk.so"));
            PublicAdditionalLibraries.Add(Path.Combine(androidDir,"libs","x86_64","libnakama-sdk.so"));

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

        PrivateDependencyModuleNames.AddRange(new string[]{ "Core", "HTTP", "WebSockets" });
    }
}