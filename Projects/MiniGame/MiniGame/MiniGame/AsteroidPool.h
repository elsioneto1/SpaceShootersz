
#include "Asteroid.h"
#include <vector>

#pragma once



class AsteroidPool
{



public:

	// where all the asteroids are stored and retireved

	static AsteroidPool& Instance()
	{
		static AsteroidPool instance;
		return instance;
	}


	std::vector<Asteroid*> asteroidPool;


	AsteroidPool();
	~AsteroidPool();
};

