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

`PrivateDependencyModuleNames.AddRange(new string[] { "NakamaCore" });`

So, you might end up with the file that looks something like this:

```c#
using UnrealBuildTool;

public class MyUnrealProject : ModuleRules
{
	public MyUnrealProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "NakamaCore" });
	}
}
```

## Threading model

Nakama C++ is designed to use in one thread only.

## Usage

The client object has many methods to execute various features in the server or open realtime socket connections with the server.

Include nakama header.

```cpp
#include "NakamaCore.h"
```

Use nakama namespace.

```cpp
using namespace NAKAMA_NAMESPACE;
```

Use the connection credentials to build a client object.

```cpp
NClientParameters parameters;
parameters.serverKey = "defaultkey";
parameters.host = "127.0.0.1";
parameters.port = DEFAULT_PORT;
NClientPtr client = createDefaultClient(parameters);
```

The `createDefaultClient` will create HTTP/1.1 client to use REST API.

## Tick

The `tick` method pumps requests queue and executes callbacks in your thread. You must call it periodically, the `Tick` method of actor is good place for this.

```cpp
// Called every frame
void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    client->tick();
    if (rtClient) rtClient->tick();
}
```

Without this the default client and realtime client will not work, and you will not receive responses from the server.

### Authenticate

There's a variety of ways to [authenticate](https://heroiclabs.com/docs/authentication) with the server. Authentication can create a user if they don't already exist with those credentials. It's also easy to authenticate with a social profile from Google Play Games, Facebook, Game Center, etc.

```cpp
string email = "super@heroes.com";
string password = "batsignal";

auto successCallback = [](NSessionPtr session)
{
    UE_LOG(LogActor, Warning, TEXT("session token: %s"), session->getAuthToken().c_str());
};

auto errorCallback = [](const NError& error)
{
};

client->authenticateEmail(email, password, "", false, {}, successCallback, errorCallback);
```

### Sessions

When authenticated the server responds with an auth token (JWT) which contains useful properties and gets deserialized into a `NSession` object.

```cpp
UE_LOG(LogActor, Warning, TEXT("%s"), session->getAuthToken().c_str()); // raw JWT token
UE_LOG(LogActor, Warning, TEXT("%s"), session->getUserId().c_str());
UE_LOG(LogActor, Warning, TEXT("%s"), session->getUsername().c_str());
UE_LOG(LogActor, Warning, TEXT("Session has expired: %s"), session->isExpired() ? "yes" : "no");
UE_LOG(LogActor, Warning, TEXT("Session expires at: %llu"), session->getExpireTime());
UE_LOG(LogActor, Warning, TEXT("Session created at: %llu"), session->getCreateTime());
```

It is recommended to store the auth token from the session and check at startup if it has expired. If the token has expired you must reauthenticate. The expiry time of the token can be changed as a setting in the server.

```cpp
string authtoken = "restored from somewhere";
NSessionPtr session = restoreSession(authtoken);
if (session->isExpired())
{
    UE_LOG(LogActor, Warning, TEXT("Session has expired. Must reauthenticate!"));
}
```

### Requests

The client includes lots of builtin APIs for various features of the game server. These can be accessed with the async methods. It can also call custom logic as RPC functions on the server. These can also be executed with a socket object.

All requests are sent with a session object which authorizes the client.

```cpp
auto successCallback = [](const NAccount& account)
{
    UE_LOG(LogActor, Warning, TEXT("user id : %s"), account.user.id.c_str());
    UE_LOG(LogActor, Warning, TEXT("username: %s"), account.user.username.c_str());
    UE_LOG(LogActor, Warning, TEXT("wallet  : %s"), account.wallet.c_str());
};

client->getAccount(session, successCallback, errorCallback);
```

### Realtime client

The client can create one or more realtime clients with the server. Each realtime client can have it's own events listener registered for responses received from the server.

```cpp
bool createStatus = true; // if the socket should show the user as online to others.
// define realtime client in your class as NRtClientPtr rtClient;
rtClient = client->createRtClient(DEFAULT_PORT);
// define listener in your class as NRtDefaultClientListener listener;
listener.setConnectCallback([]()
{
    UE_LOG(LogActor, Warning, TEXT("Socket connected"));
});
rtClient->setListener(&listener);
rtClient->connect(session, createStatus);
```

Don't forget to call `tick` method. See [Tick](#tick) section for details.

### Logging

Client logging is off by default.

To enable logs output to console with debug logging level:

```cpp
#include "NUnrealLogSink.h"

NLogger::init(std::make_shared<NUnrealLogSink>(), NLogLevel::Debug);
```

### Development

To check verify that the Nakama plugin builds on Windows:

`& "${env:UnrealEngine}\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -Plugin="${env:nakama-unreal}\Nakama\Nakama.uplugin" -TargetPlatforms=Win64 -Package="${env:nakama-unreal}/Out"`

On Mac:

`"${UNREAL_ENGINE}/Engine/Build/BatchFiles/RunUAT.sh" BuildPlugin -Plugin="${NAKAMA_UNREAL}/Nakama/Nakama.uplugin" -TargetPlatforms=Mac -Package="${NAKAMA_UNREAL}/Out"`

You can include the flag `-Rocket` after the `BuildPlugin` command if you'd like to test the plugin building in a packaged (i.e., not-source) distribution of Unreal.

Additionally, you can compile our Unreal test project using our Unreal Nakama module. Run following from the `./test/unreal` directory:

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
