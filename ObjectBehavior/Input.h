#pragma once
#include "define.h"
#include "Worker.h"

class Input : public Worker {
private:
	inline static const int MOUSE_X = 0, MOUSE_Y = 0;

private:
	inline static Input* _self = nullptr;

private:
	inline static int _mx = MOUSE_X, _my = MOUSE_Y;
	inline static int _mx_hist = MOUSE_X, _my_hist = MOUSE_Y;

	inline static char mouse[3] = { 0, 0, 0 };
	inline static bool _useMouse = true;

private:
	inline static char _key[n_key];
	inline static bool _useKey = true;

public:
	Input();

public:
	static int getMouseX() { return _mx; }
	static int getMouseY() { return _my; }
	static int getMouseXHist() { return _mx_hist; }
	static int getMouseYHist() { return _my_hist; }
	static int getDX() { return getMouseX() - getMouseXHist(); }
	static int getDY() { return getMouseY() - getMouseYHist(); }
	static bool isMove() { return getDX() != 0 || getDY != 0; }

public:
	static void setUseMouse(bool useMouse) { _useMouse = useMouse; }
	static void setUseKey(bool useKey) { _useKey = useKey; }

public:
	void update() override;
	void draw() override;
	string toString() override;
};

