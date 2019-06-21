/*
 * Copyright 2019 The Nakama Authors
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

#include "CoreOnline.h"

namespace Nakama {

    /**
     * Abstraction of a profile service online Id
     * The class is meant to be opaque
     */
    class NUniqueNetId : public FUniqueNetId
    {
    public:
        /**
         * Get the raw byte representation of this opaque data
         * This data is platform dependent and shouldn't be manipulated directly
         *
         * @return byte array of size GetSize()
         */
        const uint8 * GetBytes() const override;

        /**
         * Get the size of the opaque data
         *
         * @return size in bytes of the data representation
         */
        int32 GetSize() const override;

        /**
         * Check the validity of the opaque data
         *
         * @return true if this is well formed data, false otherwise
         */
        bool IsValid() const override;

        /**
         * Platform specific conversion to string representation of data
         *
         * @return data in string form
         */
        FString ToString() const override;

        /**
         * Get a human readable representation of the opaque data
         * Shouldn't be used for anything other than logging/debugging
         *
         * @return data in string form
         */
        FString ToDebugString() const override;
    };

}
