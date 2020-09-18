#include "Worker.h"

Worker::Worker(Comparator<Worker*> procCompare, Comparator<Worker*> drawCompare) {
	printfDx("Worker\n");
	if (_connector) { _connector->connect(this); }
	if (procCompare) { _procCompare = procCompare; }
	if (drawCompare) { _drawCompare = drawCompare; }
}

Worker::~Worker() {

};

void Worker::sortSelf(Worker* self) {
	Worker* current = getCurrent();
	if (current) {
		int index = !!(self->_drawCompare(self, current) >= 0);
		sortSelf(self, current, index);
	}
	setCurrent(self);
}

void Worker::sortSelf(Worker* self, int dir) {
	if (dir <= 0 && sortSelf(self, self, 0)) {
		return;
	}
	sortSelf(self, self, 1);
}

bool Worker::sortSelf(Worker* const self, Worker* const root, const int index) {
	Worker* current = root;
	Worker* inswkr = current;
	int curidx = index;

	while ((current = getNeighbor[index](current)) &&
		(curidx = !!(self->_drawCompare(self, current) >= 0) == index)) {
		inswkr = current;
	}
	if (inswkr == self) { return false; }

	inswkr->setNeighbor[index](inswkr, self);
	if (!inswkr->getPrev()) {
		setDrawHead(inswkr);
	}

	return true;
}

void Worker::setConnector(Connector<Worker*>* connector) {
	if (_connector) { return; }
	_connector = connector;
	printfDx("Task::setConnector\n");

	// 
}

int Worker::compareTo(Worker* other) {
	return _drawCompare ? _drawCompare(this, other) : 0;
}

UnaryOperator<Worker*> Worker::getNeighbor[2] = {
	[](Worker* self) {return self->getPrev(); },
	[](Worker* self) {return self->getNext(); }
};

TypeBiConsumer<Worker*> Worker::setNeighbor[2] = {
	// self->_prev��other���Ȃ���
	[](Worker* self, Worker* other) {
		Worker* selfPrev = self->getPrev();
		Worker* otherPrev = other->getPrev();
		Worker* otherNext = other->getNext();

		// other->_prev->��other->_next���Ȃ���
		if (otherPrev) { otherPrev->setNext(otherNext); }
		if (otherNext) { otherNext->setPrev(otherPrev); }

		// self->_prev��other���Ȃ���
		if (selfPrev) {
			selfPrev->setNext(other);
			other->setPrev(selfPrev);
		}
		else {
			other->setPrev(nullptr);
		}
		self->setPrev(other);
		other->setNext(self);
	},

	// self->_next��other���Ȃ���
	[](Worker* self, Worker* other) {
		Worker* selfNext = self->getNext();
		Worker* otherPrev = other->getPrev();
		Worker* otherNext = other->getNext();

		// other->_prev->��other->_next���Ȃ���
		if (otherPrev) { otherPrev->setNext(otherNext); }
		if (otherNext) { otherNext->setPrev(otherPrev); }

		// self->_prev��other���Ȃ���
		if (selfNext) {
			selfNext->setPrev(other);
			other->setNext(selfNext);
		}
		else {
			other->setNext(nullptr);
		}
		self->setNext(other);
		other->setPrev(self);
	}
};