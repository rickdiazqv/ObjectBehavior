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

void VarRenderer::setVarArea(vector<int>&& varX, vector<int>&& varY) {
	int divX = getMaster()->getDivX();
	int divY = getMaster()->getDivY();

	for (int x : varX) {
		for (int y = 0; y < getMaster()->getDivY(); y++) {
			_variable[y * divX + x] ^= X_AXIS;
		}
	}

	for (int y : varY) {
		for (int x = 0; x < getMaster()->getDivX(); x++) {
			_variable[y * divY + x] ^= Y_AXIS;
		}
	}

	updateRenderingParam();
}

void VarRenderer::updateRenderingParam() {
	Sprites* const master = getMaster();
	const int divX = master->getDivX();
	const int divY = master->getDivY();
	const float scaleX = getScaleX();
	const float scaleY = getScaleY();
	const float width = getWidth();
	const float height = getHeight();
	int cntX = 0, cntY = 0;

	for (int i = 0; i < divX; i++) {
		if (isVariableX(i)) {
			cntX++;
		}
	}
	for (int i = 0; i < divY; i++) {
		if (isVariableY(i * divX)) {
			cntY++;
		}
	}

	const float extX = (width - (float)master->getSizeX()) / (float)cntX;
	const float extY = (height - (float)master->getSizeY()) / (float)cntY;
	float top = getTop();
	
	for (int i = 0; i < divY; i++) {
		const int row = i * divX;
		float left = getLeft();
		for (int j = 0; j < divX; j++) {
			const int index = row + j;
			Sprite* const sprite = getSpriteAt(index);
			float wid = (float)sprite->getSizeX();
			float hei = (float)sprite->getSizeY();

			if (isVariableX(index)) {
				wid += extX;
			}
			if (isVariableY(index)) {
				hei += extY;
			}

			setLeftAt(index, left);
			setTopAt(index, top);
			setWidthAt(index, wid);
			setHeightAt(index, hei);
			setXAt(index, getLeftAt(index) + getWidthAt(index) / 2.f);
			setYAt(index, getTopAt(index) + getHeightAt(index) / 2.f);

			left += getWidthAt(index);
		}

		top += getHeightAt(row);
	}
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