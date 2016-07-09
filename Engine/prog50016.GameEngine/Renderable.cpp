#include "Core.h"
#include "Renderable.h"
#include "RenderSystem.h"

IMPLEMENT_ABSTRACT_CLASS(Renderable);

void Renderable::initialize()
{
	Component::initialize();
	RenderSystem::Instance().addRenderable(this, layer);
}

Renderable::~Renderable()
{
	RenderSystem::Instance().removeRenderable(this, layer);
}

void Renderable::load(XMLElement* node)
{
	Component::load(node);

	layer = node->IntAttribute("layer");
}

void Renderable::save(XMLElement* node)
{
	Component::save(node);
	
	node->SetAttribute("layer", layer);
}