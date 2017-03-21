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

#ifdef __UNREAL__
#include "Nakama/Private/NakamaPrivatePCH.h"
#endif

#include "NSession.h"
#include "NibbleAndAHalf/base64.h"

namespace Nakama {

	std::string ConvertGuidStringToBytes(std::string guid) {
		std::string rVal = "";

		char count = 0, byteValue = 0, charValue = 0;
		for (size_t i = 0, maxI = guid.length(); i < maxI; i++)
		{
			char curr = guid[i];

			// parse of the value of the current char.  Must be [0-9][A-F][a-f]
			if (curr >= '0' && curr <= '9') {
				charValue = curr - '0';
			}
			else if (curr >= 'A' && curr <= 'F') {
				charValue = curr - 'A' + 10;
			}
			else if (curr >= 'a' && curr <= 'f') {
				charValue = curr - 'a' + 10;
			}
			else continue;

			// high value
			if (count == 0) {
				byteValue = 16 * charValue;
				count++;
				continue;
			}

			// low value
			byteValue += charValue;
			rVal.append(&byteValue, 1);
			count = 0;
		}

		return rVal;
	}

	std::string NSession::GetId() {
		if (cachedId != "") return cachedId;

		// Hack decode JSON payload from JWT
		// first we narrow down to the segment between the first two '.'
		int dotIndex1 = token.find('.');
		int dotIndex2 = token.find('.', dotIndex1 + 1);
		std::string payload = token.substr(dotIndex1 + 1, dotIndex2 - dotIndex1 - 1);

		// the segment is base64 encoded, so decode it...
		int decodedLen = 0;
		unsigned char* decoded = unbase64(payload.c_str(), payload.length(), &decodedLen);

		// now we have some json to parse.
		// e.g.: {"exp":1489862293,"uid":"3c01e3ee-878a-4ec4-8923-40d51a86f91f"}
		std::string json = std::string((const char*)decoded, decodedLen);

		// find our uid key...
		size_t index = json.find("\"uid\"");

		// find the boundaries of the uid value
		size_t guidIndex1 = json.find("\"", index + 5);
		size_t guidIndex2 = json.find("\"", guidIndex1 + 1);

		// now pull out the uid
		std::string guid = json.substr(guidIndex1 + 1, guidIndex2 - guidIndex1 - 1);

		// we now need to turn this into a byte sequence.  We still store in a string for convenience.
		cachedId = ConvertGuidStringToBytes(guid);
		return cachedId;
	}

	NSession NSession::Restore(std::string token)
	{
		auto span = FDateTime::UtcNow().ToUnixTimestamp();
		return NSession(token, span);
	}

}
