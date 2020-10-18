#include "SpriteManager.h"
#include "CSVEditor.h"
#include "Sprites.h"

SpriteManager::SpriteManager() {
	const char* const fpath = "data/json/sprites/sprites.json";
	//const char* const fpath = "data/json/sprites/test.json";
	json config = json::parse(DxFileRead(fpath));
	configure(config);
	//printfDx(DxFileRead("data/json/sprites/sprites.json").c_str());
}

SpriteManager::~SpriteManager() {
	for (auto s : _sprites) {
		delete s.second;
	}
}

void SpriteManager::loadSprite(const char* const fpath) {
	/*CSVEditor csv(fpath);
	string type = csv.getString(0, 0);

	if (type == SINGLE) {
		setSprite(csv);
	}
	else if (type == COMBINE) {
		setSprites(csv);
	}*/
}

void SpriteManager::setSprite(json& config) {
	/*for (int i = 0; i < csv.rowLength(); i++) {
		_sprites[csv.getString(i, 0)] = new Sprite(csv.getString(i, 1).c_str());
	}*/
}

void SpriteManager::setSprites(json& config) {
	_sprites[j2s(config[j_key])] = new Sprites(config);
}

void SpriteManager::configure(json& config) {
	json& confList = config[j_config];

	for (json& conf : confList) {
		string type = j2s(conf[j_class]);
		if (type == "Sprite") {
			setSprite(conf);
		}
		else if (type == "Sprites") {
			setSprites(conf);
		}
	}
}