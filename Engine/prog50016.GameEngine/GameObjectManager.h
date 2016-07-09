#ifndef _GAMEOBJECTMANAGER_H_
#define _GAMEOBJECTMANAGER_H_
#pragma once

#include "ISystem.h"

class GameObject;
class Component;

class GameObjectManager : public ISystem
{
private:
	// list of Parent Game Objects
	std::list<std::shared_ptr<GameObject>> rootGameObjects;

	std::list<GameObject*> destroyGameObjects;

public:

	inline static GameObjectManager& Instance()
	{
		static GameObjectManager instance;
		return instance;
	}


	void AddRootGameObject(std::shared_ptr<GameObject> gameObject);
	void AddChildGameobject(std::shared_ptr<GameObject> parentObject, std::shared_ptr<GameObject> gameObject);


	std::weak_ptr<GameObject> FindGameObject(STRCODE id);

	const std::list<std::shared_ptr<GameObject>> GetAllRootGameObjects();

	std::weak_ptr<GameObject> CreateGameObject(tinyxml2::XMLDocument* doc);
	void DestroyGameObject(GameObject* go);

	void save(tinyxml2::XMLDocument* node);
	void save(tinyxml2::XMLElement* node);
	void load(XMLElement* node, STRCODE);
	void unload(STRCODE idOfFile);

protected:
	void initialize();
	void update(float deltaTime);

private:
	void RemoveGameObject(STRCODE id);
	void RemoveGameObject(STRCODE id, std::shared_ptr<GameObject>& parent);
	void ReleaseGameObject(std::shared_ptr<GameObject>& go);

	void _update(float deltaTime, std::shared_ptr<GameObject>& gameObject);
	std::weak_ptr<GameObject> _FindGameObject(std::shared_ptr<GameObject>& parent, STRCODE id);

private:
	GameObjectManager() = default;
	~GameObjectManager() = default;
	GameObjectManager(GameObjectManager const&) = delete;

	friend class GameEngine;
};

#endif

