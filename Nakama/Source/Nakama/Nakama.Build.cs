/*
 * Copyright 2019 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

using System;
using System.IO;
using UnrealBuildTool;

public class Nakama : ModuleRules
{
	public Nakama(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModulePath, "..", "ThirdParty")
			});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			});

		string libsPath;
		
		switch (Target.Platform)
		{
			case UnrealTargetPlatform.Win32:
				libsPath = Path.Combine(LibsPath, "win32", "v" + Target.WindowsPlatform.GetVisualStudioCompilerVersionName());
				break;

			case UnrealTargetPlatform.Win64:
				libsPath = Path.Combine(LibsPath, "win64", "v" + Target.WindowsPlatform.GetVisualStudioCompilerVersionName());
				break;

			case UnrealTargetPlatform.Linux:
				libsPath = Path.Combine(LibsPath, "linux");
				break;

			case UnrealTargetPlatform.Mac:
				libsPath = Path.Combine(LibsPath, "mac");
				break;

			case UnrealTargetPlatform.IOS:
				libsPath = Path.Combine(LibsPath, "ios");
				break;

			case UnrealTargetPlatform.Android:
				libsPath = Path.Combine(LibsPath, "android");
				break;

			case UnrealTargetPlatform.PS4:
			case UnrealTargetPlatform.XboxOne:
			case UnrealTargetPlatform.HTML5:
			default:
				throw new NotImplementedException("Nakama Unreal client does not currently support platform: " + Target.Platform.ToString());
		}

		PublicLibraryPaths.Add(libsPath);

		if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
		{
		}
		else
		{
            // XXX: For some reason, we have to add the full path to the .a file here or it is not found :(
			PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libnakama-cpp.a"));
			PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libprotobuf.a"));
			PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libaddress_sorting.a"));
			PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libcares.a"));
			PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libgpr.a"));
			PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libgrpc++.a"));
			PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libgrpc.a"));
			PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libz.a"));
		}
	}

	private string ModulePath
	{
		get { return ModuleDirectory; }
	}

	private string LibsPath
	{
		get { return Path.Combine(ModulePath, "Private", "libs"); }
	}
}
