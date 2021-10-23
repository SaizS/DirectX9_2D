#include "framework.h"

Cursor::Cursor()
{
	for (int i = 0; i < 4; i++) {
		textures.push_back(TEXTURE->Add(L"Resource/Textures/UI/cursor.png", i, 0, 4, 1));
	}
}

Cursor::~Cursor()
{
}

void Cursor::Update()
{
	Vector2 temp = { 12, 12 };
	SetPos(WINMOUSEPOS + temp);
	World::Update();
}

void Cursor::Render()
{
	SetWorld();
	if (INPUTMANAGER->GetIsGet())
		textures[1]->AlphaRender();
	else if (INPUTMANAGER->GetIsTalk())
		textures[2]->AlphaRender();
	else if (INPUTMANAGER->GetIsAttack())
		textures[3]->AlphaRender();
	else
		textures[0]->AlphaRender();
}
