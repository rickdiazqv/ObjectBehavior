#pragma once
#include "define.h"
#include "Object.h"

class PlaneObject : public Object {
public:
	PlaneObject();
	~PlaneObject();

public:
	void update() override;
	void draw() override;
};
