#include "framework.h"

ChildWoman2::ChildWoman2()
{
	LoadActions();

	state = RIGHTWALK;
	actions[state]->Play();

	pos = { -50, 55 };

	speed = 150.0f;
}

ChildWoman2::~ChildWoman2()
{
}

void ChildWoman2::Actions()
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

void ChildWoman2::LoadActions()
{
	vector<Texture*> clips;

	wstring filePath = L"Resource/Textures/Npc/children.png";

	//UP
	clips.push_back(TEXTURE->Add(filePath, 10, 7, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 9; i < 12; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 7, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//DOWN
	clips.push_back(TEXTURE->Add(filePath, 10, 4, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 9; i < 12; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 4, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//LEFT
	clips.push_back(TEXTURE->Add(filePath, 10, 5, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 9; i < 12; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 5, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();

	//RIGHT
	clips.push_back(TEXTURE->Add(filePath, 10, 6, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 9; i < 12; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 6, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE));
	clips.clear();
}
