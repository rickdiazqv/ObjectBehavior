#pragma once
#include "define.h"
#include "Worker.h"

class Input : public Worker {
private:
	inline static const int PROC_PRIORITY = 10;
	inline static const int DRAW_PRIORITY = 10;
	inline static const int MOUSE_X = 0, MOUSE_Y = 0;

private:
	inline static Input* _self = nullptr;

private:
	int _mx = MOUSE_X, _my = MOUSE_Y;
	int _mx_hist = MOUSE_X, _my_hist = MOUSE_Y;
	char _mouse[n_mouse];
	bool _useMouse = true;
	Worker* collision = nullptr;

private:
	unordered_map<unsigned char, char> _key;
	bool _useKey = true;

public:
	static Input* getInstance() {
		if (!_self) { _self = new Input(); }
		return _self;
	}

	static void finalize() {
		delete _self;
		_self = nullptr;
	}

private:
	Input();
	~Input();

public:
	void init() override{}
	int getMouseX() { return _mx; }
	int getMouseY() { return _my; }
	int getMouseXHist() { return _mx_hist; }
	int getMouseYHist() { return _my_hist; }
	int getDX() { return getMouseX() - getMouseXHist(); }
	int getDY() { return getMouseY() - getMouseYHist(); }
	bool isMove() {
		int dx = getDX();
		int dy = getDY();
		return dx != 0 || dy != 0;
	}
	bool isMouseDown(int index) { return _mouse[index] == 1; }
	bool isMouse(int index) { return _mouse[index] > 0; }
	bool isMouseUp(int index) { return _mouse[index] == -1; }

public:
	void setUseMouse(bool useMouse) { _useMouse = useMouse; }
	void setUseKey(bool useKey) { _useKey = useKey; }

private:
	void setKey(const char* path);

public:
	void update() override;
	void draw() override;
	string toString() override;

public:
	int procCompareTo(Worker* other) override { return 1; }
	int drawCompareTo(Worker* other) override { return 1; }
};