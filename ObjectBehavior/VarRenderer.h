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
	inline void setScale(float scaleX, float scaleY) override {
		Renderer::setScale(scaleX, scaleY);
		updateRenderingParam();
	}
	inline void setScaleX(float scaleX) override {
		Renderer::setScaleX(scaleX);
		updateRenderingParam();
	}
	inline void setScaleY(float scaleY) override {
		Renderer::setScaleY(scaleY);
		updateRenderingParam();
	}
	inline void setPos(float x, float y) override {
		Renderer::setPos(x, y);
		updateRenderingParam();
	}
	inline void setX(float x) override {
		Renderer::setX(x);
		updateRenderingParam();
	}
	inline void setY(float y) override {
		Renderer::setY(y);
		updateRenderingParam();
	}

public:
	void setVarArea(vector<int>&& varX, vector<int>&& varY);
	void updateRenderingParam();

public:
	void render() override;
};