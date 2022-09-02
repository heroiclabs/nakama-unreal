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
			{UnrealTargetPlatform.IOS, Tuple.Create(Path.Combine("ios-arm64", "libnakama-sdk.dylib"), Path.Combine("ios-arm64", "libnakama-sdk.dylib"))},
			{UnrealTargetPlatform.Mac, Tuple.Create(Path.Combine("osx-universal", "libnakama-sdk.dylib"), Path.Combine("osx-universal, libnakama-sdk.dylib"))}
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

		if (!libs.ContainsKey(Target.Platform))
		{
			throw new BuildException("Unsupported platform");
		}

		var libFiles = libs[Target.Platform];

		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libnakama", libFiles.Item1));
		RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "libnakama", libFiles.Item2));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "libnakama", "include"));

		PrivateDependencyModuleNames.AddRange(new string[]{ "Core" });
	}
}