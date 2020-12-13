#pragma once
#include "define.h"

class Morton {
public:
	inline static const int DEPTH = 4;
	inline static int SQUARE = int(pow(2, DEPTH - 1));

public:
	inline static const int X_UNDER = -1;
	inline static const int X_OVER = -2;
	inline static const int Y_UNDER = -3;
	inline static const int Y_OVER = -4;

protected:
	inline static const int ID = -1;
	inline static const int SCALE = -1;

protected:
	ObjectPlate* _plate = nullptr;
	float _dx = float(WINDOW_X) / float(SQUARE);
	float _dy = float(WINDOW_Y) / float(SQUARE);

	Object* const _self = nullptr;
	int _id[DEPTH];
	int _absId = ID;
	int _depth = SCALE;

	int _oldId[DEPTH];
	int _oldAbs = _absId;
	int _oldDep = _depth;

public:
	Morton(Object* const self);
	~Morton();

public:
	inline ObjectPlate* getPlate() { return _plate; }
	inline float getDX() { return _dx; }
	inline float getDY() { return _dy; }
	inline float getWidth();
	inline float getHeight();
	inline int getMorton(int index) { return _id[index]; }
	inline int getAbsMorton() { return _absId; }
	inline int getDepth() { return _depth; }
	inline int getDeepMorton() { return _id[getDepth()]; }

	inline int getOldMorton(int index) { return _oldId[index]; }
	inline int getOldAbs() { return _oldAbs; }
	inline int getOldDep() { return _oldDep; }
	inline int getOldDeep() { return _oldId[getOldDep()]; }

	inline void updateMorton() {
		updateOldParam();
		updateMortonParam();
	}

public:
	inline void setPlate(ObjectPlate* plate) {
		setDX(getWidth() / float(SQUARE));
		setDY(getHeight() / float(SQUARE));
	}
	inline void setMorton(int id, int index) { _id[index] = id; }
	inline void setDepth(int depth) { _depth = depth; }
	inline void setAbsMorton(int absId) { _absId = absId; }
	inline void resetMorton() {
		setDepth(SCALE);
		setAbsMorton(ID);
	}

private:
	inline void setDX(float dx) { _dx = dx; }
	inline void setDY(float dy) { _dy = dy; }

protected:
	virtual void updateMortonParam();

private:
	virtual void updateOldParam() final {
		_oldAbs = _absId;
		_oldDep = _depth;
		for (int i = 0; i < _oldDep; i++) {
			_oldId[i] = _id[i];
		}
	}
	virtual void resetId() final {
		for (int i = 0; i < DEPTH; i++) { _id[i] = ID; }
	}

public:
	static void drawGrid();
	static int getUpperShiftCount(int val);

protected:
	int getOrder(float x, float y);
	static int getOrder(
		float x, float y, float dx, float dy, float width, float height);

private:
	static int log2(int v);
};