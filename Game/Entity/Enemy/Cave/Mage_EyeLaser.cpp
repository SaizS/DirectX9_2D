#include "framework.h"

Mage_EyeLaser::Mage_EyeLaser(World* world)
{
	Load();
	SetParent(world->GetWorld());
	SetCollider({ 11,700 });
}

Mage_EyeLaser::~Mage_EyeLaser()
{
}

void Mage_EyeLaser::Update()
{
	if (!isActive)
		return;

	Shoot();

	actions[state]->Update();
	World::Update();
}

void Mage_EyeLaser::Render()
{
	if (!isActive)
		return;

	SetWorld();

	actions[state]->AlphaRender();
}

void Mage_EyeLaser::SetLaser(bool isRotation)
{
	pos = { 0, 22 };
	isActive = true;
	state = 0;
	actions[state]->Play();
	this->isRotaion = isRotation;

	if (!SOUND->CheckMusic("LaserReady"))
		SOUND->Play("LaserReady");
}

void Mage_EyeLaser::ReadyShoot()
{
	isShoot = true;
	pos = { 0, 366 };
	state = 1;
	actions[state]->Play();

	if(!SOUND->CheckMusic("LaserBurst"))
		SOUND->Play("LaserBurst");
}

void Mage_EyeLaser::Shoot()
{
	if (!isShoot || isRotaion)
		return;

	shootTime += DELTA;

	if (shootTime >= 3)
	{
		isShoot = false;
		isActive = false;
		shootTime = 0.0f;
		LaserEndEvent();
		SOUND->Stop("LaserBurst");
	}
}

void Mage_EyeLaser::Load()
{
	vector<Texture*> clips;

	for (int i = 0; i < 3; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Enemy/Mage/LaserReady.png", i, 0, 3, 1));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 0; i < 2; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Enemy/Mage/LaserShoot2.png", i, 0, 2, 1));
	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	actions[0]->SetEndEvent(bind(&Mage_EyeLaser::ReadyShoot, this));
}
