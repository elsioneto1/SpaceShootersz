#ifndef _MAINMENU_H_
#define _MAINMENU_H_
#include "Component.h"
#include "MainMenuObject.h"
#include "MainMenuStructure.h"
#include "MainMenuElement.h"
#include <vector>
#include <list>

#pragma once
class MainMenu : public Component, public MainMenuElement
{

	DECLARE_DYNAMIC_DERIVED_CLASS(MainMenu, Component)




public:
	// it's a singleton!
	inline static MainMenu& Instance()
	{
		static MainMenu instance;
		return instance;
	}

	// main menu structure
	MainMenu();
	~MainMenu();

	// the menu indexes. they control how the user browse throug them
	int selectedIndex;
	int maxIndex;

	void initialize();
	void update(float deltaTime) override;

	// the item when created adds itself
	void addItem(MainMenuObject* mmo) { MainMenuStructure::Instance().addItem(mmo);}
	
	// when "enter" it's hitted
	void acceptInput(MainMenuObject* mmo);


	MainMenuObject* p_mmo;

};

#endif