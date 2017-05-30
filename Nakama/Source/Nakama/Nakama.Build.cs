// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class Nakama : ModuleRules
{
	public Nakama(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "HTTP",
                "libWebSockets"
            }
        );

        AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL", "libWebSockets", "zlib");

        PublicIncludePaths.AddRange(new string[] {
            Path.Combine(ThirdPartyPath, "include")
        });

        PrivateIncludePaths.AddRange(new string[] {
            Path.Combine(ThirdPartyPath, "src")
        });

        switch (Target.Platform)
        {
            case UnrealTargetPlatform.Win32:
            case UnrealTargetPlatform.Linux:
            case UnrealTargetPlatform.Win64:
                PrivateDependencyModuleNames.Add("SSL");
                break;
            case UnrealTargetPlatform.Mac:
                break;
            case UnrealTargetPlatform.Android:
            case UnrealTargetPlatform.IOS:
            case UnrealTargetPlatform.PS4:
            case UnrealTargetPlatform.XboxOne:
            case UnrealTargetPlatform.HTML5:
            default:
                throw new NotImplementedException("Nakama Unreal client does not currently support platform: " + Target.Platform.ToString());
        }

        // Still need to add our libs
        LoadProtobufLib(Target);
    }

    private bool LoadProtobufLib(ReadOnlyTargetRules Target)
    {
        Definitions.AddRange(
                new string[]
                {
                    "GOOGLE_PROTOBUF_NO_RTTI",
                    "NDEBUG",
                    "GOOGLE_PROTOBUF_CMAKE_BUILD",
                    "PROTOBUF_INLINE_NOT_IN_HEADERS=0"
                });

        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        {
            isLibrarySupported = true;

            string vs_path = "vs"
                + WindowsPlatform.GetVisualStudioCompilerVersionName()
                + ((Target.Platform == UnrealTargetPlatform.Win64) ? "win64" : "");
            string protobuf_lib_directory_full_path = System.IO.Path.Combine(ThirdPartyPath, "lib", vs_path);

            PublicLibraryPaths.Add(protobuf_lib_directory_full_path);

            PublicAdditionalLibraries.Add("libprotobuf.lib");

            Definitions.Add("_WINDOWS");
            if (Target.Platform == UnrealTargetPlatform.Win64)
                Definitions.Add("__x86_64__");

        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            isLibrarySupported = true;

            string bin_path = "osxx64";
            string protobuf_lib_directory_full_path = System.IO.Path.Combine(ThirdPartyPath, "lib", bin_path);

            PublicLibraryPaths.Add(protobuf_lib_directory_full_path);

            // XXX: For some reason, we have to add the full path to the .a file here or it is not found :(
            PublicAdditionalLibraries.Add(protobuf_lib_directory_full_path + "/libprotobuf.a");

            Definitions.AddRange(
                new string[]
                {
                    "_MAC",
                    "__x86_64__",
                });

        }

        // TODO: Other platforms...

        Definitions.Add(string.Format("WITH_GOOGLE_PROTOBUF_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "..", "ThirdParty")); }
    }
}
