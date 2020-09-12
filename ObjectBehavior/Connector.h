#pragma once
#include "package.h"

template<typename T>
class Connector {
public:
	virtual void connect(T self, compare<T> comp) = 0;
};