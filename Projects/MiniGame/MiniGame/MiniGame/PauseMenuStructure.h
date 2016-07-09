#include "PauseMenuObject.h"
#include <vector>
#include <list>


#pragma once
class PauseMenuStructure
{
	// Had to make a hack because for some reason my Singleton structure is being instantiated twice.
	// When I set all my variables, I lose them =(
	// I think it's related do the DYNAMIC_CLASS macro, so I made another singleton just for the data. It worked
public:
	inline static PauseMenuStructure& Instance()
	{
		static PauseMenuStructure instance;
		return instance;
	}

	std::vector<PauseMenuObject*> menuObjs;

	void addItem(PauseMenuObject* mmo)
	{
		menuObjs.push_back(mmo);
	}

	int selectedIndex;
};