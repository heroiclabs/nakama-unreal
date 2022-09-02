using System;
using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class Nakama : ModuleRules
{
	public Nakama(ReadOnlyTargetRules target) : base(target)
	{
	    var libNakamaDir = Path.Combine(ModuleDirectory, "libnakama");
		// Platform -> (buildLib, runtimeLib)
		var libs = new Dictionary<UnrealTargetPlatform, Tuple<string,string>>()
		{
			{UnrealTargetPlatform.Win64, Tuple.Create("win-x64/nakama-sdk.lib", "win-x64/nakama-sdk.dll")},
			{UnrealTargetPlatform.Linux, Tuple.Create("linux-amd64-libcxx_static/libnakama-sdk.so", "linux-amd64-libcxx_static/libnakama-sdk.so")},
		};

		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
		    var frameworkDir = Path.Combine(libNakamaDir, "macosx-universal", "nakama-sdk.framework");
		    if (!Directory.Exists(frameworkDir)) {
		        //  when in-source it is only osx-x64 for now
                frameworkDir = Path.Combine(libNakamaDir, "macosx-x64", "nakama-sdk.framework");
		    }
            PublicFrameworks.Add(frameworkDir);

            // Currently headers prefix doesn't match framework name (nakama-cpp != nakama-sdk)
            // so Clang can't find include path automatically and needs some help
            PublicIncludePaths.Add(Path.Combine(frameworkDir, "Headers"));
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
		    var frameworkDir = Path.Combine(libNakamaDir, "ios-universal", "nakama-sdk.framework");
		    if (!Directory.Exists(frameworkDir)) {
		        //  when in-source it is only ios-arm64 for now
		        frameworkDir = Path.Combine(libNakamaDir, "ios-arm64", "nakama-sdk.framework");
		    }
            PublicFrameworks.Add(frameworkDir);
            PublicIncludePaths.Add(Path.Combine(frameworkDir, "Headers"));
		} else {
            if (!libs.ContainsKey(Target.Platform))
            {
                 throw new BuildException("Unsupported platform");
            }

            var libFiles = libs[Target.Platform];

            PublicAdditionalLibraries.Add(Path.Combine(libNakamaDir, libFiles.Item1));
            RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)", Path.GetFileName(libFiles.Item2)),Path.Combine(libNakamaDir, libFiles.Item2));

            PublicIncludePaths.Add(Path.Combine(libNakamaDir, "include"));
		}

		PrivateDependencyModuleNames.AddRange(new string[]{ "Core", "HTTP", "WebSockets" });
	}
}
