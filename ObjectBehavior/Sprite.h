#pragma once
#include "define.h"

class Sprite {
protected:
	inline static const int HANDLE = 0;
	inline static const int SIZE = 0;

private:
	const char* const _fpath = nullptr;
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
	inline const char* const getFilePath() { return _fpath; }
	inline void setHandle(int hndl) { _hndl = hndl; }
	inline void setSizeX(int sizeX) { _sizeX = sizeX; }
	inline void setSizeY(int sizeY) { _sizeY = sizeY; }
	
public:
	void load();
	
private:
	void load(int hndl);
};

