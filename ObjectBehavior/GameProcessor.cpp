#include "GameProcessor.h"

GameProcessor::GameProcessor() {
	_wrkMgr = WorkManager::getInstance();
	_objMgr = ObjectManager::getInstance();
	_input = Input::getInstance();
}

GameProcessor::~GameProcessor() {
	WorkManager::finalize();
	ObjectManager::finalize();
	Input::finalize();
}

void GameProcessor::process() {
	_wrkMgr->update();
	_wrkMgr->draw();
}