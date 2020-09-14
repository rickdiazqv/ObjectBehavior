#include "WorkManager.h"

WorkManager::WorkManager() {
	printfDx("WorkManager\n");
	Worker::setConnector(this);
}

WorkManager::~WorkManager() {

}

void WorkManager::update() {
	auto mover = workers.end();
	for (auto worker = workers.begin(); worker != workers.end(); worker++) {
		(*worker)->update();
		//if((*worker)->)
	}
	// 描画順の調整 pers == trueのオブジェクトが優先的に前面に描画される
	for (auto worker = workers.begin(); worker != workers.end(); worker++) {
		//if (self->compareTo(*task) < 0) { continue; }
	}
	// queueのオブジェクトをlistに追加
	receive();
}

void WorkManager::draw() {
	//clsDx();
	int i = 0;
	for (auto worker = workers.begin(); worker != workers.end(); worker++) {
		(*worker)->draw();
		DrawFormatString(300, 100 + i * 20, 0xffffff, (*worker)->toString().c_str());
		i++;
	}
}

void WorkManager::connect(Worker* self) {
	printfDx("connect\n");
	if (!self) { return; }
	queWorkers.push(self);
	printfDx("queue size:%d\n", queWorkers.size());
}

void WorkManager::receive() {
	while (!queWorkers.empty()) {
		printfDx("while ");
		Worker* self = queWorkers.front();
		queWorkers.pop();
		if (!self) { continue; }

		if (workers.empty()) {
			printfDx("empty\n");
			workers.push_back(self);
			continue;
		}
		if (!self->comparable()) {
			printfDx("comp is null\n");
			workers.push_front(self);
			continue;
		}

		int size = workers.size();
		for (auto worker = workers.rbegin(); worker != workers.rend(); worker++) {
			if (self->compareTo(*worker) < 0) { continue; }
			printfDx("insert\n");
			workers.insert(worker.base(), self);
			break;
		}
		if (workers.size() == size) { workers.push_front(self); }
	}
	//printfDx("check tasks\n");
	//for (auto task = tasks.begin(); task != tasks.end(); task++) {
	//	printfDx("%x, ", *task);
	//	printfDx((*task)->toString().c_str());
	//	printfDx("\n");
	//}
	//printfDx("size:%d\n", tasks.size());
	//printfDx("end check\n\n");
	DrawFormatString(500, 0, 0xffffff, "tasks size:%d, queue size:%d", workers.size(), queWorkers.size());
}