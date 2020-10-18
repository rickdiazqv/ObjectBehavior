#pragma once
#include "define.h"
#include "Input.h"
#include "RectangleObject.h"
#include "Renderer.h"

class Button : public RectangleObject {
private:
	inline static int btnCnt = 0;

private:
	Input& _input = *Input::getInstance();

private:
	const string _master = btn;
	const string _values[3] = { btn_emr[0], btn_emr[1], btn_emr[2] };
	Renderer _renderer[3] = {
	   Renderer(this, _master, _values[0]),
	   Renderer(this, _master, _values[1]),
	   Renderer(this, _master, _values[2])
	};

private:
	int type = 0;
	const string _id;

public:
	Button(float x, float y);

public:
	inline string getId() override { return _id; }

public:
	void update() override;
	void draw() override;
};

