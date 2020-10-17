#include "Sprite.h"

Sprite::Sprite(const char* const fpath, bool load) : _fpath(fpath) {
	GetImageSize_File(fpath, &_sizeX, &_sizeY);
}

Sprite::Sprite(int sizeX, int sizeY) : _fpath(nullptr) {
	setSizeX(sizeX);
	setSizeY(sizeY);
}

Sprite::~Sprite() {

}

void Sprite::load() {
	if (!getFilePath()) { return; }
	setHandle(LoadGraph(getFilePath()));
}

void Sprite::load(int hndl) {
	setHandle(hndl);
}