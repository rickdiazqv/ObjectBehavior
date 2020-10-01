#pragma once

template <typename T>
using Comparator = int(*)(T, T);

template <typename T, typename R>
using Function = R(*)(T);

template<typename T, typename U, typename R>
using BiFunction = R(*)(T, U);

template<typename T>
using UnaryOperator = Function<T, T>;

template<typename T, typename R>
using TypeBiFunction = BiFunction<T,T,R>;


template<typename T>
using Consumer = void(*)(T);

template<typename T, typename U>
using BiConsumer = void(*)(T, U);

template<typename T>
using TypeBiConsumer = BiConsumer<T, T>;

template <typename Of, typename What>
inline bool instanceof(const What w)
{
	return dynamic_cast<const Of*>(w) != 0;
}