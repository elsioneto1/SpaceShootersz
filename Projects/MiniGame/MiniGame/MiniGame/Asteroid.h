#include "Component.h"
#include "MainGameElement.h"

#pragma once
class Asteroid : public Component, public MainGameElement
{

	DECLARE_DYNAMIC_DERIVED_CLASS(Asteroid, Component)


	int startX, startY;
	int endX, endY;
	float percentagePathCompletion;
	int life;
	float rotation;
	
	int damage;

public:

	Asteroid();
	~Asteroid();
	void initialize();
	// sleping boolean teels if a object is active or not. It's the same as "OnScreen" for UFO. Sorry for the lack of pattern
	bool sleeping;

	// velocity for the asteroids
	float velocity;


	void update(float deltaTime);

	// at spawn, it defines where the asteroid will spawn and where wll be his last position.
	// the asteroid behaviour is made from a linear function which build a line across the screen
	// where the asteroid is in the line, it's defined by the percentagePathCompletion variable
	void setAsteroidParams(float vel);
	void awakeBehaviour(float deltaTime);
	// if it's hit, change color and etc... Give a visual feedback
	void Hit();
	// set the object to sllep and off the screen!
	void Destroy();
	// save all relevant values to a XML
	void save(XMLElement* node, tinyxml2::XMLDocument* doc);
	// load everything back
	void loadXML(XMLElement* node);
};

