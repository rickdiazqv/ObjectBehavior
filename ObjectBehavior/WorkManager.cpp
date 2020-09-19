#include "WorkManager.h"
#include "global.h"

WorkManager::WorkManager() {
	printfDx("WorkManager\n");
	Worker::setConnector(this);
	//input = &_input;
}

WorkManager::~WorkManager() {

}

void WorkManager::update() {
	for (auto worker = _workers.begin(); worker != _workers.end(); worker++) {
		(*worker)->update();
	}
	// queueのオブジェクトをlistに追加
	receive();
}

void WorkManager::draw() {
	//clsDx();
	DrawFormatString(300, 20, 0xffffff, (*_workers.begin())->toString().c_str());
	//DrawFormatString(300, 40, 0xffffff, (*++_workers.begin())->toString().c_str());
	int i = 0;
	for (auto worker = Worker::getDrawHead(); worker != nullptr; worker = worker->getNext()) {
		worker->draw();
		DrawFormatString(300, 60 + i * 20, 0xffffff, worker->toString().c_str());
		i++;
	}
}

void WorkManager::connect(Worker* self) {
	printfDx("connect\n");
	if (!self) { return; }
	_queWorkers.push(self);
	printfDx("queue size:%d\n", _queWorkers.size());
}

void WorkManager::disconnect(Worker* self) {
	_workers.remove(self);
}

void WorkManager::receive() {
	while (!_queWorkers.empty()) {
		printfDx("while ");
		Worker* self = _queWorkers.front();
		_queWorkers.pop();
		if (!self) { continue; }

		// Workerの内部ポインタのソート
		Worker::sortSelf(self);

		// WorkManager内部のlistにWorkerを挿入
		if (_workers.empty()) {
			printfDx("empty\n");
			_workers.push_back(self);
			continue;
		}
		if (!self->procComparable()) {
			printfDx("comp is null\n");
			_workers.push_front(self);
			continue;
		}

		int size = _workers.size();
		for (auto worker = _workers.rbegin(); worker != _workers.rend(); worker++) {
			if (self->compareTo(*worker) < 0) { continue; }
			printfDx("insert\n");
			_workers.insert(worker.base(), self);
			break;
		}
		if (_workers.size() == size) { 
			_workers.push_front(self); 
		}
	}
	//printfDx("check tasks\n");
	//for (auto task = tasks.begin(); task != tasks.end(); task++) {
	//	printfDx("%x, ", *task);
	//	printfDx((*task)->toString().c_str());
	//	printfDx("\n");
	//}
	//printfDx("size:%d\n", tasks.size());
	//printfDx("end check\n\n");
	DrawFormatString(500, 0, 0xffffff, "tasks size:%d, queue size:%d", _workers.size(), _queWorkers.size());
}