#pragma once
#include "tools.h"
#include "Worker.h"
#include "EditableTask.h"
#include "Behavior.h"

using GameObject = Object*;

class Object : public Worker, public EditableTask, public Behavior<GameObject> {
protected:
	inline static const Layer LAYER = Layer::Default;
	inline static const int X = 0, Y = 0;
	inline static const int VX = 0, VY = 0;
	inline static const int AX = 0, AY = 0;
	inline static const bool PERS = false;

protected:
	Layer _layer = LAYER;
	bool _pers = PERS;

protected:
	int _x = X, _y = Y;
	int _x_hist = _x, _y_hist = _y;

public:
	int vx = VX, vy = VY;
	int ax = AX, ay = AY;
	bool collision = true;

protected:
	//Object* _prev = nullptr;
	//Object* _next = nullptr;

public:
	Object();
	Object(int x, int y, Layer layer, bool pers);
	~Object();

// getter
public:
	Layer getLayer() { return _layer; }
	bool getPers() { return _pers; }
	int getX() { return _x; }
	int getY() { return _y; }
	int getXHist() { return _x_hist; }
	int getYHist() { return _y_hist; }
	int getDX() { return getX() - getXHist(); }
	int getDY() { return getY() - getYHist(); }
	bool isMove() { return getDX() != 0 || getDY() != 0; }

// setter
public:
	void setLayer(Layer layer) {

	}

// Task
public:
	void update() override;
	string toString() override;

// Editable Task
public:
	void Awake() override;
	void Start() override;
	void Update() override;
	void Draw() override;

// Wroker
public:
	int drawCompareTo(Worker* other) override;
};