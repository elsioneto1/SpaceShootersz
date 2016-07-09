#include "GameCore.h"
#include "GameManager.h"
#include "Transform.h"
#include "UFOController.h"
#include "ShootPool.h"
#include "Transform.h"
#include "Asteroid.h"
#include "AsteroidPool.h"
#include "MainPlayerController.h"
#include "EnemyShootPool.h"
#include "ShootPool.h"
#include "UFOPoolManager.h"




void GameManager::update(float deltaTime)
{
	
	if (onMenu)
	{

	}
	else if (onMainGame)
	{
		updateMainGame();
	}
	else if (onPause)
	{

	}
}

void GameManager::updateMenu()
{

}

void GameManager::updateMainGame()
{
	int i;
	int j;
	float distance;
	
	// just to make sure...
	if (mainPlayer == nullptr)
		return;

	std::list<GameObject*>::iterator ufoIterator;

	for (ufoIterator = UFOs.begin(); ufoIterator != UFOs.end(); ++ufoIterator)
	{

		std::shared_ptr<Component> ufoC = (*ufoIterator)->GetComponentByType("UFOController");
		UFOController* ufo = (UFOController*)ufoC.get();
		
		if (ufo->onScreen)
		{

			for ( i = 0; i < ShootPool::Instance().ufoPool.size(); i++)
			{

				if (ShootPool::Instance().ufoPool[i]->onScreen)
				{

					 distance = sqrt(
						(
							(
								(*ufoIterator)->getTransform()->getPosition().x - ShootPool::Instance().ufoPool[i]->gameObject->getTransform()->getPosition().x) * ((*ufoIterator)->getTransform()->getPosition().x - ShootPool::Instance().ufoPool[i]->gameObject->getTransform()->getPosition().x)
							)
						+
						(
							(
								(*ufoIterator)->getTransform()->getPosition().y - ShootPool::Instance().ufoPool[i]->gameObject->getTransform()->getPosition().y) * ((*ufoIterator)->getTransform()->getPosition().y - ShootPool::Instance().ufoPool[i]->gameObject->getTransform()->getPosition().y)
							)
						)
						;

					if (distance < 50.0f)
					{
						
						ShootPool::Instance().ufoPool[i]->onScreen = false;
						ShootPool::Instance().ufoPool[i]->gameObject->getTransform()->setPosition(10000, 0);
						ufo->onScreen = false;
						increaseScore(25);
					}

				}
			}
		}
	}

	
	for ( j = 0; j < AsteroidPool::Instance().asteroidPool.size(); j++)
	{
		

		if ( !AsteroidPool::Instance().asteroidPool[j]->sleeping)
		{ 
			for (i = 0; i < ShootPool::Instance().ufoPool.size(); i++)
			{

				if (ShootPool::Instance().ufoPool[i]->onScreen)
				{

					 distance = sqrt(
						(
							(
								AsteroidPool::Instance().asteroidPool[j]->gameObject->getTransform()->getPosition().x - ShootPool::Instance().ufoPool[i]->gameObject->getTransform()->getPosition().x) * (AsteroidPool::Instance().asteroidPool[j]->gameObject->getTransform()->getPosition().x - ShootPool::Instance().ufoPool[i]->gameObject->getTransform()->getPosition().x)
							)
						+
						(
							(
								AsteroidPool::Instance().asteroidPool[j]->gameObject->getTransform()->getPosition().y - ShootPool::Instance().ufoPool[i]->gameObject->getTransform()->getPosition().y) * (AsteroidPool::Instance().asteroidPool[j]->gameObject->getTransform()->getPosition().y - ShootPool::Instance().ufoPool[i]->gameObject->getTransform()->getPosition().y)
							)
						)
						;


					if (distance < 50.0f)
					{
						//GameManager::Instance().score += 10;
						AsteroidPool::Instance().asteroidPool[j]->Hit();
						ShootPool::Instance().ufoPool[i]->onScreen = false;
						ShootPool::Instance().ufoPool[i]->gameObject->getTransform()->setPosition(10000, 0);
					}




				}
			}





			//verify collision with player

			 distance = sqrt(
				(
					(
						AsteroidPool::Instance().asteroidPool[j]->gameObject->getTransform()->getPosition().x - mainPlayer->getTransform()->getPosition().x) * (AsteroidPool::Instance().asteroidPool[j]->gameObject->getTransform()->getPosition().x - mainPlayer->getTransform()->getPosition().x)
					)
				+
				(
					(
						AsteroidPool::Instance().asteroidPool[j]->gameObject->getTransform()->getPosition().y - mainPlayer->getTransform()->getPosition().y) * (AsteroidPool::Instance().asteroidPool[j]->gameObject->getTransform()->getPosition().y - mainPlayer->getTransform()->getPosition().y)
					)
				)
				;


			 if (distance < 40)
			 {
				 std::shared_ptr<Component> ufoC = mainPlayer->GetComponentByType("MainPlayerController");
				 MainPlayerController* player = (MainPlayerController*)ufoC.get();
				 if (!player->immortal)
					 destroyPlayer(player);
			 }



		}
	}


	if (InputManager::Instance().keyPressed(sf::Keyboard::P))
	{
		setMaingame(false);
		setPause(true);
	}



}

