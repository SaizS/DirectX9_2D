#include "framework.h"

ChildMan2::ChildMan2()
{
	LoadActions();

	state = ACT1;
	actions[state]->Play();

	pos = { 76,123 };
}

ChildMan2::~ChildMan2()
{
}

void ChildMan2::LoadActions()
{
	vector<Texture*> clips;

	wstring filePath = L"Resource/Textures/Npc/children.png";

	//UP
	clips.push_back(TEXTURE->Add(filePath, 4, 3, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 3; i < 6; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 3, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//DOWN
	clips.push_back(TEXTURE->Add(filePath, 4, 0, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 3; i < 6; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 0, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//LEFT
	clips.push_back(TEXTURE->Add(filePath, 4, 1, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 3; i < 6; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 1, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//RIGHT
	clips.push_back(TEXTURE->Add(filePath, 4, 2, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 3; i < 6; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 2, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//ACT1
	for (int i = 3; i < 6; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Npc/actions2.png", i, 5, 12, 8));
	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();
}
