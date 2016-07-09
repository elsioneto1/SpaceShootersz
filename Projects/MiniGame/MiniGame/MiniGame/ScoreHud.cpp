#include "GameCore.h"
#include "ScoreHud.h"
#include "GameManager.h"

#include "FontAsset.h"

IMPLEMENT_DYNAMIC_CLASS(ScoreHud)

void ScoreHud::load(XMLElement* node)
{
	XMLElement* element = nullptr;

	//Component::load(node);

	const char * c = node->FirstChildElement()->Attribute("uuid");
	fontID = getHashCode(c);


	fontAsset = AssetManager::Instance().getAsset(fontID, FontAsset::getClassHashCode());
	float x;
	node->FirstChildElement("Position")->QueryFloatAttribute("x", &x);
	float y;
	node->FirstChildElement("Position")->QueryFloatAttribute("y", &y);
	text.setPosition(0,0);
	
}

void ScoreHud::initialize()
{
	rawr = NULL;
	if (fontAsset != nullptr)
	{
		 rawr = (FontAsset*)fontAsset.get();
		//sf::Font font = *rawr->getFont();
		//const char *c = "Resources/Fonts/cour.tff";
		//font.loadFromFile(c);
		text.setFont(*rawr->getFont());
		text.setColor(sf::Color::Cyan);
	}
	

	gameObject->setActive(true);
}

void ScoreHud::render(sf::RenderWindow* window, Transform* t)
{
	//Component::render(window, t);

	
	std::ostringstream stringStream;
	stringStream << "Score: " << GameManager::Instance().score;

	// Y U NO WORK??????!?!!?1111 @@23 1-23121 >.<

	text.setString(stringStream.str());
	text.setCharacterSize(2);
	text.setPosition(300, 300);
 	window->draw(text); // -->>>  My references are right! What's wrong with it????

}

void ScoreHud::update(float deltaTime)
{
	render(RenderSystem::Instance().GetRenderWindow(), gameObject->getTransform());
}

