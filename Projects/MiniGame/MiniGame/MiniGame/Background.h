#include "Component.h"

#pragma once
class Background : public Component
{

	DECLARE_DYNAMIC_DERIVED_CLASS(Background, Component)

public:

	// simple background.
	void load(XMLElement* node);
	void initialize();
	void update(float deltaTime);
	float vel;

	Background();
	~Background();
};

