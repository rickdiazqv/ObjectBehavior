#pragma once

template <typename T>
using compare = int(*)(T, T);

template <typename T>
using initialize = void(*)(T, const char*);

template <typename Of, typename What>
inline bool instanceof(const What w)
{
	return dynamic_cast<const Of*>(w) != 0;
}