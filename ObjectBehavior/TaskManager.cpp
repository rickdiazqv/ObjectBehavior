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
	//clsDx();
	for (auto task = tasks.begin(); task != tasks.end(); task++) {
		(*task)->draw();
	}
}

void TaskManager::connect(Task* self, compare<Task*> comp) {
	printfDx("connect\n");

	if (tasks.empty()) {
		printfDx("empty\n");
		tasks.push_back(self);
		printfDx("check tasks\n");
		for (auto task = tasks.begin(); task != tasks.end(); task++) {
			printfDx("%x, ", *task);
			printfDx((*task)->toString().c_str());
			printfDx("\n");
		}
		printfDx("size:%d\n", tasks.size());
		printfDx("end check\n\n");
		return;
	}
	if (!comp) {
		printfDx("comp is null\n");
		tasks.push_front(self);
		return;
	}

	for (auto task = tasks.rbegin(); task != tasks.rend(); task++) {
		if (comp(self, *task) < 0) { continue; }
		tasks.insert(task.base(), self);
		break;
	}
	printfDx("check tasks\n");
	for (auto task = tasks.begin(); task != tasks.end(); task++) {
		printfDx("%x, ", *task);
		printfDx((*task)->toString().c_str());
		printfDx("\n");
	}
	printfDx("size:%d\n", tasks.size());
	printfDx("end check\n\n");
}