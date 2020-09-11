#pragma once
#include "package.h"

template<typename T>
class Connector {
public:
	virtual void connect(T obj) = 0;
};