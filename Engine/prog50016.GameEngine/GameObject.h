#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#pragma once

#include "Object.h"

class Component;
class Transform;
class GameObjectManager;

class GameObject final : public Object
{
	friend class GameObjectManager;

	DECLARE_DYNAMIC_DERIVED_CLASS(GameObject, Object)

private:
	STRCODE fileID;
	STRCODE UID;
	std::string name;
	bool saveAble;

	bool active = true;

	std::multimap<STRCODE, std::shared_ptr<Component>> components;

	// We didn't make it and its safe in the component array
	Transform* transform;

public:
	std::weak_ptr<GameObject> parent;
	std::list<std::shared_ptr<GameObject>> children;

public:
	STRCODE getFileID() { return fileID; }
	void setFileID(STRCODE _fileID) { fileID = _fileID; }

	void setUID(STRCODE uid) { UID = uid; }
	STRCODE getUID() { return UID; }

	bool isActive() { return active; }
	void setActive(bool value) { active = value; }

	const std::string& getName() { return name; }

	void setTransform(Transform* trans) { transform = trans; }
	Transform* getTransform() { return transform; }

	void AddComponent(std::shared_ptr<Component> component);
	void RemoveComponent(STRCODE component);

	std::list<std::shared_ptr<GameObject>>& getChildren() { return children; }

	std::multimap<STRCODE, std::shared_ptr<Component>>& getComponents() { return components; }

	// The Following Get Component functions have been removed for test
	//Name of this has to be changed to "GetComponentByTypeName", being used in RenderSystem at the moment, must speak with a member
	std::shared_ptr<Component> GameObject::GetComponentByType(std::string className);
	//template <class CompType>
	//std::shared_ptr<CompType> GetComponentByUUID(STRCODE uuid);	
	//template <class CompType>
	//std::shared_ptr<CompType> GetComponent();
	//template <class CompType>
	//std::list<std::shared_ptr<CompType>> getComponents();
	//template <class T>
	//std::list<std::shared_ptr<T>> getComponents()
	//{
	//	std::list<std::shared_ptr<T>> requestedCompList;// = std::list<std::shared_ptr<CompType>>();
	//	for (std::multimap<STRCODE, std::shared_ptr<Component>>::iterator it = components.begin(); it != components; ++it)
	//	{
	//		if ((*it).second.get()->isA(T::getClassHashCode()))
	//		{
	//			requestedCompList.push_back((*it).second);
	//		}
	//	}
	//	return requestedCompList;
	//}

	virtual void update(float deltaTime);

	void load(XMLElement* node);
	void save(XMLElement* node);

	bool isSaveAble();
	void AddChild(std::shared_ptr<GameObject>);
	void RemoveChild(std::shared_ptr<GameObject>);
	std::weak_ptr<GameObject> getChildByName(std::string name);

};

#endif

