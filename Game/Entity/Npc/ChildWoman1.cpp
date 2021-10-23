#include "framework.h"

ChildWoman1::ChildWoman1()
{
	LoadActions();

	state = RIGHTWALK;
	actions[state]->Play();

	pos = { -100, 55 };
	
	speed = 150.0f;
}
void ChildWoman1::Actions()
{
	switch (state)
	{
	case Npc::UPWALK:
	{
		pos.y -= speed * DELTA;
		if (pos.y <= 55)
			SetActions(RIGHTWALK);
	}
		break;
	case Npc::DOWNWALK:
	{
		pos.y += speed * DELTA;
		if (pos.y >= 150)
			SetActions(LEFTWALK);
	}
		break;
	case Npc::LEFTWALK:
	{
		pos.x -= speed * DELTA;
		if (pos.x <= -170)
			SetActions(UPWALK);
	}
		break;
	case Npc::RIGHTWALK:
	{
		pos.x += speed * DELTA;
		if (pos.x >= 200)
			SetActions(DOWNWALK);
	}
		break;
	default:
		break;
	}
}

void ChildWoman1::LoadActions()
{
	vector<Texture*> clips;

	wstring filePath = L"Resource/Textures/Npc/children.png";

	//UP
	clips.push_back(TEXTURE->Add(filePath, 7, 7, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 6; i < 9; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 7, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//DOWN
	clips.push_back(TEXTURE->Add(filePath, 7, 4, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 6; i < 9; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 4, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//LEFT
	clips.push_back(TEXTURE->Add(filePath, 7, 5, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 6; i < 9; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 5, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//RIGHT
	clips.push_back(TEXTURE->Add(filePath, 7, 6, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 6; i < 9; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 6, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();
}
