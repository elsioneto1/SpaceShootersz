#include "GameCore.h"
#include "MainPlayerController.h"
#include "Transform.h"
#include "GameManager.h"
#include "ShootPool.h"
#include "Sprite.h"

IMPLEMENT_DYNAMIC_CLASS(MainPlayerController)


void MainPlayerController::load(XMLElement* node)
{
	Component::load(node);

	speed = 9;

	node->FirstChildElement()->QueryFloatAttribute("Speed", &speed);
	

	
}

void MainPlayerController::initialize()
{
	gameOver = false;
	chasePosition = sf::Vector2f(0,0);
	currentPosition = sf::Vector2f(0,0);
	gameObject->getTransform()->setPosition(0,0);
	left = false;
	right = false;
	up = false;
	down = false;

	respawning = false;
	respawnTime = 2; // seconds
	respawnTimer = 0;

	immortal = false;
	immortalTime = 2; // seconds
	immortalTimer = 0;

	lives = 3;
	GameManager::Instance().mainPlayer = gameObject;
}


void MainPlayerController::update(float deltaTime)
{
	Component::update(deltaTime);

	
	// verify if element state is active   
	gameObject->setActive(mayUpdate);
	MainGameElement::update();
	if (!mayUpdate)
		return;
	
	if (gameOver)
		return;
	

	if (respawning)
	{
		respawnTimer += deltaTime;
		if (respawnTimer > respawnTime)
		{
			Component::gameObject->getTransform()->setPosition(0, 0);
			chasePosition = sf::Vector2f(0, 0);
			respawning = false;
			immortal = true;
			respawnTimer = 0;
			left = false;
			right = false;
			up = false;
			down = false;


			
		}
		else
		{
			Component::gameObject->getTransform()->setPosition(2000, 0);
		}

		return;
	}

	if (immortal)
	{
		immortalTimer += deltaTime;

		std::shared_ptr<Component> spriteC = gameObject->GetComponentByType("Sprite");
		Sprite * sprite = (Sprite*)spriteC.get();
		if (immortalTimer > immortalTime)
		{
			immortal = false;
			immortalTimer = 0;
			sprite->renderableSprite->setColor(sf::Color(255, 255, 255));
		}
		else
		{
			sprite->renderableSprite->setColor(sf::Color(128, 128, 255));
		}
	}


	//if (InputManager::Instance().mousePressed(sf::Mouse::Button::Left))
	{
		ShootPool::Instance().canShoot = true;
	}

	//if (InputManager::Instance().mouseReleased(sf::Mouse::Button::Left))
	{
		//ShootPool::Instance().canShoot = false;
	}


	inputManager();
	movementManager(deltaTime);



	


}


void MainPlayerController::inputManager()
{

	if (InputManager::Instance().keyPressed(sf::Keyboard::A))
	{
		left = true;
	}

	if (InputManager::Instance().keyReleased(sf::Keyboard::A))
	{

		left = false;
	}


	if (InputManager::Instance().keyPressed(sf::Keyboard::D))
	{
		right = true;
	}

	if (InputManager::Instance().keyReleased(sf::Keyboard::D))
	{

		right = false;
	}


	if (InputManager::Instance().keyPressed(sf::Keyboard::W))
	{
		up = true;
	}

	if (InputManager::Instance().keyReleased(sf::Keyboard::W))
	{

		up = false;
	}

	if (InputManager::Instance().keyPressed(sf::Keyboard::S))
	{
		down = true;
	}

	if (InputManager::Instance().keyReleased(sf::Keyboard::S))
	{

		down = false;
	}

}

void MainPlayerController::movementManager(float deltaTime)
{
	if (left)
	{
		chasePosition.x -= 20;
		if (chasePosition.x < -GameManager::Instance().screenWidth * 0.5f)
			chasePosition.x = -GameManager::Instance().screenWidth * 0.5f;
	}
	if (right)
	{
		chasePosition.x += 20;
		if (chasePosition.x > GameManager::Instance().screenWidth * 0.5f)
			chasePosition.x = GameManager::Instance().screenWidth * 0.5f;
	}
	if (down)
	{
		chasePosition.y += 18;
		if (chasePosition.y > GameManager::Instance().screenHeight * 0.5f)
			chasePosition.y = GameManager::Instance().screenHeight * 0.5f;
	}
	if (up)
	{
		chasePosition.y -= 14;
		if (chasePosition.y < -GameManager::Instance().screenHeight * 0.5f)
			chasePosition.y = -GameManager::Instance().screenHeight * 0.5f;
	}

	sf::Vector2f tempCurrpos = gameObject->getTransform()->getPosition();
	float distance = sqrt(
		((chasePosition.x - tempCurrpos.x) * (chasePosition.x - tempCurrpos.x)) +
		((chasePosition.y - tempCurrpos.y) * (chasePosition.y - tempCurrpos.y))
		);

	if (distance < 2.0f)
		return;

	float newX = gameObject->getTransform()->getPosition().x;
	float newY = gameObject->getTransform()->getPosition().y;
	newX -= (tempCurrpos.x - chasePosition.x) * speed * deltaTime;
	newY -= (tempCurrpos.y - chasePosition.y) * speed * deltaTime;


	currentPosition = sf::Vector2f(newX, newY);
	Component::gameObject->getTransform()->setPosition(currentPosition);
	

}

void MainPlayerController::save(XMLElement * node, tinyxml2::XMLDocument* doc)
{
	XMLElement * lifes = doc->NewElement("Lifes");
	lifes->SetAttribute("Value", lifes);
	XMLElement * pos = doc->NewElement("Pos");
	pos->SetAttribute("X", gameObject->getTransform()->getPosition().x);
	pos->SetAttribute("Y", gameObject->getTransform()->getPosition().y);

	XMLElement * SpecialInfo = doc->NewElement("SpecialInfo");
	SpecialInfo->SetAttribute("respawnTimer", respawnTimer);
	SpecialInfo->SetAttribute("respawning", respawning);
	SpecialInfo->SetAttribute("immortalTimer", immortalTimer);
	SpecialInfo->SetAttribute("immortal", immortal);

	node->InsertEndChild(SpecialInfo);
	node->InsertEndChild(lifes);
	node->InsertEndChild(pos);
}

void MainPlayerController::Destroy()
{
	decreaseLife();
	Component::gameObject->getTransform()->setPosition(3000,0);
	chasePosition = sf::Vector2f(3000,0);
	respawning = true;
}


void MainPlayerController::decreaseLife()
{

	lives--;
	if (lives < 0)
	{
		gameOver = true;
		
		return;
	}
	std::cout << "LIFES LEFT " << lives << std::endl;
}