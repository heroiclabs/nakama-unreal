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

		if (UnrealTargetPlatform.Win32 == Target.Platform || UnrealTargetPlatform.Win64 == Target.Platform)
		{
			HandleWindows(Target);
		}
		else if (UnrealTargetPlatform.Linux == Target.Platform)
		{
			HandleLinux(Target);
		}
		else if (UnrealTargetPlatform.Mac == Target.Platform)
		{
			HandleMac(Target);
		}
		else if (UnrealTargetPlatform.IOS == Target.Platform)
		{
			HandleIOS(Target);
		}
		else if (UnrealTargetPlatform.Android == Target.Platform)
		{
			HandleAndroid(Target);
		}
		else
		{
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
		PublicDelayLoadDLLs.Add("nakama-cpp" + libSuffix + ".dll");
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
		string nakamaDylibPath = Path.Combine(libsPath, "libnakama-cpp.dylib");

		PublicDelayLoadDLLs.Add(nakamaDylibPath);
		RuntimeDependencies.Add(nakamaDylibPath);
	}

	private void HandleIOS(ReadOnlyTargetRules Target)
	{
		string libsPath = Path.Combine(CommonSharedLibsPath, "ios");
		
		PublicLibraryPaths.Add(libsPath);
		
		PublicAdditionalLibraries.Add(Path.Combine(libsPath, "libnakama-cpp.dylib"));
	}

	private bool isArch_x64(ReadOnlyTargetRules Target)
	{
		System.Console.WriteLine("ARCH: {0}", Target.Architecture);

		return Target.Architecture.StartsWith("x86_64") || Target.Architecture.StartsWith("x64");
	}

	private void HandleLinux(ReadOnlyTargetRules Target)
	{
		string libsPath = Path.Combine(CommonSharedLibsPath, "linux", isArch_x64(Target) ? "x64" : "x86");
		string libName = "libnakama-cpp.so";
		string binLibPath = Path.Combine(libsPath, libName);

		RuntimeDependencies.Add(binLibPath);

		// For some reason, we have to add the full path here or it is not found :(
		PublicAdditionalLibraries.Add(binLibPath);
	}

	private void CopyTo(string Filepath, string toPath)
	{
		string filename = Path.GetFileName(Filepath);

		if (!Directory.Exists(toPath))
			Directory.CreateDirectory(toPath);

		CopyFile(Filepath, Path.Combine(toPath, filename));
	}

	private void CopyToBinaries(string Filepath, ReadOnlyTargetRules Target)
	{
		string binariesDir = GetTargetProjectPlatformBinariesPath(Target);
		CopyTo(Filepath, binariesDir);
	}

	private string GetTargetProjectPath(ReadOnlyTargetRules Target)
	{
		return Path.GetDirectoryName(Target.ProjectFile.ToString());
	}

	private string GetTargetProjectPlatformBinariesPath(ReadOnlyTargetRules Target)
	{
		string projectPath = GetTargetProjectPath(Target);
		string binariesDir = Path.Combine(projectPath, "Binaries", Target.Platform.ToString());
		return binariesDir;
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
			throw new Exception("Failed to copy file: " + ex.Message);
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
