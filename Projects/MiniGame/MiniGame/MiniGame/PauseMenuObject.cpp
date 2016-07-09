#include "GameCore.h"
#include "PauseMenuObject.h"
#include "PauseMenu.h"
#include "GameManager.h"

IMPLEMENT_DYNAMIC_CLASS(PauseMenuObject)

PauseMenuObject::PauseMenuObject()
{
}


PauseMenuObject::~PauseMenuObject()
{
}

void PauseMenuObject::load(XMLElement * node)
{
	if (node->FirstChildElement("id") != NULL)
	{
		id = atoi(node->FirstChildElement("id")->GetText());
		add = true;
	}
}

void PauseMenuObject::initialize()
{
	if (add)
		PauseMenu::Instance().addItem(this);
	
}

void PauseMenuObject::setActive(bool b)
{
	
	gameObject->setActive(b);
}


void PauseMenuObject::update(float deltaTime)
{
	// verify if element state is active   
	gameObject->setActive(mayUpdate);
	PauseMenuElement::update();
	if (!mayUpdate)
	{
		return;
	}

}
