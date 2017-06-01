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

#include "Defines.h"

using namespace server;

namespace Nakama {
	
	enum NAKAMA_API ErrorCode {
		Unknown = 0,
		RuntimeException,
		UnrecognizedPayload,
		MissingPayload,
		BadInput,
		AuthError,
		UserLinkInuse,
		UserLinkProviderUnavailable,
		UserLinkDisallowed,
		UserHandleInuse,
		GroupNameInuse,
		StorageFetchDisallowed,
		MatchNotFound
	};

	class NAKAMA_API NError {

	public:
		NError(std::string message = std::string()) : 
			message(message), code(ErrorCode::Unknown) {}
		NError(const AuthenticateResponse_Error error) : 
			message(error.message()) {
			auto c = error.code();
			if (c >= Unknown && c <= MatchNotFound) code = (ErrorCode)c;
			else code = ErrorCode::Unknown;
		}
		NError(server::Error error) :
			message(error.message()) {
			auto c = error.code();
			if (c >= Unknown && c <= MatchNotFound) code = (ErrorCode)c;
			else code = ErrorCode::Unknown;
		}

		~NError() {}

		std::string GetErrorMessage() { return message; }
		ErrorCode GetErrorCode() { return code; }

	private:
		std::string message;
		ErrorCode code;
	};

}
