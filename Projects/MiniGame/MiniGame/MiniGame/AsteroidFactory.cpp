#include "GameCore.h"
#include "AsteroidFactory.h"
#include "PrefabAsset.h"
#include "AsteroidPool.h"



IMPLEMENT_DYNAMIC_CLASS(AsteroidFactory)

AsteroidFactory::AsteroidFactory()
{
}


AsteroidFactory::~AsteroidFactory()
{
}

void AsteroidFactory::load(XMLElement * node)
{
	Component::load(node);

	const char * c = node->FirstChildElement()->Attribute("uuid");
	prefabID = getHashCode(c);
	std::shared_ptr<Asset> asset = AssetManager::Instance().getAsset(prefabID);


	node->FirstChildElement("SpawnDelay")->QueryFloatAttribute("StartTime", &SpawnTime);
	node->FirstChildElement("SpawnDelay")->QueryFloatAttribute("EndTime", &minSpawnTimel);
	node->FirstChildElement("SpawnDelay")->QueryFloatAttribute("MinBaseVel", &baseVelocity);
	node->FirstChildElement("SpawnDelay")->QueryFloatAttribute("MaxBaseVel", &maxBaseVelocity);
	node->FirstChildElement("SpawnDelay")->QueryFloatAttribute("MaxVelMultiplier", &maxVelMultiplier);

	velMultiplier = 1;

	currentSpawnTime = 0;

	
	for (int i = 0; i < 20; i++)
	{
		PrefabAsset* prefab = (PrefabAsset*)asset.get();
		prefab->CreatePrefab();
	}

}

void AsteroidFactory::update(float deltaTime)
{

	Component::update(deltaTime);

	MainGameElement::update();
	if (!mayUpdate)
	{
		return;
	}

	currentSpawnTime += deltaTime;
	// I was planning to make a super cool logic to spawn the asteroids, but I didn't had time to do it
	// they have a general behaviour with hardcoded values
	if (currentSpawnTime > SpawnTime)
	{

		currentSpawnTime = 0;

		SpawnTime -= deltaTime * 0.5;

		if (SpawnTime < minSpawnTimel)
		{
			SpawnTime = minSpawnTimel;
		}

		int asteroidNumber;
		asteroidNumber = Random.Random() * 5 + 2;
		int spawnedAsteroids;
		spawnedAsteroids = 0;
		int index = 0;

		int as = AsteroidPool::Instance().asteroidPool.size();
		for (index; index < AsteroidPool::Instance().asteroidPool.size(); index++)
		{

			if (AsteroidPool::Instance().asteroidPool[index]->sleeping)
			{
				spawnedAsteroids++;

				AsteroidPool::Instance().asteroidPool[index]->setAsteroidParams(3);
				AsteroidPool::Instance().asteroidPool[index]->sleeping = false;

			}


			if (spawnedAsteroids > asteroidNumber)
				break;

		}


	}


}


































