#include "Core.h"
#include "InputManager.h"
#include "SFML\Graphics.hpp"
#include "RenderSystem.h"

using namespace sf;

void InputManager::initialize()
{
	maxEvents = 50; // default in case file load fails

	loadSettings();

	events.reserve(50);
	for (int i = 0; i < 50; i++)
	{
		events.push_back(Event());
	}
}

void InputManager::loadSettings()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/InputManagerSettings.xml");

	if (doc.ErrorID() == XML_SUCCESS)
	{
		XMLElement* element = NULL;

		element = doc.FirstChildElement("EventCount");
		if (element != NULL)
		{
			element->QueryIntText(&maxEvents);
		}

		element = doc.FirstChildElement("KeyBindings");
		if (element != NULL)
		{
			XMLElement* bindingEl = element->FirstChildElement("KeyBinding");

			while (bindingEl != NULL) {
				std::string id = bindingEl->Attribute("id");
				XMLElement* keyEl = bindingEl->FirstChildElement("Key");

				while (keyEl != NULL) {
					std::pair<int, int> key;
					keyEl->QueryIntAttribute("code", &key.first);
					keyEl->QueryIntAttribute("weight", &key.second);

					keyBindings.insert(std::make_pair(id, key));

					keyEl = keyEl->NextSiblingElement("Key");
				}

				XMLElement* stickEl = bindingEl->FirstChildElement("Joystick");
				while (stickEl != NULL) {
					std::pair<int, int> key;
					stickEl->QueryIntAttribute("code", &key.first);
					stickEl->QueryIntAttribute("weight", &key.second);

					stickBindings.insert(std::make_pair(id, key));

					stickEl = stickEl->NextSiblingElement("Joystick");
				}

				XMLElement* buttonEl = bindingEl->FirstChildElement("Button");
				while (buttonEl != NULL) {
					std::pair<int, int> key;
					buttonEl->QueryIntAttribute("code", &key.first);
					buttonEl->QueryIntAttribute("weight", &key.second);

					buttonBindings.insert(std::make_pair(id, key));

					buttonEl = buttonEl->NextSiblingElement("Button");
				}

				bindingEl = bindingEl->NextSiblingElement("KeyBinding");
			}
		}
	}
}

void InputManager::update(float deltaTime)
{
	numEvents = 0;
	while (RenderSystem::Instance().GetRenderWindow()->pollEvent(events[numEvents]))
	{
		numEvents++;
	}
}

float InputManager::getAxis(std::string axisName)
{
	float weight = 0.0f;

	std::multimap<std::string, std::pair<int, int>>::iterator kt = keyBindings.find(axisName);
	while (kt != keyBindings.end()) {
		if ((*kt).first == axisName) {
			if (RenderSystem::Instance().GetRenderWindow()->hasFocus() && Keyboard::isKeyPressed((Keyboard::Key)(*kt).second.first)) {
				weight += (*kt).second.second;
			}
		}
		else {
			break;
		}

		++kt;
	}

	std::multimap<std::string, std::pair<int, int>>::iterator st = stickBindings.find(axisName);
	while (st != stickBindings.end()) {
		if ((*st).first == axisName) {
			if (RenderSystem::Instance().GetRenderWindow()->hasFocus()) {
				int axis = (Joystick::Axis)(*st).second.first;
				float input = Joystick::getAxisPosition((*st).second.second, (Joystick::Axis)axis) / 100.0f;

				if (abs(input) > 0.2f) {
					weight += input;
				}
			}
		}
		else {
			break;
		}

		++st;
	}

	std::multimap<std::string, std::pair<int, int>>::iterator bt = buttonBindings.find(axisName);
	while (bt != buttonBindings.end()) {
		if ((*bt).first == axisName) {
			if (RenderSystem::Instance().GetRenderWindow()->hasFocus()) {
				int button = (Joystick::Axis)(*bt).second.first;
				bool input = Joystick::isButtonPressed((*bt).second.second, (Joystick::Axis)button);

				if (input) {
					weight += 1.0f;
				}
			}
		}
		else {
			break;
		}

		++bt;
	}

	if (weight > 1.0f) {
		weight = 1.0f;
	}
	else if (weight < -1.0f) {
		weight = -1.0f;
	}

	return weight;
}

//returns true if a key was pressed this frame
bool InputManager::keyPressed(Keyboard::Key key)
{
	for (int i = 0; i < numEvents; i++)
	{
		if ((events[i].type == Event::KeyPressed) && (events[i].key.code == key))
		{
			return true;
		}
	}

	return false;
}

//returns true if a key was released this frame
bool InputManager::keyReleased(Keyboard::Key key)
{
	//check for a release event with specified key
	for (int i = 0; i < numEvents; i++)
	{
		if ((events[i].type == Event::KeyReleased) && (events[i].key.code == key))
		{
			return true;
		}
	}

	return false;
}

//returns true if a mouse button was pressed this frame
bool InputManager::mousePressed(Mouse::Button button)
{
	for (int i = 0; i < numEvents; i++)
	{
		if ((events[i].type == Event::MouseButtonPressed) && (events[i].mouseButton.button == button))
		{
			return true;
		}
	}

	return false;
}

//returns true if a mouse button was released this frame
bool InputManager::mouseReleased(Mouse::Button button)
{
	for (int i = 0; i < numEvents; i++)
	{
		if ((events[i].type == Event::MouseButtonReleased) && (events[i].mouseButton.button == button))
		{
			return true;
		}
	}

	return false;
}

bool InputManager::mouseMoved()
{
	for (int i = 0; i < numEvents; i++)
	{
		if (events[i].type == Event::MouseMoved)
		{
			return true;
		}
	}

	return false;
}

float InputManager::getMouseWheelTicks()
{
	//check for a release event with specified key
	for (int i = 0; i < numEvents; i++)
	{
		if (events[i].type == Event::MouseWheelScrolled)
		{
			return events[i].mouseWheelScroll.delta;
		}
	}

	return false; //event not found
}

