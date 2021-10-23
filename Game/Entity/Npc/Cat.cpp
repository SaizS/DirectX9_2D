#include "framework.h"

Cat::Cat()
{
	LoadActions();

	state = (State)0;
	actions[state]->Play();

	pos = {406, 585};

}

Cat::~Cat()
{
}

void Cat::LoadActions()
{
	vector<Texture*> clips;

	for (int i = 0; i < 3; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Npc/actions2.png", i, 7, 12, 8));

	actions.push_back(new Animation(clips, Type::REVERSE, 0.12));
}
