#pragma once

template <typename T>
using Comparator = int(*)(T, T);

template <typename Of, typename What>
inline bool instanceof(const What w)
{
	return dynamic_cast<const Of*>(w) != 0;
}