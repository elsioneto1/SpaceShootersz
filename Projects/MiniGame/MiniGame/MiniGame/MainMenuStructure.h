#include "MainMenuObject.h"
#include <vector>
#include <list>


#pragma once
class MainMenuStructure
{
	// Had to make a hack because for some reason my Singleton structure is being instantiated twice.
	// When I set all my variables, I lose them =(
	// I think it's related do the DYNAMIC_CLASS macro, so I made another singleton just for the data. It worked
public:

	// where all the menu data is stored
	inline static MainMenuStructure& Instance()
	{
		static MainMenuStructure instance;
		return instance;
	}

	std::vector<MainMenuObject*> menuObjs;

	void addItem(MainMenuObject* mmo)
	{
		menuObjs.push_back(mmo);
	}

	int selectedIndex;
};