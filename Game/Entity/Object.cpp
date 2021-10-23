#include "framework.h"

Object::Object(Texture* texture)
{
	this->texture = texture;
}

Object::~Object()
{
}

void Object::Update()
{
	World::Update();
}

void Object::Render()
{
	SetWorld();
	texture->AlphaRender();
}