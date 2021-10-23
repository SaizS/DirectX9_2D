#include "framework.h"

Flower_Bullet::Flower_Bullet() : isActive(false), angle(0.0f), speed(180.0f), attack(10.0f)
{
	Load();
	SetCollider({ 15,15 });
}

Flower_Bullet::~Flower_Bullet()
{
	delete bullet;
}

void Flower_Bullet::Update()
{
	if (!isActive)
		return;

	pos.x += cos(angle) * speed * DELTA;
	pos.y += sin(angle) * speed * DELTA;

	bullet->Update();
	World::Update();
}

void Flower_Bullet::Render()
{
	if (!isActive)
		return;

	SetWorld();

	bullet->AlphaRender();

	RenderBox();
}

void Flower_Bullet::Fire(Vector2 pos, float angle)
{
	this->pos = pos;
	this->angle = angle;

	isActive = true;
}

void Flower_Bullet::Load()
{
	vector<Texture*> clips;

	for (int i = 0; i < 4; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Enemy/Mountain/Flower_Bullet.png", i, 0, 4, 1));
	
	bullet = new Animation(clips, Type::LOOP);
	bullet->Play();
}
