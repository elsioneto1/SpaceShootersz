#include "GameCore.h"

#include "LoadHighScore.h"
#include "GameManager.h"

IMPLEMENT_DYNAMIC_CLASS(LoadHighScore)


LoadHighScore::LoadHighScore()
{
}


LoadHighScore::~LoadHighScore()
{
}

void LoadHighScore::initialize()
{

	tinyxml2::XMLDocument doc;
	XMLError error = doc.LoadFile("HighScore.xml");
	// we dont want errors, right?
	
	if (error == XMLError::XML_SUCCESS )
		doc.FirstChildElement()->FirstChildElement()->QueryIntAttribute("HighScore", &GameManager::Instance().highScore); //hello high score!

}
