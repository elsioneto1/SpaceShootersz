
#include "Component.h"
#include "MainGameElement.h"

#pragma once
class ShootObject : public Component, public MainGameElement
{

	DECLARE_DYNAMIC_DERIVED_CLASS(ShootObject, Component)

public:
	ShootObject();
	~ShootObject();
	// Player bullet class
	// the name can be deceiving here, but its just the bullet object (green laser)

	void initialize();
	void update(float deltaTime);
	void load(XMLElement * element);

	// if it's on screen or not
	bool onScreen;

};

