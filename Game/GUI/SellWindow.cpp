#include "framework.h"

SellWindow::SellWindow() : takeGold(0), sellStack(0)
{
	isActive = false;
	panel = TEXTURE->Add(L"Resource/Textures/UI/notice_sell.png");
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

	takeText = new ImageFont(2.0f, ImageFont::LEFT);
	takeText->SetPos(-12, 42);
	takeText->SetParent(&world);

	sellBtn = new UIButton(TEXTURE->Add(L"Resource/Textures/UI/sell.png"), { 2, 85 });
	sellBtn->SetParent(&world);
	//구매 이벤트 설정

	cancelBtn = new UIButton(TEXTURE->Add(L"Resource/Textures/UI/cancel.png"), { 75, -84 }, { 0, 0 }, bind(&SellWindow::Inactive, this));
	cancelBtn->SetParent(&world);
	//창 종료 이벤트 설정
}

SellWindow::~SellWindow()
{
	delete image;
	delete stackText;
	delete takeText;
	delete sellBtn;
	delete cancelBtn;
}

void SellWindow::Update()
{
	if (!isActive)
		return;
	World::Update();
	sellBtn->Update();
	cancelBtn->Update();

	if (KEYDOWN(VK_LBUTTON) && Collision(WINMOUSEPOS))
		printf("판매 알림 충돌");

	if (selectedItem != NULL) {
		image->ChangeImage(selectedItem->image);

		if (KEYPRESS(VK_SHIFT)) {
			if (WHEELUP) {
				SOUND->Play("mouseWheel");
				sellStack += 10;
				if (sellStack > (int)selectedItem->stack) {
					sellStack = (int)selectedItem->stack;
					SOUND->Stop("mouseWheel");
				}
			}
			if (WHEELDOWN) {
				SOUND->Play("mouseWheel");
				sellStack -= 10;
				if (sellStack < 1) {
					sellStack = 1;
					SOUND->Stop("mouseWheel");
				}
			}
		}
		else {
			if (WHEELUP) {
				SOUND->Play("mouseWheel");
				sellStack++;
				if (sellStack > (int)selectedItem->stack) {
					sellStack = (int)selectedItem->stack;
					SOUND->Stop("mouseWheel");
				}
			}
			if (WHEELDOWN) {
				SOUND->Play("mouseWheel");
				sellStack--;
				if (sellStack < 1) {
					sellStack = 1;
					SOUND->Stop("mouseWheel");
				}
			}
		}

		stackText->SetValue((UINT)sellStack);
		stackText->Update();
		takeGold = selectedItem->price * sellStack * 0.2f;
		takeText->SetValue(takeGold);
		takeText->Update();

		void* temp = (void*)(selectedItem);
		sellBtn->SetVoidPtr(temp);
		sellBtn->SetIntValue(sellStack);
		sellBtn->SetVoidIntEvent(bind(&Inventory::SellItem, GUI->GetInven(), temp, sellStack));

	}
	else {
		image->ChangeImage(-1);
	}
}

void SellWindow::Render()
{
	if (!isActive)
		return;
	SetWorld();
	panel->AlphaRender();
	image->Render();
	if (stackText->GetValue() > 0)
		stackText->Render();
	if (takeText->GetValue() >= 0)
		takeText->Render();
	sellBtn->Render();
	cancelBtn->Render();
}

void SellWindow::SetActive(Vector2 pos, ItemData* item)
{
	selectedItem = item;
	isActive = true;
	this->pos = pos;
	mouseOffset = pos;
	sellBtn->SetMouseOffset(pos);
	cancelBtn->SetMouseOffset(pos);
	SetOffset(-pos);

	sellStack = 1;
}

void SellWindow::Inactive()
{
	if (isActive) {
		SOUND->Play("off");
		selectedItem = NULL;
		isActive = false;
		sellStack = 1;
		takeGold = 0;
		GUI->GetInven()->ClearSelectItem();
	}
}
