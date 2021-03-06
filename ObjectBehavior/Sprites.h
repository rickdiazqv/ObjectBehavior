#pragma once
#include "define.h"
#include "Sprite.h"

class Sprites final : public Sprite {
protected:
	inline static const int DIVISION = 1;

private:
	struct DivSprite {
		const int index;
		Sprite* const sprite;

	public:
		DivSprite(int index, int sizeX, int sizeY) :
			index(index), sprite(new Sprite(sizeX, sizeY)) {

		}
		~DivSprite() {
			delete sprite;
		}
	};

private:
	unordered_map<string, DivSprite*> _sprites;
	unordered_map<string, DivSprite*>::iterator _iterator;
	int* _hndls = nullptr;
	int _divX = DIVISION, _divY = DIVISION;
	int _sprNum = SIZE;
	int _eSizeX = SIZE, _eSizeY = SIZE;

public:
	Sprites(CSVEditor& csv, bool load = false);
	Sprites(json& config, bool load = false);
	~Sprites();

public:
	inline Sprite* getSpriteAt(const string& divSprite) {
		if (_sprites.count(divSprite)) { return _sprites[divSprite]->sprite; }
		return nullptr;
	}
	inline int getSprite(Sprite** const sprite) {
		if (_iterator == _sprites.end()) { _iterator = _sprites.begin(); }
		*sprite = _iterator->second->sprite;
		return (_iterator++)->second->index;
	}
	inline int getDivX() { return _divX; }
	inline int getDivY() { return _divY; }
	inline int getSpritesNum() { return _sprNum; }
	inline int getSpriteSizeX() { return _eSizeX; }
	inline int getSpriteSizeY() { return _eSizeY; }

private:
	inline int getHandleAt(int index) { return _hndls[index]; }
	inline void setDivX(int div) { _divX = div; }
	inline void setDivY(int div) { _divY = div; }
	inline void setSpritesNum(int num) { _sprNum = num; }
	inline void setSpriteSizeX(int size) { _eSizeX = size; }
	inline void setSpriteSizeY(int size) { _eSizeY = size; }

public:
	void load() override;
};