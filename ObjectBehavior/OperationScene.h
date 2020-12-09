#pragma once
#include "gamedata.h"
#include "Scene.h"

class OperationScene : public Scene {
public:
	OperationScene();
	~OperationScene();

public:
	void update() override;
	void draw() override;

private:

};

