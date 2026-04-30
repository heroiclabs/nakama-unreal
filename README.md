Nakama Unreal
=============

## Overview

[Nakama](https://github.com/heroiclabs/nakama) is an open-source server designed to power modern games and apps. Features include user accounts, chat, social, matchmaker, realtime multiplayer, and much [more](https://heroiclabs.com).

This client implements the full Nakama API and socket options with the server, as well as the [Satori](https://heroiclabs.com/docs/satori/concepts/introduction/index.html) API.  
It's written in C++ with minimal dependencies to support Unreal 4 and 5.

If you experience any issues with the client, it can be useful to enable debug logs and [open an issue](https://github.com/heroiclabs/nakama-cpp/issues).

Plugin documentation including Getting Started and Code Examples is online at [https://heroiclabs.com/docs/unreal-client-guide/](https://heroiclabs.com/docs/unreal-client-guide/).

Other Docs like Nakama Documentation can be found at [https://heroiclabs.com/docs](https://heroiclabs.com/docs).

## Development

### Task Automation

This project uses [Taskfile](https://taskfile.dev/) to automate common development tasks. Taskfile provides a consistent interface for building, testing, and deploying the project across different platforms and environments.

#### Why Taskfile?

- **Consistency**: GitHub Actions and local development use the same tasks, ensuring what works locally will work in CI/CD
- **Easy Verification**: You can run the exact same commands locally that run in CI/CD pipelines
- **Cross-Platform**: Works consistently on macOS, Linux, and Windows
- **Simple Syntax**: YAML-based configuration that's easy to read and maintain
- **Heroic Standard**: Consistent across Heroic products

#### Installation

##### macOS
```shell
brew install go-task
```

Or using the install script:
```shell
sh -c "$(curl --location https://taskfile.dev/install.sh)" -- -d -b /usr/local/bin
```

##### Windows
```powershell
# Using Chocolatey
choco install go-task

# Using Scoop
scoop install task

# Using Winget
winget install Task.Task
```

##### Linux
```shell
# Using Snap
snap install task --classic

# Using install script
sh -c "$(curl --location https://taskfile.dev/install.sh)" -- -d -b ~/.local/bin
```

#### Available Tasks

Run `task --list` to see all available tasks. 

### Testing

The client comes with a test suite that comes as an Unreal Project that can be found under `IntegrationTests/`. 
To build and run the test project in headless mode, you can issue this command:

```powershell
task test
```

## Contribute

The development roadmap is managed as GitHub issues and pull requests are welcome. If you're interested in enhancing the code please open an issue to discuss the changes or drop in and discuss it in the [community forum](https://forum.heroiclabs.com).

## License

This project is licensed under the [Apache-2 License](https://github.com/heroiclabs/nakama-dotnet/blob/master/LICENSE).
