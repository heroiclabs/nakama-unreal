// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class Nakama : ModuleRules
{
	public Nakama(TargetInfo Target)
	{

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
                "libWebSockets",
                "SSL"
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
                break;
            case UnrealTargetPlatform.Win64:
                break;
            case UnrealTargetPlatform.Mac:
                bUseRTTI = true; // turn on RTTI
                break;
            case UnrealTargetPlatform.Linux:
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

    private bool LoadProtobufLib(TargetInfo Target)
    {
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

            Definitions.AddRange(
                new string[]
                {
                    ((Target.Platform == UnrealTargetPlatform.Win64) ? "WIN64" : "WIN32"),
                    "_WINDOWS",
                    "NDEBUG",
                    "GOOGLE_PROTOBUF_CMAKE_BUILD",
                    "PROTOBUF_INLINE_NOT_IN_HEADERS=0"
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
