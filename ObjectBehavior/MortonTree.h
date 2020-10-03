#pragma once
#include "define.h"

class MortonTree {
public:
	int index = 0;

private:
	Object* _head = nullptr;
	MortonTree* _parent = nullptr;
	MortonTree* _child[4] = { nullptr, nullptr, nullptr, nullptr };
	MortonTree* _prev = nullptr;
	MortonTree* _next = nullptr;
	bool _isLeaf = true;
	int _childIndex = 0;

public:
	MortonTree();
	~MortonTree();

public:
	Object* getHead() { return _head; }
	MortonTree* getParent() { return _parent; }
	MortonTree* getChild(int index) { return _child[index]; }
	MortonTree* getPrev() { return _prev; }
	MortonTree* getNext() { return _next; }
	bool isLeaf() { return _isLeaf; }
	MortonTree* getNextChild() {
		if (_childIndex == 4) {
			_childIndex = 0;
			return nullptr;
		}
		return getChild(_childIndex++);
	}

public:
	void setHead(Object* obj) { _head = obj; }
	void setParent(MortonTree* tree) { _parent = tree; }
	void setChild(MortonTree* tree, int index) { _child[index] = tree; }
	void setPrev(MortonTree* tree) { _prev = tree; }
	void setNext(MortonTree* tree) { _next = tree; }
	void setIsLeaf(bool isLeaf) { _isLeaf = isLeaf; }
	void resetChildIndex() { _childIndex = 0; }
};