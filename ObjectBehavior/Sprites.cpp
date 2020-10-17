#include "Sprites.h"
#include "CSVEditor.h"

Sprites::Sprites(CSVEditor& csv, bool load) : Sprite(csv.getString(0, 2).c_str(), load) {

	/*for (int i = 1; i < csv.rowLength(); i++) {
		_sprites[csv.getString(i, 0)]
	}*/
}


Sprites::Sprites(json& config, bool load) : Sprite(j2s(config["path"]).c_str(), load) {
	json& sprites = config[j_sprites];
	string s = j2s(config);
	json& div = config[j_div];

	setDivX(j2i(div[j_x]));
	setDivY(j2i(div[j_y]));
	setSpritesNum(getDivX() * getDivY());
	setSpriteSizeX(getSizeX() / getDivX());
	setSpriteSizeY(getSizeY() / getDivY());
	_hndls = new int[getSpritesNum()];
	for (json& sprite : sprites) {
		json& reg = sprite[j_reg];
		int regX = j2i(reg[j_x]);
		int regY = j2i(reg[j_y]);

		_sprites[j2s(sprite[j_key])] = new DivSprite(getDivX() * regY + regX, getSpriteSizeX(), getSpriteSizeY());
	}
}

Sprites::~Sprites() {
	for (auto sprite : _sprites) {
		delete sprite.second;
	}
}