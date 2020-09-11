#pragma once
#include "Task.h"
#include "Connector.h"

class Worker : public Task {
private:
	inline static Connector<Task*>* connector = nullptr;

public:
	Worker();
	~Worker();

public:
	static void setConnector(Connector<Task*>* con);
};

