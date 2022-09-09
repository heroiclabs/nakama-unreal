Nakama Unreal
=============

[![GitHub release](https://img.shields.io/github/release/heroiclabs/nakama-unreal.svg)](https://github.com/heroiclabs/nakama-unreal/releases/latest)
[![Forum](https://img.shields.io/badge/forum-online-success.svg)](https://forum.heroiclabs.com)
[![Client guide](https://img.shields.io/badge/client_guide-online-brightgreen)](https://heroiclabs.com/docs/unreal-client-guide)
[![Reference](https://img.shields.io/badge/reference-online-brightgreen)](https://heroiclabs.github.io/nakama-cpp/html/index.html)
[![License](https://img.shields.io/github/license/heroiclabs/nakama.svg)](https://github.com/heroiclabs/nakama/blob/master/LICENSE)

> Unreal Editor 4/5 client for Nakama server.

[Nakama](https://github.com/heroiclabs/nakama) is an open-source server designed to power modern games and apps. Features include user accounts, chat, social, matchmaker, realtime multiplayer, and much [more](https://heroiclabs.com).

This client implements the full API and socket options with the server. It's written in C++ with minimal dependencies to support Unreal, unreal and other custom engines and frameworks.

If you experience any issues with the client, it can be useful to enable debug logs (see [Logging](#logging) section) and [open an issue](https://github.com/heroiclabs/nakama-cpp/issues).

Full documentation is online - https://heroiclabs.com/docs

## Getting Started

You'll need to setup the server and database before you can connect with the client. The simplest way is to use Docker but have a look at the [server documentation](https://github.com/heroiclabs/nakama#getting-started) for other options.

To get started using Nakama in Unreal, you will need the following:

1. Install and run the servers. Follow these [instructions](https://heroiclabs.com/docs/install-docker-quickstart).
1. [Unreal Engine](https://www.unrealengine.com/dashboard) 4.21 or greater.
1. A compiler for the platform you are developing on, such as [Visual Studio](https://www.visualstudio.com/vs/community/) on Windows or [XCode](https://developer.apple.com/xcode/download/) on OSX.
1. [nakama-unreal](https://github.com/heroiclabs/nakama-unreal/releases)

#### Setup

To use nakama-unreal in your Unreal project, you'll need to copy the nakama-unreal files you downloaded into the appropriate place. To do this:

1. Open your Unreal project folder (for example, `D:\\MyUnrealProject\\`) in Explorer or Finder.
1. If one does not already exist, create a `Plugins` folder here.
1. Copy the `Nakama` folder from the nakama-unreal release you downloaded, into this `Plugins` folder.
1. Now, edit your project's `.Build.cs` file, located in the project folder under `Source\\[ProjectFolder]` (for example, `D:\\MyUnrealProject\\Source\\MyUnrealProject\\MyUnrealProject.Build.cs`). Add this line to the constructor:

`PrivateDependencyModuleNames.AddRange(new string[] { "NakamaUnreal" });`

So, you might end up with the file that looks something like this:

```c#
using UnrealBuildTool;

public class MyUnrealProject : ModuleRules
{
	public MyUnrealProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "NakamaUnreal" });
	}
}
```

## Threading model

Nakama C++ is designed to use in one thread only.

### Development

To check verify that the Nakama plugin builds on Windows:

`& "${env:UnrealEngine}\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -Plugin="${env:nakama-unreal}\Nakama\Nakama.uplugin" -TargetPlatforms=Win64 -Package="${env:nakama-unreal}/Out"`

On Mac:

`"${UNREAL_ENGINE}/Engine/Build/BatchFiles/RunUAT.sh" BuildPlugin -Plugin="${NAKAMA_UNREAL}/Nakama/Nakama.uplugin" -TargetPlatforms=Mac -Package="${NAKAMA_UNREAL}/Out"`

You can include the flag `-Rocket` after the `BuildPlugin` command if you'd like to test the plugin building in a packaged (i.e., not-source) distribution of Unreal.

## Contribute

The development roadmap is managed as GitHub issues and pull requests are welcome. If you're interested to enhance the code please open an issue to discuss the changes or drop in and discuss it in the [community forum](https://forum.heroiclabs.com).

## Source Builds

The Unreal module is based on [General C++ SDK](https://github.com/heroiclabs/nakama-cpp)

### Nakama Unreal Client guide

You can find Nakama Unreal Client guide [here](https://heroiclabs.com/docs/unreal-client-guide/).

## License

This project is licensed under the [Apache-2 License](https://github.com/heroiclabs/nakama-dotnet/blob/master/LICENSE).

## Special Thanks

Thanks to [@dimon4eg](https://github.com/dimon4eg) for this excellent support on developing Nakama C++, Unreal and Cocos2d-x client libraries.
