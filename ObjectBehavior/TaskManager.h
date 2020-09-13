#pragma once
#include "package.h"
#include "Worker.h"

class TaskManager : public Task, public Connector<Worker*> {
private:
	list<Worker*> tasks;
	queue<Worker*> newTasks;

public:
	TaskManager();
	~TaskManager();

public:
	void update() override;
	void draw() override;

	void connect(Worker* self) override;

public:
	void receive();
};