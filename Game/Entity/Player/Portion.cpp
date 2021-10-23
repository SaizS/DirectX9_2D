#include "framework.h"

Potion::Potion()
{
	texture = TEXTURE->Add(L"Resource/Textures/Player/TestPortion.png");

	pos = { 0, 0 };
	speed = 250;
	angle = 0;
	rotSpeed = 0;
	isActive = false;

	SetCollider(texture->GetSize());
}

Potion::~Potion()
{
}

void Potion::Update()
{
	if (!isActive)
		return;

	pos.x += cos(angle) * speed * DELTA;
	pos.y += sin(angle) * speed * DELTA;
	rot.z += rotSpeed;

	World::Update();
}

void Potion::Render()
{
	if (!isActive)
		return;

	SetWorld();
	texture->AlphaRender();
}

void Potion::Fire(float angle, Vector2 pos)
{
	isActive = true;

	this->angle = angle;
	this->pos = pos;

	if (angle > -(PI * 0.5f) && angle < (PI * 0.5f))
		rotSpeed = 15 * DELTA;
	else
		rotSpeed = -(15 * DELTA);
}

void Potion::Fire(Texture* texture, float angle, Vector2 pos)
{
}

void Potion::Crash()
{
	if (isActive)
		isActive = false;

	EFFECT->Play("Hit", pos); 
}

void Potion::LoadActions()
{
}
