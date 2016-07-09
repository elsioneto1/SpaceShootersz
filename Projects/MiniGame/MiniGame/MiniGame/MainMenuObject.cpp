#include "GameCore.h"

#include "MainMenuObject.h"
#include "MainMenu.h"

IMPLEMENT_DYNAMIC_CLASS(MainMenuObject)

MainMenuObject::MainMenuObject()
{

}

MainMenuObject::~MainMenuObject()
{

}

void MainMenuObject::load(XMLElement * node)
{
	if (node->FirstChildElement("id") != NULL)
	{
		id = atoi(node->FirstChildElement("id")->GetText());
		add = true;
	}
}

void MainMenuObject::initialize()
{
	if (add)
		MainMenu::Instance().addItem(this);
}

void MainMenuObject::setActive(bool b)
{
	gameObject->setActive(b);
}

void MainMenuObject::update(float deltaTime)
{
	// verify if element state is active   
	gameObject->setActive(mayUpdate);
	MainMenuElement::update();
	if (!mayUpdate)
	{
		return;
	}
}
