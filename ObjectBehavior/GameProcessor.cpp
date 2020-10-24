#include "GameProcessor.h"
#include "WorkManager.h"
#include "ObjectManager.h"
#include "Input.h"
#include "SpriteManager.h"
#include "SceneManager.h"

GameProcessor::GameProcessor() {
	_sprMgr = SpriteManager::getInstance();
	_wrkMgr = WorkManager::getInstance();
	_objMgr = ObjectManager::getInstance();
	_input = Input::getInstance();
	_scMgr = SceneManager::getInstance();
}

GameProcessor::~GameProcessor() {
	WorkManager::finalize();
	ObjectManager::finalize();
	Input::finalize();
	SpriteManager::finalize();
	SceneManager::finalize();
}

void GameProcessor::process() {
	_wrkMgr->update();
	_wrkMgr->draw();
}