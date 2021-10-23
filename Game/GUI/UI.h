#pragma once
#define GUI UI::GetInstance()
#define INVEN_X 190
#define INVEN_Y 385
#define STORE_X 830
#define STORE_Y 385
#define CAULDRON_X 810
#define CAULDRON_Y 385
#define GWM_X 88
#define GWM_Y 668


class UI
{
private:
	static UI* instance;
	UI();
	~UI();


	D3DXMATRIX view;
	bool isActive;

	Cursor* cursor;

	Inventory* inven;
	Store* store;
	Cauldron* cauldron;
	StateBar* stateBar;
	BossHpBar* bossHpBar;
	HotBar* hotBar;
	QuickSlot* quickSlot;
	GWManager* gwm;

	vector<UIObject*> UIObjects;
	vector<UIButton*> UIButtons;
public:
	static UI* GetInstance() { return instance; }
	static void Create() { instance = new UI(); }
	static void Delete() { delete instance; }
	bool UIClickCheck(); //마우스가 UI 오브젝트를 클릭했는 지 여부를 확인하고 클릭 시 참을 반환하는 함수
	void Update();
	void Render();
	void SetHp(float* curHp, float* maxHp);
	void SetBossHp(float* curHp, float* maxHp);
	BossHpBar* GetBossHpBar() { return bossHpBar; }
	HotBar* GetHotBar() { return hotBar; }
	QuickSlot* GetQuickSlot() { return quickSlot; }
	Inventory* GetInven() { return inven; }
	Store* GetStore() { return store; }
	Cauldron* GetCauldron() { return cauldron; }
	GWManager* GetGWM() { return gwm; }
};