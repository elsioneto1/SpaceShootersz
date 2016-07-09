#include "Component.h"
#include "MainGameElement.h"
#include <vector>
#include <list>

#pragma once
class EnemyShootObject : public Component, public MainGameElement
{

	DECLARE_DYNAMIC_DERIVED_CLASS(EnemyShootObject, Component)

public:
	EnemyShootObject();
	~EnemyShootObject();


	// the enemy laser class


	void initialize();
	void update(float deltaTime);
	void load(XMLElement * element);
	// it's the same thing as "sleeping" for asteroid. Sorry for the lack of pattern!
	bool onScreen;
	// normal vector for direction
	sf::Vector2f direction;

	// save and load
	void save(XMLElement * node, tinyxml2::XMLDocument* doc);
	void loadXML(XMLElement* node);
};

