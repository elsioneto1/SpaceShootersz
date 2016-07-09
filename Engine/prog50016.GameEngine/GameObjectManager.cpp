#include "Core.h"
#include "GameObjectManager.h"

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "Transform.h"

void GameObjectManager::initialize()
{
	ISystem::initialize();

	REGISTER_ABSTRACT_CLASS(Component);
	REGISTER_DYNAMIC_CLASS(Sprite);
	REGISTER_DYNAMIC_CLASS(Transform);
	REGISTER_DYNAMIC_CLASS(GameObject);
}

void GameObjectManager::AddRootGameObject(std::shared_ptr<GameObject> gameObject)
{
	// add this game object to parents list
	rootGameObjects.push_back(gameObject);
}

void GameObjectManager::AddChildGameobject(std::shared_ptr<GameObject> parentObject, std::shared_ptr<GameObject> gameObject)
{
	parentObject->getChildren().push_back(gameObject);
}

void GameObjectManager::RemoveGameObject(STRCODE id)
{
	std::list<std::shared_ptr<GameObject>>::iterator iter = rootGameObjects.begin();
	while (iter != rootGameObjects.end())
	{
		if ((*iter)->getUID() == id)
		{
			ReleaseGameObject((*iter));
			(*iter).reset();
			rootGameObjects.erase(iter);
			break;
		}
		else
		{
			RemoveGameObject(id, (*iter));
		}
		++iter;
	}
}

void GameObjectManager::RemoveGameObject(STRCODE id, std::shared_ptr<GameObject>& parent)
{
	std::list<std::shared_ptr<GameObject>>::iterator iter = parent->getChildren().begin();
	while (iter != parent->getChildren().end())
	{
		if ((*iter)->getUID() == id)
		{
			std::cout << "Remove Game Object: " << id << std::endl;
			ReleaseGameObject((*iter));
			(*iter).reset();
			parent->getChildren().erase(iter);
			break;
		}
		else
		{
			RemoveGameObject(id, (*iter));
		}
		++iter;
	}
}

void GameObjectManager::ReleaseGameObject(std::shared_ptr<GameObject>& go)
{
	std::list<std::shared_ptr<GameObject>>::iterator iter = go->getChildren().begin();
	while (iter != go->getChildren().end())
	{
		ReleaseGameObject((*iter));
		(*iter).reset();
		++iter;
	}

	go->parent.reset();
}

std::weak_ptr<GameObject> GameObjectManager::_FindGameObject(std::shared_ptr<GameObject>& parent, STRCODE id)
{
	std::list<std::shared_ptr<GameObject>>::iterator iter = parent->getChildren().begin();
	while (iter != parent->getChildren().end())
	{
		if ((*iter)->getUID() == id)
		{
			(*iter).reset();

			std::weak_ptr<GameObject> wp = (*iter);
			return wp;
		}

		std::weak_ptr<GameObject> wp = _FindGameObject((*iter), id);
		if (wp.expired() == false)
		{
			return wp;
		}

		++iter;
	}
}

std::weak_ptr<GameObject> GameObjectManager::FindGameObject(STRCODE id)
{
	std::list<std::shared_ptr<GameObject>>::iterator iter = rootGameObjects.begin();
	while (iter != rootGameObjects.end())
	{
		if ((*iter)->getUID() == id)
		{
			(*iter).reset();

			std::weak_ptr<GameObject> wp = (*iter);
			return wp;
		}

		std::weak_ptr<GameObject> wp = _FindGameObject((*iter), id);
		if (wp.expired() == false)
		{
			return wp;
		}

		++iter;
	}
	
	return std::weak_ptr<GameObject>();
}

std::weak_ptr<GameObject> GameObjectManager::CreateGameObject(tinyxml2::XMLDocument* doc)
{
	XMLElement* gameObjElement = doc->FirstChildElement("GameObject");
	THROW_RUNTIME_ERROR(gameObjElement == nullptr, "Unable to Load Game Object Prefab");

	std::shared_ptr<GameObject> gObj = std::shared_ptr<GameObject>(new GameObject());

	gObj->setFileID(NoName);
	gObj->load(gameObjElement);

	UUID uid;
	CreateUUID(&uid);
	gObj->setUID(GUIDToSTRCODE(uid));

	rootGameObjects.push_back(gObj);

	return std::weak_ptr<GameObject>(gObj);
}

