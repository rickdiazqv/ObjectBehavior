#pragma once
#include "package.h"
#include "Object.h"

class Plane : public Object {
public:
	Plane();
	~Plane();

public:
	void update() override;
	void draw() override;
};
