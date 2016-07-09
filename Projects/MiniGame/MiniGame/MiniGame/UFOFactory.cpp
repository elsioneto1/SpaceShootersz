#include "GameCore.h"
#include "UFOFactory.h"
#include "UFOController.h"
#include "UFOPoolManager.h"
#include "PrefabAsset.h"

IMPLEMENT_DYNAMIC_CLASS(UFOFactory)

void UFOFactory::load(XMLElement* node)
{
	XMLElement* element = nullptr;

	Component::load(node);

	const char * c = node->FirstChildElement()->Attribute("uuid");
	prefabID = getHashCode(c);
	currentSpawnDelay = 0;
	spawnDelay = 5;
	
	std::shared_ptr<Asset> asset = AssetManager::Instance().getAsset(prefabID);

	for (int i = 0; i < 20; i++)
	{
		

		PrefabAsset* prefab = (PrefabAsset*)asset.get();
		prefab->CreatePrefab();

		GameObject* go = (GameObject*)prefab;
		Transform *t = go->getTransform();
		ufoObjs.push_back(go);
	}


	// TODO: UFOFactory - 1
	// Load the data from the filesd

}
void UFOFactory::update(float deltaTime)
{
	Component::update(deltaTime);

	// verify if element state is active   
	gameObject->setActive(mayUpdate);
	MainGameElement::update();
	if (!mayUpdate)
	{
		return;
	}

	currentSpawnDelay += deltaTime;

	if (currentSpawnDelay > spawnDelay)
	{
		maxSpawnPerTime = Random.Random() *3;
		spawnDelay = Random.Random() * 5 + 2;
		currentSpawnDelay = 0.0f;
		UFOController* ufo;
		for (int i = 0; i < UFOPoolManager::Instance().ufoPool.size(); i++)
		{

			ufo = UFOPoolManager::Instance().ufoPool[i];
			//std::cout << ufo->onScreen << std::endl;
			if (!ufo->onScreen)
			{
				maxSpawnPerTime--;
				ufo->onScreen = true;
				if ( maxSpawnPerTime < 0)
					break;
			}

		}
	}



	// TODO: UFOFactory - 2
	// Simple spawn factory code however there are 2 bugs!!!!!
	// Fix the code below to spawn them properly (based off time)
}
