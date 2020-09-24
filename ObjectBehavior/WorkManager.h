#pragma once
#include "tools.h"
#include "Task.h"
#include "Connector.h"
#include "Worker.h"
#include "Input.h"

class WorkManager : public Task, public Connector<Worker*> {
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