#pragma once
#include "define.h"

class Morton {
protected:
	inline static const int ID = -1;
	inline static const int SCALE = -1;
	inline static const int DEPTH = 5;

	inline static const float DX =
		float(double(winx) / pow(2, DEPTH));

	inline static const float DY =
		float(double(winy) / pow(2, DEPTH));

protected:
	int _id[DEPTH];
	int _absId = ID;
	int _scale = SCALE;

public:
	Morton();
	~Morton();

public:
	virtual int getMorton(int index) final { return _id[index]; }
	virtual int getDeepMorton() final { return _id[DEPTH - 1]; }
	virtual int getAbsMorton()final { return _absId; }
	virtual int getScale()final { return _scale; }
	virtual void setMorton(float x, float y);

public:
	static void drawGrid();

protected:
	static int getOrder(float x, float y);

private:
	static int log2(int v);
};