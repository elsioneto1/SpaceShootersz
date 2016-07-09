#ifndef _MAINGAMEELEMENT_H_
#define _MAINGAMEELEMENT_H_
#pragma once

#include "GameManager.h"

class MainGameElement
{

protected:

	// Elements class controls if the update will be run or not. 
	bool mayUpdate;
	void update() { 

		mayUpdate = GameManager::Instance().getMaingame(); 
	}

};



#endif