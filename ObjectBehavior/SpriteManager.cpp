#include "SpriteManager.h"
#include "CSVEditor.h"
#include "Sprites.h"

SpriteManager::SpriteManager() {

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
	_sprites[config["key"]] = new Sprites(config);
}

void SpriteManager::configure(json& config) {
	json& confList = config["config"];

	for (json& conf : confList) {
		string type = conf["class"];
		if (type == "Sprite") {
			setSprite(conf);
		}
		else if (type == "Sprites") {
			setSprites(conf);
		}
	}
}