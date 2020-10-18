#pragma once
#include "define.h"
#include "Object.h"
#include "Morton.h"

class Input : public Object {
public:
	inline static const int LEFT = 0;
	inline static const int MIDDLE = 1;
	inline static const int RIGHT = 2;

private:
	inline static const int PROC_PRIORITY = 9;
	inline static const int DRAW_PRIORITY = 9;
	inline static const int MOUSE_X = 0, MOUSE_Y = 0;
	inline static const Shape SHAPE = Shape::Dot;

private:
	inline static Input* _self = nullptr;

private:
	//int _mx = MOUSE_X, _my = MOUSE_Y;
	//int _mx_hist = MOUSE_X, _my_hist = MOUSE_Y;
	char _mouse[n_mouse];
	bool _useMouse = true;
	Object* _collision = nullptr;

private:
	unordered_map<unsigned char, char> _key;
	bool _useKey = true;

private:
	const string _id;

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
	//void init() override{}
	float getX() = delete;
	float getY() = delete;
	float getXHist() = delete;
	float getYHist() = delete;
	float getDX() = delete;
	float getDY() = delete;
	inline float getMouseX() { return _x; }
	inline float getMouseY() { return _y; }
	inline float getMouseXHist() { return _xHist; }
	inline float getMouseYHist() { return _yHist; }
	inline float getMouseDX() { return getMouseX() - getMouseXHist(); }
	inline float getMouseDY() { return getMouseY() - getMouseYHist(); }
	inline bool isMove() {
		int dx = getMouseDX();
		int dy = getMouseDY();
		return dx != 0 || dy != 0;
	}
	inline bool isMouseDown(int index) { return _mouse[index] == 1; }
	inline bool isMouse(int index) { return _mouse[index] > 0; }
	inline bool isMouseUp(int index) { return _mouse[index] == -1; }
	inline string getId() override { return _id; }

public:
	inline void setUseMouse(bool useMouse) { _useMouse = useMouse; }
	inline void setUseKey(bool useKey) { _useKey = useKey; }

private:
	void setKey(const char* path);

public:
	void update() override;
	void draw() override;
	string toString() override;

public:
	inline int procCompareTo(Worker* other) override { return 1; }
	inline int drawCompareTo(Worker* other) override { return 1; }
};