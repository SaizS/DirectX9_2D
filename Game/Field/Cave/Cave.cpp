#include "framework.h"

Cave::Cave()
{
	backGround = TEXTURE->Add(L"Resource/Textures/Cave/Cave.png");
	mage = ENEMY->GetMage();

	for (World* world : DATA->GetCollisionWorldData("CaveCollisionWorlds"))
		collisionWorld.push_back(world);

	pos = { 0,0 };
}

Cave::~Cave()
{
}

void Cave::Update()
{
	CollisionEvent();

	player->Update();
	mage->Update();
	World::Update();

	if (collisionWorld.size() != 0)
	{
		for (World* world : collisionWorld)
			world->CollisionMove(player);
	}
	for (Potion* potion : player->GetPortions())
		potion->Update();

	for (Effect* effect : EFFECT->GetEffect("Hit"))
		effect->Update();
}

void Cave::Render()
{
	SetWorld();

	backGround->Render();
	mage->Render();
	player->Render();

	for (Potion* potion : player->GetPortions())
		potion->Render();

	for (Effect* effect : EFFECT->GetEffect("Hit"))
		effect->Render();
}

void Cave::CollisionEvent()
{
	for (World* world : collisionWorld)
	{
		for (Potion* potion : player->GetPortions())
		{
			if (potion->GetIsActive())
			{
				if (world->Collision(potion))
					potion->Crash();
			}
		}

		for (Mage_FireBall* fireBall : mage->GetFireBall())
		{
			if (fireBall->GetIsActive())
			{
				if (fireBall->Collision(world))
				{
					fireBall->FireBallCrash();
					SOUND->Play("FireBallHit");
				}
			}
		}
	}
}
