#pragma once
#include "define.h"

class GameProcessor {
private:
	inline static GameProcessor* _self = nullptr;

private:
	WorkManager* _wrkMgr = nullptr;
	ObjectManager* _objMgr = nullptr;
	Input* _input = nullptr;

private:
	GameProcessor();
	~GameProcessor();

public:
	static GameProcessor* geInstance() {
		if (!_self) { _self = new GameProcessor(); }
		return _self;
	}

	static void finalize() {
		delete _self;
		_self = nullptr;
	}

public:
	void process();
};