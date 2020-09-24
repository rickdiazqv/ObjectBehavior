#include "GameProcessor.h"

GameProcessor::GameProcessor() {
	_workManager = WorkManager::getInstance();
	_input = Input::getInstance();
}

GameProcessor::~GameProcessor() {
	WorkManager::finalize();
	Input::finalize();
}

void GameProcessor::process() {
	_workManager->update();
	_workManager->draw();
}