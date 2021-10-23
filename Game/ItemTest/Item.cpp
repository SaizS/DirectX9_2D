#include "framework.h"

Item::Item(ItemData data, Vector2 pos) : Button(DATA->GetItemImage(data.key), pos), data(data), state(INVEN)
{
	selectTexture = TEXTURE->Add(L"Resource/Textures/UI/selected.png");
}

Item::~Item()
{
}

void Item::Update()
{
	Button::Update();
}

void Item::Render()
{
	Button::Render();
}
