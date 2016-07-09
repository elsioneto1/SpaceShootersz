


#include "GameCore.h"

#include "UFOController.h"

#include "Transform.h"
#include "GameManager.h"
#include "UFOPoolManager.h"
#include "EnemyShootPool.h"

IMPLEMENT_DYNAMIC_CLASS(UFOController)
UFOController::~UFOController()
{
	GameManager::Instance().UFOs.remove(gameObject);
}

void UFOController::initialize()
{
	Component::initialize();
	

	sf::Vector2f pos;
	pos.x = (0);
	pos.y = (-800);
	gameObject->getTransform()->setPosition(pos);
	destroy = (RenderSystem::Instance().GetRenderWindow()->getSize().y * 0.5f) + 48.0f;
	

	GameManager::Instance().UFOs.push_back (gameObject);
	onScreen = false;


	UFOPoolManager::Instance().ufoPool.push_back(this);

	behaviourComplete = 0;
	behaviourDefined = false;
	selectedBehaviour = -1;
	subBehaviour = -1;

	startX = 5000;
	startY = 5000;
	endX = 5000;
	endY = 5000;
}

void UFOController::load(XMLElement* element)
{
	Component::load(element);


	float min;
	element->FirstChildElement("MinSpeed")->QueryFloatAttribute("value", &min);
	float max;
	element->FirstChildElement("MaxSpeed")->QueryFloatAttribute("value", &max);

	
	speed = Random.Random() * max + min;


}

void UFOController::update(float deltaTime)
{
	Component::update(deltaTime);

	gameObject->setActive(mayUpdate);
	MainGameElement::update();
	if (!mayUpdate)
	{
		return;
	}

	if (!onScreen)
	{
		behaviourDefined = false;
		gameObject->getTransform()->setPosition(0, -800);//RenderSystem::Instance().GetRenderWindow()->getSize().y / 2);
		return;
	}
	else
	{
		behaviour1();
	}

}


void UFOController::behaviour1()
{
	if (!behaviourDefined )
	{
		behaviourComplete = 0;
		behaviourDefined = true;
		subBehaviour = Random.Random() * 5;

		startX = 0;
		startY = 0;


		if (subBehaviour == 4)
		{
			startX = Random.Random() * 720 - 360;
		}
		endX	= 720;
		endY	= 1024;

	}
	 

	if (behaviourComplete < 100)
	{
		// when the ufo should shoot at you
		if (behaviourComplete > 40 && behaviourComplete < 60)
		{
			EnemyShootPool::Instance().spawnShots(60,gameObject->getTransform()->getPosition());
		}

		// CRAZY MATH AHEAD, STOP AT THIS POINT

		// basically it's quadratic + cubic + crazy variation  with specific variation
		// the X behaviour is linear, while the Y one is doing the variations
		if (subBehaviour >= 0)
		{
			if (subBehaviour == 0)
			{
				behaviourComplete += 0.5;

				float percentageComplete = (behaviourComplete / 100);
				float fX;

				fX = ((startX - endX)) * (behaviourComplete / 100) + 360;

				float behaviourY = ((9 * (percentageComplete *percentageComplete * percentageComplete)) -
					15 * (percentageComplete *percentageComplete))
					+ 30 * (percentageComplete*percentageComplete*percentageComplete*percentageComplete*percentageComplete);
	
				float fY = behaviourY  *  endY*0.5 + endY / 2;

				gameObject->getTransform()->setPosition(fX, fY);
			}
			else if (subBehaviour == 1)
			{
				behaviourComplete += 0.5;

				float percentageComplete = (behaviourComplete / 100);
				float fX;

				fX = (( endX - startX )) * (behaviourComplete / 100) - 360 ;

				float behaviourY = ((9 * (percentageComplete *percentageComplete * percentageComplete)) -
					15 * (percentageComplete *percentageComplete))
					+ 30 * (percentageComplete*percentageComplete*percentageComplete*percentageComplete*percentageComplete);

				float fY = behaviourY  *  endY*0.5 + endY / 2;

				gameObject->getTransform()->setPosition(fX, fY);
			}
			else if (subBehaviour == 2)
			{
				behaviourComplete += 0.5;

				float percentageComplete = (behaviourComplete / 100);
				float fX;

				fX = ((endX - startX)) * (behaviourComplete / 100) - 360;

				float behaviourY = ((9 * (percentageComplete *percentageComplete * percentageComplete)) -
					15 * (percentageComplete *percentageComplete))
					+ 30 * (percentageComplete*percentageComplete*percentageComplete*percentageComplete*percentageComplete);

				float fY = -behaviourY  *  endY*0.5 + -endY / 2;

				gameObject->getTransform()->setPosition(fX, fY);
			}
			else if (subBehaviour == 3)
			{
				behaviourComplete += 0.5;

				float percentageComplete = (behaviourComplete / 100);
				float fX;

				fX = ((startX - endX)) * (behaviourComplete / 100) + 360;

				float behaviourY = ((9 * (percentageComplete *percentageComplete * percentageComplete)) -
					15 * (percentageComplete *percentageComplete))
					+ 30 * (percentageComplete*percentageComplete*percentageComplete*percentageComplete*percentageComplete);

				float fY = -behaviourY  *  endY*0.5 + -endY / 2;

				gameObject->getTransform()->setPosition(fX, fY);
			}
			else if (subBehaviour == 4)
			{
				behaviourComplete += 0.5;

				float percentageComplete = (behaviourComplete / 100);
				float fX;

				fX = 0;

				float behaviourY = ((9 * (percentageComplete *percentageComplete * percentageComplete)) -
					15 * (percentageComplete *percentageComplete))
					+ 30 * (percentageComplete*percentageComplete*percentageComplete*percentageComplete*percentageComplete);

				float fY = -behaviourY  *  endY*0.5 + -endY / 2;

				gameObject->getTransform()->setPosition(fX, fY);
			}
		}
	
	}
	else
	{
		endBehaviour();
	}

}

