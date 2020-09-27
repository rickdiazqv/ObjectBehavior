#pragma once
#include "define.h"

template<typename T, typename  R, typename  S>
class Connector {
public:
	virtual R connect(T self) = 0;
	virtual S disconnect(T self) = 0;
};