void GameObjectManager::load(XMLElement* node, STRCODE idOfFile)
{
	XMLElement* gameObjElement = node->FirstChildElement("GameObject");
	while (gameObjElement != NULL)
	{
		std::shared_ptr<GameObject> gObj = std::shared_ptr<GameObject>(new GameObject());
		gObj->setFileID(idOfFile);
		gObj->load(gameObjElement);

		rootGameObjects.push_back(gObj);

		gameObjElement = gameObjElement->NextSiblingElement("GameObject");
	}
}

void GameObjectManager::unload(STRCODE idOfFile)
{
	//for (std::map<STRCODE, std::shared_ptr<GameObject>>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	//{
	//	if ((it)->second->fileID == idOfFile)
	//	{
	//		delete &it->second;
	//		gameObjects.erase(it);
	//	}
	//}
}

void GameObjectManager::save(tinyxml2::XMLElement* node)
{
	//tinyxml2::XMLElement* gameElement = node->GetDocument()->NewElement("GameObjects");
	//node->GetDocument()->InsertFirstChild(gameElement);
	//for (std::map<STRCODE, std::shared_ptr<GameObject>>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	//{
	//	if ((*it).second->isSaveAble())
	//	{
	//		tinyxml2::XMLElement* gObjElement = node->GetDocument()->NewElement("GameObject");
	//		(*it).second->save(gObjElement);
	//		gameElement->InsertEndChild(gObjElement);
	//	}
	//}
}

const std::list<std::shared_ptr<GameObject>> GameObjectManager::GetAllRootGameObjects()
{
	return rootGameObjects;
}

void GameObjectManager::DestroyGameObject(GameObject* go)
{
	destroyGameObjects.push_back(go);
}

void GameObjectManager::_update(float deltaTime, std::shared_ptr<GameObject>& gameObject)
{
	gameObject->update(deltaTime);

	std::list<std::shared_ptr<GameObject>>::iterator iter = gameObject->getChildren().begin();
	while (iter != gameObject->getChildren().end())
	{
		//if ((*iter)->isActive())
		{
			_update(deltaTime, (*iter));
		}
		++iter;
	}
}

void GameObjectManager::update(float deltaTime)
{
	std::list<std::shared_ptr<GameObject>>::iterator iter = rootGameObjects.begin();
	while (iter != rootGameObjects.end())
	{
		//if ((*iter)->isActive())
		{
			_update(deltaTime, (*iter));
		}
		iter++;
	}

	std::list<GameObject*>::iterator destIt = destroyGameObjects.begin();
	while (destIt != destroyGameObjects.end())
	{
		RemoveGameObject((*destIt)->getUID());
		++destIt;
	}
	destroyGameObjects.clear();
}

//template <class CompType>
//std::vector<std::weak_ptr<CompType>> getAllComponents();

//template <class CompType>
//std::vector<std::weak_ptr<CompType>> GameObjectManager::getAllComponents()
//{
//	// get Strcode id from component that is passed in
//	STRCODE idOfComp = CompType::getClassHashCode;
//
//	std::map<STRCODE, std::shared_ptr<GameObject>>::iterator it = gameObjects.begin();
//
//	int compCount = 0;
//
//	// get total count of all the components in each game object of specific type
//	while (it != gameObjects.end())
//	{
//		compCount += it->second->components.count(idOfComp);
//		++it;
//	}
//
//	// make a vector with the initial size calculated above
//	std::vector<std::weak_ptr<Component>> components(compCount);
//
//	// iterate over all the game objects and get vector of components
//	it = gameObjects.begin();
//	while (it != gameObjects.end())
//	{
//		std::list<std::weak_ptr<CompType>> compReturned = it->second->getComponents<CompType>();
//
//		std::list<std::weak_ptr<CompType>>::iterator itC = compReturned.begin();
//		while (itC != compReturned.end())
//		{
//			components.push_back(itC->second);
//			++itC;
//		}
//
//		++it;
//	}
//
//	return components;
//}

