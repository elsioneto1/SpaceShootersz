
#include "Component.h"
#include <vector>
#include <list>

#pragma once
class ShootFactory : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(ShootFactory, Component)


public:

	// creates all the necessary objects for the game
	ShootFactory();
	~ShootFactory();

	void load(XMLElement* node);
	void update(float deltaTime);

	std::vector<GameObject*> shootObjs;

	bool spacePressed;

	STRCODE prefabID;
	STRCODE prefabID2;


};

