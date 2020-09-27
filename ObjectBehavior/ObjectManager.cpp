#include "ObjectManager.h"
#include "Object.h"
ObjectManager::ObjectManager() :Worker(PROC_PRIORITY, DRAW_PRIORITY) {
	_cell = new Object * [CELL];
	for (int i = 0; i < CELL; i++) {
		_cell[i] = nullptr;
	}
	Object::setConnector(this);
}

ObjectManager::~ObjectManager() {
	delete[] _cell;
}

void ObjectManager::update() {

}


Object* ObjectManager::connect(Object* self) {
	Morton* morton = self->getMorton();
	int absId = morton->getAbsMorton();

	if (absId < 0 || CELL <= absId) {
		printfDx("objmgr con error\n");
		return nullptr;
	}

	int index = (int(pow(4, morton->getDepth())) - 1) / 3 +
		morton->getAbsMorton();
	printfDx("cell:%d, idx:%d\n", CELL, index);

	if (!_cell[index]) {
		_cell[index] = self;
		return nullptr;
	}

	Object* current = _cell[index];
	while (current->getMortonNext()) {
		current = current->getMortonNext();
	}

	return current;
}

bool ObjectManager::disconnect(Object* self) {
	Morton* morton = self->getMorton();
	int absId = morton->getAbsMorton();

	if (absId < 0 || CELL <= absId) {
		printfDx("objmgr dis error: out of bound\n");
		return false;
	}

	int index = (int(pow(4, morton->getDepth())) - 1) / 3 +
		morton->getAbsMorton();
	printfDx("cell:%d, idx:%d\n", CELL, index);
	
	if (!_cell[index]) {
		//printfDx("objmgr dis error: cell is null\n");
		return false; 
	}

	Object* current = _cell[index];
	do {
		if (current == self) {
			if (!self->getMortonPrev()) {
				_cell[index] = self->getMortonNext();
			}
			return true;
		}
		current = current->getMortonNext();
	} while (current->getMortonNext());

	//printfDx("objmgr dis error: self is not found\n");

	return false;
}