#pragma once
#include "define.h"
#include "Renderer.h"
#include "Sprites.h"

class VarRenderer : public Renderer {
public:
	inline static const int X_AXIS = 0b1;
	inline static const int Y_AXIS = 0b10;

private:
	Sprites* const _master;
	const int _sprNum;
	Sprite** const _sprites;
	int* const _variable;
	float* const _widths;
	float* const _heights;
	float* const _lefts;
	float* const _tops;
	float* const _xs;
	float* const _ys;

public:
	VarRenderer(Object* const parent, const string& master);
	~VarRenderer();

public:
	inline Sprites* getMaster() { return _master; }
	inline Sprite* getSpriteAt(int index) { return _sprites[index]; }
	inline int getSprNum() { return _sprNum; }
	inline int isVariable(int index) { return _variable[index]; }
	inline bool isVariableX(int index) { return isVariable(index) & X_AXIS; }
	inline bool isVariableY(int index) { return isVariable(index) & Y_AXIS; }
	inline float getWidthAt(int index) { return _widths[index]; }
	inline float getHeightAt(int index) { return _heights[index]; }
	inline float getLeftAt(int index) { return _lefts[index]; }
	inline float getTopAt(int index) { return _tops[index]; }
	inline float getXAt(int index) { return _xs[index]; }
	inline float getYAt(int index) { return _ys[index]; }

public:
	inline void setWidthAt(int index, int width) { _widths[index] = width; }
	inline void setHeightAt(int index, int height) { _heights[index] = height; }
	inline void setLeftAt(int index, int left) { _lefts[index] = left; }
	inline void setTopAt(int index, int top) { _tops[index] = top; }
	inline void setXAt(int index, int x) { _xs[index] = x; }
	inline void setYAt(int index, int y) { _ys[index] = y; }

public:
	/*
	x方向、y方向それぞれに対し、任意の数の領域を拡張描画の対象にできるような
	メソッドを実装する

	width配列、height配列をそれぞれ用意する

	updateRenderingParamメソッドは、setVarAreaが実行されたとき、
	scaleが変化したとき、相対描画座標が変化したときに実行される
	*/

	template<typename First, typename... Rest>
	void setVarAreaX(bool isUpdate, First first, Rest... rest) {
		__setVarArea__(X_AXIS, first, rest...);

		if (isUpdate) {
			updateRenderingParam();
		}
	}

	template<typename First, typename... Rest>
	void setVarAreaY(bool isUpdate, First first, Rest... rest) {
		__setVarArea__(Y_AXIS, first, rest...);

		if (isUpdate) {
			updateRenderingParam();
		}
	}

	void updateRenderingParam() {
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

private:
	void __setVarArea__(int axis, int first) {
		switch (axis) {
		case X_AXIS: {
			int div = getMaster()->getDivX();
			for (int i = 0; i < getMaster()->getDivY(); i++) {
				_variable[i * div + first] ^= X_AXIS;
			}
			break;
		}

		case Y_AXIS: {
			int div = getMaster()->getDivY();
			for (int i = 0; i < getMaster()->getDivX(); i++) {
				_variable[first * div + i] ^= Y_AXIS;
			}
			break;
		}
		}
	}

public:
	void render() override;

private:
	template<typename... Rest>
	void __setVarArea__(int axis, int first, Rest... rest);
	template<typename First, typename... Rest>
	void __setVarArea__(int axis, First first, Rest... rest);
	template<typename First>
	void __setVarArea__(int axis, First first) {}
};

template<typename... Rest>
void VarRenderer::__setVarArea__(int axis, int first, Rest... rest) {
	__setVarArea__(axis, first);
	__setVarArea__(axis, rest...);
}
template<typename First, typename... Rest>
void VarRenderer::__setVarArea__(int axis, First first, Rest... rest) {
	__setVarArea__(axis, rest...);
}