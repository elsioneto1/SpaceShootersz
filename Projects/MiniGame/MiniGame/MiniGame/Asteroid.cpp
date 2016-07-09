#include "GameCore.h"


#include "Asteroid.h"
#include "AsteroidPool.h"
#include "Transform.h"
#include "GameManager.h"
#include "Sprite.h"

IMPLEMENT_DYNAMIC_CLASS(Asteroid)


Asteroid::Asteroid()
{
}


Asteroid::~Asteroid()
{
}


void Asteroid::initialize()
{


	gameObject->getTransform()->setPosition(-3000,0);
	AsteroidPool::Instance().asteroidPool.push_back(this);
	int size = AsteroidPool::Instance().asteroidPool.size();
	sleeping = true;
	percentagePathCompletion = 0;
	life = 20;
	rotation = 0;
	damage = 120;
	velocity = 3;
	startX = 5000;
	startY = 5000;
	endX = 5000;
	endY = 5000;


}


void Asteroid::update(float deltaTime)
{
	Component::update(deltaTime);

	MainGameElement::update();
	gameObject->setActive(mayUpdate);
	if (!mayUpdate)
	{
		return;
	}

	

	if (!sleeping)
	{
		awakeBehaviour(deltaTime);
	}

}

void Asteroid::setAsteroidParams(float vel)
{

	velocity = vel;

	int random;
	rotation = Random.Random() * 90;

	random = Random.Random() * 10;
	int axis;
	if (random <= 5)
	{
		axis = -1; // spawn at Y
	}
	else if ( random > 5)
	{
		axis = 1; // spawn at X
	}

	bool positive;

	random = Random.Random() * 10;
	if (random <= 5)
	{
		positive = false;
	}
	else if (random > 5)
	{
		positive = true; 
	}

	if (axis < 0)
	{
		// crazy math setting up the initial and final position for the asteroids
		if (positive)
		{
			startY = -GameManager::Instance().screenHeight / 2 - 100;
			endY =  GameManager::Instance().screenHeight / 2 + 100;
			startX = (Random.Random()* GameManager::Instance().screenWidth) - GameManager::Instance().screenWidth / 2;
			endX = (Random.Random()* GameManager::Instance().screenHeight) - GameManager::Instance().screenHeight / 2;
		}
		else
		{
			startY = GameManager::Instance().screenHeight / 2 + 100;
			endY = -GameManager::Instance().screenHeight / 2 - 100;
			startX = (Random.Random()* GameManager::Instance().screenWidth) - GameManager::Instance().screenWidth / 2;
			endX = (Random.Random()* GameManager::Instance().screenHeight) - GameManager::Instance().screenHeight / 2;
		}

	}
	else if (axis> 0)
	{
		if (positive)
		{
			startY = (Random.Random()* GameManager::Instance().screenHeight) - GameManager::Instance().screenHeight / 2;
			endY = (Random.Random()* GameManager::Instance().screenHeight) - GameManager::Instance().screenHeight / 2;
			startX = -GameManager::Instance().screenWidth / 2 - 100;
			endX = GameManager::Instance().screenWidth / 2 + 100;
		}
		else
		{
			startY = (Random.Random()* GameManager::Instance().screenHeight) - GameManager::Instance().screenHeight / 2;
			endY = (Random.Random()* GameManager::Instance().screenHeight) - GameManager::Instance().screenHeight / 2;
			startX = GameManager::Instance().screenWidth / 2 + 100;
			endX = -GameManager::Instance().screenWidth / 2 - 100;
		}
	}

	
}


void Asteroid::awakeBehaviour(float deltaTime)
{

	// which point in the line is the asteroid
	percentagePathCompletion += deltaTime * velocity * 5 ;
	if (percentagePathCompletion < 100)
	{
		float percentage = percentagePathCompletion / 100;
		float x = ((endX - startX) * percentage) + startX;
		float y = ((endY - startY) * percentage) + startY;

		gameObject->getTransform()->setPosition(x,y);
	}
	else
	{
		Destroy();
	}
	rotation += deltaTime * velocity * 5;
	gameObject->getTransform()->setRotation(rotation);
}


void Asteroid::Hit()
{
	// increase damage value and change color for feedback
	damage += 5;
	std::shared_ptr<Component> spriteC = gameObject->GetComponentByType("Sprite");
	Sprite * sprite = (Sprite*)spriteC.get();
	sprite->renderableSprite->setColor(sf::Color(damage,200,200));
	if (damage > 250)
	{

		GameManager::Instance().increaseScore(10);
		Destroy();
		
	}
}

void Asteroid::Destroy()
{
	// back to sleep!
	damage = 120;
	sleeping = true;
	percentagePathCompletion = 0;
	std::shared_ptr<Component> spriteC = gameObject->GetComponentByType("Sprite");
	Sprite * sprite = (Sprite*)spriteC.get();
	sprite->renderableSprite->setColor(sf::Color(255, 255, 255));
	gameObject->getTransform()->setPosition(5000, 0);

}

void Asteroid::save(XMLElement * node, tinyxml2::XMLDocument* doc)
{

	XMLElement * Damage = doc->NewElement("Damage");
	Damage->SetAttribute("Value", damage);
	XMLElement * pos = doc->NewElement("PercentageComplete");
	pos->SetAttribute("Value", percentagePathCompletion);

	XMLElement * PathValues = doc->NewElement("PathValues");
	PathValues->SetAttribute("startX", startX);
	PathValues->SetAttribute("startY", startY);
	PathValues->SetAttribute("endX", endX);
	PathValues->SetAttribute("endY", endY);

	XMLElement * pSleeping = doc->NewElement("Sleeping");


	pSleeping->SetAttribute("Value", sleeping);

	XMLElement * pAngle = doc->NewElement("Angle");
	pAngle->SetAttribute("Value", rotation);



	node->InsertEndChild(Damage);
	node->InsertEndChild(pos);
	node->InsertEndChild(pSleeping);
	node->InsertEndChild(PathValues);
	node->InsertEndChild(pAngle);

}

void Asteroid::loadXML(XMLElement* node)
{
	
	node->FirstChildElement("Damage")->QueryIntAttribute("Value", &damage);
	node->FirstChildElement("PercentageComplete")->QueryFloatAttribute("Value", &percentagePathCompletion);
	node->FirstChildElement("Sleeping")->QueryBoolAttribute("Value", &sleeping);
	node->FirstChildElement("PathValues")->QueryIntAttribute("startX", &startX);
	node->FirstChildElement("PathValues")->QueryIntAttribute("startY", &startY);
	node->FirstChildElement("PathValues")->QueryIntAttribute("endX", &endX);
	node->FirstChildElement("PathValues")->QueryIntAttribute("endY", &endY);
	node->FirstChildElement("PathValues")->QueryFloatAttribute("Angle", &rotation);


	std::shared_ptr<Component> spriteC = gameObject->GetComponentByType("Sprite");
	Sprite * sprite = (Sprite*)spriteC.get();
	if (damage == 120)
		sprite->renderableSprite->setColor(sf::Color(255, 255, 255));
	else
		sprite->renderableSprite->setColor(sf::Color(damage, 200, 200));

}


