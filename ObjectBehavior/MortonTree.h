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
	inline Object* getHead() { return _head; }
	inline MortonTree* getParent() { return _parent; }
	inline MortonTree* getChild(int index) { return _child[index]; }
	inline MortonTree* getPrev() { return _prev; }
	inline MortonTree* getNext() { return _next; }
	inline bool isLeaf() { return _isLeaf; }
	inline MortonTree* getNextChild() {
		if (_childIndex == 4) {
			_childIndex = 0;
			return nullptr;
		}
		return getChild(_childIndex++);
	}

public:
	inline void setHead(Object* obj) { _head = obj; }
	inline void setParent(MortonTree* tree) { _parent = tree; }
	inline void setChild(MortonTree* tree, int index) { _child[index] = tree; }
	inline void setPrev(MortonTree* tree) { _prev = tree; }
	inline void setNext(MortonTree* tree) { _next = tree; }
	inline void setIsLeaf(bool isLeaf) { _isLeaf = isLeaf; }
	inline void resetChildIndex() { _childIndex = 0; }
};