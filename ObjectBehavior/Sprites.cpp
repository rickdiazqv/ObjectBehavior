#include "Sprites.h"
#include "CSVEditor.h"

Sprites::Sprites(CSVEditor& csv, bool load) : Sprite(csv.getString(0, 2).c_str(), load) {

	/*for (int i = 1; i < csv.rowLength(); i++) {
		_sprites[csv.getString(i, 0)]
	}*/
}


Sprites::Sprites(json& config, bool load) : Sprite(j2s(config["path"]).c_str(), load) {
	json& sprites = config[j_sprites];
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

	for (json& sprite : sprites) {
		json& reg = sprite[j_reg];
		int regX = j2i(reg[j_x]);
		int regY = j2i(reg[j_y]);

		string s = j2s(sprite[j_key]);
		if (s == btn_emr[0]) {
			int sx = getSizeX();
			int sy = getSizeY();
			int ssx = getSpriteSizeX();
			int ssy = getSpriteSizeY();
			int divx = getDivX();
			int n = getDivX() * regY + regX;
			int a = 0;
		}

		_sprites[j2s(sprite[j_key])] = new DivSprite(getDivX() * regY + regX, getSpriteSizeX(), getSpriteSizeY());
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
	
	char cd[256];
	GetCurrentDirectory(256, cd);
	int h = LoadGraph(fpath.c_str());

	LoadDivGraph(getFilePath().c_str(), getSpritesNum(), getDivX(), getDivY(), getSpriteSizeX(), getSpriteSizeY(), _hndls);
	for (auto entry : _sprites) {
		DivSprite& ds = *entry.second;
		ds.sprite->load(getHandleAt(ds.index));
	}
}