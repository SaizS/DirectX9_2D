#include "framework.h"

InvenTab::InvenTab(Vector2 pos, int imageNumber, Vector2 offset) : UIButton(TEXTURE->Add(L"Resource/Textures/UI/invenTab.png"), pos, offset)
{
	image = new ItemImage(imageNumber);
	image->SetPos(-3, 3);
	image->SetParent(&world);
	SetSize({ texture->GetSize().x, texture->GetSize().y });
}

InvenTab::~InvenTab()
{
	delete image;
}

void InvenTab::Update()
{
	UIButton::Update();
}

void InvenTab::Render()
{
	UIButton::Render();
	image->Render();
}
