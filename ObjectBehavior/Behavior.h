#pragma once
#include "define.h"

template <typename T>
class Behavior {
protected:
	virtual void onCollisionEnter(T obj) {}
	virtual void onCollisionStay(T obj) {}
	virtual void onCollisionExit(T obj) {}
};