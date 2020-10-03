#pragma once
#include "define.h"
#include "EditableTask.h"
#include "Behavior.h"
#include "Worker.h"

using GameObject = Object*;

class Object : public Worker, public EditableTask, public Behavior<GameObject> {
private:
	inline static const int PROC_PRIORITY = 5;
	inline static const int DRAW_PRIORITY = 5;

protected:
	inline static const Layer LAYER = Layer::Default;
	inline static const float X = .0f, Y = .0f;
	inline static const float VX = .0f, VY = .0f;
	inline static const float AX = .0f, AY = .0f;
	inline static const bool PERS = false;

private:
	inline static Connector<Object*, Object*, bool>* _connector = nullptr;
	inline static unordered_map <int, TypeBiFunction<Object*, bool>> colliderFunction;

protected:
	 Shape _shape = Shape::Dot;
	Layer _layer = LAYER;
	bool _pers = PERS;

protected:
	float _x = X, _y = Y;
	float _xHist = _x, _yHist = _y;
	Morton* _morton;
	Object* _mortonNext = nullptr;
	Object* _mortonPrev = nullptr;

public:
	float vx = VX, vy = VY;
	float ax = AX, ay = AY;

protected:
	bool _collisionable = true;	// 当たり判定を有効にするか
	bool _collision = false;		// 衝突したかどうか
	bool _crossLayer = false;	// レイヤーを跨いで当たり判定を行うかどうか

public:
	Object();
	Object(float x, float y, Layer layer, bool pers, Shape shape);
	~Object();

protected:
	virtual void createMorton();

	// getterk
public:
	void init() override final;
	inline Layer getLayer() { return _layer; }
	inline bool getPers() { return _pers; }
	inline float getX() { return _x; }
	inline float getY() { return _y; }
	inline float getXHist() { return _xHist; }
	inline float getYHist() { return _yHist; }
	inline float getDX() { return getX() - getXHist(); }
	inline float getDY() { return getY() - getYHist(); }
	inline bool isMove() { return getDX() != .0f || getDY() != .0f; }
	inline Morton* getMorton() { return _morton; }
	inline Object* getMortonNext() { return _mortonNext; }
	inline Object* getMortonPrev() { return _mortonPrev; }

	// setter
public:
	void setLayer(Layer layer) {}

protected:
	inline void setXHist(float xHist) { _xHist = xHist; }
	inline void setYHist(float yHist) { _yHist = yHist; }

private:
	void setMortonNext(Object* other) { _mortonNext = other; }
	void setMortonPrev(Object* other) { _mortonPrev = other; }
	void updateMortonTree();

public:
	static void setConnector(Connector<Object*, Object*, bool>* connector);

private:
	static void setColliderFunction();

	// Task
public:
	void update() override;
	string toString() override;

	// Editable Task
public:
	void Awake() override;
	void Start() override;
	void Update() override;
	void Draw() override;

	// Wroker
public:
	int drawCompareTo(Worker* other) override;

public:
	bool isCollider(Object* other) {
		bool res = _collision = colliderFunction[(int)this->_shape + (int)other->_shape](this, other);
		return res;
	}
};