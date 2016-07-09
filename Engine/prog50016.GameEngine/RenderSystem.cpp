#include "Core.h"
#include "RenderSystem.h"
#include "Renderable.h"
#include "GameObjectManager.h"
#include "GameObject.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

void RenderSystem::initialize()
{
	ISystem::initialize();

	loadedSettings = false;
	window = NULL;
	views = "default";
	voriginX = 0;
	voriginY = 0;
	loadSettings();

	if (loadedSettings)
	{
		window = new sf::RenderWindow(sf::VideoMode(width, height), name.c_str());
		window->setFramerateLimit(60);

		if (views == "custom")
		{
			view = sf::View(sf::Vector2f(voriginX, voriginY), sf::Vector2f(width, height));
		}
		else
		{
			view = sf::View(sf::Vector2f((width * 0.5f), (-height * 0.5)), sf::Vector2f(width, height));
		}
	}
}

void RenderSystem::loadSettings()
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->LoadFile("Resources/RenderSystemSettings.xml");

	if (doc->ErrorID() == XML_SUCCESS)
	{
		XMLElement* element = NULL;

		element = doc->FirstChildElement("name");
		if (element != NULL)
		{
			name = element->GetText();
		}
		element = doc->FirstChildElement("width");
		if (element != NULL)
		{
			element->QueryIntText(&width);
		}
		element = doc->FirstChildElement("height");
		if (element != NULL)
		{
			element->QueryIntText(&height);
		}
		element = doc->FirstChildElement("fullscreen");
		if (element != NULL)
		{
			element->QueryBoolText(&fullscreen);
		}
		element = doc->FirstChildElement("Xorigin");
		if (element != NULL)
		{
			element->QueryIntText(&voriginX);
			views = "custom";
		}
		element = doc->FirstChildElement("Yorigin");
		if (element != NULL)
		{
			element->QueryIntText(&voriginY);
			views = "custom";
		}
		loadedSettings = true;
	}
	delete doc;
}

void RenderSystem::addRenderable(Renderable* renderable, int layer)
{
	renderComponents.insert(std::pair<int, Renderable*>(layer, renderable));
}

void RenderSystem::removeRenderable(Renderable* renderable, int layer)
{
	std::multimap<int, Renderable*>::iterator it = renderComponents.find(layer);
	while (it != renderComponents.end())
	{
		if ((*it).second == renderable)
		{
			renderComponents.erase(it);
			break;
		}
		++it;
	}
}

void RenderSystem::update(float deltaTime)
{
	if (window != NULL)
	{
		window->clear();

		window->setView(view);

		for (auto& iter : renderComponents)
		{
			if (iter.second->gameObject->isActive())
				iter.second->render(window, iter.second->gameObject->getTransform());
		}

		//const std::list<std::shared_ptr<GameObject>> gameObjectsToRender = GameObjectManager::Instance().GetAllRootGameObjects();
		//for (auto iter = gameObjectsToRender.begin(); iter != gameObjectsToRender.end(); ++iter)
		//{
		//	renderObject((*iter));
		//}

		window->display();
	}
}

void RenderSystem::renderObject(const std::shared_ptr<GameObject>& gObj)
{
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(1.0f, -1.0f, 1.0f);
	window->pushGLStates();

	std::multimap<STRCODE, std::shared_ptr<Component>>& components = gObj->getComponents();
	std::multimap<STRCODE, std::shared_ptr<Component>>::iterator iter = components.begin();
	while (iter != components.end())
	{
		(*iter).second->render(window, gObj->getTransform());
		++iter;
	}

	for (auto iter = gObj->children.begin(); iter != gObj->children.end(); ++iter)
	{
		renderObject((*iter));
	}

	window->popGLStates();
}

