#pragma once
#include "package.h"
#include "Task.h"
#include "Connector.h"

using varptr = const void*;

class Worker : public Task {
private:
	inline static Connector<Task*>* connector = nullptr;

public:
	Worker(compare<Task*> comp, initialize<Task*> init, const char* params = nullptr, ...);
	~Worker();

public:
	static void setConnector(Connector<Task*>* con);
};