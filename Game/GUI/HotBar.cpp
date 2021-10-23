#include "framework.h"

HotBar::HotBar()
{
	isActive = true;
	panel = TEXTURE->Add(L"Resource/Textures/UI/hotbar.png");

	if (selectedPotion != NULL)
		image = new ItemImage(selectedPotion->image);
	else
		image = new ItemImage();
	image->SetPos(-12, 3);
	image->SetParent(&world);

	stackText = new ImageFont(2.0f, ImageFont::RIGHT);
	stackText->SetPos(16, 16);
	stackText->SetParent(&world);
}

HotBar::~HotBar()
{
	delete image;
	delete stackText;
}

void HotBar::Update()
{
	if (selectedPotion != NULL) {
		image->ChangeImage(selectedPotion->image);
		stackText->SetValue(selectedPotion->stack);
		stackText->Update();
	}
	else {
		image->ChangeImage(-1);
	}
}

void HotBar::Render()
{
	World::Update();
	if (!isActive)
		return;
	SetWorld();
	panel->AlphaRender();
	image->Render();
	if(stackText->GetValue() > 0 && selectedPotion != NULL)
		stackText->Render();
}
