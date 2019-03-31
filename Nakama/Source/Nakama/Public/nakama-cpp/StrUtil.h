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

#include <string>

namespace Nakama {

    typedef std::string Base64Buffer;

    /**
     * Encode bytes buffer using `base64` algorithm
     * 
     * @param buffer byte buffer to encode
     * @return std::string encoded `base64` string
     */
    std::string base64Encode(const Base64Buffer& buffer);

    /**
     * Decode `base64` string
     * 
     * @param base64str `base64` string
     * @return Base64Buffer byte buffer
     */
    Base64Buffer base64Decode(const std::string& base64str);

    /**
     * Get the field value from json string
     * 
     * Supports only simple field types: number, string, boolean and null
     * 
     * @param json the json string
     * @param field_name name of field
     * @return std::string value of specified field
     */
    std::string getJsonFieldValue(const std::string& json, const std::string& field_name);

    /**
     * Encode string to allow use it in an URL
     * 
     * @param str string to encode
     * @return std::string encoded string
     */
    std::string urlEncode(const std::string& str);

} // namespace Nakama
