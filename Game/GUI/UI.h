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
	bool UIClickCheck(); //���콺�� UI ������Ʈ�� Ŭ���ߴ� �� ���θ� Ȯ���ϰ� Ŭ�� �� ���� ��ȯ�ϴ� �Լ�
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