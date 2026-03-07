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
#include <type_traits>

// Forward declaration
template<typename T> struct TNakamaFuture;

/** Type trait: is T a TNakamaFuture<U>? */
template<typename T> struct TIsTNakamaFuture : std::false_type {};
template<typename T> struct TIsTNakamaFuture<TNakamaFuture<T>> : std::true_type {};

/**
 * Chainable future wrapper for async Nakama operations.
 * Parameterized by concrete result type (e.g. FNakamaSessionResult or FNakamaWebSocketResponse).
 *
 * Three .Next() overloads:
 *
 * 1. Chaining with auto-propagation: Next(callback(const ValueType&) -> TNakamaFuture<Other>)
 *    Only available for result types that define ::ValueType (HTTP result structs).
 *    If the outer result has bIsError=true, the error is forwarded and the callback is skipped.
 *
 * 2. Chaining without auto-propagation: Next(callback(ResultT) -> TNakamaFuture<Other>)
 *    Available for all result types including WebSocket types. The user receives the full
 *    result (including any error) and decides what to return.
 *
 * 3. Terminal: Next(callback(ResultT) -> void)
 *    Called unconditionally when the future resolves. User inspects the result for errors.
 */
template<typename ResultT>
struct TNakamaFuture
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

	TNakamaFuture() = default;
	explicit TNakamaFuture(TSharedPtr<FState> InState) noexcept
		: State(MoveTemp(InState)) {}
	TNakamaFuture(TNakamaFuture&& Other) noexcept = default;
	TNakamaFuture& operator=(TNakamaFuture&& Other) noexcept = default;
	TNakamaFuture(const TNakamaFuture&) = delete;
	TNakamaFuture& operator=(const TNakamaFuture&) = delete;

	/**
	 * Overload 1 — Chaining with auto-propagation.
	 * callback(const ValueType&) -> TNakamaFuture<OtherResult>
	 * Only enabled when ResultT has ::ValueType.
	 * On error, propagates to OtherResult without calling the callback.
	 */
	template<typename Func,
		typename VT = typename ResultT::ValueType,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, const VT&>,
		std::enable_if_t<TIsTNakamaFuture<Ret>::value, int> = 0>
	Ret Next(Func&& Callback) && noexcept
	{
		using InnerResultT = typename Ret::WrappedResultType;
		auto OuterState = MakeShared<typename TNakamaFuture<InnerResultT>::FState>();
		auto CapturedState = State;
		UE::Tasks::Launch(UE_SOURCE_LOCATION,
			[Cb = Forward<Func>(Callback), CapturedState, OuterState]() mutable
			{
				if (CapturedState->Result.bIsError)
				{
					OuterState->Resolve(InnerResultT{{}, CapturedState->Result.Error, true});
					return;
				}
				Ret Inner = Cb(CapturedState->Result.Value);
				auto InnerState = Inner.State;
				UE::Tasks::Launch(UE_SOURCE_LOCATION,
					[InnerState, OuterState]()
					{
						OuterState->Resolve(MoveTemp(InnerState->Result));
					},
					InnerState->Event);
			},
			CapturedState->Event);
		State.Reset();
		return TNakamaFuture<InnerResultT>(OuterState);
	}

	/**
	 * Overload 2 — Chaining, user handles errors.
	 * callback(ResultT) -> TNakamaFuture<OtherResult>
	 * Available for all ResultT, including WebSocket types without ::ValueType.
	 * The callback receives the full result and is responsible for error handling.
	 */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, ResultT>,
		std::enable_if_t<TIsTNakamaFuture<Ret>::value, int> = 0>
	Ret Next(Func&& Callback) && noexcept
	{
		using InnerResultT = typename Ret::WrappedResultType;
		auto OuterState = MakeShared<typename TNakamaFuture<InnerResultT>::FState>();
		auto CapturedState = State;
		UE::Tasks::Launch(UE_SOURCE_LOCATION,
			[Cb = Forward<Func>(Callback), CapturedState, OuterState]() mutable
			{
				Ret Inner = Cb(MoveTemp(CapturedState->Result));
				auto InnerState = Inner.State;
				UE::Tasks::Launch(UE_SOURCE_LOCATION,
					[InnerState, OuterState]()
					{
						OuterState->Resolve(MoveTemp(InnerState->Result));
					},
					InnerState->Event);
			},
			CapturedState->Event);
		State.Reset();
		return TNakamaFuture<InnerResultT>(OuterState);
	}

	/** Overload 3 — Terminal. callback(ResultT) -> void */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, ResultT>,
		std::enable_if_t<!TIsTNakamaFuture<Ret>::value, int> = 0>
	void Next(Func&& Callback) && noexcept
	{
		auto CapturedState = State;
		UE::Tasks::Launch(UE_SOURCE_LOCATION,
			[Cb = Forward<Func>(Callback), CapturedState]() mutable
			{
				Cb(MoveTemp(CapturedState->Result));
			},
			CapturedState->Event);
		State.Reset();
	}
};

/**
 * Create a pre-resolved TNakamaFuture.
 * Useful for returning an immediate result (e.g. an error) from a chaining callback.
 */
template<typename ResultT>
TNakamaFuture<ResultT> MakeCompletedFuture(ResultT Value)
{
	auto State = MakeShared<typename TNakamaFuture<ResultT>::FState>();
	State->Resolve(MoveTemp(Value));
	return TNakamaFuture<ResultT>(State);
}
