#include "Object.h"
#include "Morton.h"
#include "RectangleObject.h"

Object::Object() : Object(X, Y, LAYER, PERS) {

}

Object::Object(float x, float y, Layer layer, bool pers) : Worker(PROC_PRIORITY, DRAW_PRIORITY) {
	printfDx("Object\n");
	_layer = layer;
	_pers = pers;

	_x = x;
	_y = y;
	setXHist(getX());
	setYHist(getY());

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
	Object* tail = _connector->connect(this);
	if (tail) {
		tail->setMortonNext(this);
		this->setMortonPrev(tail);
	}
}

void Object::setConnector(Connector<Object*, Object*, bool>* connector) {
	if (_connector) { return; }
	_connector = connector;
	printfDx("Object::setConnector\n");

	setColliderFunction();
}

void Object::update() {
	bool move = vx != .0f || vy != .0f;

	setXHist(getX());
	setYHist(getY());

	if (move) {
		_x += vx;
		_y += vy;
	}

	vx += ax;
	vy += ay;

	if (!move) { return; }

	float dx = getDX(), dy = getDY();
	if (dy != .0f) { sortSelf(this, dy >= .0f ? 1 : -1); }

	if (_y >= winy - 25) {
		int a = 0;
	}
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
	oss << "Layer: " << int(getLayer()) << ", pers: " << getPers() << ", (" << _x << ", " << _y << ")";
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
			comp = (this->getY() - otr->getY()) >= .0f ? 1 : -1;
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
	int d = (int)Shape::Dot;
	int t = (int)Shape::Tryangle;
	int r = (int)Shape::Rectangle;
	int c = (int)Shape::Circle;

	colliderFunction[d + r] = [](Object* self, Object* other) {
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

		float& x = dot->_x, & y = dot->_y;
		float l = rect->getLeft(), t = rect->getTop();
		return l <= x && x < l + rect->getWidth() &&
			t <= y && y < t + rect->getHeight();
	};
}