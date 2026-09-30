/*
 * Copyright 2026 The Nakama Authors
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

/* This code is auto-generated. DO NOT EDIT. */











#include "Nakama.gen.h"
#include "NakamaHttpHelper.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Misc/Base64.h"





namespace NakamaInternal
{
FNakamaApiRequestModel NAKAMA_API BuildSessionRefreshRequest (
  const FNakamaSessionRefreshRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/session/refresh");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildAuthenticateAppleRequest (
  const FNakamaAuthenticateAppleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/apple");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Create.IsEmpty() == false) { QueryArgs.Add({TEXT("create"), LexToString(Params.Create.GetValue())}); }
  if (Params.Username.IsEmpty() == false) { QueryArgs.Add({TEXT("username"), Params.Username}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildAuthenticateCustomRequest (
  const FNakamaAuthenticateCustomRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/custom");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Create.IsEmpty() == false) { QueryArgs.Add({TEXT("create"), LexToString(Params.Create.GetValue())}); }
  if (Params.Username.IsEmpty() == false) { QueryArgs.Add({TEXT("username"), Params.Username}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildAuthenticateDeviceRequest (
  const FNakamaAuthenticateDeviceRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/device");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Create.IsEmpty() == false) { QueryArgs.Add({TEXT("create"), LexToString(Params.Create.GetValue())}); }
  if (Params.Username.IsEmpty() == false) { QueryArgs.Add({TEXT("username"), Params.Username}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildAuthenticateEmailRequest (
  const FNakamaAuthenticateEmailRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/email");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Create.IsEmpty() == false) { QueryArgs.Add({TEXT("create"), LexToString(Params.Create.GetValue())}); }
  if (Params.Username.IsEmpty() == false) { QueryArgs.Add({TEXT("username"), Params.Username}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildAuthenticateFacebookRequest (
  const FNakamaAuthenticateFacebookRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/facebook");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Create.IsEmpty() == false) { QueryArgs.Add({TEXT("create"), LexToString(Params.Create.GetValue())}); }
  if (Params.Username.IsEmpty() == false) { QueryArgs.Add({TEXT("username"), Params.Username}); }
  if (Params.Sync.IsEmpty() == false) { QueryArgs.Add({TEXT("sync"), LexToString(Params.Sync.GetValue())}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildAuthenticateFacebookInstantGameRequest (
  const FNakamaAuthenticateFacebookInstantGameRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/facebookinstantgame");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Create.IsEmpty() == false) { QueryArgs.Add({TEXT("create"), LexToString(Params.Create.GetValue())}); }
  if (Params.Username.IsEmpty() == false) { QueryArgs.Add({TEXT("username"), Params.Username}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildAuthenticateGameCenterRequest (
  const FNakamaAuthenticateGameCenterRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/gamecenter");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Create.IsEmpty() == false) { QueryArgs.Add({TEXT("create"), LexToString(Params.Create.GetValue())}); }
  if (Params.Username.IsEmpty() == false) { QueryArgs.Add({TEXT("username"), Params.Username}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildAuthenticateGoogleRequest (
  const FNakamaAuthenticateGoogleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/google");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Create.IsEmpty() == false) { QueryArgs.Add({TEXT("create"), LexToString(Params.Create.GetValue())}); }
  if (Params.Username.IsEmpty() == false) { QueryArgs.Add({TEXT("username"), Params.Username}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildAuthenticateSteamRequest (
  const FNakamaAuthenticateSteamRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/steam");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Create.IsEmpty() == false) { QueryArgs.Add({TEXT("create"), LexToString(Params.Create.GetValue())}); }
  if (Params.Username.IsEmpty() == false) { QueryArgs.Add({TEXT("username"), Params.Username}); }
  if (Params.Sync.IsEmpty() == false) { QueryArgs.Add({TEXT("sync"), LexToString(Params.Sync.GetValue())}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildCreateGroupRequest (
  const FNakamaCreateGroupRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildGetUsersRequest (
  const FNakamaGetUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/user");

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  for (const auto& Item : Params.Ids)
  {
    QueryArgs.Add({TEXT("ids"), Item});
  }
  for (const auto& Item : Params.Usernames)
  {
    QueryArgs.Add({TEXT("usernames"), Item});
  }
  for (const auto& Item : Params.FacebookIds)
  {
    QueryArgs.Add({TEXT("facebook_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildGetSubscriptionRequest (
  const FNakamaGetSubscriptionRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/subscription/{product_id}");
  Url = Url.Replace(TEXT("{product_id}"), *FGenericPlatformHttp::UrlEncode(Params.ProductId));

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListChannelMessagesRequest (
  const FNakamaListChannelMessagesRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/channel/{channel_id}");
  Url = Url.Replace(TEXT("{channel_id}"), *FGenericPlatformHttp::UrlEncode(Params.ChannelId));

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.Forward.IsEmpty() == false) { QueryArgs.Add({TEXT("forward"), LexToString(Params.Forward.GetValue())}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListFriendsRequest (
  const FNakamaListFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/friend");

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.State.IsEmpty() == false) { QueryArgs.Add({TEXT("state"), FString::Printf(TEXT("%d"), Params.State.GetValue())}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListFriendsOfFriendsRequest (
  const FNakamaListFriendsOfFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/friend/friends");

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListGroupsRequest (
  const FNakamaListGroupsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group");

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Name.IsEmpty() == false) { QueryArgs.Add({TEXT("name"), Params.Name}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.LangTag.IsEmpty() == false) { QueryArgs.Add({TEXT("lang_tag"), Params.LangTag}); }
  if (Params.Members.IsEmpty() == false) { QueryArgs.Add({TEXT("members"), FString::Printf(TEXT("%d"), Params.Members.GetValue())}); }
  if (Params.Open.IsEmpty() == false) { QueryArgs.Add({TEXT("open"), LexToString(Params.Open.GetValue())}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListGroupUsersRequest (
  const FNakamaListGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group/{group_id}/user");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.State.IsEmpty() == false) { QueryArgs.Add({TEXT("state"), FString::Printf(TEXT("%d"), Params.State.GetValue())}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListLeaderboardRecordsRequest (
  const FNakamaListLeaderboardRecordsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/leaderboard/{leaderboard_id}");
  Url = Url.Replace(TEXT("{leaderboard_id}"), *FGenericPlatformHttp::UrlEncode(Params.LeaderboardId));

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  if (Params.Expiry.IsEmpty() == false) { QueryArgs.Add({TEXT("expiry"), FString::Printf(TEXT("%lld"), Params.Expiry.GetValue())}); }
  for (const auto& Item : Params.OwnerIds)
  {
    QueryArgs.Add({TEXT("owner_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListLeaderboardRecordsAroundOwnerRequest (
  const FNakamaListLeaderboardRecordsAroundOwnerRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/leaderboard/{leaderboard_id}/owner/{owner_id}");
  Url = Url.Replace(TEXT("{leaderboard_id}"), *FGenericPlatformHttp::UrlEncode(Params.LeaderboardId));
  Url = Url.Replace(TEXT("{owner_id}"), *FGenericPlatformHttp::UrlEncode(Params.OwnerId));

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.Expiry.IsEmpty() == false) { QueryArgs.Add({TEXT("expiry"), FString::Printf(TEXT("%lld"), Params.Expiry.GetValue())}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListMatchesRequest (
  const FNakamaListMatchesRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/match");

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.Authoritative.IsEmpty() == false) { QueryArgs.Add({TEXT("authoritative"), LexToString(Params.Authoritative.GetValue())}); }
  if (Params.Label.IsEmpty() == false) { QueryArgs.Add({TEXT("label"), Params.Label}); }
  if (Params.MinSize.IsEmpty() == false) { QueryArgs.Add({TEXT("min_size"), FString::Printf(TEXT("%d"), Params.MinSize.GetValue())}); }
  if (Params.MaxSize.IsEmpty() == false) { QueryArgs.Add({TEXT("max_size"), FString::Printf(TEXT("%d"), Params.MaxSize.GetValue())}); }
  if (Params.Query.IsEmpty() == false) { QueryArgs.Add({TEXT("query"), Params.Query}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListPartiesRequest (
  const FNakamaListPartiesRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/party");

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.Open.IsEmpty() == false) { QueryArgs.Add({TEXT("open"), LexToString(Params.Open.GetValue())}); }
  if (Params.Query.IsEmpty() == false) { QueryArgs.Add({TEXT("query"), Params.Query}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListNotificationsRequest (
  const FNakamaListNotificationsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/notification");

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.CacheableCursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cacheable_cursor"), Params.CacheableCursor}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListStorageObjectsRequest (
  const FNakamaListStorageObjectsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/storage/{collection}");
  Url = Url.Replace(TEXT("{collection}"), *FGenericPlatformHttp::UrlEncode(Params.Collection));

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.UserId.IsEmpty() == false) { QueryArgs.Add({TEXT("user_id"), Params.UserId}); }
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListSubscriptionsRequest (
  const FNakamaListSubscriptionsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/subscription");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListTournamentsRequest (
  const FNakamaListTournamentsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/tournament");

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.CategoryStart.IsEmpty() == false) { QueryArgs.Add({TEXT("category_start"), FString::Printf(TEXT("%d"), Params.CategoryStart.GetValue())}); }
  if (Params.CategoryEnd.IsEmpty() == false) { QueryArgs.Add({TEXT("category_end"), FString::Printf(TEXT("%d"), Params.CategoryEnd.GetValue())}); }
  if (Params.StartTime.IsEmpty() == false) { QueryArgs.Add({TEXT("start_time"), FString::Printf(TEXT("%d"), Params.StartTime.GetValue())}); }
  if (Params.EndTime.IsEmpty() == false) { QueryArgs.Add({TEXT("end_time"), FString::Printf(TEXT("%d"), Params.EndTime.GetValue())}); }
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListTournamentRecordsRequest (
  const FNakamaListTournamentRecordsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/tournament/{tournament_id}");
  Url = Url.Replace(TEXT("{tournament_id}"), *FGenericPlatformHttp::UrlEncode(Params.TournamentId));

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  if (Params.Expiry.IsEmpty() == false) { QueryArgs.Add({TEXT("expiry"), FString::Printf(TEXT("%lld"), Params.Expiry.GetValue())}); }
  for (const auto& Item : Params.OwnerIds)
  {
    QueryArgs.Add({TEXT("owner_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListTournamentRecordsAroundOwnerRequest (
  const FNakamaListTournamentRecordsAroundOwnerRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/tournament/{tournament_id}/owner/{owner_id}");
  Url = Url.Replace(TEXT("{tournament_id}"), *FGenericPlatformHttp::UrlEncode(Params.TournamentId));
  Url = Url.Replace(TEXT("{owner_id}"), *FGenericPlatformHttp::UrlEncode(Params.OwnerId));

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.Expiry.IsEmpty() == false) { QueryArgs.Add({TEXT("expiry"), FString::Printf(TEXT("%lld"), Params.Expiry.GetValue())}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildListUserGroupsRequest (
  const FNakamaListUserGroupsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/user/{user_id}/group");
  Url = Url.Replace(TEXT("{user_id}"), *FGenericPlatformHttp::UrlEncode(Params.UserId));

  //
  // Verb
  Request.Verb = TEXT("GET");

  //
  // Query/Body Params
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Limit.IsEmpty() == false) { QueryArgs.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())}); }
  if (Params.State.IsEmpty() == false) { QueryArgs.Add({TEXT("state"), FString::Printf(TEXT("%d"), Params.State.GetValue())}); }
  if (Params.Cursor.IsEmpty() == false) { QueryArgs.Add({TEXT("cursor"), Params.Cursor}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildReadStorageObjectsRequest (
  const FNakamaReadStorageObjectsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/storage");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildRpcFuncRequest (
  const FNakamaRpc& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/rpc/{id}");
  Url = Url.Replace(TEXT("{id}"), *FGenericPlatformHttp::UrlEncode(Params.Id));

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  {
    FString Escaped = Params.Payload;
    Escaped = Escaped.Replace(TEXT("\\"), TEXT("\\\\"));
    Escaped = Escaped.Replace(TEXT("\""), TEXT("\\\""));
    Escaped = Escaped.Replace(TEXT("\r"), TEXT("\\r"));
    Escaped = Escaped.Replace(TEXT("\n"), TEXT("\\n"));
    Escaped = Escaped.Replace(TEXT("\t"), TEXT("\\t"));
    Request.Body = TEXT("\"") + Escaped + TEXT("\"");
  }
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.HttpKey.IsEmpty() == false) { QueryArgs.Add({TEXT("http_key"), Params.HttpKey}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseAppleRequest (
  const FNakamaValidatePurchaseAppleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/purchase/apple");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildValidateSubscriptionAppleRequest (
  const FNakamaValidateSubscriptionAppleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/subscription/apple");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseGoogleRequest (
  const FNakamaValidatePurchaseGoogleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/purchase/google");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildValidateSubscriptionGoogleRequest (
  const FNakamaValidateSubscriptionGoogleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/subscription/google");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseHuaweiRequest (
  const FNakamaValidatePurchaseHuaweiRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/purchase/huawei");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseFacebookInstantRequest (
  const FNakamaValidatePurchaseFacebookInstantRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/purchase/facebookinstant");

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildWriteLeaderboardRecordRequest (
  const FNakamaWriteLeaderboardRecordRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/leaderboard/{leaderboard_id}");
  Url = Url.Replace(TEXT("{leaderboard_id}"), *FGenericPlatformHttp::UrlEncode(Params.LeaderboardId));

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.Record.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildWriteStorageObjectsRequest (
  const FNakamaWriteStorageObjectsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/storage");

  //
  // Verb
  Request.Verb = TEXT("PUT");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildWriteTournamentRecordRequest (
  const FNakamaWriteTournamentRecordRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/tournament/{tournament_id}");
  Url = Url.Replace(TEXT("{tournament_id}"), *FGenericPlatformHttp::UrlEncode(Params.TournamentId));

  //
  // Verb
  Request.Verb = TEXT("PUT");

  //
  // Query/Body Params
  TSharedPtr<FJsonObject> BodyJson = Params.Record.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);

  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildAddFriendsRequest (
  const FNakamaAddFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/friend");
  Request.Verb = TEXT("POST");
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Metadata.IsEmpty() == false) { QueryArgs.Add({TEXT("metadata"), Params.Metadata}); }
  for (const auto& Item : Params.Ids)
  {
    QueryArgs.Add({TEXT("ids"), Item});
  }
  for (const auto& Item : Params.Usernames)
  {
    QueryArgs.Add({TEXT("usernames"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildAddGroupUsersRequest (
  const FNakamaAddGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/group/{group_id}/add");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Verb = TEXT("POST");
  TArray<TPair<FString, FString>> QueryArgs;
  for (const auto& Item : Params.UserIds)
  {
    QueryArgs.Add({TEXT("user_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildSessionLogoutRequest (
  const FNakamaSessionLogoutRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/session/logout");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildBanGroupUsersRequest (
  const FNakamaBanGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/group/{group_id}/ban");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Verb = TEXT("POST");
  TArray<TPair<FString, FString>> QueryArgs;
  for (const auto& Item : Params.UserIds)
  {
    QueryArgs.Add({TEXT("user_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildBlockFriendsRequest (
  const FNakamaBlockFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/friend/block");
  Request.Verb = TEXT("POST");
  TArray<TPair<FString, FString>> QueryArgs;
  for (const auto& Item : Params.Ids)
  {
    QueryArgs.Add({TEXT("ids"), Item});
  }
  for (const auto& Item : Params.Usernames)
  {
    QueryArgs.Add({TEXT("usernames"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildDeleteFriendsRequest (
  const FNakamaDeleteFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/friend");
  Request.Verb = TEXT("DELETE");
  TArray<TPair<FString, FString>> QueryArgs;
  for (const auto& Item : Params.Ids)
  {
    QueryArgs.Add({TEXT("ids"), Item});
  }
  for (const auto& Item : Params.Usernames)
  {
    QueryArgs.Add({TEXT("usernames"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildDeleteGroupRequest (
  const FNakamaDeleteGroupRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/group/{group_id}");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Verb = TEXT("DELETE");
  TArray<TPair<FString, FString>> QueryArgs;
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildDeleteLeaderboardRecordRequest (
  const FNakamaDeleteLeaderboardRecordRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/leaderboard/{leaderboard_id}");
  Url = Url.Replace(TEXT("{leaderboard_id}"), *FGenericPlatformHttp::UrlEncode(Params.LeaderboardId));
  Request.Verb = TEXT("DELETE");
  TArray<TPair<FString, FString>> QueryArgs;
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildDeleteNotificationsRequest (
  const FNakamaDeleteNotificationsRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/notification");
  Request.Verb = TEXT("DELETE");
  TArray<TPair<FString, FString>> QueryArgs;
  for (const auto& Item : Params.Ids)
  {
    QueryArgs.Add({TEXT("ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildDeleteTournamentRecordRequest (
  const FNakamaDeleteTournamentRecordRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/tournament/{tournament_id}");
  Url = Url.Replace(TEXT("{tournament_id}"), *FGenericPlatformHttp::UrlEncode(Params.TournamentId));
  Request.Verb = TEXT("DELETE");
  TArray<TPair<FString, FString>> QueryArgs;
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildDeleteStorageObjectsRequest (
  const FNakamaDeleteStorageObjectsRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/storage/delete");
  Request.Verb = TEXT("PUT");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildEventRequest (
  const FNakamaEvent& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/event");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildImportFacebookFriendsRequest (
  const FNakamaImportFacebookFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/friend/facebook");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Reset.IsEmpty() == false) { QueryArgs.Add({TEXT("reset"), LexToString(Params.Reset.GetValue())}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildImportSteamFriendsRequest (
  const FNakamaImportSteamFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/friend/steam");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Reset.IsEmpty() == false) { QueryArgs.Add({TEXT("reset"), LexToString(Params.Reset.GetValue())}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildJoinGroupRequest (
  const FNakamaJoinGroupRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/group/{group_id}/join");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Verb = TEXT("POST");
  TArray<TPair<FString, FString>> QueryArgs;
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildJoinTournamentRequest (
  const FNakamaJoinTournamentRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/tournament/{tournament_id}/join");
  Url = Url.Replace(TEXT("{tournament_id}"), *FGenericPlatformHttp::UrlEncode(Params.TournamentId));
  Request.Verb = TEXT("POST");
  TArray<TPair<FString, FString>> QueryArgs;
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildKickGroupUsersRequest (
  const FNakamaKickGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/group/{group_id}/kick");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Verb = TEXT("POST");
  TArray<TPair<FString, FString>> QueryArgs;
  for (const auto& Item : Params.UserIds)
  {
    QueryArgs.Add({TEXT("user_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildLeaveGroupRequest (
  const FNakamaLeaveGroupRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/group/{group_id}/leave");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Verb = TEXT("POST");
  TArray<TPair<FString, FString>> QueryArgs;
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildLinkAppleRequest (
  const FNakamaAccountApple& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/link/apple");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildLinkCustomRequest (
  const FNakamaAccountCustom& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/link/custom");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildLinkDeviceRequest (
  const FNakamaAccountDevice& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/link/device");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildLinkEmailRequest (
  const FNakamaAccountEmail& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/link/email");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildLinkFacebookRequest (
  const FNakamaLinkFacebookRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/link/facebook");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.Account.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  TArray<TPair<FString, FString>> QueryArgs;
  if (Params.Sync.IsEmpty() == false) { QueryArgs.Add({TEXT("sync"), LexToString(Params.Sync.GetValue())}); }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildLinkFacebookInstantGameRequest (
  const FNakamaAccountFacebookInstantGame& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/link/facebookinstantgame");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildLinkGameCenterRequest (
  const FNakamaAccountGameCenter& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/link/gamecenter");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildLinkGoogleRequest (
  const FNakamaAccountGoogle& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/link/google");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildLinkSteamRequest (
  const FNakamaLinkSteamRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/link/steam");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildPromoteGroupUsersRequest (
  const FNakamaPromoteGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/group/{group_id}/promote");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Verb = TEXT("POST");
  TArray<TPair<FString, FString>> QueryArgs;
  for (const auto& Item : Params.UserIds)
  {
    QueryArgs.Add({TEXT("user_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildDemoteGroupUsersRequest (
  const FNakamaDemoteGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/group/{group_id}/demote");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Verb = TEXT("POST");
  TArray<TPair<FString, FString>> QueryArgs;
  for (const auto& Item : Params.UserIds)
  {
    QueryArgs.Add({TEXT("user_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryArgs);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildUnlinkAppleRequest (
  const FNakamaAccountApple& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/unlink/apple");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildUnlinkCustomRequest (
  const FNakamaAccountCustom& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/unlink/custom");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildUnlinkDeviceRequest (
  const FNakamaAccountDevice& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/unlink/device");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildUnlinkEmailRequest (
  const FNakamaAccountEmail& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/unlink/email");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildUnlinkFacebookRequest (
  const FNakamaAccountFacebook& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/unlink/facebook");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildUnlinkFacebookInstantGameRequest (
  const FNakamaAccountFacebookInstantGame& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/unlink/facebookinstantgame");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildUnlinkGameCenterRequest (
  const FNakamaAccountGameCenter& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/unlink/gamecenter");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildUnlinkGoogleRequest (
  const FNakamaAccountGoogle& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/unlink/google");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildUnlinkSteamRequest (
  const FNakamaAccountSteam& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account/unlink/steam");
  Request.Verb = TEXT("POST");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildUpdateAccountRequest (
  const FNakamaUpdateAccountRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/account");
  Request.Verb = TEXT("PUT");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildUpdateGroupRequest (
  const FNakamaUpdateGroupRequest& Params
)
{
  FNakamaApiRequestModel Request;
  FString Url = TEXT("/v2/group/{group_id}");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Verb = TEXT("PUT");
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);
  Request.Url = Url;
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildGetAccountRequest ()
{
  FNakamaApiRequestModel Request;
  Request.Url = TEXT("/v2/account");
  Request.Verb = TEXT("GET");
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildGetMatchmakerStatsRequest ()
{
  FNakamaApiRequestModel Request;
  Request.Url = TEXT("/v2/matchmaker/stats");
  Request.Verb = TEXT("GET");
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildDeleteAccountRequest ()
{
  FNakamaApiRequestModel Request;
  Request.Url = TEXT("/v2/account");
  Request.Verb = TEXT("DELETE");
  return Request;
}
FNakamaApiRequestModel NAKAMA_API BuildHealthcheckRequest ()
{
  FNakamaApiRequestModel Request;
  Request.Url = TEXT("/healthcheck");
  Request.Verb = TEXT("GET");
  return Request;
}
} // namespace NakamaInternal

