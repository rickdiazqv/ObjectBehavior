#pragma once
#include "define.h"
#include "RectangleObject.h"
#include "VarRenderer.h"
#include "Input.h"

constexpr const char* window_master = "variable_window";

class Window : public RectangleObject {
private:
	inline static int wndCnt = 0;

private:
	Input& _input = *Input::getInstance();

private:
	const string _master = window_master;
	VarRenderer _renderer = VarRenderer(this, _master);

private:
	const string _id;

public:
	Window(float x, float y);
	Window(float x, float y, float width, float height);
	~Window();

public:
	inline string getId() override { return _id; }

public:
	void update() override;
	void draw() override;
};

