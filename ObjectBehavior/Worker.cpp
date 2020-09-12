#include "Worker.h"

Worker::Worker(compare<Task*> comp, initialize<Task*> init, const char* params, ...) {
	printfDx("Worker\n");
	if (init) {
		va_list args;
		va_start(args, params);
		init(this, args); 
	}
	if (connector) { connector->connect(this, comp); }
}

Worker::~Worker() {

};

void Worker:: setConnector(Connector<Task*>* con) {
	if (connector) { return; }
	connector = con;
	printfDx("Task::setConnector\n");
}