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

public:
	inline static const int X_UNDER = -1;
	inline static const int X_OVER = -2;
	inline static const int Y_UNDER = -3;
	inline static const int Y_OVER = -4;

protected:
	inline static const int ID = -1;
	inline static const int SCALE = -1;

protected:
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
	virtual int getMorton(int index) final { return _id[index]; }
	virtual int getAbsMorton() final { return _absId; }
	virtual int getDepth() final { return _depth; }
	virtual int getDeepMorton() final { return _id[getDepth()]; }

	virtual int getOldMorton(int index) final { return _oldId[index]; }
	virtual int getOldAbs()final { return _oldAbs; }
	virtual int getOldDep()final { return _oldDep; }
	virtual int getOldDeep() final { return _oldId[getOldDep()]; }

	virtual void updateMorton() final {
		updateOldParam();
		updateMortonParam();
	}


public:
	virtual void setMorton(int id, int index) final { _id[index] = id; }
	virtual void setDepth(int depth) final { _depth = depth; }
	virtual void setAbsMorton(int absId) final { _absId = absId; }
	virtual void resetMorton() final {
		setDepth(SCALE);
		setAbsMorton(ID);
	}

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
	static int getOrder(float x, float y);

private:
	static int log2(int v);
};