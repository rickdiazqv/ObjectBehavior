#include "TaskManager.h"

TaskManager::TaskManager() {
	printfDx("TaskManager\n");
	Worker::setConnector(this);
}

TaskManager::~TaskManager() {

}

void TaskManager::update() {
	for (auto task = tasks.begin(); task != tasks.end(); task++) {
		(*task)->update();
	}
}

void TaskManager::draw() {
	for (auto task = tasks.begin(); task != tasks.end(); task++) {
		(*task)->draw();
	}
}

void TaskManager::connect(Task* obj) {
	tasks.push_back(obj);
}
