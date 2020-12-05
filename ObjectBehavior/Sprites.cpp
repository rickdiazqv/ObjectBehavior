#include "Sprites.h"
#include "CSVEditor.h"

Sprites::Sprites(CSVEditor& csv, bool load) :
	_iterator(_sprites.end()),
	Sprite(csv.getString(0, 2).c_str(), load) {

	/*for (int i = 1; i < csv.rowLength(); i++) {
		_sprites[csv.getString(i, 0)]
	}*/
}


Sprites::Sprites(json& config, bool load) :
	_iterator(_sprites.end()),
	Sprite(j2s(config[j_path]).c_str(), load) {
	json& div = config[j_div];

	setDivX(j2i(div[j_x]));
	setDivY(j2i(div[j_y]));
	setSpritesNum(getDivX() * getDivY());
	setSpriteSizeX(getSizeX() / getDivX());
	setSpriteSizeY(getSizeY() / getDivY());

	_hndls = new int[getSpritesNum()];
	for (int i = 0; i < getSpritesNum(); i++) {
		_hndls[i] = 0;
	}

	if (config.count(j_sprites) > 0) {
		json& sprites = config[j_sprites];

		for (json& sprite : sprites) {
			json& reg = sprite[j_reg];
			int regX = j2i(reg[j_x]);
			int regY = j2i(reg[j_y]);

			_sprites[j2s(sprite[j_key])] =
				new DivSprite(getDivX() * regY + regX,
					getSpriteSizeX(), getSpriteSizeY());
		}
	}
	else {
		for (int i = 0; i < getSpritesNum(); i++) {
			_sprites[to_string(i)] = 
				new DivSprite(i, getSpriteSizeX(), getSpriteSizeY());
		}
	}
}

Sprites::~Sprites() {
	delete[] _hndls;
	for (auto sprite : _sprites) {
		delete sprite.second;
	}
}

void Sprites::load() {
	if (getFilePath().empty() || getHandle() > 0) { return; }

	string& fpath = getFilePath();
	int n = getSpritesNum();
	int dx = getDivX();
	int dy = getDivY();
	int sx = getSpriteSizeX();
	int sy = getSpriteSizeY();

	LoadDivGraph(getFilePath().c_str(), getSpritesNum(), getDivX(), getDivY(), getSpriteSizeX(), getSpriteSizeY(), _hndls);
	for (auto entry : _sprites) {
		DivSprite& ds = *entry.second;
		ds.sprite->load(getHandleAt(ds.index));
	}
}