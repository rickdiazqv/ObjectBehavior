#pragma once
#include "define.h"
#include "Object.h"
#include "ObjectPlate.h"

class Camera : public Object {
private:
	inline static const int PROC_PRIORITY = 3;
	inline static const int DRAW_PRIORITY = 3;

private:
	ObjectPlate* const _plate = nullptr;

public:
	Camera(float x, float y, ObjectPlate* plate);
	~Camera();

public:
	void setWorldX(float x) = delete;
	void setWorldY(float y) = delete;
	void addWorldX(float x) = delete;
	void addWorldY(float y) = delete;

public:
	void update() override;
	void draw() override;
};