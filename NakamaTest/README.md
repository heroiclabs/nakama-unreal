# Nakama Test Project
This is a test Unreal Engine project testing the core features of the Nakama Unreal Engine plugin.

# Build and Test
Build the Nakama plugin and place it in the Plugins folder.

Follow these instructions to package the example project:

https://docs.unrealengine.com/4.27/en-US/Basics/Projects/Packaging/

Follow these instructions to package the test project:

https://docs.unrealengine.com/4.27/en-US/Basics/Projects/Packaging/

### Windows

To build the test, run:

`$UNREAL_ENGINE/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project="$NAKAMA_UNREAL/NakamaTest/NakamaTest.uproject" -clientconfig=Test -noP4 -platform=Win64 -clientconfig=Test -installed -utf8output -build -cook -stage -package -verbose`

To run the test, run:

`./NakamaTest/Binaries/Win64/NakamaTest-Win64-Test.exe -nullrhi -stdout -forcelogflush -ExecCmds="Automation RunTests NakamaTest.Core"`

### Mac

To build the test, run:

`$UNREAL_ENGINE/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project="$NAKAMA_UNREAL/NakamaTest/NakamaTest.uproject" -clientconfig=Test -noP4 -platform=Mac -Architecture_Mac=arm64 -targetconfig=Debug -installed -unrealexe=UnrealEditor -utf8output -build -cook -stage -package -verbose`


To run the test, run:

`.NakamaTest/Binaries/Mac/NakamaTest-Mac-Test.app/Contents/MacOS/NakamaTest-Mac-Test -nullrhi -stdout -forcelogflush -ExecCmds="Automation RunTests NakamaTest.Core"`

You can pass `List` instead to the `Automation` command to view all tests. It will include engine tests.

### Linux

To build the test, run:

`$UNREAL_ENGINE/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project="$NAKAMA_UNREAL/NakamaTest/NakamaTest.uproject" -clientconfig=Test -noP4 -platform=Linux -targetconfig=Debug -installed  -utf8output -build -cook -stage -package -verbose`

To run the test:

`NakamaTest/Binaries/Linux/NakamaTest-Linux-Test -nullrhi -stdout -forcelogflush -ExecCmds="Automation RunTests NakamaTest.Core"`

To debug with LLDB on Mac:

`lldb ${NAKAMA_UNREAL}/NakamaTest/Binaries/Mac/NakamaTest-Mac-Test.app/Contents/MacOS/NakamaTest-Mac-Test`

Set the startup args inside the lldb shell:

`settings set -- target.run-args -nullrhi -stdout -forcelogflush -ExecCmds="Automation RunTests NakamaTest.Core"`

Then call `run`.
