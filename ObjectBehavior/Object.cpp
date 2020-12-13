#include "header.h"
#include "Input.h"
#include "Object.h"

Input* const Object::_input = Input::getInstance();

/*Object::Object() : Object(X, Y, LAYER, PERS, Shape::Dot) {

}*/
Object::Object(float x, float y, Layer layer, bool pers, Shape shape) : 
	Object(x, y, layer, pers, shape, PROC_PRIORITY, DRAW_PRIORITY) {

}

Object::Object(
	float x, float y, Layer layer, bool pers, Shape shape, 
	int procPriority, int drawPriority) : 
	_shape(shape), 
	Worker(procPriority, procPriority) {
	//printfDx("Object\n");
	_layer = layer;
	_pers = pers;

	setWorldX(x);
	setWorldY(y);
	setWorldXHist(getWorldX());
	setWorldYHist(getWorldY());

	Awake();
}

Object::~Object() {
	delete _morton;
}

void Object::createMorton() {
	_morton = new Morton(this);
}

void Object::init() {
	if (!_morton) {
		if (instanceof<Input, Object>(this)) {
			int a = 0;
		}
		createMorton();
		_morton->updateMorton();
	}
	updateMortonTree();
}

void Object::updateMortonTree() {
	if (_connector->disconnect(this)) {
		Object* prev = getMortonPrev();
		Object* next = getMortonNext();
		if (prev) { prev->setMortonNext(next); }
		if (next) { next->setMortonPrev(prev); }
	}
	this->setMortonPrev(nullptr);
	this->setMortonNext(nullptr);
	Object* tail = _connector->connect(this);
	if (tail) {
		tail->setMortonNext(this);
		this->setMortonPrev(tail);
	}
}

void Object::updatePosition() {

}

void Object::update() {
	setOldCollision(isCollision());
	setCollision(false);

	setWorldXHist(getWorldX());
	setWorldYHist(getWorldY());

	float worldVX = getWorldVX();
	float worldVY = getWorldVY();
	bool worldMoveX = worldVX != .0f;
	bool worldMoveY = worldVX != .0f;

	if (worldMoveX) {
		addWorldX(worldVX);
	}
	if (worldMoveY) {
		addWorldY(worldVY);
	}

	float windowVX = getWindowVX();
	float windowVY = getWindowVY();
	bool windowMoveX = windowVX != .0f;
	bool windowMoveY = windowVY != .0f;

	if (windowMoveX) {
		addWindowX(windowVX);
	}
	if (windowMoveY) {
		addWindowY(windowVY);
	}

	float worldAX = getWorldAX();
	float worldAY = getWorldAY();
	bool worldMoveVX = worldAX != .0f;
	bool worldMoveVY = worldAX != .0f;

	if (worldMoveVX) {
		addWorldVX(getWorldAX());
	}
	if (worldMoveVY) {
		addWorldVY(getWorldAY());
	}

	float windowAX = getWindowAX();
	float windowAY = getWindowAY();
	bool windowMoveVX = windowAX != .0f;
	bool windowMoveVY = windowAX != .0f;

	if (windowMoveVX) {
		addWindowVX(getWindowAX());
	}
	if (windowMoveVY) {
		addWindowVY(getWindowAY());
	}

	if (!worldMoveX && !worldMoveY) { return; }

	float dx = getWorldDX(), dy = getWorldDY();

	if (dy != .0f) { sortSelf(this, dy >= .0f ? 1 : -1); }

	int depthHist = _morton->getDepth();
	int absIdHist = _morton->getAbsMorton();
	_morton->updateMorton();
	int depth = _morton->getDepth();
	int absId = _morton->getAbsMorton();

	if (depth == depthHist && absId == absIdHist) { return; }
	updateMortonTree();
}

string Object::toString() {
	ostringstream oss;
	oss << "Layer: " << int(getLayer()) << ", pers: " << getPers() <<
		", (" << getWorldX() << ", " << getWorldY() << ")" <<
		", (" << getWindowX() << ", " << getWindowY() << ")";
	return oss.str();
}

void Object::Awake() {

}

void Object::Start() {

}

void Object::Update() {

}

void Object::Draw() {

}

int Object::drawCompareTo(Worker* other) {
	Object* otr = dynamic_cast<Object*>(other);
	int comp = 0;
	if (!otr) {
		//printfDx("can not cast\n");
		return this->getDrawPriority() - other->getDrawPriority();
	}

	comp = int(this->getLayer()) - int(otr->getLayer());
	if (comp == 0) {
		bool pslf = this->getPers();
		bool potr = otr->getPers();

		if (pslf && potr) {
			comp = (this->getWorldY() - otr->getWorldY()) >= .0f ? 1 : -1;
		}
		else if (pslf && !potr) {
		}
		else if (!pslf && potr) {
			comp = -1;
		}
		else {

		}
	}

	return comp;
}

