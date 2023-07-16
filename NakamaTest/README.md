# Nakama Test Project
This is a test Unreal Engine project testing the core features of the Nakama Unreal Engine plugin.

# Build and Test
Build the Nakama plugin and place it in the Plugins folder.

Follow these instructions to package the example project:

https://docs.unrealengine.com/4.27/en-US/Basics/Projects/Packaging/

Follow these instructions to package the test project:

https://docs.unrealengine.com/4.27/en-US/Basics/Projects/Packaging/

To package it from the command line on Windows run:


```& "${env:UnrealEngine}\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -Platform=Win64 -Project="${env:NakamaUnreal}\NakamaTest\NakamaTest.uproject" -ClientConfig=Development -Cook -Build```

On Mac:

`$UNREAL_ENGINE/Engine/Build/BatchFiles/Mac/Build.sh NakamaTest Mac Development -Architecture_Mac=arm64 -Project="${NAKAMA_UNREAL}/NakamaTest/NakamaTest.uproject"`
