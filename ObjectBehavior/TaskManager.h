#pragma once
#include "package.h"
#include "Worker.h"

class TaskManager : public Task, public Connector<Task*> {
private:
	vector<Task*> tasks;

public:
	TaskManager();
	~TaskManager();

public:
	void update() override;
	void draw() override;
	void connect(Task* obj) override;
};