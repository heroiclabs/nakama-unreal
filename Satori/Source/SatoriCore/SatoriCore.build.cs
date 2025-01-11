using System;
using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class SatoriCore : ModuleRules
{
    public SatoriCore(ReadOnlyTargetRules target) : base(target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // Platform -> (buildLib, runtimeLib)
        var libs = new Dictionary<UnrealTargetPlatform, Tuple<string,string>>()
        {
            {UnrealTargetPlatform.Linux, Tuple.Create(Path.Combine("linux-x64", "libsatori-sdk.so"), Path.Combine("linux-x64", "libsatori-sdk.so"))},
        };

        if (target.Platform == UnrealTargetPlatform.Win64)
        {
            string configurationDirectory = null;
            string arch = null;

            if (IsX64Arch())
            {
                arch = "win-x64";
            }
            else
            {
                arch = "win-arm64";
            }

            if (Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT)
            {
                configurationDirectory = "Debug";
                RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "satori-sdk.pdb"), Path.Combine(ModuleDirectory, "libsatori", arch, configurationDirectory, "satori-sdk.pdb"));
            }
            else
            {
                configurationDirectory = "Release";
            }

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libsatori", arch, configurationDirectory, "satori-sdk.lib"));
            RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "satori-sdk.dll"), Path.Combine(ModuleDirectory, "libsatori", arch, configurationDirectory, "satori-sdk.dll"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
			string dylibPath;
            if (IsX64Arch())
            {
                dylibPath = Path.Combine(ModuleDirectory, "libsatori", "macosx-x64", "libsatori-sdk.dylib");
            }
            else
            {
                dylibPath = Path.Combine(ModuleDirectory, "libsatori", "macosx-arm64", "libsatori-sdk.dylib");
            }

			PublicDelayLoadDLLs.Add(dylibPath);
			RuntimeDependencies.Add(dylibPath);
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            var dylibPath = Path.Combine(ModuleDirectory, "libsatori", "ios-arm64", "libsatori-sdk.dylib");
			PublicDelayLoadDLLs.Add(dylibPath);
			RuntimeDependencies.Add(dylibPath);
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libsatori", "armeabi-v7a", "libsatori-sdk.so"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libsatori", "arm64-v8a", "libsatori-sdk.so"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libsatori", "x86_64", "libsatori-sdk.so"));

            string relAPLPath = Utils.MakePathRelativeTo(Path.Combine(ModuleDirectory, "Satori_APL.xml"), Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", relAPLPath);
        }
        else
        {
            if (!libs.ContainsKey(Target.Platform))
            {
                throw new BuildException("Unsupported platform");
            }

            var libFiles = libs[Target.Platform];

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libsatori", libFiles.Item1));
            RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", Path.GetFileName(libFiles.Item2)), Path.Combine(ModuleDirectory, "libsatori", libFiles.Item2));
        }

        PrivateDependencyModuleNames.AddRange(new string[]{ "Core", "HTTP" });
		PublicDependencyModuleNames.AddRange(new string[]{ "WebSockets" });
	}

	private bool IsX64Arch()
	{
#if UE_5_2_OR_LATER
		return Target.Architecture == UnrealArch.X64;
#else
		// empty string is the "default architecture" which is x64
		return Target.Architecture == "" || Target.Architecture.StartsWith("x86_64") || Target.Architecture.StartsWith("x64");
#endif
	}
}
