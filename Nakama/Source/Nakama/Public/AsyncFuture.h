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

#pragma once

#include "CoreMinimal.h"
#include "Tasks/Task.h"
#include "Async/TaskGraphInterfaces.h"
#include <type_traits>

// Forward declaration
template<typename T> struct TAsyncFuture;

/** Type trait: is T a TAsyncFuture<U>? */
template<typename T> struct TIsTAsyncFuture : std::false_type {};
template<typename T> struct TIsTAsyncFuture<TAsyncFuture<T>> : std::true_type {};

/**
 * Chainable, game-thread-safe future for async operations.
 *
 * Parameterized by a concrete result type (e.g. FNakamaSessionResult or
 * FSatoriSessionResult).  Every user-visible callback is dispatched to the
 * game thread via AsyncTask(ENamedThreads::GameThread, ...) so that callers
 * can safely touch UObject*, fire delegates, or update UI without additional
 * marshalling.
 *
 * Three .Next() overloads are provided:
 *
 * 1. Chaining with auto-propagation:
 *       Next(callback(const ValueType&) -> TAsyncFuture<Other>)
 *    Available only when ResultT defines ::ValueType.
 *    On error the error is forwarded to the outer future and the callback is
 *    skipped entirely (error propagation runs on the background thread because
 *    no user code is involved).
 *
 * 2. Chaining without auto-propagation:
 *       Next(callback(ResultT) -> TAsyncFuture<Other>)
 *    Available for all ResultT, including types without ::ValueType (e.g.
 *    WebSocket envelope types).  The callback receives the full result and is
 *    responsible for inspecting bIsError and deciding what to return.
 *
 * 3. Terminal:
 *       Next(callback(ResultT) -> void)
 *    Called unconditionally when the future resolves.  The caller inspects
 *    the result for errors inside the callback.
 */
template<typename ResultT>
struct TAsyncFuture
{
	using WrappedResultType = ResultT;

	struct FState
	{
		ResultT Result{};
		UE::Tasks::FTaskEvent Event{ UE_SOURCE_LOCATION };
		void Resolve(ResultT&& InResult)
		{
			Result = MoveTemp(InResult);
			Event.Trigger();
		}
	};

	TSharedPtr<FState> State;

	TAsyncFuture() = default;
	explicit TAsyncFuture(TSharedPtr<FState> InState) noexcept
		: State(MoveTemp(InState)) {}
	TAsyncFuture(TAsyncFuture&& Other) noexcept = default;
	TAsyncFuture& operator=(TAsyncFuture&& Other) noexcept = default;
	TAsyncFuture(const TAsyncFuture&) = delete;
	TAsyncFuture& operator=(const TAsyncFuture&) = delete;

	/**
	 * Overload 1 — Chaining with auto-propagation.
	 * callback(const ValueType&) -> TAsyncFuture<OtherResult>
	 * Only enabled when ResultT has ::ValueType.
	 * On error, propagates to OtherResult without calling the callback.
	 */
	template<typename Func,
		typename VT = typename ResultT::ValueType,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, const VT&>,
		std::enable_if_t<TIsTAsyncFuture<Ret>::value, int> = 0>
	Ret Next(Func&& Callback) && noexcept
	{
		using InnerResultT = typename Ret::WrappedResultType;
		auto OuterState = MakeShared<typename TAsyncFuture<InnerResultT>::FState>();
		auto CapturedState = State;
		UE::Tasks::Launch(UE_SOURCE_LOCATION,
			[Cb = Forward<Func>(Callback), CapturedState, OuterState]() mutable
			{
				if (CapturedState->Result.bIsError)
				{
					// Error propagation: no user code involved, safe on any thread.
					OuterState->Resolve(InnerResultT{{}, CapturedState->Result.Error, true});
					return;
				}
				// User callback may touch UObject* or fire delegates — dispatch to game thread.
				AsyncTask(ENamedThreads::GameThread,
					[Cb = MoveTemp(Cb), CapturedState, OuterState]() mutable
					{
						Ret Inner = Cb(CapturedState->Result.Value);
						auto InnerState = Inner.State;
						UE::Tasks::Launch(UE_SOURCE_LOCATION,
							[InnerState, OuterState]()
							{
								OuterState->Resolve(MoveTemp(InnerState->Result));
							},
							InnerState->Event);
					});
			},
			CapturedState->Event);
		State.Reset();
		return TAsyncFuture<InnerResultT>(OuterState);
	}

	/**
	 * Overload 2 — Chaining, user handles errors.
	 * callback(ResultT) -> TAsyncFuture<OtherResult>
	 * Available for all ResultT, including WebSocket types without ::ValueType.
	 * The callback receives the full result and is responsible for error handling.
	 */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, ResultT>,
		std::enable_if_t<TIsTAsyncFuture<Ret>::value, int> = 0>
	Ret Next(Func&& Callback) && noexcept
	{
		using InnerResultT = typename Ret::WrappedResultType;
		auto OuterState = MakeShared<typename TAsyncFuture<InnerResultT>::FState>();
		auto CapturedState = State;
		UE::Tasks::Launch(UE_SOURCE_LOCATION,
			[Cb = Forward<Func>(Callback), CapturedState, OuterState]() mutable
			{
				// User callback may touch UObject* or fire delegates — dispatch to game thread.
				AsyncTask(ENamedThreads::GameThread,
					[Cb = MoveTemp(Cb), CapturedState, OuterState]() mutable
					{
						Ret Inner = Cb(MoveTemp(CapturedState->Result));
						auto InnerState = Inner.State;
						UE::Tasks::Launch(UE_SOURCE_LOCATION,
							[InnerState, OuterState]()
							{
								OuterState->Resolve(MoveTemp(InnerState->Result));
							},
							InnerState->Event);
					});
			},
			CapturedState->Event);
		State.Reset();
		return TAsyncFuture<InnerResultT>(OuterState);
	}

	/** Overload 3 — Terminal. callback(ResultT) -> void */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, ResultT>,
		std::enable_if_t<!TIsTAsyncFuture<Ret>::value, int> = 0>
	void Next(Func&& Callback) && noexcept
	{
		auto CapturedState = State;
		UE::Tasks::Launch(UE_SOURCE_LOCATION,
			[Cb = Forward<Func>(Callback), CapturedState]() mutable
			{
				// User callback may touch UObject* or fire delegates — dispatch to game thread.
				AsyncTask(ENamedThreads::GameThread,
					[Cb = MoveTemp(Cb), CapturedState]() mutable
					{
						Cb(MoveTemp(CapturedState->Result));
					});
			},
			CapturedState->Event);
		State.Reset();
	}
};

/**
 * Create a pre-resolved TAsyncFuture.
 * Useful for returning an immediate result (e.g. a local error) from a
 * chaining callback without going through the network stack.
 */
template<typename ResultT>
TAsyncFuture<ResultT> MakeCompletedAsyncFuture(ResultT Value)
{
	auto State = MakeShared<typename TAsyncFuture<ResultT>::FState>();
	State->Resolve(MoveTemp(Value));
	return TAsyncFuture<ResultT>(State);
}
