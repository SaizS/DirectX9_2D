#include "framework.h"

ChildMan1::ChildMan1()
{
	LoadActions();

	state = ACT1;
	actions[state]->Play();

	pos = { 40, 250 };
}

ChildMan1::~ChildMan1()
{
}

void ChildMan1::LoadActions()
{
	vector<Texture*> clips;

	wstring filePath = L"Resource/Textures/Npc/children.png";

	//UP
	clips.push_back(TEXTURE->Add(filePath, 1, 3, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 0; i < 3; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 3, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//DOWN
	clips.push_back(TEXTURE->Add(filePath, 1, 0, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 0; i < 3; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 0, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//LEFT
	clips.push_back(TEXTURE->Add(filePath, 1, 1, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 0; i < 3; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 1, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//RIGHT
	clips.push_back(TEXTURE->Add(filePath, 1, 2, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 0; i < 3; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 2, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//ACT1
	for (int i = 3; i < 6; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Npc/actions2.png", i, 4, 12, 8));
	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();
}
