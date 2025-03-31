/*
* Copyright 2025 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ENakamaStoragePermissionRead : uint8
{
	// The object is only readable by server runtime
	NO_READ = 0 UMETA(DisplayName = "No Read"),
	// Only the user who owns it may access
	OWNER_READ = 1 UMETA(DisplayName = "Owner Read"),
	// Any user can read the object
	PUBLIC_READ = 2 UMETA(DisplayName = "Public Read"),

};

UENUM(BlueprintType)
enum class ENakamaStoragePermissionWrite : uint8
{
	// The object is only writable by server runtime
	NO_WRITE = 0 UMETA(DisplayName = "No Write"),
	// Only the user who owns it may write
	OWNER_WRITE = 1 UMETA(DisplayName = "Owner Write"),

};