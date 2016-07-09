#include "GameCore.h"
#include "Background.h"
#include "Transform.h"
#include "GameManager.h"

IMPLEMENT_DYNAMIC_CLASS(Background)




Background::Background()
{
}


Background::~Background()
{
}

void Background::load(XMLElement* node)
{
	vel = 0;
	node->FirstChildElement("Velocity")->QueryFloatAttribute("Value", &vel);

}

void Background::initialize()
{

}

void Background::update(float deltaTime)
{
	if (GameManager::Instance().getPause())
		return;
	//When it reaches the bootom, send them up!
	gameObject->getTransform()->move(0,15);
	if (gameObject->getTransform()->getPosition().y > 768)
	{
		gameObject->getTransform()->setPosition(gameObject->getTransform()->getPosition().x, gameObject->getTransform()->getPosition().y - 768 - 768);
	}
}
