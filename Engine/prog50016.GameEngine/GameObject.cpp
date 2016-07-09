#include "Core.h"
#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"

IMPLEMENT_DYNAMIC_CLASS(GameObject)

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	STRCODE _componentHashCode = component->getDerivedClassHashCode();
	std::multimap<STRCODE, std::shared_ptr<Component>>::iterator it = components.find(_componentHashCode);
	if (it != components.end())
	{
		(*it).second.reset();
	}

	components.insert(std::pair<STRCODE, std::shared_ptr<Component>>(component->getDerivedClassHashCode(), component));
}

void GameObject::RemoveComponent(STRCODE component)
{
	std::multimap<STRCODE, std::shared_ptr<Component>>::iterator it = components.find(component);
	if (it != components.end())
	{
		(*it).second.reset();
		components.erase(component);
	}
}

//template <class CompType>
//std::shared_ptr<CompType> GameObject::GetComponentByUUID(STRCODE uuid)
//{
//	std::multimap<STRCODE, std::shared_ptr<Component>>::iterator it = components.find(uuid);
//
//	if (it != components.end())
//	{
//		return (*it).second;
//	}
//
//	return std::shared_ptr<CompType>();
//}
//
//template <class CompType>
//std::shared_ptr<CompType> GameObject::GetComponent()
//{
//	// Returns the first component found of given type
//	for (std::multimap<STRCODE, std::shared_ptr<Component>>::iterator it = components.begin(); it != components; ++it)
//	{
//		if ((*it).second.get()->getClassName == comp)
//		{
//			return (*it).second;
//		}
//	}
//}
//
std::shared_ptr<Component> GameObject::GetComponentByType(std::string className)
{
	for (auto it = components.begin(); it != components.end(); it++)
	{
		if (it->second->getDerivedClassName() == className)
		{
			return it->second;
		}
	}

	return nullptr;
}
//template <class CompType>
//std::list<std::shared_ptr<CompType>> GameObject::getComponents()
//{
//	std::list<std::shared_ptr<CompType>> requestedCompList = std::list<std::shared_ptr<CompType>>();
//
//	for (std::multimap<STRCODE, std::shared_ptr<Component>>::iterator it = components.begin(); it != components; ++it)
//	{
//		if ((*it).second.get()->getClassName == comp)
//		{
//			requestedCompList.push_back((*it).second);
//		}
//	}
//
//	return requestedCompList;
//}

void GameObject::update(float deltaTime)
{
	for (auto component : components)
	{
		component.second->update(deltaTime);
	}
}

void GameObject::load(XMLElement* node)
{
	if (node != NULL)
	{
		UID = getHashCode(node->Attribute("uuid"));
		name = node->Attribute("name");

		XMLElement* compsElement = node->FirstChildElement("Components");
		if (compsElement != NULL)
		{
			XMLElement* cElement = compsElement->FirstChildElement("Component");
			while (cElement != NULL)
			{
				const char* className = cElement->Attribute("class");
				THROW_RUNTIME_ERROR(className == nullptr, "Component class name missing");

				std::shared_ptr<Component> component((Component*)CreateObject(className));
				component->setGameObject(this);
				component->load(cElement);
				component->initialize();
				AddComponent(component);
			
				cElement = cElement->NextSiblingElement("Component");
			}
		}

		//XMLElement* childElement = node->FirstChildElement("Children");
		//if (childElement != NULL)
		//{
		//	XMLElement* gameObjElement = childElement->FirstChildElement("GameObject");
		//	while (gameObjElement != NULL)
		//	{
		//		std::shared_ptr<GameObject> childObj = std::shared_ptr<GameObject>(new GameObject());

		//		childObj->setFileID(fileID);
		//		childObj->load(gameObjElement);
		//		
		//		childObj->parent = this;
		//		addChild(childObj);

		//		gameObjElement = gameObjElement->NextSiblingElement("GameObject");
		//	}
		//}
	}
}

void GameObject::save(XMLElement* node)
{
	tinyxml2::XMLElement* compsElement = node->GetDocument()->NewElement("Components");
	node->GetDocument()->InsertFirstChild(compsElement);;
	for (std::multimap<STRCODE, std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it)
	{
		tinyxml2::XMLElement* cElement = node->GetDocument()->NewElement("Component");
		cElement->SetAttribute("class", (*it).second->getDerivedClassName().c_str());
		(*it).second->save(cElement);
		compsElement->InsertEndChild(cElement);
	}
	tinyxml2::XMLElement* childElement = node->GetDocument()->NewElement("Children");
	node->GetDocument()->InsertFirstChild(compsElement);
	for (std::list<std::shared_ptr<GameObject>>::iterator iter = children.begin(); iter != children.end();)
	{
		tinyxml2::XMLElement* childGObjElement = node->GetDocument()->NewElement("GameObject");
		childGObjElement->SetAttribute("class", (*iter)->getDerivedClassName().c_str());
		(*iter)->save(childGObjElement);
		childElement->InsertEndChild(childGObjElement);
	}
}

bool GameObject::isSaveAble()
{
	return saveAble;
}

void GameObject::AddChild(std::shared_ptr<GameObject> gameObject)
{
	children.push_back(gameObject);
}

void GameObject::RemoveChild(std::shared_ptr<GameObject> gameObject)
{
	for (std::list<std::shared_ptr<GameObject>>::iterator iter = children.begin(); iter != children.end();)
	{
		if ((*iter) == gameObject)
		{
			children.erase(iter);
			break;
		}
		else
		{
			++iter;
		}
	}
}

std::weak_ptr<GameObject> GameObject::getChildByName(std::string name)
{
	for (std::list<std::shared_ptr<GameObject>>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		if ((*iter)->getName() == name)
		{
			return (*iter);
		}
	}
	// if one is not found, return an empty game object...
	return std::weak_ptr<GameObject>();
}

