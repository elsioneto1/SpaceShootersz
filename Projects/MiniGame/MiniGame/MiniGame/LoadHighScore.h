

#pragma once

#include "Component.h"

class LoadHighScore : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(LoadHighScore, Component)

public:

	// simple class to load the score
	LoadHighScore();
	~LoadHighScore();

	void initialize();

};

