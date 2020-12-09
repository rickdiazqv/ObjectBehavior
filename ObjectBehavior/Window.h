#pragma once
#include "define.h"
#include "RectangleObject.h"
#include "VarRenderer.h"
#include "Input.h"

class Window : public RectangleObject {
private:
	inline static int wndCnt = 0;

protected:
	Input& _input = *Input::getInstance();

protected:
	const string _master;
	VarRenderer _renderer = VarRenderer(this, _master);

private:
	const string _id;

public:
	Window(
		float x,
		float y,
		float width,
		float height,
		string&& master,
		vector<int>&& varX,
		vector<int>&& varY);
	~Window();

public:
	inline string getId() override { return _id; }

public:
	void update() override;
	void draw() override;
};