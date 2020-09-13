#include "Worker.h"

Worker::Worker(compare<Worker*> comp) {
	printfDx("Worker\n");
	if (connector) { connector->connect(this); }
	_comp = comp;
}

Worker::~Worker() {

};

void Worker:: setConnector(Connector<Worker*>* con) {
	if (connector) { return; }
	connector = con;
	printfDx("Task::setConnector\n");
}

int Worker::compareTo(Worker* other) {
	return _comp ? _comp(this, other) : 0;
}