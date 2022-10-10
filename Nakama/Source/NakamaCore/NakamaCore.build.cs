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
		    var frameworkDir = Path.Combine(ModuleDirectory, "libnakama", "macosx-universal", "nakama-sdk.framework");
            PublicFrameworks.Add(frameworkDir);

            // Currently headers prefix doesn't match framework name (nakama-cpp != nakama-sdk)
            // so Clang can't find include path automatically and needs some help
            PublicIncludePaths.Add(Path.Combine(frameworkDir, "Headers"));
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
		    var frameworkDir = Path.Combine(ModuleDirectory, "libnakama", "ios-universal", "nakama-sdk.framework");
            PublicFrameworks.Add(frameworkDir);
            PublicIncludePaths.Add(Path.Combine(frameworkDir, "Headers"));
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