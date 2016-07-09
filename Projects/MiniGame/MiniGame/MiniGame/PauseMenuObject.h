#pragma once

#include "Component.h"

#include "PauseMenuElement.h"
#include <SFML\System.hpp>

class PauseMenuObject : public Component, public PauseMenuElement
{
	DECLARE_DYNAMIC_DERIVED_CLASS(PauseMenuObject, Component)
public:
	PauseMenuObject();
	~PauseMenuObject();

	bool add = false;
	void load(XMLElement* node);
	void initialize();
	void setActive(bool b);
	void update(float deltaTime);
	int id;

};

