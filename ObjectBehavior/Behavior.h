#pragma once
#include "define.h"

template <typename T>
class Behavior {
protected:
	virtual void onClick() {}
	virtual void onMouseDown() {}
	virtual void onMouseUp() {}
	virtual void onMouseEntry() {}
	virtual void onMouseExit() {}
	virtual void onCollisionEnter(T obj) {}
	virtual void onCollisionStay(T obj) {}
	virtual void onCollisionExit(T obj) {}
};