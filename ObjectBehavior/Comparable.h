#pragma once
#include "package.h"

template<typename T>
class Comparable {
public:
	virtual int compareTo(T other) = 0;
};
