#pragma once
#include "tools.h"
#include "Task.h"
#include "Connector.h"
#include "Worker.h"

class WorkManager : public Task, public Connector<Worker*> {
private:
	list<Worker*> _workers;
	//Worker* _procHead = nullptr;
	//Worker* _procTail = nullptr;
	//Worker* _drawHead = nullptr;
	//Worker* _drawTail = nullptr;
	queue<Worker*> _queWorkers;

public:
	WorkManager();
	~WorkManager();

public:
	void update() override;
	void draw() override;

	void connect(Worker* self) override;
	void disconnect(Worker* self) override;

public:
	void receive();
};