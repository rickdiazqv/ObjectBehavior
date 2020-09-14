#pragma once
#include "tools.h"

class EditableTask {
public:
	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

