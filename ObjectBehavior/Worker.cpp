#include "Worker.h"

Worker::Worker() {
	if (connector) { connector->connect(this); }
}

Worker::~Worker() {

}

void Worker::setConnector(Connector<Task*>* con) {
	if (connector) { return; }
	connector = con;
	printfDx("Task::setConnector\n");
}
