#pragma once
#include "define.h"
#include "Connector.h"
#include "Configurable.h"
#include "Sprite.h"

class SpriteManager : public Connector<Sprite*, string, bool>, public Configurable<json> {
private:
	inline static const string SINGLE = "single";
	inline static const string COMBINE = "combine";

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
	inline Sprite* getSprite(string sprite) { 
		if (_sprites.count(sprite)) {
			return _sprites[sprite];
		}
		return nullptr;
	}
	void loadSprite(const char* const fpath);

private:
	void setSprite(json& config) ;
	void setSprites(json& config);

public:
	string connect(Sprite* self) { return string(); }
	bool disconnect(Sprite* self) { return false; }

public:
	void configure(json& config) override;
};

