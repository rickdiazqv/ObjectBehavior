#pragma once
#include "package.h"

class Task {
public:
	virtual void update() = 0;
	virtual void draw() = 0;
public:
	virtual string toString() { return "Task::toString\n"; }
};