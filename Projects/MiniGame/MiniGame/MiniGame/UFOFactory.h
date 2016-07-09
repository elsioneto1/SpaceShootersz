#ifndef _UFOFACTORY_H_
#define _UFOFACTORY_H_

#pragma once

#include "Component.h"
#include "MainGameElement.h"

class UFOFactory : public Component, public MainGameElement
{
	DECLARE_DYNAMIC_DERIVED_CLASS(UFOFactory, Component)

public:
	// creates all the necessary objects for the game

	virtual void update(float deltaTime);
	virtual void load(XMLElement* node);

	std::vector<GameObject*> ufoObjs;
private:
	int maxSpawnPerTime;
	float spawnDelay;
	float currentSpawnDelay = 0.0f;
	STRCODE prefabID;
};

#endif