void UFOController::endBehaviour()
{
	// set everything to the inital state
	behaviourDefined = false;
	behaviourComplete = 0;
	behaviourDefined = false;
	selectedBehaviour = -1;
	subBehaviour = -1;
	onScreen = false;

}

void  UFOController::save(XMLElement * node, tinyxml2::XMLDocument* doc)
{

	XMLElement * pos = doc->NewElement("PercentageComplete");
	pos->SetAttribute("Value", behaviourComplete);

	XMLElement * PathValues = doc->NewElement("PathValues");
	PathValues->SetAttribute("startX", startX);
	PathValues->SetAttribute("startY", startY);
	PathValues->SetAttribute("endX", endX);
	PathValues->SetAttribute("endY", endY);

	XMLElement * pSleeping = doc->NewElement("Sleeping");
	pSleeping->SetAttribute("Value", onScreen);


	XMLElement * pBehaviour = doc->NewElement("Behaviour");
	pBehaviour->SetAttribute("behaviourDefined", behaviourDefined);
	pBehaviour->SetAttribute("subBehaviour", subBehaviour);

	node->InsertEndChild(pos);
	node->InsertEndChild(pBehaviour);
	node->InsertEndChild(pSleeping);
	node->InsertEndChild(PathValues);
	
}

void UFOController::loadXML(XMLElement * node)
{

	node->FirstChildElement("PercentageComplete")->QueryFloatAttribute("Value", &behaviourComplete);
	node->FirstChildElement("Sleeping")->QueryBoolAttribute("Value", &onScreen);
	node->FirstChildElement("PathValues")->QueryFloatAttribute("startX", &startX);
	node->FirstChildElement("PathValues")->QueryFloatAttribute("startY", &startY);
	node->FirstChildElement("PathValues")->QueryFloatAttribute("endX", &endX);
	node->FirstChildElement("PathValues")->QueryFloatAttribute("endY", &endY);
	node->FirstChildElement("Behaviour")->QueryBoolAttribute("behaviourDefined", &behaviourDefined);
	node->FirstChildElement("Behaviour")->QueryIntAttribute("subBehaviour", &subBehaviour);

}
