/**
* Copyright 2017 The Nakama Authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

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