void Object::setColliderFunction() {
	if (_colliderFunction.size() > 0) { return; }

	int d = (int)Shape::Dot;
	int t = (int)Shape::Tryangle;
	int r = (int)Shape::Rectangle;
	int c = (int)Shape::Circle;

	_colliderFunction[0] = nullptr;

	_colliderFunction[d + d] = [](Object* self, Object* other) {
		return
			self->getWorldX() == other->getWorldX() &&
			self->getWorldY() == other->getWorldY();
	};

	_colliderFunction[d + r] = [](Object* self, Object* other) {
		Object* dot = nullptr;
		RectangleObject* rect = nullptr;

		if (rect = dynamic_cast<RectangleObject*>(self)) {
			dot = other;
		}
		else if (rect = dynamic_cast<RectangleObject*>(other)) {
			dot = self;
		}
		else {
			return false;
		}

		float x = dot->getWorldX(), y = dot->getWorldY();
		float l = rect->getWorldLeft(), t = rect->getWorldTop();
		return l <= x && x < l + rect->getWidth() &&
			t <= y && y < t + rect->getHeight();
	};

	_colliderFunction[d + c] = [](Object* self, Object* other) {
		Object* dot = nullptr;
		CircleObject* cir = nullptr;

		if (cir = dynamic_cast<CircleObject*>(self)) {
			dot = other;
		}
		else if (cir = dynamic_cast<CircleObject*>(other)) {
			dot = self;
		}
		else {
			return false;
		}

		return
			pow(dot->getWorldX() - cir->getWorldX(), 2) +
			pow(dot->getWorldY() - cir->getWorldY(), 2)
			<= pow(cir->getRadius(), 2);
	};

	_colliderFunction[r + r] = [](Object* self, Object* other) {
		RectangleObject* rects = nullptr;
		RectangleObject* recto = nullptr;

		if (!(rects = dynamic_cast<RectangleObject*>(self))) {
			return false;
		}
		if (!(recto = dynamic_cast<RectangleObject*>(other))) {
			return false;
		}

		return abs(rects->getWorldX() - recto->getWorldX()) <
			(rects->getWidth() + recto->getWidth()) * .5f &&
			abs(rects->getWorldY() - recto->getWorldY()) <
			(rects->getHeight() + recto->getHeight()) * .5f;
	};

	_colliderFunction[r + c] = [](Object* self, Object* other) {
		RectangleObject* rect = (RectangleObject*)self;
		CircleObject* cir = (CircleObject*)other;

		if (rect = dynamic_cast<RectangleObject*>(self)) {
			cir = dynamic_cast<CircleObject*>(other);
		}
		else if (rect = dynamic_cast<RectangleObject*>(other)) {
			cir = dynamic_cast<CircleObject*>(self);
		}
		if (!rect || !cir) { return false; }

		float l = rect->getWorldLeft(), t = rect->getWorldTop();
		float r = l + rect->getWidth(), b = t + rect->getHeight();
		float x = cir->getWorldX(), y = cir->getWorldY();
		float rad = cir->getRadius();
		float radSq = cir->getRadSq();

		if (x < l - rad || r + rad < x ||
			y < t - rad || b + rad < y) {
			return false;
		}
		if (x < l && y < t &&
			!(pow(l - x, 2) + pow(t - y, 2) < radSq)) {
			return false;
		}
		if (r < x && y < t &&
			!(pow(r - x, 2) + pow(t - y, 2) < radSq)) {
			return false;
		}
		if (x < l && b < y &&
			!(pow(l - x, 2) + pow(b - y, 2) < radSq)) {
			return false;
		}
		if (r < x && b < y &&
			!(pow(r - x, 2) + pow(b - y, 2) < radSq)) {
			return false;
		}

		return true;
	};


	_colliderFunction[c + c] = [](Object* self, Object* other) {
		CircleObject* cirs = nullptr;
		CircleObject* ciro = nullptr;

		if (!(cirs = dynamic_cast<CircleObject*>(self))) {
			return false;
		}
		if (!(ciro = dynamic_cast<CircleObject*>(other))) {
			return false;
		}

		return
			pow(cirs->getWorldX() - ciro->getWorldX(), 2) +
			pow(cirs->getWorldY() - ciro->getWorldY(), 2) <
			pow(cirs->getRadius() + ciro->getRadius(), 2);
	};
}

void Object::callCollisionMouseEvent(Object* self) {
	MouseListener<Object*>* listener = self->getMouseListener();
	int left = Input::LEFT;

	// クリックしたとき
	if (_input->isMouseDown(left)) {
		listener->onMouseDown(left, self);
	}
	// クリックを離したとき
	else if (_input->isMouseUp(left)) {
		listener->onClick(self);
	}

	// オブジェクトに侵入したとき
	if (!self->isOldCollision()) {
		listener->onMouseEntry(self);
	}
}

void Object::callNonCollisionMouseEvent(Object* self) {
	MouseListener<Object*>* listener = self->getMouseListener();

	// オブジェクトから離れたとき
	if (self->isOldCollision()) {
		listener->onMouseExit(self);
	}
}

bool Object::isCollider(Object* other, bool skipIfStill) {
	if (!this->isCollisionable() || !other->isCollisionable()) { return false; }

	//bool skip = skipIfStill && !this->isMove() && !other->isMove();
	bool res = _colliderFunction
		[(int)this->_shape + (int)other->_shape](this, other);

	if (res && (this->getId() == "rect4" || other->getId() == "rect4")) {
		int a = 0;
	}

	if (!this->isCollision()) {
		this->setCollision(res);
	}
	if (!other->isCollision()) {
		other->setCollision(res);
	}

	/*if (skip) {
		this->setCollision(this->isOldCollision());
		other->setCollision(other->isOldCollision());
		res = this->isCollision() && other->isCollision();
	}
	else {
		res = _colliderFunction
			[(int)this->_shape + (int)other->_shape](this, other);
		this->setCollision(res);
		other->setCollision(res);
	}*/


	Object* input = nullptr, * obj = nullptr;
	if (this == _input) { input = this; obj = other; }
	else if (other == _input) { input = other; obj = this; }

	if (input && obj && obj->getMouseListener()) {
		if (res) { callCollisionMouseEvent(obj); }
		else { callNonCollisionMouseEvent(obj); }
	}

	return res;
}