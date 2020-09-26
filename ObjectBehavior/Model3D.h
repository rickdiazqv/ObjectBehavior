#pragma once
#include "define.h"
#include "PlaneObject.h"

class Model3D : public PlaneObject {
private:
	int modelHandle, attachIndex;
	float totalTime, playTime, time = .0f;

public:
	Model3D(const char* const path);

public:
	void update() override;
	void draw() override;
};