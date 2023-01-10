# Change Log
All notable changes to this project are documented below.

The format is based on [keep a changelog](http://keepachangelog.com/) and this project uses [semantic versioning](http://semver.org/).

### [2.7.0] - [2023-01-10]
### Added
- Added Android support.
- Added Authentication Refresh node for Blueprints.
- Added Update Chat Message node for Blueprints.
- Added `IsConnected` function to Realtime Client.
- Added `GetHeartbeatIntervalMs` function to Realtime Client.
- Added `SetHeartbeatIntervalMs` function to Realtime Client.
- Added `ALL` to `ENakamaGroupState` enum.
- Added `RPCHttpKey` function to Client for calling an RPC via HTTP key.

### Changed
- Updated transport logic for UE4 support.
- Various improvements to client logic.

### Fixed
- Fixed issue with create client node in demo project.
- Version property now copied correctly in `FNakamaStoreObjectAck` constructor.
- Fixed compilation issue on Linux.

### [2.6.0] - [2022-09-09]
### Added
- Added support for Unreal native types. Use the `NakamaUnreal` module and see the README for details on how to use it.
- Added support for Blueprints. Use the `NakamaBlueprints` module if you are interested and see the README for details on how to use it.
- Old functionality exposed in previous releases has been moved to `NakamaCore`. The other modules depend on `NakamaCore`.

### [2.5.0] - [2021-09-13]
### Added
- Added realtime parties support.

### Fixed
- Fixed assignment of cursor in listing of storage objects.

## [2.4.0] - [2020-11-01]
### Added
- Support server 2.13.0
- Added authentication with Apple ID: `authenticateApple`, `linkApple` and `unlinkApple`
- Added `demoteGroupUsers`
- Added `NClientInterface::rpc` with `http key`
- Added `disableTime` to `NAccount`
- Added `updateTime` to `NFriend`
- Improve future-compatibility with server changes

### Fixed
- Fix listFriends failing on 2.3.0 against 2.13.0 server

## [2.3.0] - [2020-02-29]
### Fixed
- fix crash when response is received after NClient was deleted

## [2.2.4] - 2019-12-08
### Fixed
- fix uint16_t is too small for our match data (#25)
- fix getUsername and getUserId in session wrapper
- RPC call fails when body is empty
- RPC payload differences between Rest and RT clients

## [2.2.2] - 2019-10-03
### Added
- Support Linux

## [2.2.0] - 2019-09-16
### Added
- Support server 2.7
- Support UE 4.23

### Changed
- Following client API has been added/changed to support server 2.7:
  - NSessionInterface
    - getVariables
    - getVariable
  - NClientInterface
    - authenticateDevice
    - authenticateEmail
    - authenticateFacebook
    - authenticateGoogle
    - authenticateGameCenter
    - authenticateCustom
    - authenticateSteam
    - listFriends
    - createGroup
    - listGroupUsers
    - listUserGroups
  - NRtClientInterface
    - joinMatch
- Updated optional lib to v.3.2.0

## [2.1.0] - 2019-06-19
### Added
- REST client (HTTP/1.1).
- Add tournament start active time to the API response.
- Add "Activity timeout" to Websocket.

### Changed
- Now we use one C++ REST library for all platforms instead of Websocketpp and IXWebsocket.
- gRPC client is off.

### Fixed
- Fixed loading dynamic library on Mac.

## [2.0.3] - 2019-05-01
### Added
- support Windows (VS 2015, 2017, 2019).

### Fixed
- enable SSL for IXWebsocket.

## [2.0.2] - 2019-04-16
### Changed
- Now targeting nakama 2.x on Mac and iOS

## [0.10.1] - 2018-02-16
### Changed
- Now targeting nakama 1.4.0

### Fixed
- Updated session parsing to look for "han" for handle keyword.
- Added correct purchase records processing.

## [0.10.0] - 2017-12-05
### Changed
- Now targeting nakama 1.3.0

## [0.9.0] - 2017-12-03
### Added
- Advanced Matchmaking with custom filters and user properties.
- Expose Collation ID when client operations result in an error.

### Changed
- Now targeting nakama 1.1.0

## [0.8.1] - 2017-09-28
### Changed
- Now targeting nakama 1.0.1

## [0.8.0] - 2017-09-28
### Added
- A paging cursor can now be serialized and restored.
- New storage partial update feature.
- New storage list feature.
- A session now exposes `.ExpiresAt` and `.Handle` from the token.

### Changed
- Added default builder for notification list and remove messages.
- A group self list operation now return the user's membership state with each group.
- A group leave operation now return a specific error code when the last admin attempts to leave.

## [0.7.0] - 2017-09-26
### Added
- Add new In-App Notification feature.
- Add new In-App Purchase Validation feature.

### Changed
- Update Client to support the new batching API.

## [0.6.1] - 2017-06-03
### Changed
- Support for Nakama API 0.13.0
- New matchmaking feature.
- Optionally send match data to a subset of match participants.
- Expose a way to toggle `TCP_NODELAY` socket option.
- Send RPC messages to run custom code.
- Fetch users by handle.
- Add friend by handle.
- Filter by IDs in leaderboard list message.
- Storage messages can now set records with public read permission.
- Update user fetch add handle method name to match changes in nakama-unity 0.6.1.

### Fixed
- Dispatch callbacks when sending match data.
- Improve leaderboard list message to handle multiple filters.

## [0.5.1] - 2017-06-01
### Added
- Support for Nakama API 0.12.1
- Support for fetching groups by name.

## [0.5.0] - 2017-06-01
### Added
- Support for Nakama API 0.12.0
- Blueprint support
- Add support for dynamic leaderboards.
- Add error codes for error messages in server protocol.

### Changed
- Update session token parse code for user's handle.
- Update user presence protocol message to contain user handles.

## [0.4.2] - 2017-03-21
### Added
- Initial public release - modeled after nakama-unity 0.4.2
