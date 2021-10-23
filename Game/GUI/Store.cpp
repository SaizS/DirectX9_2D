#include "framework.h"

Store::Store()
{
	texture = TEXTURE->Add(L"Resource/Textures/UI/store.png");
	SetSize({ texture->GetSize().x, texture->GetSize().y });
	SetOffset(-STORE_X, -STORE_Y);

	itemInfo = new ItemInfo();

	buyWindow = new BuyWindow();
	sellWindow = new SellWindow();

	mouseOffset = { STORE_X, STORE_Y };

	for (int j = 0; j < 3; j++) { //j - y
		for (int i = 0; i < WIDTHCELLCOUNT; i++) { //i - x
			ItemData tempData;
			ItemSlot* temp = new ItemSlot(tempData, { i * 62 - 124.0f , j * 62 - 120.0f }, mouseOffset);
			temp->SetVoidPtr((void*)(&temp->GetData()));
			temp->SetVoidEvent(bind(&Store::SetSelectedItem, this, temp->GetVoidItemData()));
			temp->SetIntValue(i + (j * WIDTHCELLCOUNT));
			temp->SetIntEvent(bind(&Store::SelectSlot, this, placeholders::_1));
			temp->SetParent(&world);
			goods.push_back(temp);
		}
	}

	GoodsChange();

}

Store::~Store()
{
	for (ItemSlot* slot : goods)
		delete slot;
	delete itemInfo;
	delete buyWindow;
	delete sellWindow;
}

void Store::Update()
{
	mousePos = WINMOUSEPOS - mouseOffset;

	if (!*invenActive) {
		isActive = false;
		selectItem = NULL;
		buyWindow->Inactive();
		sellWindow->Inactive();
	}

	if (!isActive)
		return;
	World::Update();
	if (buyWindow->isActive) {
		for (ItemSlot* slot : goods)
			slot->canClick = false;
	}
	else {
		for (ItemSlot* slot : goods)
			slot->canClick = true;
	}
	for (ItemSlot* slot : goods)
		slot->Update();
	buyWindow->Update();
	sellWindow->Update();

	ItemInfoUpdate();
}

void Store::ItemInfoUpdate()
{
	itemInfo->ChangeImage(-1);
	itemInfo->ChangeType(0);
	for (ItemSlot* index : goods) {
		if (index->Collision(mousePos)) {
			ItemData temp = index->GetData();
			itemInfo->ChangeImage(temp.key);
			itemInfo->ChangeType(temp.type);
			break;
		}
	}
	Vector2 offset = { STORE_X, STORE_Y };
	switch (itemInfo->GetType())
	{
	case 0:
		itemInfo->SetPos(mousePos + offset + (DATA->GetItemInfoImage(0)->GetSize() * 0.5f));
		break;
	case 1:
		itemInfo->SetPos(mousePos + offset + (DATA->GetItemInfoImage(100)->GetSize() * 0.5f));
		break;
	case 2:
		itemInfo->SetPos(mousePos + offset + (DATA->GetItemInfoImage(200)->GetSize() * 0.5f));
		break;
	default:
		break;
	}
	if (itemInfo->pos.x > WIN_WIDTH - (DATA->GetItemInfoImage(0)->GetSize().x * 0.5f)) {
		float temp = itemInfo->pos.x - WIN_WIDTH + (DATA->GetItemInfoImage(0)->GetSize().x * 0.5f);
		itemInfo->pos.x -= temp;
	}
}

void Store::GoodsChange()
{
	int temp;
	goods[0]->SetData(0, 0, 0, 0, 0, 25, 25);
	goods[1]->SetData(1, 1, 0, 0, 0, 25, 25);

	temp = OP::Random(2, 3);
	goods[2]->SetData(temp, temp, 0, 0, 0, 75, 75);
	goods[3]->SetData(12, 12, 0, 0, 0, 100, 100);

	temp = OP::Random(0, 2);
	goods[4]->SetData(5 + temp, 5 + temp, 0, 0, 0, 200, 200);
}

void Store::OpenStore()
{
	if (*invenActive) {
		isActive = true;
		if (isActive) {
			GUI->GetInven()->ClearSelectItem();
		}
	}
	selectItem = NULL;
	buyWindow->Inactive();
	sellWindow->Inactive();
}

void Store::Render()
{
	if (!isActive)
		return;
	SetWorld();
	texture->AlphaRender();
	for (ItemSlot* slot : goods)
		slot->Render();
}

void Store::ItemInfoRender()
{
	if (!buyWindow->isActive && !sellWindow->isActive && isActive)
		itemInfo->Render();
}

void Store::WindowRender()
{
	if (buyWindow->isActive)
		buyWindow->Render();
	if (sellWindow->isActive)
		sellWindow->Render();
}

void Store::SelectSlot(int value)
{
	if (!buyWindow->isActive) {
		if (selectItem->key >= 0) {
			if (!sellWindow->isActive) {
				SOUND->Play("btnPress");
				buyWindow->SetActive({ WIN_HALFWIDTH, STORE_Y }, selectItem);
			}
		}
	}
}
