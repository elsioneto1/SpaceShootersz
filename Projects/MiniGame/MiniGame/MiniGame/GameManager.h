#ifndef _GAMEEMANAGER_H_
#define _GAMEEMANAGER_H_
#pragma once

class GameManager
{
public:

	inline static GameManager& Instance()
	{
		static GameManager instance;
		return instance;
	}

	// most of the game logic is run here
	// 

	static GameManager instance;
	void update(float deltaTime);

	GameObject* mainPlayer = nullptr;
	std::list<GameObject*> UFOs;
	int score = 0;
	int highScore = 0;
	// it was a pain to write this whole line EVERY TIME to get the screen values!
	int screenWidth		= RenderSystem::Instance().GetRenderWindow()->getViewport(RenderSystem::Instance().GetRenderWindow()->getView()).width;
	int screenHeight	= RenderSystem::Instance().GetRenderWindow()->getViewport(RenderSystem::Instance().GetRenderWindow()->getView()).height;

	void updateMenu();
	void updateMainGame();
	void updatePause();
	

	// toggle game states
	bool getMenu() { return onMenu; }
	bool getMaingame() { return onMainGame; }
	bool getPause() { return onPause; }

	void setMenu(bool b) { onMenu = b; }
	void setMaingame(bool b) { onMainGame = b; }
	void setPause(bool b) { onPause = b; }

	// increase the player score
	void increaseScore(int add);
	// kills the player
	void destroyPlayer(void *  player);

	// set all the objects to the initial state
	void cleanObjects();

	// persistence methods
	void saveScore();
	void saveGame();
	void loadGame();

private:

	bool onMenu = true;
	bool onMainGame = false;
	bool onPause = false;

	

	GameManager() = default;
	~GameManager() = default;
	GameManager(GameManager const&) = delete;

};

#endif

