#include "SceneManager.h"
#include "Scene.h"
#include "Title.h"

SceneManager::SceneManager() : Worker(PROC_PRIORITY, DRAW_PRIORITY) {
	Scene::setSceneChanger(this);
	changeScene(sc_init);
	changeScene();
}

SceneManager::~SceneManager() {

}

inline void SceneManager::changeScene() {
	if (_nextSceneId == SCENE_ID) { return; }

	switch (_nextSceneId) {
	case SceneId::Title:
		changeScene(new Title());
		break;

	case SceneId::Home:
		break;

	case SceneId::World:
		break;

	case SceneId::Battle:
		break;

	case SceneId::None:
		break;
	}
}

void SceneManager::update() {
	changeScene();
}

void SceneManager::draw() {

}