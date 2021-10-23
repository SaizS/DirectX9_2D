#include "framework.h"

FolkTwo::FolkTwo()
{
	LoadActions();

	state = UPIDLE;
	actions[state]->Play();

	pos = { 354, 148 };
	SetCollider(35, 50);
}

FolkTwo::~FolkTwo()
{
	delete actions[0];
}

void FolkTwo::LoadActions()
{
	vector<Texture*> clips;

	for (int i = 3; i < 6; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Npc/actions1.png", i, 4, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE, 0.15f));

}
