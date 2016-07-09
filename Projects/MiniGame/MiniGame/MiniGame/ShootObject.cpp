#include "GameCore.h"

#include "ShootObject.h"
#include "Transform.h"
#include "ShootPool.h"


IMPLEMENT_DYNAMIC_CLASS(ShootObject)

ShootObject::ShootObject()
{



}


ShootObject::~ShootObject()
{

}


void ShootObject::initialize()
{
	Component::initialize();
	onScreen = false;



	// external structure to store the shoots
	ShootPool::Instance().ufoPool.push_back(this);
	

}

void ShootObject::load(XMLElement * element)
{

	Component::load(element);

}


void ShootObject::update(float deltaTime)
{
	// basically the soot movement. The collision is manages by the game manager
	Component::update(deltaTime);
	MainGameElement::update();
	gameObject->setActive(mayUpdate);
	if (!mayUpdate)
	{
		return;
	}
	if (onScreen)
	{
		gameObject->getTransform()->move(0, -1500 * deltaTime);

		if (gameObject->getTransform()->getPosition().y < -RenderSystem::Instance().GetRenderWindow()->getViewport(RenderSystem::Instance().GetRenderWindow()->getView()).height)
		{
			onScreen = false;

			gameObject->getTransform()->setPosition(0, 10000);
		}
	}

}