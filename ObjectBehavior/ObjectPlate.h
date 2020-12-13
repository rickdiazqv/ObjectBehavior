#pragma once
#include "define.h"
#include "RectangleObject.h"

class ObjectPlate : public RectangleObject {
private:
	inline static const int PROC_PRIORITY = 4;
	inline static const int DRAW_PRIORITY = 4;

public:
	static ObjectPlate* const DEFAULT_PLATE;

public:
	ObjectPlate(float width, float height, Layer layer, bool pers = false);
	ObjectPlate(float x, float y, float width, float height, Layer layer, bool pers = false);
	~ObjectPlate();

public:
	void setWorldX(float x) = delete;
	void setWorldY(float y) = delete;
	void addWorldX(float x) = delete;
	void addWorldY(float y) = delete;

public:
	inline void setWindowX(float x) override {
		RectangleObject::setWindowX(x);
		// children�ɒʒm
	}
	inline void setWindowY(float y) override {
		RectangleObject::setWindowX(y);
		// children�ɒʒm
	}

public:
	void update() override;
	void draw() override;
};

