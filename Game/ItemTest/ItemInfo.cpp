#include "framework.h"

ItemInfo::ItemInfo(int value) : imageNumber(value)
{
	if (imageNumber < 0)
		return;
	else {
		texture = DATA->GetItemInfoImage(imageNumber);
	}
}

void ItemInfo::Render()
{
	World::Update();
	SetWorld();
	if (imageNumber < -1)
		imageNumber = -1;
	if (imageNumber > 300)
		imageNumber = 300;
	if (imageNumber < 0)
		return;
	texture = DATA->GetItemInfoImage(imageNumber);
	texture->AlphaRender();
}
