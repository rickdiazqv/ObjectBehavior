#include "ObjectManager.h"
#include "Object.h"
#include "MortonTree.h"

ObjectManager::ObjectManager() : Worker(PROC_PRIORITY, DRAW_PRIORITY) {
	Object::setConnector(this);
	Object::setColliderFunction();

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
				int pidx = (absId >> 2) + _root[d - 1];
				_cell[idx].setParent(&_cell[pidx]);
			}

			// setChild
			if (d < DEPTH - 1) {
				int cidx = root + n + 4 * i;
				//printfDx("%d:%d-%d ", idx, cidx, cidx + 3);
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

	//printfDx("\n\n");
	//printMortonTree(&_cell[0], 0);
	//printfDx("\n\n");
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
	MortonTree* const root = &_cell[0];
	MortonTree* tree = root;
	MortonTree* parent = nullptr;
	MortonTree* child = tree;
	Object* self = nullptr;
	Object* other = nullptr;

	while (child) {
		// treeの更新
		tree = child;

		// 同セル内で総当り
		self = tree->getHead();
		while (self && (other = self->getMortonNext())) {
			do {
				self->isCollider(other);
			} while (other = other->getMortonNext());
			self = self->getMortonNext();
		}

		// 全ての親と総当り
		parent = tree->getParent();
		for (int d = depth; d > 0; d--, parent = parent->getParent()) {
			self = tree->getHead();

			// 親と総当り
			while (self && (other = parent->getHead())) {
				do {
					self->isCollider(other);
				} while (other = other->getMortonNext());
				self = self->getMortonNext();
			}
		}

		// nodeが葉であれば上位セルに戻る
		if (tree->isLeaf()) {
			tree->resetChildIndex();
		}
		// 下位セルに移動する
		else if (child = tree->getNextChild()) {
			depth++;
			continue;
		}

		// 上位セルに戻る
		parent = tree;
		while (parent != root && (parent = parent->getParent())) {
			depth--;
			if (child = parent->getNextChild()) {
				depth++;
				break;
			}
		}
	}
}

void ObjectManager::updateAt(Object* const self) {
	Morton* morton = self->getMorton();
	const int depth = morton->getDepth();
	const int absId = morton->getAbsMorton();

	if (absId < 0 || CELL <= absId) {
		//printfDx("objmgr con error: out of bounds\n");
		return;
	}

	const int idx = getRoot(depth) + absId;
	MortonTree* const root = &_cell[idx];
	MortonTree* parent = root->getParent();
	Object* other = nullptr;

	// 全ての親と総当り
	for (int d = depth; d > 0; d--, parent = parent->getParent()) {
		if (!(other = parent->getHead())) { continue; }
		// 親と総当り
		do {
			self->isCollider(other);
		} while (other = other->getMortonNext());
	}

	// 同セル内で総当り
	if (other = self->getMortonNext()) {
		do {
			self->isCollider(other);
		} while (other = other->getMortonNext());
	}

	// 子と総当たり
	MortonTree* child = root->getNextChild();
	while (child) {
		// 子と総当たり
		if (other = child->getHead()) {
			do {
				self->isCollider(other);
			} while (other = other->getMortonNext());
		}

		// nodeが葉であれば上位セルに戻る
		if (child->isLeaf()) {
			child->resetChildIndex();
		}
		// 下位セルに移動する
		else if (child = child->getNextChild()) {
			continue;
		}
		else {
			child = child->getParent();
		}

		// 上位セルに戻る
		parent = child;
		while (parent != root && (parent = parent->getParent())) {
			if (child = parent->getNextChild()) {
				break;
			}
		}
	}
}

void ObjectManager::draw() {
	int clr = 0x00ffff;
	int l = 0, c = 0;
	for (int i = 0; i < CELL; i++) {
		Object* obj = _cell[i].getHead();
		if (!obj) { continue; }
		DrawFormatString(0, l * 16, clr, "%3d", i);
		for (int j = 0; obj; j++, obj = obj->getMortonNext()) {
			if (obj == obj->getMortonPrev()) {
				DrawFormatString(50 + j * 200, l * 16, clr, "error");
				break;
			}

			//DrawFormatString(50 + j * 200, l * 16, clr, "(%5.1f, %5.1f)", obj->getX(), obj->getY());
			DrawFormatString(50 + j * 200, l * 16, clr, "%s(%d)", obj->getId().c_str(), obj->getMorton()->getAbsMorton());
			c++;
		}
		l++;
	}
	DrawFormatString(0, 800, 0xffffff, "n_obj:%d", c);
	if (c > 9) {
		int a = 0;
	}
}

Object* ObjectManager::connect(Object* self) {
	Morton* morton = self->getMorton();
	int depth = morton->getDepth();
	int absId = morton->getAbsMorton();
	Object* res = nullptr;

	if (absId < 0 || CELL <= absId) {
		//printfDx("objmgr con error: out of bounds\n");
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

	// isLeafの更新
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
	int absId = morton->getOldAbs();

	if (absId < 0 || CELL <= absId) {
		//printfDx("objmgr dis error: out of bounds\n");
		return false;
	}

	int idx = getRoot(morton->getOldDep()) + absId;
	//printfDx("cell:%d, idx:%d\n", CELL, index);

	if (!_cell[idx].getHead()) {
		//printfDx("objmgr dis error: cell is null\n");
		return false;
	}

	Object* current = _cell[idx].getHead();
	MortonTree* tree = &_cell[idx];
	do {
		if (current != self) {
			current = current->getMortonNext();
			continue;
		}

		if (!self->getMortonPrev()) {
			tree->setHead(self->getMortonNext());
			// ObjectがなくなったらTreeを切断する
			if (tree->getParent() && !tree->getHead()) {
				for (int i = 0; i < 4; i++) {
					if (tree->getChild(i)) { return true; }
				}
				tree->getParent()->setIsLeaf(true);
			}
		}
		return true;
	} while (current);

	//printfDx("objmgr dis error: self is not found\n");
	if (self->getX() == 222.f) {
		int a = 0;
	}

	return false;
}

void ObjectManager::printMortonTree(MortonTree* tree, int depth) {
	if (!tree) { return; }
	string space = " ";
	//for (int i = 0; i < depth; i++) { space += "　"; }
	printfDx("%d%s", tree->index, space.c_str());

	printMortonTree(tree->getNextChild(), depth + 1);
	printMortonTree(tree->getNextChild(), depth + 1);
	printMortonTree(tree->getNextChild(), depth + 1);
	printMortonTree(tree->getNextChild(), depth + 1);
	tree->resetChildIndex();
}