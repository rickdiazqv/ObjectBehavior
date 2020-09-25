#pragma once
#include "define.h"
#include "Task.h"
#include "Connector.h"
#include "Comparable.h"

class Worker : public Task, public Comparable<Worker*> {
private:
	inline static Connector<Worker*>* _connector = nullptr;
	static UnaryOperator<Worker*> getNeighbor[2];
	static TypeBiConsumer<Worker*> setNeighbor[2];
	inline static Worker* _current = nullptr;
	inline static Worker* _drawHead = nullptr;
	inline static queue<Worker*> _queWorkers;

private:
	Worker* _prev = nullptr;
	Worker* _next = nullptr;
	//Comparator<Worker*> _procCompare = [](Worker* self, Worker* other) {return 0; };
	//Comparator<Worker*> _drawCompare = _procCompare;

private:
	int _procPriority = 0;
	int _drawPriority = 0;

public:
	Worker(int procPriority, int drawPriority);
	~Worker();

public:
	Worker* getPrev() { return _prev; }
	Worker* getNext() { return _next; }
	int getProcPriority() { return _procPriority; }
	int getDrawPriority() { return _drawPriority; }

private:
	void setPrev(Worker* other) { _prev = other; };
	void setNext(Worker* other) { _next = other; };

public:
	static void sortSelf(Worker* self);

protected:
	static void sortSelf(Worker* self, int dir);

private:
	static bool sortSelf(Worker* const self, Worker* const root, const int index);

public:
	static void setConnector(Connector<Worker*>* connector);
	static void sendWorkers();
	static Worker* getCurrent() { return _current; }
	static Worker* getDrawHead() { return _drawHead; }

private:
	static void setCurrent(Worker* worker) { _current = worker; }
	static void setDrawHead(Worker* worker) { _drawHead = worker; }

public:
	//bool procComparable() { return _procCompare; }
	//bool drawComparable() { return _drawCompare; }
	int compareTo(Worker* other) override;

public:
	virtual int procCompareTo(Worker* other) { return this->getProcPriority() - other->getProcPriority(); }
	virtual int drawCompareTo(Worker* other) { return this->getDrawPriority() - other->getDrawPriority(); }
};