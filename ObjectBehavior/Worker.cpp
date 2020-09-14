#include "Worker.h"

Worker::Worker(Comparator<Worker*> compare) {
	printfDx("Worker\n");
	if (connector) { connector->connect(this); }
	_compare = compare;
}

Worker::~Worker() {

};

void Worker:: setConnector(Connector<Worker*>* con) {
	if (connector) { return; }
	connector = con;
	printfDx("Task::setConnector\n");
}

int Worker::compareTo(Worker* other) {
	return _compare ? _compare(this, other) : 0;
}