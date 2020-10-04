#include "WorkManager.h"
#include "Worker.h"
#include "Input.h"
#include "Morton.h"

WorkManager::WorkManager() {
	//printfDx("WorkManager\n");
	Worker::setConnector(this);
}

WorkManager::~WorkManager() {

}

void WorkManager::update() {
	for (auto worker = _workers.begin(); worker != _workers.end(); worker++) {
		(*worker)->update();
	}
	// queueのオブジェクトをlistに追加
	if (_receive) { receive(); }
}

void WorkManager::draw() {
	//clsDx();
	Morton::drawGrid();
	//DrawFormatString(300, 20, 0xffffff, (*_workers.begin())->toString().c_str());
	//DrawFormatString(300, 40, 0xffffff, (*++_workers.begin())->toString().c_str());
	int i = 0;
	for (auto worker = Worker::getDrawHead(); worker != nullptr; worker = worker->getNext()) {
		worker->draw();
		DrawFormatString(300, 100 + i * 40, 0xffffff, worker->toString().c_str());
		i++;
	}
}

void WorkManager::connect(Worker* self) {
	//printfDx("connect\n");
	if (!self) { return; }
	_queWorkers.push(self);
	_receive = true;
	//printfDx("queue size:%d\n", _queWorkers.size());
}

void WorkManager::disconnect(Worker* self) {
	_workers.remove(self);
}

void WorkManager::receive() {
	Worker::sendWorkers();
	while (!_queWorkers.empty()) {
		//printfDx("while ");
		Worker* self = _queWorkers.front();
		_queWorkers.pop();
		if (!self) { continue; }

		// 初期化メソッド
		self->init();

		// Workerの内部ポインタのソート
		Worker::sortSelf(self);

		// WorkManager内部のlistにWorkerを挿入
		if (_workers.empty()) {
			//printfDx("empty\n");
			_workers.push_back(self);
			continue;
		}
		int comp = self->procCompareTo(self);
		if (comp < 0) {
			//printfDx("front\n");
			_workers.push_front(self);
			continue;
		}
		if (comp > 0) {
			//printfDx("back\n");
			_workers.push_back(self);
			continue;
		}

		int size = _workers.size();
		for (auto worker = _workers.rbegin(); worker != _workers.rend(); worker++) {
			if (self->procCompareTo(*worker) < 0) { continue; }
			//printfDx("insert\n");
			_workers.insert(worker.base(), self);
			break;
		}
		if (_workers.size() == size) { 
			_workers.push_front(self); 
		}
	}
	_receive = false;
	//DrawFormatString(500, 0, 0xffffff, "tasks size:%d, queue size:%d", _workers.size(), _queWorkers.size());
	printfDx("\n");
}