#pragma once

#include <vector>
#include "EnemyShootObject.h"
#include "Transform.h"


class EnemyShootPool
{


public:

	inline static EnemyShootPool& Instance()
	{
		static EnemyShootPool instance;
		return instance;
	}

	// the name is funky here haha
	// the correct name should be BulletPool, but copying and strucutures and modifying them makes you forget things sometimes
	std::vector<EnemyShootObject*> ufoPool;
	bool canShoot;

	// put a bullet on the screen and set all the variables
	void spawnShots(float angle, sf::Vector2f pos)
	{
		int count;
		count = 0;
		float cos1;
		float sin1;
		for (int i = 0; i < EnemyShootPool::Instance().ufoPool.size(); i++)
		{
			EnemyShootObject* so = EnemyShootPool::Instance().ufoPool[i];

			if (!so->onScreen)
			{

				count++;
				so->onScreen = true;
				ufoPool[i]->gameObject->getTransform()->setPosition(pos);

				// simple conversion
				float cos1 = cos((angle * 3.14) / 180);
				float sin1 = sin((angle * 3.14) / 180);
				angle += 90;
				


				//ufoPool[i]->direction(cos1);

				ufoPool[i]->direction.x = cos1;
				ufoPool[i]->direction.y = sin1;

				ufoPool[i]->gameObject->getTransform()->setRotation(angle);

				if ( count == 4)
					break;

			}
		}
	}


};