#include "GameProcessor.h"
#include "WorkManager.h"
#include "ObjectManager.h"
#include "Input.h"
#include "SpriteManager.h"

GameProcessor::GameProcessor() {
	_wrkMgr = WorkManager::getInstance();
	_objMgr = ObjectManager::getInstance();
	_input = Input::getInstance();
	_sprMgr = SpriteManager::getInstance();
}

GameProcessor::~GameProcessor() {
	WorkManager::finalize();
	ObjectManager::finalize();
	Input::finalize();
	SpriteManager::finalize();
}

void GameProcessor::process() {
	_wrkMgr->update();
	_wrkMgr->draw();
}