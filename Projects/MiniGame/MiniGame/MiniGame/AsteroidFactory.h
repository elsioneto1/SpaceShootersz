#include "Component.h"
#include "MainGameElement.h"

#pragma once
class AsteroidFactory : public Component, public MainGameElement
{

	DECLARE_DYNAMIC_DERIVED_CLASS(AsteroidFactory, Component)


public:


	// creates all the asteroids

	float SpawnTime;
	float minSpawnTimel;
	float baseVelocity;
	float maxBaseVelocity;
	float velMultiplier;
	float maxVelMultiplier;


	float currentSpawnTime;

	AsteroidFactory();
	~AsteroidFactory();

	void load(XMLElement* node);
	void update(float deltaTime);


	STRCODE prefabID;

};

