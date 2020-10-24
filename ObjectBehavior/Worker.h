#pragma once
#include "define.h"
#include "Task.h"
#include "Comparable.h"

class Worker : public Task, public Comparable<Worker*> {
private:
	inline static Connector<Worker*, void, void>* _connector = nullptr;
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
	virtual void init() = 0;
	inline Worker* getPrev() { return _prev; }
	inline Worker* getNext() { return _next; }
	inline int getProcPriority() { return _procPriority; }
	inline int getDrawPriority() { return _drawPriority; }

private:
	inline void setPrev(Worker* other) { _prev = other; };
	inline void setNext(Worker* other) { _next = other; };

public:
	inline static void setConnector(Connector<Worker*, void, void>* connector) {
		if (!_connector) { _connector = connector; }
	}
	static void sortSelf(Worker* self);

protected:
	static void sortSelf(Worker* self, int dir);

private:
	static bool sortSelf(Worker* const self, Worker* const root, const int index);

public:
	static void sendWorkers();
	inline static Worker* getCurrent() { return _current; }
	inline static Worker* getDrawHead() { return _drawHead; }

private:
	inline static void setCurrent(Worker* worker) { _current = worker; }
	inline static void setDrawHead(Worker* worker) { _drawHead = worker; }

public:
	//bool procComparable() { return _procCompare; }
	//bool drawComparable() { return _drawCompare; }
	int compareTo(Worker* other) override;

public:
	inline virtual int procCompareTo(Worker* other) { return this->getProcPriority() - other->getProcPriority(); }
	inline virtual int drawCompareTo(Worker* other) { return this->getDrawPriority() - other->getDrawPriority(); }
};