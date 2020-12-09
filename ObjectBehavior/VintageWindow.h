#pragma once
#include "define.h"
#include "Window.h"

constexpr const char* window_master = "variable_window";

class VintageWindow : public Window {
public:
	VintageWindow(
		float x,
		float y,
		float width,
		float height);
	~VintageWindow();
};