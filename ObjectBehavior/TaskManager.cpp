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
	// 描画順の調整 pers == trueのオブジェクトが優先的に前面に描画される
	for (auto task = tasks.begin(); task != tasks.end(); task++) {
		//if (self->compareTo(*task) < 0) { continue; }
	}
	// queueのオブジェクトをlistに追加
	receive();
}

void TaskManager::draw() {
	//clsDx();
	int i = 0;
	for (auto task = tasks.begin(); task != tasks.end(); task++) {
		(*task)->draw();
		DrawFormatString(300, 100 + i * 20, 0xffffff, (*task)->toString().c_str());
		i++;
	}
}

void TaskManager::connect(Worker* self) {
	printfDx("connect\n");
	if (!self) { return; }
	newTasks.push(self);
	printfDx("queue size:%d\n", newTasks.size());
}

void TaskManager::receive() {
	while (!newTasks.empty()) {
		printfDx("while ");
		Worker* self = newTasks.front();
		newTasks.pop();
		if (!self) { continue; }

		if (tasks.empty()) {
			printfDx("empty\n");
			tasks.push_back(self);
			continue;
		}
		if (!self->comparable()) {
			printfDx("comp is null\n");
			tasks.push_front(self);
			continue;
		}

		int size = tasks.size();
		for (auto task = tasks.rbegin(); task != tasks.rend(); task++) {
			if (self->compareTo(*task) < 0) { continue; }
			printfDx("insert\n");
			tasks.insert(task.base(), self);
			break;
		}
		if (tasks.size() == size) { tasks.push_front(self); }
	}
	//printfDx("check tasks\n");
	//for (auto task = tasks.begin(); task != tasks.end(); task++) {
	//	printfDx("%x, ", *task);
	//	printfDx((*task)->toString().c_str());
	//	printfDx("\n");
	//}
	//printfDx("size:%d\n", tasks.size());
	//printfDx("end check\n\n");
	DrawFormatString(500, 0, 0xffffff, "tasks size:%d, queue size:%d", tasks.size(), newTasks.size());
}