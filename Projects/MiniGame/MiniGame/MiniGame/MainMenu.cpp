#include "GameCore.h"
#include "MainMenuStructure.h"

#include "MainMenu.h"
#include "GameManager.h"
#include "MainPlayerController.h"
#include <cstdlib>
IMPLEMENT_DYNAMIC_CLASS(MainMenu)


MainMenu::MainMenu()
{

}


MainMenu::~MainMenu()
{

}

void MainMenu::initialize()
{

	MainMenuStructure::Instance().selectedIndex = 0;
	p_mmo = NULL;
}

void MainMenu::update(float deltaTime)
{

	gameObject->setActive(mayUpdate);
	MainMenuElement::update();
	if (!mayUpdate)
	{
		return;
	}

	maxIndex = MainMenuStructure::Instance().menuObjs.size();

	
	if (InputManager::Instance().keyPressed(sf::Keyboard::Up))
	{
		//std::cout << " up " << std::endl;
		if (MainMenuStructure::Instance().selectedIndex > 0)
		{
			MainMenuStructure::Instance().selectedIndex--;
		}
	}
	else if (InputManager::Instance().keyPressed(sf::Keyboard::Down))
	{
		if (MainMenuStructure::Instance().selectedIndex < maxIndex - 1)
		{
			MainMenuStructure::Instance().selectedIndex++;
		}
		//std::cout << " down " << std::endl;
		
	}

	for (int i = 0; i < maxIndex; i++)
	{
		MainMenuStructure::Instance().menuObjs[i]->setActive(true);

	}

	if (MainMenuStructure::Instance().menuObjs.size() > 0)
	{
		MainMenuStructure::Instance().menuObjs[MainMenuStructure::Instance().selectedIndex]->setActive(false);
		p_mmo = MainMenuStructure::Instance().menuObjs[MainMenuStructure::Instance().selectedIndex];
	}


	if (InputManager::Instance().keyPressed(sf::Keyboard::Return))
	{

		if (p_mmo != NULL)
		{
			acceptInput(p_mmo);
		}
	}


}

void MainMenu::acceptInput(MainMenuObject* mmo)
{
	// new game
	if (mmo->id == 0)
	{
		GameManager::Instance().setMaingame(true);
		GameManager::Instance().setMenu(false);

		std::shared_ptr<Component> ufoC = GameManager::Instance().mainPlayer->GetComponentByType("MainPlayerController");
		MainPlayerController* player = (MainPlayerController*)ufoC.get();
		player->initialize();

		GameManager::Instance().score = 0;

		std::cout << "HIGH SCORE " << GameManager::Instance().highScore << std::endl;
	}
	// continue
	else if (mmo->id == 1)
	{

		GameManager::Instance().loadGame();

	}
	
}