void GameManager::updatePause()
{

}

void GameManager::increaseScore(int add)
{
	score += add;

	std::cout << "Score " << score << std::endl;

	if (score > highScore)
	{
		highScore = score;
	}
	std::cout << "HIGH SCORE " << highScore << std::endl;
}


void GameManager::destroyPlayer(void * player)
{
	MainPlayerController* playerCast = (MainPlayerController*)player;

	playerCast->Destroy();
	if (playerCast->gameOver)
	{
		cleanObjects();
		saveScore();
		std::cout << "GAME OVER!!"<< std::endl;
	}
	

}

void GameManager::cleanObjects()
{
	int j;
	for (j = 0; j < AsteroidPool::Instance().asteroidPool.size(); j++)
	{
		AsteroidPool::Instance().asteroidPool[j]->Destroy();
	}

	std::list<GameObject*>::iterator ufoIterator;
	for (ufoIterator = UFOs.begin(); ufoIterator != UFOs.end(); ++ufoIterator)
	{
		std::shared_ptr<Component> ufoC = (*ufoIterator)->GetComponentByType("UFOController");
		UFOController* ufo = (UFOController*)ufoC.get();
		ufo->endBehaviour();
	}

	for (j = 0; j < EnemyShootPool::Instance().ufoPool.size(); j++)
	{
		EnemyShootPool::Instance().ufoPool[j]->onScreen = false;
		EnemyShootPool::Instance().ufoPool[j]->gameObject->getTransform()->setPosition(3000, 0);
	}

	for (j = 0; j < ShootPool::Instance().ufoPool.size(); j++)
	{
		ShootPool::Instance().ufoPool[j]->onScreen = false;
		ShootPool::Instance().ufoPool[j]->gameObject->getTransform()->setPosition(3000,0);
	}

	setMenu(true);
	setMaingame(false);
	setPause(false);
}

void GameManager::saveScore()
{
	tinyxml2::XMLDocument xmlDoc;

	XMLNode * pRoot = xmlDoc.NewElement("Root");
	xmlDoc.InsertFirstChild(pRoot);

	XMLElement * pScore = xmlDoc.NewElement("HighScore");
	pScore->SetAttribute("HighScore", highScore);
	pRoot->InsertEndChild(pScore);

	


	XMLError eResult = xmlDoc.SaveFile("HighScore.xml");

}


void GameManager::saveGame()
{
	// save the whole thing!

	tinyxml2::XMLDocument xmlDoc;

	XMLNode * pRoot = xmlDoc.NewElement("Root");
	xmlDoc.InsertFirstChild(pRoot);

	XMLElement * pGameManager = xmlDoc.NewElement("GameManager");

	pGameManager->SetAttribute("Score", score);
	pRoot->InsertEndChild(pGameManager);


	XMLElement * pPlayer = xmlDoc.NewElement("PlayerInfo");
	std::shared_ptr<Component> ufoC = mainPlayer->GetComponentByType("MainPlayerController");
	MainPlayerController* player = (MainPlayerController*)ufoC.get();
	player->save(pPlayer, &xmlDoc);
	pRoot->InsertEndChild(pPlayer);

	pGameManager->SetAttribute("Score", score);
	pRoot->InsertEndChild(pGameManager);


	XMLElement * pAsteroids = xmlDoc.NewElement("Asteroids");
	int j;
	for (j = 0; j < AsteroidPool::Instance().asteroidPool.size(); j++)
	{
		XMLElement * pAsteroid = xmlDoc.NewElement("Asteroid");
		AsteroidPool::Instance().asteroidPool[j]->save(pAsteroid, &xmlDoc);
		pAsteroids->InsertEndChild(pAsteroid);
	}
	pRoot->InsertEndChild(pAsteroids);


	XMLElement * pUfos = xmlDoc.NewElement("Ufos");
	for (j = 0; j < UFOPoolManager::Instance().ufoPool.size(); j++)
	{
		XMLElement * pUfo = xmlDoc.NewElement("Ufo");
		UFOPoolManager::Instance().ufoPool[j]->save(pUfo, &xmlDoc);
		pUfos->InsertEndChild(pUfo);
	}
	pRoot->InsertEndChild(pUfos);


	XMLElement * pShoots = xmlDoc.NewElement("Shoots");
	for (j = 0; j < EnemyShootPool::Instance().ufoPool.size(); j++)
	{
		XMLElement * pUfo = xmlDoc.NewElement("Bullet");
		EnemyShootPool::Instance().ufoPool[j]->save(pUfo, &xmlDoc);
		pShoots->InsertEndChild(pUfo);
	}
	pRoot->InsertEndChild(pShoots);


	XMLError eResult = xmlDoc.SaveFile("SaveGame.xml");



}

