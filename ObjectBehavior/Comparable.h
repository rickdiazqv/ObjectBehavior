#pragma once
#include "define.h"

template<typename T>
class Comparable {
public:
	virtual int compareTo(T other) = 0;
};
