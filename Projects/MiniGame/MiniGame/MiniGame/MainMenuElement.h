#ifndef _MAINMENUELEMENT_H_
#define _MAINMENUELEMENT_H_
#pragma once

#include "GameManager.h"

class MainMenuElement
{

protected:
	// Elements class controls if the update will be run or not. 
	bool mayUpdate;
	void update() {

		mayUpdate = GameManager::Instance().getMenu();
		
	}

};



#endif