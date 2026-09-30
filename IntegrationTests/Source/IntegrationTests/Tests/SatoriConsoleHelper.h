#pragma once

#include "CoreMinimal.h"
#include "Async/Future.h"

/**
 * Fetches the Satori API key from the Console REST API.
 *
 * On first call: authenticates as admin, lists existing keys (creating one if none exist),
 * and caches the result. Subsequent calls return the cached value immediately.
 */
TFuture<FString> GetSatoriApiKey();
