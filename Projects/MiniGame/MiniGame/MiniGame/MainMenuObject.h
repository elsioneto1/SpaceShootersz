#ifndef _MAINMENUOBJECT_H_
#define _MAINMENUOBJECT_H_
#pragma once



#include "Component.h"
#include "MainMenuElement.h"
#include <SFML\System.hpp>

class MainMenuObject : public Component, public MainMenuElement
{

	DECLARE_DYNAMIC_DERIVED_CLASS(MainMenuObject, Component)

public:


	MainMenuObject();
	~MainMenuObject();
	// if you interact with it, add it to the menu
	// the object is toggled between active or not
	bool add = false;
	void load(XMLElement* node);
	void initialize();
	void setActive(bool b);
	void update(float deltaTime);
	int id ;
};


#endif
