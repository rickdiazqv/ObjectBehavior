#pragma once
#include "tools.h"
#include "Worker.h"
#include "EditableTask.h"
#include "Behavior.h"

class Object : public Worker, public EditableTask, public Behavior<Object*> {
protected:
	inline static const Layer LAYER = Layer::Default;
	inline static const int X = 0, Y = 0;
	inline static const bool PERS = false;

private:
	Layer _layer = LAYER;
	bool _pers = PERS;

protected:
	int _x = X, _y = Y;
	int _x_hist = _x, _y_hist = _y;

protected:
	Object* _prev = nullptr;
	Object* _next = nullptr;

public:
	Object();
	Object(int x, int y, Layer layer, bool perse);
	~Object();

public:
	Layer getLayer() { return _layer; }
	bool getPers() { return _pers; }
	int getX() { return _x; }
	int getY() { return _y; }

public:
	void setLayer(Layer layer) {

	}

public:
	void Awake() override;
	void Start() override;
	void Update() override;
	void Draw() override;
	string toString() override;
};

using GameObject = Object*;