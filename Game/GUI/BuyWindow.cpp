#include "framework.h"

BuyWindow::BuyWindow() :cost(0), buyStack(0)
{
	isActive = false;
	panel = TEXTURE->Add(L"Resource/Textures/UI/notice_buy.png");
	SetSize({ panel->GetSize().x, panel->GetSize().y });


	if (selectedItem != NULL)
		image = new ItemImage(selectedItem->image);
	else
		image = new ItemImage();
	image->SetPos(0, -17);
	image->SetParent(&world);

	stackText = new ImageFont(2.0f, ImageFont::RIGHT);
	stackText->SetPos(28, -3);
	stackText->SetParent(&world);

	costText = new ImageFont(2.0f, ImageFont::LEFT);
	costText->SetPos(-12, 42);
	costText->SetParent(&world);

	buyBtn = new UIButton(TEXTURE->Add(L"Resource/Textures/UI/buy.png"), { 2, 85 });
	buyBtn->SetParent(&world);
	//구매 이벤트 설정

	cancelBtn = new UIButton(TEXTURE->Add(L"Resource/Textures/UI/cancel.png"), { 75, -84 }, { 0, 0 }, bind(&BuyWindow::Inactive, this));
	cancelBtn->SetParent(&world);
	//창 종료 이벤트 설정
}

BuyWindow::~BuyWindow()
{
	delete image;
	delete stackText;
	delete costText;
	delete buyBtn;
	delete cancelBtn;
}

void BuyWindow::Update()
{
	if (!isActive)
		return;
	World::Update();
	buyBtn->Update();
	cancelBtn->Update();

	if (selectedItem != NULL) {
		image->ChangeImage(selectedItem->image);

		if (KEYPRESS(VK_SHIFT)) {
			if (WHEELUP) {
				SOUND->Play("mouseWheel");
				buyStack += 10;
				if (buyStack > 99) {
					buyStack = 99;
					SOUND->Stop("mouseWheel");
				}
			}
			if (WHEELDOWN) {
				SOUND->Play("mouseWheel");
				buyStack -= 10;
				if (buyStack < 1) {
					buyStack = 1;
					SOUND->Stop("mouseWheel");
				}
			}
		}
		else {
			if (WHEELUP) {
				SOUND->Play("mouseWheel");
				buyStack ++;
				if (buyStack > 99) {
					buyStack = 99;
					SOUND->Stop("mouseWheel");
				}
			}
			if (WHEELDOWN) {
				SOUND->Play("mouseWheel");
				buyStack --;
				if (buyStack < 1) {
					buyStack = 1;
					SOUND->Stop("mouseWheel");
				}
			}
		}

		stackText->SetValue((UINT)buyStack);
		stackText->Update();
		cost = selectedItem->stack * buyStack;
		costText->SetValue(cost);
		costText->Update();

		void* temp = (void*)(selectedItem);
		buyBtn->SetVoidPtr(temp);
		buyBtn->SetIntValue(buyStack);
		buyBtn->SetVoidIntEvent(bind(&Inventory::BuyItem, GUI->GetInven(), temp, buyStack));

	}
	else {
		image->ChangeImage(-1);
	}
}

void BuyWindow::Render()
{
	if (!isActive)
		return;
	SetWorld();
	panel->AlphaRender();
	image->Render();
	if (stackText->GetValue() > 0)
		stackText->Render();
	if (costText->GetValue() >= 0)
		costText->Render();
	buyBtn->Render();
	cancelBtn->Render();
}

void BuyWindow::SetActive(Vector2 pos, ItemData* item)
{
	selectedItem = item;
	isActive = true;
	this->pos = pos;
	mouseOffset = pos;
	buyBtn->SetMouseOffset(pos);
	cancelBtn->SetMouseOffset(pos);
	buyStack = 1;
}

void BuyWindow::Inactive()
{
	if (isActive) {
		SOUND->Play("off");
		selectedItem = NULL;
		isActive = false;
		buyStack = 1;
		cost = 0;
	}
}
