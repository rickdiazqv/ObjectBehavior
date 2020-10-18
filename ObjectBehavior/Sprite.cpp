#include "Sprite.h"

Sprite::Sprite(const char* const fpath, bool load) : _fpath(fpath) {
	GetImageSize_File(fpath, &_sizeX, &_sizeY);
	//printfDx("%s, (%d, %d)\n", fpath, getSizeX(), getSizeY());
}

Sprite::Sprite(int sizeX, int sizeY) : _fpath("") {
	setSizeX(sizeX);
	setSizeY(sizeY);
}

Sprite::~Sprite() {

}