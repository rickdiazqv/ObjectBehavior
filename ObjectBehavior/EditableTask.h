#pragma once
#include "package.h"

class EditableTask {
public:
	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

