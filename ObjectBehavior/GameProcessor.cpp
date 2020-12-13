#include "GameProcessor.h"
#include "ConfigLoader.h"
#include "WorkManager.h"
#include "ObjectManager.h"
#include "Input.h"
#include "SpriteManager.h"
#include "SceneManager.h"
#include "ObjectPlate.h"

GameProcessor::GameProcessor() {
	// ���\�[�X�̃��[�h
	ConfigLoader::getInstance()->configure(path_conf);
	ConfigLoader::finalize();

	// ���\�[�X�I�u�W�F�N�g
	_sprMgr = SpriteManager::getInstance();

	// ���o�̓I�u�W�F�N�g
	_input = Input::getInstance();

	// �Q�[���I�u�W�F�N�g
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

	delete ObjectPlate::DEFAULT_PLATE;
}

void GameProcessor::process() {
	_wrkMgr->update();
	_wrkMgr->draw();
}