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

### Mac

To build the test, run:

`$UNREAL_ENGINE/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project="$NAKAMA_UNREAL/NakamaTest/NakamaTest.uproject" -clientconfig=Test -noP4 -platform=Mac -clientconfig=Development -installed -unrealexe=UnrealEditor -utf8output -build -cook -stage -package`

To run the test, run:

`./NakamaTest/Binaries/Mac/NakamaTest-Mac-Test.app/Contents/MacOS/NakamaTest-Mac-Test -nullrhi -stdout -forcelogflush -ExecCmds="Automation RunTests NakamaTest.Core"`

You can pass `List` instead to teh `Automation` command to view all tests. It will include engine tests.