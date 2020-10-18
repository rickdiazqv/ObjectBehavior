#pragma once
#include "define.h"

class Sprite {
protected:
	inline static const int HANDLE = 0;
	inline static const int SIZE = 0;

private:
	string _fpath;
	int _hndl = HANDLE;
	int _sizeX = SIZE, _sizeY = SIZE;

public:
	Sprite(const char* const fpath, bool load = false);
	Sprite(int sizeX, int sizeY);
	Sprite() {};
	~Sprite();

public:
	inline int getHandle() { return _hndl; }
	inline int getSizeX() { return _sizeX; }
	inline int getSizeY() { return _sizeY; }

protected:
	inline string& getFilePath() { return _fpath; }
	inline void setHandle(int hndl) { _hndl = hndl; }
	inline void setSizeX(int sizeX) { _sizeX = sizeX; }
	inline void setSizeY(int sizeY) { _sizeY = sizeY; }
	
public:
	inline virtual void load() {
		if (getFilePath().empty()) { return; }
		setHandle(LoadGraph(getFilePath().c_str()));
	}
	inline void load(int hndl) { setHandle(hndl); }
};

