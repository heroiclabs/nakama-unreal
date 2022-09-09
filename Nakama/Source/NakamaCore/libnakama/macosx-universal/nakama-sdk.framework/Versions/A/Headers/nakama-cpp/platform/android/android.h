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

#ifdef __ANDROID__

#include <nakama-cpp/NTypes.h>
#include <nakama-cpp/NExport.h>
#include <jni.h>

NAKAMA_NAMESPACE_BEGIN

    /*
     * Initialize SDK with JVM (on Android only)
     * 
     * @param vm the pointer Java Virtual Machine
     *
     * Note: If you do not do this, your application will terminate upon attempting to create a Client.
     */
    NAKAMA_API void init(JavaVM* vm);

NAKAMA_NAMESPACE_END

#endif // __ANDROID__
