#include "GameCore.h"

#include "EnemyShootObject.h"
#include "EnemyShootPool.h"
#include "Transform.h"
#include "GameManager.h"
#include "MainPlayerController.h"

IMPLEMENT_DYNAMIC_CLASS(EnemyShootObject)

EnemyShootObject::EnemyShootObject()
{
}


EnemyShootObject::~EnemyShootObject()
{
}



void EnemyShootObject::initialize()
{
	Component::initialize();
	onScreen = false;



	// external structure to store the shoots
	EnemyShootPool::Instance().ufoPool.push_back(this);

	// normal vector for the direction
	direction.x = 0;
	direction.y = 0;

	// stay off the screen!
	gameObject->getTransform()->setPosition(2000, 0);

}

void EnemyShootObject::load(XMLElement * element)
{

	Component::load(element);

}


void EnemyShootObject::update(float deltaTime)
{
	Component::update(deltaTime);

	MainGameElement::update();

	// set active only toggles if a object is rendering or not ( modified in the engine)
	gameObject->setActive(mayUpdate);
	if (!mayUpdate)
	{
		return;
	}
	if (onScreen)
	{
		//velocity
		float f = 500;
		gameObject->getTransform()->move((direction * f ) * deltaTime );
		
		
		// is on screen bounds?
		if (gameObject->getTransform()->getPosition().y <		-GameManager::Instance().screenHeight /2
			|| gameObject->getTransform()->getPosition().y >	GameManager::Instance().screenHeight / 2
			|| gameObject->getTransform()->getPosition().x <	-GameManager::Instance().screenWidth / 2
			|| gameObject->getTransform()->getPosition().x >	GameManager::Instance().screenWidth / 2)
		{
			onScreen = false;

			gameObject->getTransform()->setPosition(0, 10000);
		}

		// distance to the player
		float distance = sqrt(
			(
				(
					gameObject->getTransform()->getPosition().x - GameManager::Instance().mainPlayer->getTransform()->getPosition().x) * (gameObject->getTransform()->getPosition().x - GameManager::Instance().mainPlayer->getTransform()->getPosition().x)
				)
			+
			(
				(
					gameObject->getTransform()->getPosition().y - GameManager::Instance().mainPlayer->getTransform()->getPosition().y) * (gameObject->getTransform()->getPosition().y - GameManager::Instance().mainPlayer->getTransform()->getPosition().y)
				)
			)
			;

		// see if it hits the object
		if (distance < 40)
		{
			std::shared_ptr<Component> ufoC = GameManager::Instance().mainPlayer->GetComponentByType("MainPlayerController");
			MainPlayerController* player = (MainPlayerController*)ufoC.get();
			if (!player->immortal)
				GameManager::Instance().destroyPlayer(player);
		}



	}
}

void EnemyShootObject::save(XMLElement * node, tinyxml2::XMLDocument* doc)
{


	XMLElement * pPos = doc->NewElement("Pos");
	pPos->SetAttribute("X", gameObject->getTransform()->getPosition().x);
	pPos->SetAttribute("Y", gameObject->getTransform()->getPosition().y);


	XMLElement * normalDirection = doc->NewElement("normalDirection");
	normalDirection->SetAttribute("X", direction.x);
	normalDirection->SetAttribute("Y", direction.y);


	XMLElement * onScreen = doc->NewElement("OnScreen");
	onScreen->SetAttribute("Value", onScreen);

	node->InsertEndChild(pPos);
	node->InsertEndChild(onScreen);
	node->InsertEndChild(normalDirection);
}

void EnemyShootObject::loadXML(XMLElement * node)
{
	int posX;
	int posY;
	node->FirstChildElement("Pos")->QueryIntAttribute("X", &posX);
	node->FirstChildElement("Pos")->QueryIntAttribute("Y", &posY);
	gameObject->getTransform()->setPosition(posX,posY);
	node->FirstChildElement("normalDirection")->QueryFloatAttribute("X", &direction.x);
	node->FirstChildElement("normalDirection")->QueryFloatAttribute("Y", &direction.y);
	node->FirstChildElement("OnScreen")->QueryBoolAttribute("Value", &onScreen);

}
