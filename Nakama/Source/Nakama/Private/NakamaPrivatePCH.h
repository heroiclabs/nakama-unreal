#pragma once

#include "Runtime/Launch/Resources/Version.h"
#include <functional>
#include <string>

#if ENGINE_MINOR_VERSION >= 15
#include "CoreMinimal.h"
#include "EngineDefines.h"
#include "Engine/Engine.h"
#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#else
#include "CoreUObject.h"
#include "Engine.h"
#endif

#include "Http.h"
#include "ModuleManager.h"

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#endif

#define UI UI_ST
#ifndef LWS_INCLUDED
#include "libwebsockets.h"
#define LWS_INCLUDED
#endif
#undef UI

#if PLATFORM_WINDOWS
#include "HideWindowsPlatformTypes.h"
#endif

typedef struct lws_context				WebSocketInternalContext;
typedef struct lws						WebSocketInternal;
typedef struct lws_protocols			WebSocketInternalProtocol;
typedef enum lws_callback_reasons		WebSocketInternalCallback;

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.

DECLARE_LOG_CATEGORY_EXTERN(LogNakama, Log, All);
