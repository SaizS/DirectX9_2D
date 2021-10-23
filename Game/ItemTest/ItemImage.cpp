#include "framework.h"

ItemImage::ItemImage(int value) : imageNumber(value)
{
	if (imageNumber < -1 && imageNumber > 300) {
		if (imageNumber < -1)
			imageNumber = -1;
		if (imageNumber > 299)
			imageNumber = 299;
		texture = DATA->GetItemImage(value);
		return;
	}
	else {
		texture = DATA->GetItemImage(imageNumber);
	}
}

void ItemImage::Update()
{
	if (imageNumber < 0)
		return;
	else {
		texture = DATA->GetItemImage(imageNumber);
		texture->AlphaRender();
	}
}

void ItemImage::Render()
{
	World::Update();
	SetWorld();
	if (imageNumber < -1)
		imageNumber = -1;
	if (imageNumber > 299)
		imageNumber = 299;
	if (imageNumber < 0)
		return;
	else {
		texture = DATA->GetItemImage(imageNumber);
		texture->AlphaRender();
	}
}

void ItemImage::UnSetWorldRender()
{
	World::Update();
	if (imageNumber < -1)
		imageNumber = -1;
	if (imageNumber > 299)
		imageNumber = 299;
	if (imageNumber < 0)
		return;
	else {
		texture = DATA->GetItemImage(imageNumber);
		texture->AlphaRender();
	}
}
