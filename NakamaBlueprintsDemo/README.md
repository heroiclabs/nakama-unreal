# Nakama Demo Project
This is an example Unreal Engine project showcasing the core features of Nakama, made using only the plugins and 100% Blueprints.

This documentation is NOT Final and subject to change.

This repository includes the Nakama plugin within the `Plugins` folder.

It is primarily tested on Unreal Engine 5.0

# Getting Started
These are the steps to get started with the project.

1. Install and run the Nakama server. Follow these [instructions](https://heroiclabs.com/docs/install-docker-quickstart).
2. Install [Unreal Engine](https://www.unrealengine.com) 5.0 or greater
3. Right click the .uproject and select `Generate Visual Studio Project Files`
4. Open the solution in your Unreal Compatible IDE (Visual Studio, Xcode, Rider) and run the project
5. Once the Unreal Editor is open, click Play and start testing the features
6. If you have different server credentials than the default ones, or are running a remote server, open the `NakamaDemoController` and replace the server parameters in the `Create Default Client` and `Setup Realtime Client` which are highlighted in green.

# Build and Test
Follow these instructions to package the example project:

https://docs.unrealengine.com/5.0/en-US/packaging-unreal-engine-projects/

To package it from the command line on Windows run:

```& "${env:UnrealEngine}\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -Platform=Win64 -Project="${env:NakamaUnreal}\NakamaBlueprintsDemo\NakamaBlueprintsDemo.uproject" -ClientConfig=Development -Cook -Build```

On Mac:

```"$UNREAL_ENGINE/Engine/Build/BatchFiles/RunUAT.sh" BuildCookRun -Platform=Mac -Project="${NAKAMA_UNREAL}/NakamaBlueprintsDemo/NakamaBlueprintsDemo.uproject" -ClientConfig=Development -Cook -Build -Architecture_Mac=arm64```