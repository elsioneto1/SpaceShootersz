#include "GameCore.h"
#include "PauseMenu.h"


IMPLEMENT_DYNAMIC_CLASS(PauseMenu)

PauseMenu::PauseMenu()
{
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::initialize()
{

	PauseMenuStructure::Instance().selectedIndex = 0;
	p_mmo = NULL;
}

void PauseMenu::update(float deltaTime)
{

	gameObject->setActive(mayUpdate);
	PauseMenuElement::update();
	if (!mayUpdate)
	{
		return;
	}

	maxIndex = PauseMenuStructure::Instance().menuObjs.size();

	if (InputManager::Instance().keyPressed(sf::Keyboard::Up))
	{
		if (PauseMenuStructure::Instance().selectedIndex > 0)
		{
			PauseMenuStructure::Instance().selectedIndex--;
		}
	}
	else if (InputManager::Instance().keyPressed(sf::Keyboard::Down))
	{

		if (PauseMenuStructure::Instance().selectedIndex < maxIndex - 1)
		{
			PauseMenuStructure::Instance().selectedIndex++;
		}
		
	}

	for (int i = 0; i < maxIndex; i++)
	{
		PauseMenuStructure::Instance().menuObjs[i]->setActive(true);

	}

	if (PauseMenuStructure::Instance().menuObjs.size() > 0)
	{
		PauseMenuStructure::Instance().menuObjs[PauseMenuStructure::Instance().selectedIndex]->setActive(false);
		p_mmo = PauseMenuStructure::Instance().menuObjs[PauseMenuStructure::Instance().selectedIndex];
	}



	if (InputManager::Instance().keyPressed(sf::Keyboard::Return))
	{

		if (p_mmo != NULL)
		{
			acceptInput(p_mmo);
		}
	}


}

void PauseMenu::acceptInput(PauseMenuObject * mmo)
{
	//continue
	if (mmo->id == 0)
	{
		GameManager::Instance().setMaingame(true);
		GameManager::Instance().setPause(false);
	}
	// save
	else if (mmo->id == 1)
	{
		GameManager::Instance().saveGame();
		std::cout << "Game Saved" << std::endl;
	}
	else if (mmo->id == 2)
	{
		GameManager::Instance().cleanObjects();
	}

}
