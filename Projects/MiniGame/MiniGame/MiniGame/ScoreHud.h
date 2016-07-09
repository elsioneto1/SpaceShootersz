#pragma once

#include "Renderable.h"
#include "FontAsset.h"

class ScoreHud : public Renderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(ScoreHud, Renderable)



	// I DON'T KNOW WHY THIS IS NOT WORKING!!!
	// I've spent hours trying to make this work and nothing. 
	// it was working in the previous engine version, don't know what happened!
public:
	void load(XMLElement* node) ;
	void initialize();
	void render(sf::RenderWindow* window, Transform* t);
	void update(float deltaTime);
	
private:
	STRCODE fontID;
	std::shared_ptr<Asset> fontAsset;
	FontAsset* rawr;
	sf::Vector2f position;
	sf::Text text;
	std::string display;
};

