#pragma once
#include "define.h"

template <typename T>
class MouseListener {
public:
	virtual void onClick(T ev) = 0;
	virtual void onMouseDown(int index, T ev) = 0;
	virtual void onMouseUp(int index, T ev) = 0;
	virtual void onMouseEntry(T ev) = 0;
	virtual void onMouseExit(T ev) = 0;
};