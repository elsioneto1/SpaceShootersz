#ifndef _MAINPLAYERCONTROLLER_H_
#define _MAINPLAYERCONTROLLER_H_

#pragma once

#include "Component.h"
#include "MainGameElement.h"
#include <SFML\System.hpp>

class MainPlayerController : public Component, public MainGameElement
{
	DECLARE_DYNAMIC_DERIVED_CLASS(MainPlayerController, Component)

public:

	// the player class!

	void initialize() override;
	void load(XMLElement* fileElement) override;
	void update(float deltaTime) override;
	//gets the inputs
	void inputManager();
	void movementManager(float deltaTime);
	void save(XMLElement * node, tinyxml2::XMLDocument* doc);

	// little set of bools to give a better feel for the movements
	bool left, right, up, down;

	// special variables for special cases. If the player dies theres a delay until he gets back to the screen
	// and a invincibility period which he cant be hit
	bool respawning;
	float respawnTime;
	float respawnTimer;
	bool immortal;
	float immortalTime;
	float immortalTimer;

	//  game over, dude
	bool gameOver;

	// kill the player and verifies if he have any lifes left
	void Destroy();
	int lives;
	void decreaseLife();

	// there are two vector for positioning the player. Chase position it's a point where you wish the player to be
	// with this, it's possibles do lerp the player position instead of just setting the player in a fixed position
	// giver a better feel when controlling the ship
	sf::Vector2f chasePosition;
	sf::Vector2f currentPosition;
private:
	// player speed
	float speed;
	
};

#endif

