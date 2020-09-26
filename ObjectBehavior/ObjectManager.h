#pragma once
#include "define.h"
#include "Worker.h"
#include "Object.h"
#include "Morton.h"

class ObjectManager final : public Worker {
public:
	inline static const int PROC_PRIORITY = 9;
	inline static const int DRAW_PRIORITY = 9;
	inline static const int CELL = (pow(4, Morton::DEPTH) - 1) / 3;

private:
	inline static ObjectManager* _self = nullptr;

	Object** _cell = nullptr;

private:
	ObjectManager();
	~ObjectManager();

public:
	static ObjectManager* getInstance() {
		if (!_self) { _self = new ObjectManager(); }
		return _self;
	}

	static void finalize() {
		delete _self;
		_self = nullptr;
	}

public:
	void init() override {}
	void update() override;
	void draw() override {}
};