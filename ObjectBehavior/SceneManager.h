#pragma once
#include "define.h"
#include "Worker.h"
#include "SceneChanger.h"

class SceneManager : public Worker, public SceneChanger {
private:
	inline static const int PROC_PRIORITY = 0;
	inline static const int DRAW_PRIORITY = 0;
	inline static const SceneId SCENE_ID = SceneId::None;

private:
	inline static SceneManager* _self;

private:
	Scene* _scene = nullptr;
	SceneId _nextSceneId = SCENE_ID;

private:
	SceneManager();
	~SceneManager();

private:
	inline void changeScene();
	inline void changeScene(Scene* scene) {
		closeScene();
		_scene = scene;
		changeScene(SCENE_ID);
	}
	inline void closeScene() {
		delete _scene;
		_scene = nullptr;
	}

public:
	inline static SceneManager* getInstance() {
		if (!_self) { _self = new SceneManager(); }
		return _self;
	}
	inline static void finalize() {
		delete _self;
		_self = nullptr;
	}

public:
	void init() override {}
	void update() override;
	void draw() override;

public:
	inline void changeScene(SceneId sceneId) override { 
		_nextSceneId = sceneId;
	}
};

