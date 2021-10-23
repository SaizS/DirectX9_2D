#include "framework.h"

Mage_BlackBall::Mage_BlackBall() : durationTime(0.0f)
{
	LoadActions();
	SetCircle(35);
	speed = 20.0f;

	isActive = false;
}

Mage_BlackBall::~Mage_BlackBall()
{
}

void Mage_BlackBall::Update()
{
	if (!isActive)
		return;

	durationTime += DELTA;

	if (durationTime > 5)
	{
		durationTime = 0.0f;
		isActive = false;
		actions[0]->Stop();
		EndEvent();
	}

	pos = LERP( pos, player->pos, DELTA * 3 );
	actions[0]->Update();
	World::Update();

	if (CollisionCircleRect(player->GetHitBox()))
	{
		player->hp -= DELTA * 20;
	}
}

void Mage_BlackBall::Render()
{
	if (!isActive)
		return;

	SetWorld();

	actions[0]->AlphaRender();
}

void Mage_BlackBall::EnemyActions()
{
}

void Mage_BlackBall::Idle()
{
}

void Mage_BlackBall::LoadActions()
{
	vector<Texture*> clips;

	for (int i = 0; i < 10; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Enemy/Mage/BlackBall.png", i, 0, 10, 1));
	actions.push_back(new Animation(clips, Type::LOOP, 0.05f));
}

void Mage_BlackBall::Shoot(Vector2 pos)
{
	this->pos = pos;
	isActive = true;
	actions[0]->Play();
}
