 Nakama Unreal
=============

[Nakama](https://github.com/heroiclabs/nakama) is an open-source server designed to power modern games and apps. Features include user accounts, chat, social, matchmaker, realtime multiplayer, and much [more](https://heroiclabs.com).

This client implements the full API and socket options with the server. It's written in C++ with minimal dependencies to support Unreal 4 and 5.

If you experience any issues with the client, it can be useful to enable debug logs and [open an issue](https://github.com/heroiclabs/nakama-cpp/issues).

Full documentation is online - https://heroiclabs.com/docs

# General Information

This plugin can also be used for programmers who like C++ or Blueprints. All variables and functions are exposed to types used by Unreal Engine (UPROPERTIES, USTRUCT, UFUNCTIONS etc.)

The plugin is divided into three modules which can be pulled in depending on your needs.

- `NakamaUnreal` The recommended C++ based module for using Nakama in UnrealEngine. This integrates with Unreal's native types and UObjects.
- `NakamaBlueprints` For users who would prefer to use Blueprints in their project.
- `NakamaCore` For users who are migrating from our old Unreal client and want to make minimal changes, or use our lower-level C++ API without Unreal types: (https://github.com/heroiclabs/nakama-cpp)

Clients are referred in this documentation as **Realtime Client** and **Default Client** in which the realtime client is the socket and the default client is using REST API to communicate with Nakama.

# Getting Started

You'll need to setup the server and database before you can connect with the client. The simplest way is to use Docker but have a look at the [server documentation](https://github.com/heroiclabs/nakama#getting-started) for other options.

To get started using Nakama in Unreal you will need the following:

1. Install and run the servers. Follow these [instructions](https://heroiclabs.com/docs/install-docker-quickstart).
2. A copy of the core [Nakama Unreal](https://github.com/heroiclabs/nakama-unreal) plugin
3. [Unreal Engine](https://www.unrealengine.com) 4.25 or greater or 5.
4. A compiler for the platform you are developing on, such as [Visual Studio](https://www.visualstudio.com/vs/community/) on Windows or [XCode](https://developer.apple.com/xcode/download/) on OSX.

Also, please ensure your Unreal project is a C++ project.  If it is Blueprint only, you can add a new C++ file to your project in Unreal Editor via "File -> New C++ Class".  Set it private and name it whatever you like.  Having this file in your project lets Unreal compile the plugin.

## Installing the Plugin

To use Nakama in your Unreal project, you'll need to download our plugin from the Unreal Marketplace or copy the nakama-unreal files you downloaded into the appropriate place. To do the latter:

1. Open your Unreal project folder (for example, `C:\\MyUnrealProject\\`) in Explorer or Finder.
2. If one does not already exist, create a `Plugins` folder here.
3. Copy the `Nakama` folder from [nakama-unreal](https://github.com/heroiclabs/nakama-unreal/releases) and put it in the `Plugins` folder

**Optionally:** you can put the plugins inside your Unreal Engine plugin folder (for example, `C:\Program Files\Epic Games\UE_4.26\Engine\Plugins\Marketplace`) to use the plugin on multiple projects.

At this point, you are done. Restart Unreal. After it compiles things, open Edit->Plugins and scroll to the bottom. If all went well, you should see HeroicLabs.Nakama listed as a plugin.

 **Clients**

You have to decide where you want to create and keep record of these clients.

 **Sessions**

 Sessions are portable UObjects that contain a session pointer and a struct with the actual data in the session, like the tokens, user data, expiry information an so on. There are also some utility functions provided with the Session objects, like getting a specific variable or restoring the session.

  **Tick System**

Normally you would have to handle ticking on a C++ basis, luckily this is done automatically under the hood in this plugin after you have created the client. When you create the Client you can define a Tick Interval, by default this is set to 0, which means it will tick every frame, if you want it to tick every 50ms you have to set it as 0.05, to make it tick every second this number would be 1.

# Getting Started with NakamaUnreal (C++ with Unreal Types)

Below is a simple example of setting up a default client, authenticating, setting up a realtime client and joining a chat room. In the example we will put everything in a empty AActor class that is placed in the level.

Remember to add NakamaUnreal and NakamaCore to your Private Dependencies under your project Build.cs file. For example:

```cs

PrivateDependencyModuleNames.AddRange(new string[] { "NakamaUnreal", "NakamaCore" });

```

Starting with the headers public variables, we are using a blank actor that will be placed in the scene in this example.

```cpp
UPROPERTY()
UNakamaClient* NakamaClient;

UPROPERTY()
UNakamaRealtimeClient* NakamaRealtimeClient;

UPROPERTY()
UNakamaSession* UserSession;

UFUNCTION()
void OnAuthenticationSuccess(UNakamaSession* LoginData);

UFUNCTION()
void OnAuthenticationError(const FNakamaError& Error);

UFUNCTION()
void OnRealtimeClientConnectSuccess();

UFUNCTION()
void OnRealtimeClientConnectError();

// Initialize client and authenticate here
virtual void BeginPlay() override;
```

Then inside the Begin Play we setup default client, authenticate and bind delegates.

```cpp
// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	// Default Client Parameters
	FString ServerKey = FString(TEXT("defaultkey"));
	FString Host = FString(TEXT("localhost"));
	FString ClientName = FString(TEXT("Main"));

	// Setup Default Client
	NakamaClient = UNakamaClient::CreateDefaultClient(ServerKey, Host, 7350, false, true, ENakamaClientType::DEFAULT, 0.05f, ClientName);

	// Authentication Parameters
	FString Email = FString(TEXT("debug@mail.com"));
	FString Password = FString(TEXT("verysecretpassword"));
	FString Username = FString(TEXT("debug-user"));
	TMap<FString, FString> Variables;

	// Setup Delegates of same type and bind them to local functions
	FOnAuthUpdate AuthenticationSuccessDelegate;
	AuthenticationSuccessDelegate.AddDynamic(this, &AMyActor::OnAuthenticationSuccess);

	FOnError AuthenticationErrorDelegate;
	AuthenticationErrorDelegate.AddDynamic(this, &AMyActor::OnAuthenticationError);

	NakamaClient->AuthenticateEmail(Email, Password, Username, true, Variables, AuthenticationSuccessDelegate, AuthenticationErrorDelegate);
}
```

Then the response of the authentication callbacks

```cpp
void AMyActor::OnAuthenticationSuccess(UNakamaSession* LoginData)
{
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Authenticated As %s"), *LoginData->SessionData.Username));

	UserSession = LoginData;

	// Setup Delegates of same type and bind them to local functions
	FOnRealtimeClientConnected ConnectionSuccessDelegate;
	ConnectionSuccessDelegate.AddDynamic(this, &AMyActor::OnRealtimeClientConnectSuccess);

	FOnRealtimeClientError ConnectionErrorDelegate;
	ConnectionErrorDelegate.AddDynamic(this, &AMyActor::OnRealtimeClientConnectError);

	// This is our realtime client (socket) ready to use
	NakamaRealtimeClient = NakamaClient->SetupRealtimeClient(UserSession, true, 7350, ENakamaRealtimeClientProtocol::Protobuf, 0.05f, "");

	// Remember to Connect
	NakamaRealtimeClient->Connect(ConnectionSuccessDelegate, ConnectionErrorDelegate);

}

void AMyActor::OnAuthenticationError(const FNakamaError& Error)
{
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Failed to Authenticate: %s"), *Error.Message));
}
```

And finally the overridden realtime client setup callback, you can now use the realtime client.

```cpp
void AMyActor::OnRealtimeClientConnectSuccess()
{
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString(TEXT("Socket Setup Success!")));

	// Example of Joining Chat without callbacks
	NakamaRealtimeClient->JoinChat("Heroes", ENakamaChannelType::ROOM, true, false, {}, {});

}

void AMyActor::OnRealtimeClientConnectError()
{
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString(TEXT("Socket Setup Failed!")));
}
```

If you setup everything correctly, create a blueprint version of this actor and place it in the level you will see on-screen messages saying you authenticated, your username and then socket connected message.

# Getting Started with `NakamaBlueprints`

In this section you will learn how to manually create and manage Nakama clients that are provided by this plugin, entirely in blueprints.

It is up to the you where to create and store references to the clients, this could be done in any actor, component, character, gamemode etc. A good place to put the clients is in the Player Controller or the Game Instance.


Start by adding the **Create Default Client** node which is a part fo the Nakama Library.

![image createclient-1](./images/Client-1.png)

It is good practice to promote the clients to variables so you can access them other places in your blueprint graphs.


![image createclient-2](./images/Client-2.png)

You are now ready to authenticate, using one of the many provided Nakama authentication types, in this example we will be authenticating with email and password, normally you would setup a Widget Blueprint and pass the input from the UI into the authentication node, and authenticate by pressing a login button.

![image createclient-3](./images/Client-3.png)


As you can see, this returns a session object that will be passed into other functions, make sure to promote the session object for later use. With this plugin you may have multiple sessions per unreal instance, it is up to you to keep record and decide how you want to use the sessions. The variables pin also needs to be connected, but you can leave the string map empty if you don't want to use custom variables.

![image createclient-4](./images/Client-4.png)


After you have created a default client you'll be able to setup one or more realtime clients (sockets) that interact with the server.

Drag out from the **NakamaClient** that you created earlier, and call the **Setup Realtime Client** function.


![image createclient-4](./images/Client-5.png)

Remember to provide the user session from the successful authentication earlier, then bind custom events to the success and error callbacks. The Realtime Client will be returned from this node, and is ready to be used to communicate with the Nakama server. You can now use features such as Chat and Matchmaker.

![image createclient-5](./images/Client-6.png)


# Setting up Listeners and Binding to Events

Before you bind to event callbacks you need to setup the listener first, drag out from the realtime client and type `Listener`, you will be provided a list over different events you can listen to, there is also a `Listen to All Callbacks` which will open up all listeners.

![image binding-1](./images/Bindings-1.png)

After setting up your specific listeners you are ready to bind to the callbacks.

![image binding-2](./images/Bindings-2.png)

Create a custom event and give it a meaningful name.

![image binding-3](./images/Bindings-3.png)

 In the example below, we setup a listener for notifications, then we bind to the event, loop over notifications and print them as debug strings on the screen.

 ![image binding-4](./images/Bindings-4.png)

In the next example we listen to matchmaker matched event then bind to it and handle the response by joining a match with the returned token which then returns a Match including the match id, presences, label and so on.

![image binding-5](./images/Bindings-5.png)


# Session Management

As described earlier, when you authenticate with Nakama you'll receive a Session Object which you should store somewhere easily accessible in your Blueprints, since many of the nodes in this plugin require a session object as input to function.

The session object contains the actual session reference and also a structure with the data readable in blueprints. Drag out from the session and get the session data.

![image sessions-1](./images/Sessions-1.png)

Right click the structure to split or break the struct to see the values

![image sessions-2](./images/Sessions-2.png)

Here are all the values contained within the session

![image sessions-3](./images/Sessions-3.png)

There are also some additional session management methods like restoring the session and checking if the session has expired

![image sessions-4](./images/Sessions-4.png)

It is recommended to store the auth token from the session and check at startup if it has expired. If the token has expired you must reauthenticate. The expiry time of the token can be changed as a setting in the server.


# Requests

The clients include lots of builtin APIs for various features of the game server. These can be accessed with the async methods, which returns Success and Error callbacks. They can also call custom logic as RPC functions on the server. All requests are sent with a session object which authorizes the clients.

![image requests](./images/Requests.png)

The RPC node can be used to run specific functionality on the server, the payload should be in JSON format.

![image rpc](./images/RPC.png)

Moving forward, you should be ready to use all functionality of Nakama to power your awesome Unreal Engine built game or app, done entirely in Blueprints. Please refer to the official documentation at https://heroiclabs.com/docs even though some of the documentation is described in C++ the same core functionality applies to the Blueprint implementation.


# Cursors

Cursors are used to add paging functionality to certain nodes, like friends list and leaderboard records. When there is more data to be retrieved, a cursor string will be returned in the Success callback. You can store this cursor as a string and use it later, like when a person clicks a "more" button or use it immediately to fetch more data. Look at the example below.

![image cursors](./images/Cursors.png)

# Additional Information

Some of the features of this plugin depend on JSON, such as sending chat messages and storing data using storage objects. It is therefore recommended that if you use purely blueprints that you find a plugin that can construct and parse Json strings such as [VaRest](https://github.com/ufna/VaRest).

When you are developing within the editor, you can run multiple unreal instances using PIE (Play In Editor) and are able to authenticate using separate accounts, which is very useful when testing functionalities that require multiple players, such as chat, realtime multiplayer, matchmaking and so on.

In the installation part of this documentation we add C++ to our project, this is only to be able to compile the plugin, you can still use only Blueprints.


# Example Project

Provided with this plugin is an [example project](https://github.com/heroiclabs/nakama-unreal/tree/master/NakamaBlueprintsDemo) which is developed in pure Blueprints that showcases almost all of the Nakama core features.


![image example-1](./images/ExampleProject-1.png)

![image example-2](./images/ExampleProject-2.png)

![image example-3](./images/ExampleProject-3.png)

## Contribute

The development roadmap is managed as GitHub issues and pull requests are welcome. If you're interested to enhance the code please open an issue to discuss the changes or drop in and discuss it in the [community forum](https://forum.heroiclabs.com).

## Source Builds

The Unreal module is based on [General C++ SDK](https://github.com/heroiclabs/nakama-cpp)

We use vcpkg to install nakama-sdk for any given toolchain before placing it in the `NakamaCore/libnakama` directory:

arm64-osx:
`vcpkg install --overlay-triplets=./triplets --host-triplet=arm64-osx-release-heroic --triplet=arm64-osx-release-heroic`

x64-windows:
`vcpkg install --overlay-triplets=./triplets --host-triplet=x64-windows-release-heroic --triplet=x64-windows-release-heroic`

arm64-windows:
`vcpkg install --overlay-triplets=./triplets --host-triplet=arm64-windows-release-heroic --triplet=arm64-windows-release-heroic`

x64-linux:
`vcpkg install --overlay-triplets=./triplets --host-triplet=x64-linux-release-heroic --triplet=x64-linux-release-heroic`

Then copy the library from vcpkg_installed into the libnakama directory and the headers to `NakamaCore/Public/nakama-cpp`.

You can then compile the plugin from the command line, passing the `-Rocket` flag if you intalled the editor through
the Epic launcher. However, using an Epic launcher distribution is not recommended at least for running the command line.

Windows:

```${UNREAL_ENGINE}/Engine/Build/BatchFiles/RunUAT.sh BuildPlugin -NoHostPlatform -Plugin="${NAKAMA_UNREAL}/Nakama/Nakama.uplugin" -TargetPlatforms=Win64 -package=${NAKAMA_UNREAL}/Out/Nakama```

Mac:

```${UNREAL_ENGINE}/Engine/Build/BatchFiles/RunUAT.sh BuildPlugin -NoHostPlatform -Plugin="${NAKAMA_UNREAL}/Nakama/Nakama.uplugin" -TargetPlatforms=Mac -package=${NAKAMA_UNREAL}/Out/Nakama -Architecture_Mac=arm64```

For iOS, pass `iOS` to `TargetPlatforms`.

To view the full list of automation commands, run:

`${UNREAL_ENGINE}/Engine/Build/BatchFiles/RunUAT.sh -List`

Linux:

```${UNREAL_ENGINE}/Engine/Build/BatchFiles/RunUAT.sh BuildPlugin -NoHostPlatform -Plugin="${NAKAMA_UNREAL}/Nakama/Nakama.uplugin" -TargetPlatforms=Linux -package=${NAKAMA_UNREAL}/Out/Nakama```

### Nakama Unreal Client guide

You can find Nakama Unreal Client guide [here](https://heroiclabs.com/docs/unreal-client-guide/).

## License

This project is licensed under the [Apache-2 License](https://github.com/heroiclabs/nakama-dotnet/blob/master/LICENSE).
