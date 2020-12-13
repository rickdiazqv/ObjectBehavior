#pragma once
#include "define.h"
#include "EditableTask.h"
#include "Behavior.h"
#include "Worker.h"

using GameObject = Object*;

class Object : public Worker, public EditableTask, public Behavior<GameObject> {
protected:
	inline static const int PROC_PRIORITY = 5;
	inline static const int DRAW_PRIORITY = 5;

protected:
	inline static const Layer LAYER = Layer::Default;
	inline static const float X = .0f, Y = .0f;
	inline static const float VX = .0f, VY = .0f;
	inline static const float AX = .0f, AY = .0f;
	inline static const bool PERS = false;

private:
	inline static unordered_map <int, TypeBiFunction<Object*, bool>>
		_colliderFunction;
	inline static Connector<Object*, Object*, bool>* _connector = nullptr;
	MouseListener<Object*>* _mouseListener = nullptr;
	static Input* const _input;
	inline static int objCnt = 0;

protected:
	Shape _shape = Shape::Dot;
	Layer _layer = LAYER;
	bool _pers = PERS;

private:
	float _worldX = X, _worldY = Y;
	float _windowX = X, _windowY = Y;
	float _correctionX = .0f, _correctionY = .0f;
	float _worldXHist = _worldX, _worldYHist = _worldY;
	float _windowXHist = _windowX, _windowYHist = _windowY;
	float _worldVX = VX, _worldVY = VY;
	float _windowVX = VX, _windowVY = VY;
	float _worldAX = AX, _worldAY = AY;
	float _windowAX = AX, _windowAY = AY;

protected:
	Morton* _morton = nullptr;
	Object* _mortonNext = nullptr;
	Object* _mortonPrev = nullptr;

private:
	bool _collisionable = true;	// 当たり判定を有効にするか
	bool _collision = false;		// 衝突したかどうか
	bool _oldCollision = _collision;
	bool _crossLayer = false;	// レイヤーを跨いで当たり判定を行うかどうか

private:
	const string _id;

public:
	//Object();
	Object(float x, float y, Layer layer, bool pers,
		Shape shape);
	Object(float x, float y, Layer layer, bool pers,
		Shape shape, int procPriority, int drawPriority);
	~Object();

protected:
	virtual void createMorton();

private:
	void updateMortonTree();
	void updatePosition();

	// getter
public:
	void init() override final;
	inline Layer getLayer() { return _layer; }
	inline bool getPers() { return _pers; }
	inline float getWorldX() { return _worldX; }
	inline float getWorldY() { return _worldY; }
	inline float getWindowX() { return _windowX; }
	inline float getWindowY() { return _windowY; }
	inline float getCorrectionX() { return _correctionX; }
	inline float getCorrectionY() { return _correctionY; }
	inline float getWorldVX() { return _worldVX; }
	inline float getWorldVY() { return _worldVY; }
	inline float getWorldAX() { return _worldAX; }
	inline float getWorldAY() { return _worldAY; }
	inline float getWindowVX() { return _windowVX; }
	inline float getWindowVY() { return _windowVY; }
	inline float getWindowAX() { return _windowAX; }
	inline float getWindowAY() { return _windowAY; }
	inline float getWorldXHist() { return _worldXHist; }
	inline float getWorldYHist() { return _worldYHist; }
	inline float getWindowXHist() { return _windowXHist; }
	inline float getWindowYHist() { return _windowYHist; }
	inline float getWorldDX() { return getWorldX() - getWorldXHist(); }
	inline float getWorldDY() { return getWorldY() - getWorldYHist(); }
	inline float getWindowDX() { return getWindowX() - getWindowXHist(); }
	inline float getWindowDY() { return getWindowY() - getWindowYHist(); }
	inline bool isMove() { return getWorldDX() != .0f || getWorldDY() != .0f; }
	inline virtual string getId() { return _id; }
	inline Morton* getMorton() { return _morton; }
	inline Object* getMortonNext() { return _mortonNext; }
	inline Object* getMortonPrev() { return _mortonPrev; }
	inline bool isCollisionable() { return _collisionable; }
	inline bool isCollision() { return _collision; }
	inline bool isOldCollision() { return _oldCollision; }
	inline bool isCrossLayer() { return _crossLayer; }

private:
	inline MouseListener<Object*>* getMouseListener() { return _mouseListener; }

