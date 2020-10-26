#pragma once
#include "define.h"
#include "Worker.h"
#include "Morton.h"
#include "Connector.h"

class ObjectManager final :
	public Worker,
	public Connector<Object*, Object*, bool> {
public:
	inline static const int PROC_PRIORITY = 10;
	inline static const int DRAW_PRIORITY = 10;
	inline static const int DEPTH = Morton::DEPTH;
	inline static int CELL = (pow(4, DEPTH) - 1) / 3;

private:
	inline static ObjectManager* _self = nullptr;

	MortonTree* _cell = nullptr;
	int* _n = nullptr;
	int* _root = nullptr;

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

private:
	int getN(int index) { return _n[index]; }
	int getRoot(int index) { return _root[index]; }

public:
	void init() override {}
	void update() override;
	void draw() override;

public:
	Object* connect(Object* self) override;
	bool disconnect(Object* self) override;

public:
	void updateAt(MortonTree* const self);

private:
	void updateAt(Object* const root);
	void printMortonTree(MortonTree* tree, int depth);
};

/*
‡@“¯ƒZƒ‹“à‚Å‘“–‚è
‡A‘S‚Ä‚ÌãˆÊƒZƒ‹‚Æ‘“–‚½‚è
‡Bq‚ğQÆ
‡C‡@`‡B‚ğŒJ‚è•Ô‚·
*/