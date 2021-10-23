#include "framework.h"
#include "ItemSlot.h"

ItemSlot::ItemSlot(ItemData data, Vector2 pos, Vector2 offset) : UIButton(TEXTURE->Add(L"Resource/Textures/UI/slot.png"), pos, offset), data(data), isActive(true), isSelected(false)
{
	image = new ItemImage(this->data.image);
	image->SetParent(&world);

	itemStackText = new ImageFont(2.0f, ImageFont::RIGHT);
	itemStackText->SetPos(28, 13);
	itemStackText->SetParent(&world);

	selectTexture = TEXTURE->Add(L"Resource/Textures/UI/selected.png");

	//이벤트 바인드
}

ItemSlot::~ItemSlot()
{
	delete image;
	delete itemStackText;
}

void ItemSlot::Update()
{
	if (!isActive)
		return;
	image->ChangeImage(data.image);
	image->Update();
	itemStackText->SetValue(data.stack);
	itemStackText->Update();
	UIButton::Update();
}

void ItemSlot::Render()
{
	if (!isActive)
		return;
	SetWorld();
	UIButton::Render();
	image->Render();
	if (isSelected)
		selectTexture->AlphaRender();
	if (itemStackText->GetValue() > 0)
		itemStackText->Render();
}

void ItemSlot::SetData(int key, int image, int type, int effect, int amount, UINT stack, UINT price)
{
	data.key = key;
	data.image = image;
	data.type = type;
	data.effect = effect;
	data.amount = amount;
	data.stack = stack;
	data.price = price;
}