void GameManager::loadGame()
{
	// load the whole thing!
	tinyxml2::XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile("SaveGame.xml");

	// if there's an error, throw a polite message
	if (eResult != XMLError::XML_SUCCESS)
	{
		std::cout << "There is an error with your Save File. Sorry for that!" << std::endl;
	}
	else
	{

		XMLElement* pRoot = xmlDoc.FirstChildElement();

		std::shared_ptr<Component> ufoC = mainPlayer->GetComponentByType("MainPlayerController");
		MainPlayerController* player = (MainPlayerController*)ufoC.get();
		pRoot->FirstChildElement("PlayerInfo")->FirstChildElement("Lifes")->QueryIntAttribute("Value", &player->lives);
		int playerX;
		int playerY;
		pRoot->FirstChildElement("PlayerInfo")->FirstChildElement("Pos")->QueryIntAttribute("X", &playerX);
		pRoot->FirstChildElement("PlayerInfo")->FirstChildElement("Pos")->QueryIntAttribute("Y", &playerY);
		player->gameObject->getTransform()->setPosition(playerX,playerY);
		player->currentPosition.x = playerX;
		player->currentPosition.y = playerY;
		player->chasePosition.x = playerX;
		player->chasePosition.y = playerY;

		pRoot->FirstChildElement("PlayerInfo")->FirstChildElement("SpecialInfo")->QueryFloatAttribute("respawnTimer", &player->respawnTimer);
		pRoot->FirstChildElement("PlayerInfo")->FirstChildElement("SpecialInfo")->QueryFloatAttribute("immortalTimer", &player->immortalTimer);
		pRoot->FirstChildElement("PlayerInfo")->FirstChildElement("SpecialInfo")->QueryBoolAttribute("respawning", &player->respawning);
		pRoot->FirstChildElement("PlayerInfo")->FirstChildElement("SpecialInfo")->QueryBoolAttribute("immortal", &player->immortal);
		player->gameOver = false;


		pRoot->FirstChildElement("GameManager")->QueryIntAttribute("Score", &score);



		int j;
		XMLElement* asteroidNode;
		asteroidNode = pRoot->FirstChildElement("Asteroids")->FirstChildElement();
		for (j = 0; j < AsteroidPool::Instance().asteroidPool.size(); j++)
		{
			
			AsteroidPool::Instance().asteroidPool[j]->loadXML(asteroidNode);
			asteroidNode = asteroidNode->NextSiblingElement();
		}

		XMLElement* ufosNode;
		ufosNode = pRoot->FirstChildElement("Ufos")->FirstChildElement();
		for (j = 0; j < UFOPoolManager::Instance().ufoPool.size(); j++)
		{
			UFOPoolManager::Instance().ufoPool[j]->loadXML(ufosNode);
			ufosNode = ufosNode->NextSiblingElement();
		}

		XMLElement* bulletsNode;
		bulletsNode = pRoot->FirstChildElement("Shoots")->FirstChildElement();
		for (j = 0; j < EnemyShootPool::Instance().ufoPool.size(); j++)
		{
		
			EnemyShootPool::Instance().ufoPool[j]->loadXML(bulletsNode);
			bulletsNode = bulletsNode->NextSiblingElement();
		}



		setMenu(false);
		setMaingame(true);

	}
}