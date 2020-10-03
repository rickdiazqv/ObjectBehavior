#include "ObjectManager.h"
#include "Object.h"
#include "MortonTree.h"

ObjectManager::ObjectManager() : Worker(PROC_PRIORITY, DRAW_PRIORITY) {
	_cell = new MortonTree[CELL];
	_n = new int[DEPTH];
	_root = new int[DEPTH];

	for (int i = 0; i < CELL; i++) { _cell[i].index = i; }

	for (int d = 0; d < DEPTH; d++) {
		int n = _n[d] = pow(4, d);
		int root = _root[d] = (n - 1) / 3;
		for (int i = 0, idx = root; i < n; i++, idx++) {
			int absId = idx - root;

			// setParent
			if (d > 0) {
				int pidx = absId >> 2 + _root[d - 1];
				_cell[idx].setParent(&_cell[pidx]);
			}

			// setChild
			if (d < DEPTH - 1) {
				int cidx = root + n + 4 * i;
				printfDx("%d:%d-%d ", idx, cidx, cidx + 3);
				for (int j = 0, c = cidx; j < 4; j++, c++) {
					_cell[idx].setChild(&_cell[c], j);
				}
			}

			// setPrev
			if (idx % 4) {
				_cell[idx].setPrev(&_cell[idx - 1]);
			}
			// setNext
			if (idx % 4 != 3) {
				_cell[idx].setNext(&_cell[idx + 1]);
			}
		}
	}
	Object::setConnector(this);

	printfDx("\n\n");
	printMortonTree(&_cell[0], 0);
	printfDx("\n\n");
}

ObjectManager::~ObjectManager() {
	delete[] _cell;
	delete[] _n;
	delete[] _root;
}

void ObjectManager::update() {
	int depth = 0;
	int idx = 0;
	int sq = 0;
	MortonTree* tree = &_cell[0];
	MortonTree* parent = nullptr;
	MortonTree* child = tree;

	while (child) {
		// tree�̍X�V
		tree = child;

		// ���Z�����ő�����
		Object* self = tree->getHead();
		Object* other = nullptr;
		while (self && (other = self->getMortonNext())) {
			do {
				self->isCollider(other);

			} while (other = other->getMortonNext());
			self = self->getMortonNext();
		}

		// �S�Ă̐e�Ƒ�����
		parent = tree->getParent();
		for (int d = depth; d > 0; d--,
			parent = parent->getParent()) {

			self = tree->getHead();
			other = parent->getHead();

			// �e�Ƒ�����
			while (self && other) {
				do {
					self->isCollider(other);
				} while (other = other->getMortonNext());
				self = self->getMortonNext();
			}
		}

		// ���ʃZ���Ɉړ�����
		child = tree->getNextChild();
		if (tree->isLeaf()) {
			tree->resetChildIndex();
		}
		else if (child) { continue; }

		// ��ʃZ���ɖ߂�
		parent = tree;
		while (parent = parent->getParent()) {
			if (child = parent->getNextChild()) {
				break;
			}
		}
	}
}

Object* ObjectManager::connect(Object* self) {
	Morton* morton = self->getMorton();
	int depth = morton->getDepth();
	int absId = morton->getAbsMorton();
	Object* res = nullptr;

	if (absId < 0 || CELL <= absId) {
		printfDx("objmgr con error\n");
		return nullptr;
	}

	int idx = getRoot(depth) + absId;
	//printfDx("cell:%d, idx:%d\n", CELL, index);

	if (!_cell[idx].getHead()) {
		_cell[idx].setHead(self);
	}
	else {
		Object* current = _cell[idx].getHead();
		while (current->getMortonNext()) {
			current = current->getMortonNext();
		}
		res = current;
	}

	// isLeaf�̍X�V
	MortonTree* tree = &_cell[idx];
	MortonTree* parent = nullptr;
	bool isLeaf = true;
	for (int i = 0; i < 4; i++) {
		if (tree->getChild(i)) {
			isLeaf = false;
			break;
		}
	}
	if (isLeaf) {
		tree->setIsLeaf(true);
	}
	for (int i = 0; i < depth; i++) {
		parent = tree->getParent();
		parent->setIsLeaf(false);
	}

	return res;
}

bool ObjectManager::disconnect(Object* self) {
	Morton* morton = self->getMorton();
	int absId = morton->getAbsMorton();

	if (absId < 0 || CELL <= absId) {
		printfDx("objmgr dis error: out of bound\n");
		return false;
	}

	int index = getRoot(morton->getDepth()) + absId;
	//printfDx("cell:%d, idx:%d\n", CELL, index);

	if (!_cell[index].getHead()) {
		//printfDx("objmgr dis error: cell is null\n");
		return false;
	}

	Object* current = _cell[index].getHead();
	MortonTree* tree = &_cell[index];
	do {
		if (current != self) {
			current = current->getMortonNext();
			continue;
		}

		if (!self->getMortonPrev()) {
			tree->setHead(self->getMortonNext());
			// Object���Ȃ��Ȃ�����Tree��ؒf����
			if (tree->getParent() && !tree->getHead()) {
				for (int i = 0; i < 4; i++) {
					if (tree->getChild(i)) { return true; }
				}
				tree->getParent()->setIsLeaf(true);
			}
		}
		return true;
	} while (current && current->getMortonNext());

	//printfDx("objmgr dis error: self is not found\n");

	return false;
}

void ObjectManager::printMortonTree(MortonTree* tree, int depth) {
	if (!tree) { return; }
	string space = " ";
	//for (int i = 0; i < depth; i++) { space += "�@"; }
	printfDx("%d%s", tree->index, space.c_str());

	printMortonTree(tree->getNextChild(), depth + 1);
	printMortonTree(tree->getNextChild(), depth + 1);
	printMortonTree(tree->getNextChild(), depth + 1);
	printMortonTree(tree->getNextChild(), depth + 1);
	tree->resetChildIndex();
}