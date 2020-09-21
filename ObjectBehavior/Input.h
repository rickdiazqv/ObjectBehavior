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
	inline static char _mouse[n_mouse];
	inline static bool _useMouse = true;
	inline static Worker* collision = nullptr;

private:
	inline static unordered_map<unsigned char, char> _key;
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
	static bool isMove() {
		int dx = getDX();
		int dy = getDY();
		return dx != 0 || dy != 0;
	}
	static bool isMouseDown(int index) { return _mouse[index] == 1; }
	static bool isMouse(int index) { return _mouse[index] > 0; }
	static bool isMouseUp(int index) { return _mouse[index] == -1; }

public:
	static void setUseMouse(bool useMouse) { _useMouse = useMouse; }
	static void setUseKey(bool useKey) { _useKey = useKey; }

private:
	static void setKey(const char* path);

public:
	void update() override;
	void draw() override;
	string toString() override;

public:
	int procCompareTo(Worker* other) override { return 1; }
	int drawCompareTo(Worker* other) override { return 1; }
};