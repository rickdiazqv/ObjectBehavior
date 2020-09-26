#pragma once
#include "define.h"
#include "Worker.h"
#include "EditableTask.h"
#include "Behavior.h"
#include "Morton.h"

using GameObject = Object*;

class Object : public Worker, public EditableTask, public Behavior<GameObject> {
private:
	inline static const int PROC_PRIORITY = 5;
	inline static const int DRAW_PRIORITY = 5;

protected:
	inline static const Layer LAYER = Layer::Default;
	inline static const float X = .0f, Y = .0f;
	inline static const float VX = .0f, VY = .0f;
	inline static const float AX = .0f, AY = .0f;
	inline static const bool PERS = false;

protected:
	Layer _layer = LAYER;
	bool _pers = PERS;

protected:
	float _x = X, _y = Y;
	float _x_hist = _x, _y_hist = _y;
	Morton* _morton;

public:
	float vx = VX, vy = VY;
	float ax = AX, ay = AY;
	bool collision = true;

protected:
	//Object* _prev = nullptr;
	//Object* _next = nullptr;

public:
	Object();
	Object(float x, float y, Layer layer, bool pers);
	~Object();

protected:
	virtual void createMorton();

	// getterk
public:
	void init() override final;
	Layer getLayer() { return _layer; }
	bool getPers() { return _pers; }
	float getX() { return _x; }
	float getY() { return _y; }
	float getXHist() { return _x_hist; }
	float getYHist() { return _y_hist; }
	float getDX() { return getX() - getXHist(); }
	float getDY() { return getY() - getYHist(); }
	bool isMove() { return getDX() != .0f || getDY() != .0f; }

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