#include "framework.h"

BlackSmith::BlackSmith()
{
	LoadActions();

	state = DOWNIDLE;

	pos = { 781, 661 };
	SetCollider(35, 50);

	actions[state]->Play();
}

BlackSmith::~BlackSmith()
{
	for (Animation* ani : actions)
		delete ani;
}

void BlackSmith::Update()
{
	Npc::Update();

	if (!isCreate)
		return;

}

void BlackSmith::LoadActions()
{
	vector<Texture*> clips;

	wstring filePath = L"Resource/Textures/Npc/BlackSmith/blacksmith.png";

	//UPIDLE
	clips.push_back(TEXTURE->Add(filePath, 1, 3, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	//UPWALK
	for(int i = 0; i < 3; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 3, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE, 0.2f));
	clips.clear();

	//DOWNIDLE
	clips.push_back(TEXTURE->Add(filePath, 1, 0, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	//DOWNWALK
	for (int i = 0; i < 3; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 0, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE, 0.2f));
	clips.clear();

	//LEFTIDLE
	clips.push_back(TEXTURE->Add(filePath, 1, 1, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	//LEFTWALK
	for (int i = 0; i < 3; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 1, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE, 0.2f));
	clips.clear();

	//RIGHTIDLE
	clips.push_back(TEXTURE->Add(filePath, 1, 2, 12, 8));
	actions.push_back(new Animation(clips));
	clips.clear();

	//RIGHTWALK
	for (int i = 0; i < 3; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 2, 12, 8));
	actions.push_back(new Animation(clips, Type::REVERSE, 0.2f));
	clips.clear();

	//WORK
	for (int i = 1; i < 5; i++)
	{
		wstring path = L"Resource/Textures/Npc/BlackSmith/" + to_wstring(i) + L".png";
		clips.push_back(TEXTURE->Add(path));
	}	
	actions.push_back(new Animation(clips, Type::LOOP, 0.15f));
}
