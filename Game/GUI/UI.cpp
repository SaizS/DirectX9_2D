#include "framework.h"
#include "UI.h"

UI* UI::instance = NULL;

UI::UI() : isActive(true)
{
	cursor = new Cursor();

	inven = new Inventory();
	inven->SetPos(INVEN_X, INVEN_Y);

	store = new Store();
	store->SetPos(STORE_X, STORE_Y);
	store->SetInvenActive(&inven->isActive);

	gwm = new GWManager();
	gwm->SetPos(GWM_X, GWM_Y);

	cauldron = new Cauldron();
	cauldron->SetPos(CAULDRON_X, CAULDRON_Y);
	cauldron->SetInvenActive(&inven->isActive);

	stateBar = new StateBar();
	stateBar->SetPos(117, 50);

	bossHpBar = new BossHpBar();
	bossHpBar->SetPos(WIN_HALFWIDTH, 100);
	
	hotBar = new HotBar();
	hotBar->SetPos(965, 669);

	quickSlot = new QuickSlot();
	quickSlot->SetPos(WIN_HALFWIDTH, 665);

	D3DXMatrixIdentity(&view);

	UIObjects.push_back(inven);
	UIObjects.push_back(store);
	UIObjects.push_back(store->GetBuyWindow());
	UIObjects.push_back(store->GetSellWindow());
	UIObjects.push_back(cauldron);

	UIButtons.push_back(inven->GetInvenTabs(0));
	UIButtons.push_back(inven->GetInvenTabs(1));
	UIButtons.push_back(inven->GetInvenTabs(2));
}

UI::~UI()
{
	delete cursor;
	delete gwm;
	delete inven;
	delete store;
	delete stateBar;
	delete bossHpBar;
	delete hotBar;
	delete quickSlot;
	delete cauldron;
}

bool UI::UIClickCheck()
{
	for (UIObject* index : UIObjects) {
		if (index->Collision(WINMOUSEPOS + index->offset) && KEYDOWN(VK_LBUTTON) && index->isActive)
			return true;
	}
	for (UIButton* index : UIButtons) {
		if (index->Collision({WINMOUSEPOS.x - INVEN_X, WINMOUSEPOS.y - INVEN_Y}) && KEYDOWN(VK_LBUTTON) && inven->isActive)
			return true;
	}
	return false;
}

void UI::Update()
{
	UIClickCheck();
	cursor->Update();

	if (isActive) {
		stateBar->Update();
		hotBar->Update();
		quickSlot->Update();
		gwm->Update();
		inven->Update();
		store->Update();
		cauldron->Update();
	}
}

void UI::Render()
{
	if (isActive) {
		DEVICE->SetTransform(D3DTS_VIEW, &view);
		stateBar->Render();
		bossHpBar->Render();
		hotBar->Render();
		quickSlot->Render();
		gwm->Render();
		inven->Render();
		store->Render();
		cauldron->Render();

		inven->ItemInfoRender();
		store->ItemInfoRender();
		cauldron->ItemInfoRender();

		store->WindowRender();

		cursor->Render();
	}
}

void UI::SetHp(float* curHp, float* maxHp)
{
	stateBar->SetHp(curHp, maxHp);
}

void UI::SetBossHp(float* curHp, float* maxHp)
{
	bossHpBar->SetHp(curHp, maxHp);
}
