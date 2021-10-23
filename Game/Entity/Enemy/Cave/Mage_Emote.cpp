#include "framework.h"

Mage_Emote::Mage_Emote(function<void()> Event) : isActive(false)
{
	vector<Texture*> clips;
	for (int i = 0; i < 8; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Enemy/Mage/Emote.png", i, 0, 8, 1));

	ani = new Animation(clips);
	ani->SetEndEvent(Event);

	pos = { 0, -250 };
}

Mage_Emote::~Mage_Emote()
{
}

void Mage_Emote::Update()
{
	if (!isActive)
		return;

	ani->Update();
	World::Update();
}

void Mage_Emote::Render()
{
	if (!isActive)
		return;

	SetWorld();

	ani->AlphaRender();
}

void Mage_Emote::Play()
{
	isActive = true;
	ani->Play();
}
