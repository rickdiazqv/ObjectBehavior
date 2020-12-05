#include "VarRenderer.h"
#include "SpriteManager.h"

VarRenderer::VarRenderer(Object* const parent, const string& master) :
	_master(dynamic_cast<Sprites*>(getSprite())),
	_sprNum(_master ? _master->getSpritesNum() : 0),
	_sprites(_sprNum ? new Sprite * [_sprNum] : nullptr),
	_variable(_sprNum ? new int[_sprNum] : nullptr),
	_widths(_sprNum ? new float[_sprNum] : nullptr),
	_heights(_sprNum ? new float[_sprNum] : nullptr),
	_lefts(_sprNum ? new float[_sprNum] : nullptr),
	_tops(_sprNum ? new float[_sprNum] : nullptr),
	_xs(_sprNum ? new float[_sprNum] : nullptr),
	_ys(_sprNum ? new float[_sprNum] : nullptr),
	Renderer(parent, master) {

	Sprite* sprite = nullptr;
	for (int i = 0; i < _sprNum; i++) {
		int idx = _master->getSprite(&sprite);
		_sprites[idx] = sprite;
		_variable[i] = 0;
	}

	for (int i = 0; i < _sprNum; i++) {
		Sprite* spr = _sprites[i];
		_widths[i] = _sprites[i]->getSizeX();
		_heights[i] = _sprites[i]->getSizeY();
		_lefts[i] = LEFT;
		_tops[i] = TOP;
	}

	int divX = getMaster()->getDivX();
	int divY = getMaster()->getDivY();
	for (int i = 0; i < divY; i++) {
		for (int j = 0; j < divX; j++) {
			int index = i * divX + j;
		}
	}
}

VarRenderer::~VarRenderer() {
	delete[] _sprites;
	delete[] _variable;
	delete[] _widths;
	delete[] _heights;
	delete[] _lefts;
	delete[] _tops;
	delete[] _xs;
	delete[] _ys;
}

void VarRenderer::render() {
	for (int i = 0; i < getSprNum(); i++) {
		Sprite* sprite = getSpriteAt(i);
		int left = (int)(getParent()->getX() + getLeftAt(i));
		int top = (int)(getParent()->getY() + getTopAt(i));
		int width = getWidthAt(i);
		int height = getHeightAt(i);
		if (isVariable(i)) {
			DrawExtendGraph(left, top, left + width, top + height,
				sprite->getHandle(), TRUE);
		}
		else {
			DrawGraph(left, top, sprite->getHandle(), TRUE);
		}
	}
}