	// setter
public:
	void setLayer(Layer layer) {}
	inline void setMouseListener(MouseListener<Object*>* mouseListener) {
		if (!_mouseListener) { _mouseListener = mouseListener; }
	}

public:
	inline void setWorldX(float x) {
		_worldX = x;
		setWindowX(getWorldX() + getCorrectionX());
	}
	inline void setWorldY(float y) {
		_worldY = y;
		setWindowY(getWorldY() + getCorrectionY());
	}
	inline void addWorldX(float x) {
		setWorldX(getWorldX() + x);
	}
	inline void addWorldY(float y) {
		setWorldY(getWorldY() + y);
	}
	inline virtual void setWindowX(float x) {
		_windowX = x;
		setCorrectionX(getWindowX() - getWorldX());
	}
	inline virtual void setWindowY(float y) {
		_windowY = y;
		setCorrectionY(getWindowY() - getWorldY());
	}
	inline void addWindowX(float x) {
		setWindowX(getWindowX() + x);
	}
	inline void addWindowY(float y) {
		setWindowY(getWindowY() + y);
	}
	
	inline void setWorldVX(float vx) { _worldVX = vx; }
	inline void setWorldVY(float vy) { _worldVY = vy; }
	inline void addWorldVX(float vx) { setWorldVX(getWorldVX() + vx); }
	inline void addWorldVY(float vy) { setWorldVY(getWorldVY() + vy); }
	inline void setWorldAX(float ax) { _worldAX = ax; }
	inline void setWorldAY(float ay) { _worldAY = ay; }
	inline void addWorldAX(float ax) { setWorldAX(getWorldAX() + ax); }
	inline void addWorldAY(float ay) { setWorldAY(getWorldAY() + ay); }

	inline void setWindowVX(float vx) { _windowVX = vx; }
	inline void setWindowVY(float vy) { _windowVY = vy; }
	inline void addWindowVX(float vx) { setWindowVX(getWindowVX() + vx); }
	inline void addWindowVY(float vy) { setWindowVY(getWindowVY() + vy); }
	inline void setWindowAX(float ax) { _windowAX = ax; }
	inline void setWindowAY(float ay) { _windowAY = ay; }
	inline void addWindowAX(float ax) { setWindowAX(getWindowAX() + ax); }
	inline void addWindowAY(float ay) { setWindowAY(getWindowAY() + ay); }

private:
	inline void setCorrectionX(float x) { _correctionX = x; }
	inline void setCorrectionY(float y) { _correctionX = y; }
	inline void addCorrectionX(float x) {
		setCorrectionX(getCorrectionX() + x);
	}
	inline void addCorrectionY(float y) {
		setCorrectionY(getCorrectionY() + y);
	}

protected:
	inline void setWorldXHist(float xHist) {
		_worldXHist = xHist;
		setWindowXHist(getWorldXHist() + getCorrectionX());
	}
	inline void setWorldYHist(float yHist) {
		_worldYHist = yHist;
		setWindowYHist(getWorldYHist() + getCorrectionY());
	}
	inline void setWindowXHist(float xHist) { _windowXHist = xHist; }
	inline void setWindowYHist(float yHist) { _windowYHist = yHist; }
	inline void setCollisionable(bool collisionable) { _collisionable = collisionable; }
	inline void setCollision(bool collision) { _collision = collision; }
	inline void setOldCollision(bool collision) { _oldCollision = collision; }
	inline void setCrossLayer(bool crossLayer) { _crossLayer = crossLayer; }

private:
	void setMortonNext(Object* other) { _mortonNext = other; }
	void setMortonPrev(Object* other) { _mortonPrev = other; }

public:
	inline static void setConnector(Connector<Object*, Object*, bool>* connector) {
		if (!_connector) { _connector = connector; }
	}
	static void setColliderFunction();

private:
	static void callCollisionMouseEvent(Object* self);
	static void callNonCollisionMouseEvent(Object* self);

public:
	bool isCollider(Object* other, bool skipIfStill);

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
};