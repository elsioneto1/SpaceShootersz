#include "GameCore.h"
#include "GameEngine.h"
#include "GameManager.h"

#include "MainPlayerController.h"
#include "UFOController.h"
#include "UFOFactory.h"
#include "ScoreHud.h"

void gameUpdate(float deltaTime)
{
	GameManager::Instance().update(deltaTime);
}

int main()
{
	// Register all custom components here
	REGISTER_DYNAMIC_CLASS(MainPlayerController);
	REGISTER_DYNAMIC_CLASS(UFOController);
	REGISTER_DYNAMIC_CLASS(UFOFactory);
	REGISTER_DYNAMIC_CLASS(ScoreHud);
	
	GameEngine::Instance().setGameUpdate(gameUpdate);

	GameEngine::Instance().initialize();
	GameEngine::Instance().GameLoop();
}

