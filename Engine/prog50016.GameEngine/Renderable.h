#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_
#pragma once

#include "Component.h"

class Renderable : public Component
{
	DECLARE_ABSTRACT_DERIVED_CLASS(Renderable, Component)

public:
	void initialize();
	~Renderable();

	virtual void load(XMLElement* node);
	void save(XMLElement* node);
	virtual void render(sf::RenderWindow* window, Transform* t) override {	};
protected:
	

	friend class RenderSystem;

private:
	int layer = 0;
};

#endif

