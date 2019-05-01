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
				//"Projects"
				// ... add other public dependencies that you statically link with here ...
			});

		switch (Target.Platform)
		{
			case UnrealTargetPlatform.Win32:
				HandleWindows(Target);
				break;

			case UnrealTargetPlatform.Win64:
				HandleWindows(Target);
				break;

			case UnrealTargetPlatform.Linux:
				HandleLinux(Target);
				break;

			case UnrealTargetPlatform.Mac:
				HandleMac(Target);
				break;

			case UnrealTargetPlatform.IOS:
				HandleIOS(Target);
				break;

			case UnrealTargetPlatform.Android:
				HandleAndroid(Target);
				break;

			case UnrealTargetPlatform.PS4:
			case UnrealTargetPlatform.XboxOne:
			case UnrealTargetPlatform.HTML5:
			default:
				throw new NotImplementedException("Nakama Unreal client does not currently support platform: " + Target.Platform.ToString());
		}

		PrivateDefinitions.Add("NAKAMA_SHARED_LIBRARY=1");
	}

	private void HandleWindows(ReadOnlyTargetRules Target)
	{
		string libsPath = CommonSharedLibsPath;
		
		if (Target.Platform == UnrealTargetPlatform.Win32)
		{
			libsPath = Path.Combine(libsPath, "win32");
		}
		else
		{
			libsPath = Path.Combine(libsPath, "win64");
		}
		
		switch (Target.WindowsPlatform.Compiler)
		{
		#if !UE_4_22_OR_LATER
			case WindowsCompiler.VisualStudio2015: libsPath = Path.Combine(libsPath, "v140"); break;
		#endif
			case WindowsCompiler.VisualStudio2017: libsPath = Path.Combine(libsPath, "v141"); break;
		#if UE_4_22_OR_LATER
			case WindowsCompiler.VisualStudio2019: libsPath = Path.Combine(libsPath, "v142"); break;
		#endif
			default:
				throw new NotImplementedException("Nakama Unreal client does not currently support compiler: " + Target.WindowsPlatform.GetVisualStudioCompilerVersionName());
		}

		string libSuffix;

		/*if (Target.Configuration == UnrealTargetConfiguration.DebugGame || Target.Configuration == UnrealTargetConfiguration.DebugGameEditor)
		{
			libsPath = Path.Combine(libsPath, "Debug");
			libSuffix = "d";
		}
		else*/
		{
			libsPath = Path.Combine(libsPath, "Release");
			libSuffix = "";
		}
		
		PublicLibraryPaths.Add(libsPath);
		
		PublicAdditionalLibraries.Add("nakama-cpp" + libSuffix + ".lib");
		CopyToBinaries(Path.Combine(libsPath, "nakama-cpp" + libSuffix + ".dll"), Target);
		PublicDelayLoadDLLs.AddRange(new string[] { "nakama-cpp" + libSuffix + ".dll" });
	}

	private void HandleAndroid(ReadOnlyTargetRules Target)
	{
		string libsPath = Path.Combine(CommonSharedLibsPath, "android");
		
		PublicLibraryPaths.Add(Path.Combine(libsPath, "arm64-v8a"));
		PublicLibraryPaths.Add(Path.Combine(libsPath, "armeabi-v7a"));
		PublicLibraryPaths.Add(Path.Combine(libsPath, "x86"));
		PublicLibraryPaths.Add(Path.Combine(libsPath, "x86_64"));
		
		PublicAdditionalLibraries.Add("nakama-cpp");
		
		string relAPLPath = Utils.MakePathRelativeTo(Path.Combine(ModulePath, "Nakama_APL.xml"), Target.RelativeEnginePath);
		//AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", relAPLPath));
		AdditionalPropertiesForReceipt.Add("AndroidPlugin", relAPLPath);
	}

	private void HandleMac(ReadOnlyTargetRules Target)
	{
		string libsPath = Path.Combine(CommonSharedLibsPath, "mac");
		
		PublicLibraryPaths.Add(libsPath);
		
		PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libnakama-cpp.dylib"));
	}

	private void HandleIOS(ReadOnlyTargetRules Target)
	{
		string libsPath = Path.Combine(CommonSharedLibsPath, "ios");
		
		PublicLibraryPaths.Add(libsPath);
		
		PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libnakama-cpp.dylib"));
	}

	private void HandleLinux(ReadOnlyTargetRules Target)
	{
		string libsPath = Path.Combine(CommonSharedLibsPath, "linux");
		
		PublicLibraryPaths.Add(libsPath);
		
		// For some reason, we have to add the full path to the .a file here or it is not found :(
		PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libnakama-cpp.so"));
	}

	private void CopyToBinaries(string Filepath, ReadOnlyTargetRules Target)
	{
		string binariesDir = Path.Combine(ProjectBinariesPath, Target.Platform.ToString());
		string filename = Path.GetFileName(Filepath);

		if (!Directory.Exists(binariesDir))
			Directory.CreateDirectory(binariesDir);

		CopyFile(Filepath, Path.Combine(binariesDir, filename));
	}

	private string ProjectBinariesPath
	{
		get
		{
			var basePath = Path.GetDirectoryName(RulesCompiler.GetFileNameFromType(GetType()));
			return Path.Combine(basePath, "..", "..", "..", "..", "Binaries");
			//return Path.Combine(
			//	  Directory.GetParent(ModulePath).Parent.Parent.ToString(), "Binaries");
		}
	}

	private void CopyFile(string source, string dest)
	{
		System.Console.WriteLine("Copying {0} to {1}", source, dest);
		if (System.IO.File.Exists(dest))
		{
			System.IO.File.SetAttributes(dest, System.IO.File.GetAttributes(dest) & ~System.IO.FileAttributes.ReadOnly);
		}
		try
		{
			System.IO.File.Copy(source, dest, true);
		}
		catch (System.Exception ex)
		{
			System.Console.WriteLine("Failed to copy file: {0}", ex.Message);
		}
	}

	private string ModulePath
	{
		get { return ModuleDirectory; }
	}

	private string CommonSharedLibsPath
	{
		get { return Path.Combine(ModulePath, "Private", "shared-libs"); }
	}

	private string CommonStaticLibsPath
	{
		get { return Path.Combine(ModulePath, "Private", "libs"); }
	}
}
