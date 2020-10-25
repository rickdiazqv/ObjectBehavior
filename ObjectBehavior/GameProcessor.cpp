#include "GameProcessor.h"
#include "ConfigLoader.h"
#include "WorkManager.h"
#include "ObjectManager.h"
#include "Input.h"
#include "SpriteManager.h"
#include "SceneManager.h"

GameProcessor::GameProcessor() {
	// リソースのロード
	ConfigLoader::getInstance()->configure(path_conf);
	ConfigLoader::finalize();

	// リソースオブジェクト
	_sprMgr = SpriteManager::getInstance();

	// 入出力オブジェクト
	_input = Input::getInstance();

	// ゲームオブジェクト
	_wrkMgr = WorkManager::getInstance();
	_objMgr = ObjectManager::getInstance();
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