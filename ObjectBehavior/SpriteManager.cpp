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
	_sprites[j2s(config[j_key])] = new Sprite(j2s(config[j_path]).c_str());
}

void SpriteManager::setSprites(json& config) {
	_sprites[j2s(config[j_key])] = new Sprites(config);
}

void SpriteManager::configure(json& config) {
	json& confList = config[j_config];

	for (json& conf : confList) {
		string type = j2s(conf[j_class]);
		if (type == SPRITE) {
			setSprite(conf);
		}
		else if (type == SPRITES) {
			setSprites(conf);
		}
	}
}