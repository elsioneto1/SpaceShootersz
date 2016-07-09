
#include "GameManager.h"

#pragma once
class PauseMenuElement {
public:

	bool mayUpdate;
	void update() {

		mayUpdate = GameManager::Instance().getPause();

	}
};

