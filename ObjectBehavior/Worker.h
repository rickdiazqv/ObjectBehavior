#pragma once
#include "tools.h"
#include "Task.h"
#include "Connector.h"
#include "Comparable.h"

class Worker : public Task, public Comparable<Worker*> {
private:
	inline static Connector<Worker*>* connector = nullptr;

private:
	Comparator<Worker*> _compare = nullptr;

public:
	Worker(Comparator<Worker*> compare = nullptr);
	~Worker();

public:
	static void setConnector(Connector<Worker*>* con);

public:
	bool comparable() { return _compare; }
	int compareTo(Worker* other) override;
};