#include "Core.h"
#include "Sprite.h"
#include "TextureAsset.h"
#include "AssetManager.h"
#include "Transform.h"
#include <SFML/Graphics.hpp>

IMPLEMENT_DYNAMIC_CLASS(Sprite);

void Sprite::initialize()
{
	Renderable::initialize();

	// creates the SFML sprite
	if (renderableSprite == nullptr)
	{

		renderableSprite.reset(new sf::Sprite());
	}

	if (textureAsset != nullptr)
	{
		TextureAsset* rawAsset = (TextureAsset*)textureAsset.get();
		renderableSprite->setTexture(*rawAsset->getTexture());
		renderableSprite->setOrigin(rawAsset->getTexture()->getSize().x * 0.5f, rawAsset->getTexture()->getSize().y * 0.5f);
	}
}

void Sprite::render(sf::RenderWindow* window, Transform* t)
{
	if (renderableSprite != NULL)
	{
		sf::RenderStates states;
		states.transform = t->getTransform();
		window->draw(*renderableSprite, states);
	}
}

void Sprite::ChangeTexture(std::string& uuid)
{
	textureUID = uuid;
	textureAsset = AssetManager::Instance().getAsset(getHashCode(textureUID.c_str()), TextureAsset::getClassHashCode());

	initialize();
}

void Sprite::load(XMLElement* node)
{
	Renderable::load(node);
		
	XMLElement* textureElement = node->FirstChildElement("TextureUID");
	THROW_RUNTIME_ERROR(textureElement == nullptr, "Missing TextureUID Node");

	textureUID = textureElement->Attribute("uuid");
	textureAsset = AssetManager::Instance().getAsset(getHashCode(textureUID.c_str()), TextureAsset::getClassHashCode());
}

void Sprite::save(XMLElement* node)
{
	Renderable::save(node);

	XMLElement* textureElement = node->GetDocument()->NewElement("TextureUID");
	textureElement->SetAttribute("uuid", textureUID.c_str());
	node->InsertEndChild(textureElement);
}

