#include "header.h"

/*Object::Object() : Object(X, Y, LAYER, PERS, Shape::Dot) {

}*/
Object::Object(float x, float y, Layer layer, bool pers, Shape shape) : Object(x, y, layer, pers, shape, PROC_PRIORITY, DRAW_PRIORITY) {

}

Object::Object(float x, float y, Layer layer, bool pers, Shape shape, int procPriority, int drawPriority) : _shape(shape), Worker(procPriority, procPriority) {
	//printfDx("Object\n");
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
	this->setMortonPrev(nullptr);
	this->setMortonNext(nullptr);
	Object* tail = _connector->connect(this);
	if (tail) {
		tail->setMortonNext(this);
		this->setMortonPrev(tail);
	}
}

void Object::setConnector(Connector<Object*, Object*, bool>* connector) {
	if (_connector) { return; }
	_connector = connector;
	//printfDx("Object::setConnector\n");

	setColliderFunction();
}

void Object::update() {
	_collision = false;
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
		int a = this->getDrawPriority();
		int b = other->getDrawPriority();
		int c = this->getDrawPriority() - other->getDrawPriority();
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

	colliderFunction[d + d] = [](Object* self, Object* other) {
		return self->_x == other->_x && self->_y == other->_y;
	};

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

	colliderFunction[d + c] = [](Object* self, Object* other) {
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
			pow(dot->_x - cir->getX(), 2) +
			pow(dot->_y - cir->getY(), 2)
			<= pow(cir->getRadius(), 2);
	};

	colliderFunction[r + r] = [](Object* self, Object* other) {
		RectangleObject* rects = nullptr;
		RectangleObject* recto = nullptr;

		if (!(rects = dynamic_cast<RectangleObject*>(self))) {
			return false;
		}
		if (!(recto = dynamic_cast<RectangleObject*>(other))) {
			return false;
		}

		return abs(rects->_x - recto->_x) <
			(rects->getWidth() + recto->getWidth()) * .5f &&
			abs(rects->_y - recto->_y) <
			(rects->getHeight() + recto->getHeight()) * .5f;
	};

	colliderFunction[r + c] = [](Object* self, Object* other) {
		RectangleObject* rect = (RectangleObject*)self;
		CircleObject* cir = (CircleObject*)other;

		if (rect = dynamic_cast<RectangleObject*>(self)) {
			cir = dynamic_cast<CircleObject*>(other);
		}
		else if (rect = dynamic_cast<RectangleObject*>(other)) {
			cir = dynamic_cast<CircleObject*>(self);
		}
		if (!rect || !cir) { return false; }

		float l = rect->getLeft(), t = rect->getTop();
		float r = l + rect->getWidth(), b = t + rect->getHeight();
		float& x = cir->_x, & y = cir->_y;
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


	colliderFunction[c + c] = [](Object* self, Object* other) {
		CircleObject* cirs = nullptr;
		CircleObject* ciro = nullptr;

		if (!(cirs = dynamic_cast<CircleObject*>(self))) {
			return false;
		}
		if (!(ciro = dynamic_cast<CircleObject*>(other))) {
			return false;
		}

		return
			pow(cirs->_x - ciro->_x, 2) +
			pow(cirs->_y - ciro->_y, 2) <
			pow(cirs->getRadius() + ciro->getRadius(), 2);
	};
}