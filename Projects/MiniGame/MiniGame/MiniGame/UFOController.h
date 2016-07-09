#ifndef _UFOCONTROLLER_H_
#define _UFOCONTROLLER_H_
#pragma once

#include "Component.h"
#include "MainGameElement.h"




class UFOController : public Component, public MainGameElement
{
	DECLARE_DYNAMIC_DERIVED_CLASS(UFOController, Component)

public:


	~UFOController();
	void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void load(XMLElement* element) override;
	bool onScreen ;

	float speed;

	// see if there's a defined behaviour 
	bool behaviourDefined;
	// the point where it'll start and and
	float startX, startY , endX, endY;
	float behaviourComplete; // percentage
	int selectedBehaviour; // it was planned to have 3 s
	int subBehaviour; // variation inside the behaviour
	void endBehaviour();

	//save and load relevant data
	void save(XMLElement * node, tinyxml2::XMLDocument* doc);
	void loadXML(XMLElement * node);

private:
	
	sf::Vector2f direction;
	float destroy;
	
	

	// specific behaviour for the crazy movement
	// it was planned to have multiple behaviours, but due the lack of time teher'es just one with some variations :/
	void behaviour1();
};



#endif
