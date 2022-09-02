using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.All)]
public class NakamaTestTarget : TargetRules
{
	public NakamaTestTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Program;
		LinkType = TargetLinkType.Monolithic;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		LaunchModuleName = "NakamaTest";
          

		bDeployAfterCompile = false;
		bIsBuildingConsoleApplication = true;

		// Disabling default true flags that aren't necessary for tests

		// Lean and Mean mode
		bBuildDeveloperTools = false;
		
		// No localization
		bCompileICU = false;

		// No need for shaders by default
		bForceBuildShaderFormats = false;

		// Do not link against the engine, no Chromium Embedded Framework etc.
		bCompileAgainstEngine = false;
		bCompileCEF3 = false;
		bCompileAgainstCoreUObject = false;
		bCompileAgainstApplicationCore = false;
		bUseLoggingInShipping = true;

		bool bDebugOrDevelopment = Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.Development;
		bBuildWithEditorOnlyData = Target.Platform.IsInGroup(UnrealPlatformGroup.Desktop) && bDebugOrDevelopment;

		// Disable malloc profiling in tests
		bUseMallocProfiler = false;
	}
}