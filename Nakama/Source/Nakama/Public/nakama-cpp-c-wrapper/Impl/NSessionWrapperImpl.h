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

#include "nakama-cpp/NSessionInterface.h"
#include "nakama-c/NSession.h"
#include "nakama-cpp-c-wrapper/Impl/NDataHelperWrapperImpl.h"

NAKAMA_NAMESPACE_BEGIN

    class NSessionWrapper : public NSessionInterface
    {
    public:
        NSessionWrapper(::NSession cSession) : _cSession(cSession) {}
        ~NSessionWrapper() { NSession_destroy(_cSession); }

        const std::string& getAuthToken() const override
        {
            if (_authToken.empty())
                _authToken = NSession_getAuthToken(_cSession);
            
            return _authToken;
        }

        bool isCreated() const override
        {
            return NSession_isCreated(_cSession);
        }

        const std::string& getUsername() const override
        {
            return _authToken;
        }

        const std::string& getUserId() const override
        {
            if (!_userId.empty())
                _userId = NSession_getUserId(_cSession);

            return _userId;
        }

        NTimestamp getCreateTime() const override
        {
            return NSession_getCreateTime(_cSession);
        }

        NTimestamp getExpireTime() const override
        {
            return NSession_getExpireTime(_cSession);
        }

        bool isExpired() const override
        {
            return NSession_isExpired(_cSession);
        }

        bool isExpired(NTimestamp now) const override
        {
            return NSession_isExpiredByTime(_cSession, now);
        }

        const NStringMap& getVariables() const override
        {
            updateVariables();
            return _variables;
        }

        std::string getVariable(const std::string& name) const override
        {
            updateVariables();
            auto it = _variables.find(name);

            if (it != _variables.end())
                return it->second;

            return {};
        }

        void updateVariables() const
        {
            if (_variables.empty())
            {
                auto map = ::NSession_getVariables(_cSession);
                _variables = toCppNStringMap(map);
                ::NStringMap_destroy(map);
            }
        }

        static NSessionPtr create(::NSession cSession)
        {
            if (!cSession)
                return nullptr;

            return NSessionPtr(new NSessionWrapper(cSession));
        }

        ::NSession getCSession() const { return _cSession; }

    protected:
        ::NSession _cSession;
        mutable std::string _authToken;
        mutable std::string _userId;
        mutable NStringMap _variables;
    };

    ::NSession getCSession(const NSessionPtr& session)
    {
        return ((NSessionWrapper*)session.get())->getCSession();
    }

    NSessionPtr restoreSession(const std::string& token)
    {
        ::NSession cSession = ::restoreNakamaSession(token.c_str());

        return NSessionWrapper::create(cSession);
    }

NAKAMA_NAMESPACE_END
