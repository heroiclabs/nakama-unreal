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

`$UNREAL_ENGINE/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -targetconfig=Debug -project="$NAKAMA_UNREAL/IntegrationTests/IntegrationTests.uproject" -noP4 -installed -utf8output -build -cook -stage -package -verbose -stdout -nohostplatform -useshellexecute`

To run the test, run:

```bash
./IntegrationTests/Saved/StagedBuilds/Windows/IntegrationTests.exe -nullrhi -verbose -ExecCmds="Automation RunTests IntegrationTests.Core"
```

There appears to be a problem with logging to stdout on Windows, so you'll need to obtain the test logs from `IntegrationTests\Saved\StagedBuilds\Windows\IntegrationTests\Saved\Logs\IntegrationTests.log`.

### Mac

To build the test, run:

`$UNREAL_ENGINE/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project="$NAKAMA_UNREAL/IntegrationTests/IntegrationTests.uproject" -targetConfig=Debug -noP4 -platform=Mac -Architecture_Mac=arm64 -targetconfig=Debug -installed -unrealexe=UnrealEditor -utf8output -build -cook -stage -package -verbose`

To run the test, run:

`./IntegrationTests/Binaries/Mac/IntegrationTests.app/Contents/MacOS/IntegrationTests -nullrhi -stdout -forcelogflush -ExecCmds="Automation RunTests IntegrationTests.Core"`

You can pass `List` instead to the `Automation` command to view all tests. It will include engine tests.

You can also pass `-LogCmds="<LogCategory> verbose"` where `<LogCategory>` is one of those defined by `DEFINE_LOG_CATEGORY`.

### Linux

To build the test, run:

`$UNREAL_ENGINE/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project="$NAKAMA_UNREAL/IntegrationTests/IntegrationTests.uproject" -clientconfig=Test -noP4 -platform=Linux -targetconfig=Debug -installed  -utf8output -build -cook -stage -package -verbose`

To run the test:

`IntegrationTests/Binaries/Linux/IntegrationTests-Linux-Test -nullrhi -stdout -forcelogflush -ExecCmds="Automation RunTests IntegrationTests.Core"`

To debug with LLDB on Mac:

`lldb ${NAKAMA_UNREAL}/IntegrationTests/Binaries/Mac/IntegrationTests-Mac-Test.app/Contents/MacOS/IntegrationTests-Mac-Test`

Set the startup args inside the lldb shell:

`settings set -- target.run-args -nullrhi -stdout -forcelogflush -ExecCmds="Automation RunTests IntegrationTests.Core"`

Then call `run`.
