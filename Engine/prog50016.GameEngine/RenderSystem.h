#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_
#pragma once

#include "ISystem.h"
#include <SFML\Graphics.hpp>

class Renderable;
class GameObject;

class RenderSystem : public ISystem
{
private:
	// File properties
	bool loadedSettings;
	std::string name;
	int width;
	int height;
	bool fullscreen;
	std::string views;
	int voriginX;
	int voriginY;
	sf::View view;

	/// Render components
	/// Layer & Renderable
	std::multimap<int, Renderable*> renderComponents;

	/// The Window
	sf::RenderWindow* window;

public:
	inline static RenderSystem& Instance()
	{
		static RenderSystem instance;
		return instance;
	}

	sf::View& getView() { return view; }
	sf::RenderWindow* GetRenderWindow() { return window; }

	void addRenderable(Renderable* renderable, int layer = 0);
	void removeRenderable(Renderable* renderable, int layer = 0);

	virtual void update(float deltaTime);

protected:
	virtual void initialize();

private:
	void renderObject(const std::shared_ptr<GameObject>& gObj);
	void loadSettings();

private:

	RenderSystem() = default;
	~RenderSystem() = default;
	RenderSystem(RenderSystem const&) = delete;

	friend class GameEngine;
};

#endif

