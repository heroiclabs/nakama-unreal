// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class NakamaUnreal : ModuleRules
{
	public NakamaUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);


		// NakamaUnreal no longer depends on NakamaCore
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "HTTP", "WebSockets", "JsonUtilities"
				// ... add other public dependencies that you statically link with here ...
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Engine",
				"JsonUtilities",
				"Json",
				"HTTP"
				// ... add private dependencies that you statically link with here ...
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
    }
}
