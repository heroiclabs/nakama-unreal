# Nakama Blueprints Tests

**Nakama Blueprints Tests** is a dedicated project aimed at validating the blueprint logic using Unreal's Automated Testing systems.

- 🎮 **Version Compatibility:** Primarily tested on Unreal Engine 5.2.
- 📁 **Dependencies:** The Nakama plugin is bundled within the `Plugins` directory.

## 🚀 Getting Started

Follow these steps to get the project up and running:

1. **Nakama Server Setup:** 
   - Install and boot up the Nakama server. 
   - Detailed [instructions available here](https://heroiclabs.com/docs/install-docker-quickstart).

2. **Unreal Engine Installation:** 
   - Make sure to have [Unreal Engine](https://www.unrealengine.com) version 5.0 or later.

3. **Project Initialization:** 
   - Right-click the `.uproject` file and select `Generate Visual Studio Project Files`.

4. **IDE Configuration:** 
   - Open the generated solution in your preferred Unreal-compatible IDE (e.g., Visual Studio, Xcode, Rider).
   - Launch the project.

5. **Server Credential Configuration:** 
   - If using non-default server credentials or a remote server, navigate to `Content/Tests/Base` and open `Nakama_Test_Base`.
   - Adjust the server parameters in the `CreateClient` function.

**Note: You might also be able to open the project directly after adding the Nakama Plugin into the project**

## 🧪 Running the Tests

To execute the Nakama tests:

1. In the Unreal Editor, head to `Tools` -> `Test Automation`.
2. Select your testing device (e.g., YOURNAME_123).
3. Under `Project` -> `FunctionalTests`, you'll find all the `Nakama Tests`.
4. Select the desired tests (or select all) and press `Start Tests`.
