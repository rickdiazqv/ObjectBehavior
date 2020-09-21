#include "Worker.h"

Worker::Worker() {
	printfDx("Worker\n");
	if (_connector) { _connector->connect(this); }
	else { 
		_queWorkers.push(this); 
	}
}

Worker::~Worker() {

};

void Worker::sortSelf(Worker* self) {
	Worker* current = getCurrent();
	if (current) {
		int index = !!(self->drawCompareTo(current) >= 0);
		sortSelf(self, current, index);
	}
	setCurrent(self);
}

void Worker::sortSelf(Worker* self, int dir) {
	if (dir <= 0 && sortSelf(self, self, 0)) {
		return;
	}
	if (dir >= 0) {
		sortSelf(self, self, 1);
	}
}

bool Worker::sortSelf(Worker* const self, Worker* const root, const int index) {
	Worker* current = root;
	Worker* inswkr = current;
	int curidx = index;

	while ((current = getNeighbor[index](current)) &&
		(curidx = !!(self->drawCompareTo(current) >= 0) == index)) {
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
}

void Worker::sendWorkers() {
	if (!_connector) { return; }
	while (!_queWorkers.empty()) {
		Worker* self = _queWorkers.front();
		_queWorkers.pop();
		if (!self) { continue; }

		_connector->connect(self);
	}
}

int Worker::compareTo(Worker* other) {
	return drawCompareTo(other);
}

UnaryOperator<Worker*> Worker::getNeighbor[2] = {
	[](Worker* self) {return self->getPrev(); },
	[](Worker* self) {return self->getNext(); }
};

TypeBiConsumer<Worker*> Worker::setNeighbor[2] = {
	// self->_prev‚Éother‚ð‚Â‚È‚°‚é
	[](Worker* self, Worker* other) {
		Worker* selfPrev = self->getPrev();
		Worker* otherPrev = other->getPrev();
		Worker* otherNext = other->getNext();

		// other->_prev->‚Æother->_next‚ð‚Â‚È‚°‚é
		if (otherPrev) { otherPrev->setNext(otherNext); }
		if (otherNext) { otherNext->setPrev(otherPrev); }

		// self->_prev‚Æother‚ð‚Â‚È‚°‚é
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

	// self->_next‚Éother‚ð‚Â‚È‚°‚é
	[](Worker* self, Worker* other) {
		Worker* selfNext = self->getNext();
		Worker* otherPrev = other->getPrev();
		Worker* otherNext = other->getNext();

		// other->_prev->‚Æother->_next‚ð‚Â‚È‚°‚é
		if (otherPrev) { otherPrev->setNext(otherNext); }
		if (otherNext) { otherNext->setPrev(otherPrev); }

		// self->_prev‚Æother‚ð‚Â‚È‚°‚é
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