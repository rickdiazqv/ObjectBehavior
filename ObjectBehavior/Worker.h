#pragma once
#include "package.h"
#include "Task.h"
#include "Connector.h"
#include "Comparable.h"

using varptr = const void*;

class Worker : public Task, public Comparable<Worker*> {
private:
	inline static Connector<Worker*>* connector = nullptr;

private:
	compare<Worker*> _comp = nullptr;

public:
	Worker(compare<Worker*> comp = nullptr);
	~Worker();

public:
	static void setConnector(Connector<Worker*>* con);

public:
	bool comparable() { return _comp; }
	int compareTo(Worker* other) override;
};