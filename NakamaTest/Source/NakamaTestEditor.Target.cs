// Copyright 2023 The Nakama Authors.

using UnrealBuildTool;
using System.Collections.Generic;

public class NakamaTestEditorTarget : TargetRules
{
       public NakamaTestEditorTarget( TargetInfo Target) : base(Target)
       {
               Type = TargetType.Editor;
               DefaultBuildSettings = BuildSettingsVersion.V2;
               ExtraModuleNames.AddRange( new string[] { "NakamaTest" } );
       }
}