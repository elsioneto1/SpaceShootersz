#include "GameCore.h"


#include "ShootFactory.h"
#include "ShootObject.h"
#include "Component.h"

#include "PrefabAsset.h"
#include "GameObject.h"
#include "Transform.h"
#include "ShootPool.h"
#include "EnemyShootPool.h"
#include "GameManager.h"

IMPLEMENT_DYNAMIC_CLASS(ShootFactory)



ShootFactory::ShootFactory()
{
}


ShootFactory::~ShootFactory()
{
}

void ShootFactory::load(XMLElement * node)
{
	XMLElement* element = nullptr;

	Component::load(node);

	const char * c = node->FirstChildElement()->Attribute("uuid");
	const char * c2 = node->FirstChildElement("PrefabAsset2")->Attribute("uuid");
	prefabID = getHashCode(c);
	prefabID2 = getHashCode(c2);
	// player bullet
	std::shared_ptr<Asset> asset = AssetManager::Instance().getAsset(prefabID);

	// enemy bullet
	std::shared_ptr<Asset> asset2 = AssetManager::Instance().getAsset(prefabID2);

	for (int i = 0; i < 100; i++)
	{
		PrefabAsset* prefab = (PrefabAsset*)asset.get();
		prefab->CreatePrefab();
	}

	for (int i = 0; i < 300; i++)
	{
		PrefabAsset* prefab = (PrefabAsset*)asset2.get();
		prefab->CreatePrefab();
	}


	ShootPool::Instance().canShoot = false;

}

void ShootFactory::update(float deltaTime)
{
	Component::update(deltaTime);


	std::vector<GameObject*>::iterator shootIterator;


	if (ShootPool::Instance().canShoot)
	{
		for (int i = 0; i <  ShootPool::Instance().ufoPool.size(); i++)
		{
			ShootObject* so = ShootPool::Instance().ufoPool[i];

			if (!so->onScreen)
			{
				so->onScreen = true;
				ShootPool::Instance().ufoPool[i]->gameObject->getTransform()->setPosition(GameManager::Instance().mainPlayer->getTransform()->getPosition().x, GameManager::Instance().mainPlayer->getTransform()->getPosition().y - 80);
				break;
			}
		}
	}

	
}
