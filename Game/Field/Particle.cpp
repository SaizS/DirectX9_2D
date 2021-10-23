#include "framework.h"

Paticle::Paticle()
{
	vector<Texture*> clips;

	for (int i = 0; i < 5; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Effect/YellowPaticle2.png", i, 0, 5, 1));

	paticle = new Animation(clips, Type::LOOP, 0.15f);
	paticle->Play();

	SetCollider({ 15,15 });
}

Paticle::Paticle(Vector2 pos, Stage stage, bool isActive) : stage(stage), isActive(isActive)
{
	vector<Texture*> clips;

	for (int i = 0; i < 5; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Effect/YellowPaticle2.png", i, 0, 5, 1));

	paticle = new Animation(clips, Type::LOOP, 0.15f);
	paticle->Play();

	this->pos = pos;
	SetCollider({ 30,30 });
}

Paticle::~Paticle()
{
	delete paticle;
}

void Paticle::Update()
{
	if (!isActive)
		return;

	paticle->Update();
	World::Update();
}

void Paticle::Render()
{
	if (!isActive)
		return;

	SetWorld();
	paticle->AlphaRender();
}
