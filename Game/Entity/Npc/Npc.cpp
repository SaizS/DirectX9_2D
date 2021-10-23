#include "framework.h"


void Npc::Update()
{
	Actions();
	actions[state]->Update();
	World::Update();
}

void Npc::Render()
{
	SetWorld();

	actions[state]->AlphaRender();
}

void Npc::SetActions(State val)
{
	if (state == val)
		return;

	state = val;
	actions[state]->Play();
}

void Npc::Click()
{
	if (KEYDOWN(VK_LBUTTON))
	{
		if (Collision(MOUSEPOS))
		{
			int value = state;

			value++;

			if (value >= actions.size())
				value = 0;

			state = (State)value;
		}
	}
}

void Npc::Actions()
{
}
