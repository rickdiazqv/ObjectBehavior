#pragma once
#include "package.h"
#include "Worker.h"
#include "EditableTask.h"
#include "Behavior.h"

class Object : public Worker, public EditableTask, public Behavior<Object*> {
protected:
	int _x, _y;

public:
	Object();
	~Object();

public:
	void Awake() override;
	void Start() override;
	void Update() override;
	void Draw() override;
};

using GameObject = Object*;