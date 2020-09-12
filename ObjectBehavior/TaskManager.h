#pragma once
#include "package.h"
#include "Worker.h"

class TaskManager : public Task, public Connector<Task*> {
private:
	list<Task*> tasks;

public:
	TaskManager();
	~TaskManager();

public:
	void update() override;
	void draw() override;

	void connect(Task* self, compare<Task*> comp) override;
};