#include <NakamaUnreal.h>

#include "CoreMinimal.h"

// Proper way to process events is FPlatformApplicationMisc,
// but because we run app without ui/window we can get away
// with just one Apple specific call. Proper way requires
// ApplicationCore module which is "heavyweight".
//#include "HAL/PlatformApplicationMisc.h"
#if PLATFORM_APPLE
#include "Mac/CocoaThread.h"
#endif

#include "RequiredProgramMainCPPInclude.h"

IMPLEMENT_APPLICATION(NakamaTest, "NakamaTest");

int test_main(int argc, const char *argv[]);

namespace Nakama { namespace Test {
	extern void(*g_on_tick)(int ms);
}}

INT32_MAIN_INT32_ARGC_TCHAR_ARGV()
{
	Nakama::Unreal::initLogging(Nakama::NLogLevel::Debug);


	std::vector<decltype(StringCast<ANSICHAR>(ArgV[0]))> argvs;
	std::vector<const char *> argv;
	for (int i = 0; i < ArgC; i++)
	{
		argvs.push_back(StringCast<ANSICHAR>(ArgV[i]));
		argv.push_back(argvs[i].Get());
	}

	// ProjectDir is a bedrock of the whole initialization process. Unreal has like 10 screens
	// of code dedicated just to chosing project dir. I read all of it just to write one line below
	// Here is my understanding of ProjectDir:
	// - ProjectDir is where your .uproject is
	// - .uproject is to be given as a first argument, that's how it knows where .uproject is
	// - Unless your are Type=Program, then don't pass .uproject (although you can and it even will be read),
	//   and your ProjectDir will be $ENGINE_SOURCE/Engine/Source/Programs/$APPNAME
	// - You can set your own ProjectDir with command below
	// - ProjectDir value MUST end with '/', even though this path is always used as a directory it is not sanitized properly
	// - Value is resolved relative to basedir. Which is unless overrideden with '-basedir` commandline switch is directory where binary is
	// - ProjectDir is used for gazilion of things, we use it to store Config/DefaultEngine.ini with our logging config
    FGenericPlatformMisc::SetOverrideProjectDir("../../");
	GEngineLoop.PreInit(ArgC, ArgV);

	FModuleManager::Get().LoadModuleChecked(TEXT("HTTP"));
	FModuleManager::Get().LoadModuleChecked(TEXT("WebSockets"));

    // Pretend to be a main game loop
	Nakama::Test::g_on_tick = [](int ms)
	{
		FTSTicker::GetCoreTicker().Tick( float(ms) / 1000 );
		FThreadManager::Get().Tick();
		// Proper way
		//FPlatformApplicationMisc::PumpMessages(true);
		// Our faster to compile way
#if PLATFORM_APPLE
		ProcessGameThreadEvents();
#endif
	};
	
	test_main(ArgC, argv.data());
	FEngineLoop::AppExit();
	return 0;
}