#pragma once
#include "define.h"
#include "RectangleObject.h"
#include "Renderer.h"

class BackGround : public RectangleObject {
private:
	inline static int bgCnt = 0;

private:
	const string _master = "sea";
	Renderer _renderer = Renderer(this, _master);

private:
	const string _id;

public:
	BackGround();
	~BackGround();

public:
	inline string getId() override { return _id; }

public:
	void update();
	void draw();
};