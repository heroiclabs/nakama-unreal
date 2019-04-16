Nakama Unreal
=============

> Unreal Editor 4 client for Nakama server.

Nakama is an open-source distributed server for social and realtime games. For more information have a look at the [server documentation](https://heroiclabs.com/docs/).

The [client guide](https://heroiclabs.com/docs/clients/unreal/) is available on the server documentation. The [client reference documentation](http://heroiclabs.github.io/nakama-unreal/) is deployed on gh-pages.

If you encounter any issues with the server you can generate diagnostics for us with `nakama doctor`. Send these to support@heroiclabs.com or [open an issue](https://github.com/heroiclabs/nakama/issues). If you experience any issues with the client, it can be useful to enable trace (`.Trace(true)`) to produce logs and [open an issue](https://github.com/heroiclabs/nakama-unreal/issues).

### Getting Started

#### Prerequisites

To get started using Nakama in Unreal, you will need the following:

1. [Unreal Engine](https://www.unrealengine.com/dashboard) 4.15 or greater.
1. A compiler for the platform you are developing on, such as [Visual Studio](https://www.visualstudio.com/vs/community/) on Windows or [XCode](https://developer.apple.com/xcode/download/) on OSX.
1. [nakama-unreal](https://github.com/heroiclabs/nakama-unreal/releases)

Also, please ensure your Unreal project is a C++ project.  If it is Blueprint only, you can add a new C++ file to your project in Unreal Editor via "File -> New C++ Class".  Set it private and name it whatever you like.  Having this file in your project lets Unreal know to look for C++ code.

#### Setup

To use nakama-unreal in your Unreal project, you'll need to copy the nakama-unreal files you downloaded into the appropriate place. To do this:

1. Open your Unreal project folder (for example, D:\\MyUnrealProject\\) in Explorer or Finder.
1. If one does not already exist, create a Plugins folder here.
1. Copy the Nakama folder from the nakama-unreal release you downloaded, into this Plugins folder.
1. Now, edit your project's .Build.cs file, located in the project folder under Source\\[ProjectFolder] (for example, D:\\MyUnrealProject\\Source\\MyUnrealProject\\MyUnrealProject.Build.cs).  Add this line to the constructor:

`PrivateDependencyModuleNames.AddRange(new string[] { "Nakama" });`

So, you might end up with the file that looks something like this:

```c#
// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyUnrealProject : ModuleRules
{
	public MyUnrealProject(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Nakama" });
	}
}
```

At this point, you are done.  Restart Unreal.  After it compiles things, open Edit->Plugins and scroll to the bottom.  If all went well, you should see HeroicLabs.Nakama listed as a plugin.

## Usage

The client object has many methods to execute various features in the server or open realtime socket connections with the server.

Include nakama header.

```cpp
#include "nakama-cpp/Nakama.h"
```

Use nakama namespace.

```cpp
using namespace Nakama;
```

Use the connection credentials to build a client object.

```cpp
DefaultClientParameters parameters;
parameters.serverKey = "defaultkey";
parameters.host = "127.0.0.1";
parameters.port = 7349;
NClientPtr client = createDefaultClient(parameters);
```
