#pragma once
#include "define.h"

class Morton {
public:
	inline static const int DEPTH = 4;
	inline static int SQUARE = int(pow(2, DEPTH - 1));
	inline static const float DX =
		float(double(winx) / double(SQUARE));
	inline static const float DY =
		float(double(winy) / double(SQUARE));

protected:
	inline static const int ID = -1;
	inline static const int SCALE = -1;

protected:
	Object* const _self = nullptr;
	int _id[DEPTH];
	int _absId = ID;
	int _depth = SCALE;

public:
	Morton(Object* const self);
	~Morton();

public:
	virtual int getMorton(int index) final { return _id[index]; }
	virtual int getDeepMorton() final { return _id[DEPTH - 1]; }
	virtual int getAbsMorton()final { return _absId; }
	virtual int getDepth()final { return _depth; }
	virtual void updateMorton();

protected:
	void resetId() {
		for (int i = 0; i < DEPTH; i++) { _id[i] = ID; }
	}

public:
	static void drawGrid();
	static int getUpperShiftCount(int val);

protected:
	static int getOrder(float x, float y);

private:
	static int log2(int v);
};