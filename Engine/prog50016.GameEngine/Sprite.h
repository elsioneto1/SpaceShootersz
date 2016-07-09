#ifndef _SPRITE_H_
#define _SPRITE_H_
#pragma once

#include "Renderable.h"

class Asset;
namespace sf { class Sprite; }

class Sprite : public Renderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Sprite, Renderable)

public :
	virtual void initialize();

	void load(XMLElement* node);
	void save(XMLElement* node);

	void ChangeTexture(std::string& uuid);

	virtual void render(sf::RenderWindow* window, Transform* t) override;
	std::shared_ptr<sf::Sprite> renderableSprite;
protected:

	std::shared_ptr<Asset> textureAsset;
	std::string textureUID;
};

#endif

