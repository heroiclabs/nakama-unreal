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

`$UNREAL_ENGINE/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -targetconfig=Debug -project="$NAKAMA_UNREAL/NakamaTest/NakamaTest.uproject" -noP4 -installed -utf8output -build -cook -stage -package -verbose -stdout -nohostplatform -useshellexecute`

To run the test, run:

```bash
./NakamaTest/Saved/StagedBuilds/Windows/NakamaTest.exe -nullrhi -verbose -ExecCmds="Automation RunTests NakamaTest.Core"
```

There appears to be a problem with logging to stdout on Windows, so you'll need to obtain the test logs from `NakamaTest\Saved\StagedBuilds\Windows\NakamaTest\Saved\Logs\NakamaTest.log`.

### Mac

To build the test, run:

`$UNREAL_ENGINE/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project="$NAKAMA_UNREAL/NakamaTest/NakamaTest.uproject" -clientconfig=Test -noP4 -platform=Mac -Architecture_Mac=arm64 -clientconfig=Test -installed -unrealexe=UnrealEditor -utf8output -build -cook -stage -package -verbose`


You can pass `List` instead to the `Automation` command to view all tests. It will include engine tests.

### Linux

To build the test, run:

`$UNREAL_ENGINE/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project="$NAKAMA_UNREAL/NakamaTest/NakamaTest.uproject" -clientconfig=Test -noP4 -platform=Linux -clientconfig=Test -installed  -utf8output -build -cook -stage -package -verbose`

To run the test:

`NakamaTest/Binaries/Linux/NakamaTest-Linux-Test -nullrhi -stdout -forcelogflush -ExecCmds="Automation RunTests NakamaTest.Core"`

To debug with LLDB on Mac:

`lldb ${NAKAMA_UNREAL}/NakamaTest/Binaries/Mac/NakamaTest-Mac-Test.app/Contents/MacOS/NakamaTest-Mac-Test`

Set the startup args inside the lldb shell:

`settings set -- target.run-args -nullrhi -stdout -forcelogflush -ExecCmds="Automation RunTests NakamaTest.Core"`

Then call `run`.
