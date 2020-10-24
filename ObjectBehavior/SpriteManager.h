#pragma once
#include "define.h"
#include "Connector.h"
#include "Configurable.h"
#include "Sprite.h"
#include "Sprites.h"

class SpriteManager : 
	public Connector<Sprite*, string, bool>, 
	public Configurable<json&> {

private:
	inline static const char* const CONFIG_PATH = "data/json/sprites/sprites.json";
	inline static const string SPRITE = "Sprite";
	inline static const string SPRITES = "Sprites";

private:
	inline static SpriteManager* _self = nullptr;

private:
	unordered_map<string, Sprite*> _sprites;

private:
	SpriteManager();
	~SpriteManager();

public:
	inline static SpriteManager* getInstance() {
		if (!_self) { _self = new SpriteManager(); }
		return _self;
	}

	inline static void finalize() {
		delete _self;
		_self = nullptr;
	}

public:
	inline Sprite* getSprite(const string& sprite) {
		if (_sprites.count(sprite)) { return _sprites[sprite]; }
		return nullptr;
	}
	Sprite* getSprite(const string& sprite, const string& divSprite) {
		if (!_sprites.count(sprite)) { return nullptr; }
		Sprites* sprites = dynamic_cast<Sprites*>(_sprites[sprite]);
		if (sprites) { return sprites->getSpriteAt(divSprite); }
		return nullptr;
	}
	void loadSprite(const char* const fpath);

private:
	void setSprite(json& config);
	void setSprites(json& config);

public:
	string connect(Sprite* self) { return string(); }
	bool disconnect(Sprite* self) { return false; }

public:
	void configure(json& config) override;
};

