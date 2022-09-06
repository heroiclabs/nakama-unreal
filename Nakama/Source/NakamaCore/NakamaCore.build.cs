using System;
using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class Nakama : ModuleRules
{
	public Nakama(ReadOnlyTargetRules target) : base(target)
	{
		// Platform -> (buildLib, runtimeLib)
		var libs = new Dictionary<UnrealTargetPlatform, Tuple<string,string>>()
		{
			{UnrealTargetPlatform.Win64, Tuple.Create(Path.Combine("win-x64", "nakama-sdk.lib"), Path.Combine("win-x64", "nakama-sdk.dll"))},
			{UnrealTargetPlatform.Linux, Tuple.Create(Path.Combine("linux-amd64", "libnakama-sdk.so"), Path.Combine("linux-amd64", "libnakama-sdk.so"))},
		};

#if PLATFORM_PS4
		libs[UnrealTargetPlatform.PS4] = Tuple.Create(Path.Combine("ps4", "nakama-sdk_stub_weak.a"), (Path.Combine("ps4", "nakama-sdk.prx")));
#endif

#if PLATFORM_PS5
		libs[UnrealTargetPlatform.PS5] = Tuple.Create(Path.Combine("ps5", "nakama-sdk_stub_weak.a"), Path.Combine("ps5", "nakama-sdk.prx"));
#endif

#if PLATFORM_XBOX_ONE
		libs[UnrealTargetPlatform.XboxOne] = Tuple.Create(Path.Combine("xdk", "nakama-sdk.lib"), Path.Combine("xdk", "nakama-sdk.dll"));
#endif

#if PLATFORM_XBOXONEGDK
		libs[UnrealTargetPlatform.XboxOneGDK] = Tuple.Create(Path.Combine("gdk-xbox-one", "nakama-sdk.lib"), Path.Combine("gdk-xbox-one", "nakama-sdk.dll"));
#endif

#if PLATFORM_XSX
		libs[UnrealTargetPlatform.XSX] = Tuple.Create(Path.Combine("gdk-xbox-scarlett", "nakama-sdk.lib"), Path.Combine("gdk-xbox-scarlett", "nakama-sdk.dll"));
#endif

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
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "libnakama", libFiles.Item2));
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "libnakama", "include"));
        }

		PrivateDependencyModuleNames.AddRange(new string[]{ "Core", "HTTP", "WebSockets" });
	}
}