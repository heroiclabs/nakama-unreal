/*
* Copyright 2024 The Nakama Authors
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
#include <vector>
#include <unordered_map>
#include <ctime>
#include "nakama-cpp/NTypes.h"

namespace Satori {

    // Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
    struct SAuthenticateLogoutRequest {
        // Session token to log out.
        std::string token;
        // Refresh token to invalidate.
        std::string refresh_token;
    };

    // Authenticate against the server with a refresh token.
    struct SAuthenticateRefreshRequest {
        // Refresh token.
        std::string refresh_token;
    };

    // Authentication request
    struct SAuthenticateRequest {
        // Identity ID. Must be between eight and 128 characters (inclusive).
        // Must be an alphanumeric string with only underscores and hyphens allowed.
        std::string id;
        // Optional default properties to update with this call.
        // If not set, properties are left as they are on the server.
        std::unordered_map<std::string,std::string> default_properties;
        // Optional custom properties to update with this call.
        // If not set, properties are left as they are on the server.
        std::unordered_map<std::string,std::string> custom_properties;
    };

    // A single event. Usually, but not necessarily, part of a batch.
    struct SEvent {
        // Event name.
        std::string name;
        // Optional event ID assigned by the client, used to de-duplicate in retransmission scenarios.
        // If not supplied the server will assign a randomly generated unique event identifier.
        std::string id;
        // Event metadata, if any.
        std::unordered_map<std::string,std::string> metadata;
        // Optional value.
        std::string value;
        // The time when the event was triggered on the producer side. Unit is unix time milliseconds
        Nakama::NTimestamp timestamp;
    };

    // Publish an event to the server
    struct SEventRequest {
        // Some number of events produced by a client.
        std::vector<SEvent> events;
    };

    // An experiment that this user is partaking.
    struct SExperiment {
        // Experiment name
        std::string name;
        // Value associated with this Experiment.
        std::string value;
    };

    // All experiments that this identity is involved with.
    struct SExperimentList {
        // All experiments for this identity.
        std::vector<SExperiment> experiments;
    };

    // Feature flag available to the identity.
    struct SFlag {
        // Flag name
        std::string name;
        // Value associated with this flag.
        std::string value;
        // Whether the value for this flag has conditionally changed from the default state.
        bool condition_changed;
    };

    // All flags available to the identity
    struct SFlagList {
        // All flags
        std::vector<SFlag> flags;
    };

    // Request to get all experiments data.
    struct SGetExperimentsRequest {
        // Experiment names; if empty string all experiments are returned.
        std::vector<std::string> names;
    };

    // Request to get all flags data.
    struct SGetFlagsRequest {
        // Flag names; if empty string all flags are returned.
        std::vector<std::string> names;
    };

    // Request to get all live events.
    struct SGetLiveEventsRequest {
        // Live event names; if empty string all live events are returned.
        std::vector<std::string> names;
    };

    // Enrich/replace the current session with a new ID.
    struct SIdentifyRequest {
        // Identity ID to enrich the current session and return a new session. Old session will no longer be usable.
        std::string id;
        // Optional default properties to update with this call.
        // If not set, properties are left as they are on the server.
        std::unordered_map<std::string,std::string> default_properties;
        // Optional custom properties to update with this call.
        // If not set, properties are left as they are on the server.
        std::unordered_map<std::string,std::string> custom_properties;
    };

    // A single live event.
    struct SLiveEvent {
        // Name.
        std::string name;
        // Description.
        std::string description;
        // Event value.
        std::string value;
        // Start time of current event run.
        int64_t active_start_time_sec;
        // End time of current event run.
        int64_t active_end_time_sec;
        // The live event identifier.
        std::string id;
        // Start time.
        int64_t start_time_sec;
        // End time, 0 if it repeats forever.
        int64_t end_time_sec;
        // Duration in seconds.
        int64_t duration_sec;
        // Reset CRON schedule, if configured.
        std::string reset_cron;
    };

    // List of Live events.
    struct SLiveEventList {
        // Live events.
        std::vector<SLiveEvent> live_events;
    };

    // Properties associated with an identity.
    struct SProperties {
        // Event default properties.
        std::unordered_map<std::string,std::string> default_properties;
        // Event computed properties.
        std::unordered_map<std::string,std::string> computed_properties;
        // Event custom properties.
        std::unordered_map<std::string,std::string> custom_properties;
    };

    // A session.
    struct SSession {
        // Token credential.
        std::string token;
        // Refresh token.
        std::string refresh_token;
        // Properties associated with this identity.
        SProperties properties;
    };

    // Update Properties associated with this identity.
    struct SUpdatePropertiesRequest {
        // Event default properties.
        std::unordered_map<std::string,std::string> default_properties;
        // Event custom properties.
        std::unordered_map<std::string,std::string> custom_properties;
        // Informs the server to recompute the audience membership of the identity.
        bool recompute;
    };


    struct SGetMessageListRequest {
        // Max number of messages to return. Between 1 and 100.
        int32_t limit;
        // True if listing should be older messages to newer, false if reverse.
        bool forward;
        // A pagination cursor, if any.
        std::string cursor;
    };

    // A scheduled message.
    struct SMessage {
        // The identifier of the schedule.
        std::string schedule_id;
        // The send time for the message.
        Nakama::NTimestamp send_time;
        // A key-value pairs of metadata.
        std::unordered_map<std::string, std::string> metadata;
        // The time the message was created.
        Nakama::NTimestamp create_time;
        // The time the message was updated.
        Nakama::NTimestamp update_time;
        // The time the message was read by the client.
        Nakama::NTimestamp read_time;
        // The time the message was consumed by the identity.
        Nakama::NTimestamp consume_time;
        // The message's text.
        std::string text;
        // The message's unique identifier.
        std::string id;
        // The message's title.
        std::string title;
        // The message's image url.
        std::string image_url;
    };

    // A response containing all the messages for an identity.
    struct SGetMessageListResponse {
        // The list of messages.
        std::vector<SMessage> messages;
        // The cursor to send when retrieving the next page, if any.
        std::string next_cursor;
        // The cursor to send when retrieving the previous page, if any.
        std::string prev_cursor;
        // Cacheable cursor to list newer messages. Durable and designed to be stored, unlike next/prev cursors.
        std::string cacheable_cursor;
    };

    // The request to update the status of a message.
    struct SUpdateMessageRequest {
        // The identifier of the messages.
        std::string id;
        // The time the message was read at the client.
        Nakama::NTimestamp read_time;
        // The time the message was consumed by the identity.
        Nakama::NTimestamp consume_time;
    };

    // The request to delete a scheduled message.
    struct SDeleteMessageRequest {
        // The identifier of the message.
        std::string id;
    };
}
