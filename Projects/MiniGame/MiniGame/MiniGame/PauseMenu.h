#include "Component.h"
#include "PauseMenuElement.h"
#include "PauseMenuObject.h"
#include "PauseMenuStructure.h"


#pragma once
class PauseMenu : public Component, public PauseMenuElement
{

	DECLARE_DYNAMIC_DERIVED_CLASS(PauseMenu, Component)



public:
	inline static PauseMenu& Instance()
	{
		static PauseMenu instance;
		return instance;
	}

	// pause menu class!
	// Follows the same logic as the main menu
	PauseMenu();
	~PauseMenu();

	int selectedIndex;
	int maxIndex;

	void initialize();
	void update(float deltaTime) override;

	void addItem(PauseMenuObject* mmo) { PauseMenuStructure::Instance().addItem(mmo); }
	void acceptInput(PauseMenuObject* mmo);

	PauseMenuObject* p_mmo;

};

