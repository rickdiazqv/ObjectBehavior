#pragma once
#include "define.h"
#include "Task.h"
#include "Connector.h"

class WorkManager : public Task, public Connector<Worker*, void, void> {
private:
	inline static WorkManager* _self = nullptr;

	list<Worker*> _workers;
	//Worker* _procHead = nullptr;
	//Worker* _procTail = nullptr;
	//Worker* _drawHead = nullptr;
	//Worker* _drawTail = nullptr;
	queue<Worker*> _queWorkers;
	bool _receive = true;

private:
	WorkManager();
	~WorkManager();

public:
	static WorkManager* getInstance() {
		if (!_self) { _self = new WorkManager(); }
		return _self;
	}

	static void finalize() {
		delete _self;
		_self = nullptr;
	}

public:
	void update() override;
	void draw() override;

	void connect(Worker* self) override;
	void disconnect(Worker* self) override;

public:
	void receive();
};