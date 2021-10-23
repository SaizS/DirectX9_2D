#include "framework.h"

Mage_FireBall::Mage_FireBall()
{
	LoadActions();

	isActive = false;
	speed = 800.0f;

	state = SHOOT;
	actions[state]->Play();

	offset = { 0, 30 };
	SetCollider({ 50, 50 });
}

Mage_FireBall::~Mage_FireBall()
{
}

void Mage_FireBall::Update()
{
	if (!isActive)
		return;

	if (state == SHOOT && Collision(player->GetHitBox()))
	{
		Vector2 vec = player->pos - pos;
		player->Damage(10, OP::VecToAngle(OP::GetNomalize(vec)));
		player->SetBuff(19);
		FireBallCrash();
		SOUND->Play("FireBallHit");
	}

	actions[state]->Update();

	pos.x += cos(damageAngle) * speed * DELTA;
	pos.y -= -sin(damageAngle) * speed * DELTA;

	World::Update();
}

void Mage_FireBall::Render()
{
	if (!isActive)
		return;

	SetWorld();

	shader->SetTexture("map", actions[state]->GetTexture());
	shader->SetVector("color", &color, 4);
	shader->Begin();
	actions[state]->Render();
	shader->End();
}

void Mage_FireBall::EnemyActions()
{
}

void Mage_FireBall::Idle()
{
}

void Mage_FireBall::LoadActions()
{
	vector<Texture*> clips;

	for (int i = 0; i < 4; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Enemy/Mage/Mage_FireBallShoot.png", i, 0, 4, 1));
	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	for (int i = 0; i < 6; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Enemy/Mage/Mage_FireBallCollision.png", i, 0, 6, 1));
	actions.push_back(new Animation(clips, Type::END));
	clips.clear();

	actions[CRASH]->SetEndEvent(bind(&Mage_FireBall::IsAciveFalse, this));
}

void Mage_FireBall::SetActions(Mage_FireBallState state)
{
	if (this->state == state)
		return;

	this->state = state;
	actions[state]->Play();
}

void Mage_FireBall::Shoot(Vector2 pos, float angle)
{
	this->pos = pos;
	damageAngle = angle;
	isActive = true;
	SetActions(SHOOT);
	speed = 800.0f;
}

void Mage_FireBall::FireBallCrash()
{
	SetActions(CRASH);
	speed = 0;
}

