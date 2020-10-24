#pragma once
#include "define.h"

class SceneChanger {
public:
	virtual void changeScene(SceneId sceneId) = 0;
};