#pragma once
#include "define.h"
#include "Worker.h"
#include "SceneChanger.h"

class Scene : public Worker {
private:
	inline static const int PROC_PRIORITY = 11;
	inline static const int DRAW_PRIORITY = 11;

private:
	inline static SceneChanger* _sceneChanger = nullptr;

public:
	Scene();
	~Scene();

public:
	inline static void setSceneChanger(SceneChanger* changer) {
		if (!_sceneChanger) { _sceneChanger = changer; }
	}

protected:
	inline static void changeScene(SceneId sceneId) {
		_sceneChanger->changeScene(sceneId);
	}

public:
	void init() override {};
	void update() override;
	void draw() override;
};