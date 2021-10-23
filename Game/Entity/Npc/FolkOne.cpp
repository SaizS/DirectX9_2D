#include "framework.h"

FolkOne::FolkOne()
{
	LoadActions();
	state = ACT4;
	actions[state]->Play();

	pos = { 854, -84 };
	SetCollider(35, 50);

}

FolkOne::~FolkOne()
{
	for (Animation* ani : actions)
		delete ani;
}

void FolkOne::LoadActions()
{
	vector<Texture*> clips;

	wstring filePath = L"Resource/Textures/Npc/townsfolk.png";

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

	//ACT1 - °í°³ ²ô´öÀÌ±â
	//ACT2 - °í°³ Á£±â
	//ACT3 - ¿ô±â
	//ACT4 - ºøÀÚ·çÁú

	for (int i = 0; i < 4; i++)
	{
		for (int j = 3; j < 6; j++)
			clips.push_back(TEXTURE->Add(filePath, j, i, 12, 8));
		actions.push_back(new Animation(clips, Type::REVERSE, 0.15f));
		clips.clear();
	}
}
