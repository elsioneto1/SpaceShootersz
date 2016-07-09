#pragma once

#include <vector>
#include "ShootObject.h"


class ShootPool
{


public:

	// where all the player bullets are stored
	inline static ShootPool& Instance()
	{
		static ShootPool instance;
		return instance;
	}

	// the name is funky here haha
	// the correct name should be BulletPool, but copying and strucutures and modifying them makes you forget things sometimes
	std::vector<ShootObject*> ufoPool;
	bool canShoot;

};