#pragma once
#include "tools.h"

template<typename T>
class Connector {
public:
	virtual void connect(T self) = 0;
	virtual void disconnect(T self) = 0;
};