#pragma once
#define WIDTHCELLCOUNT 5

class Inventory : public UIObject
{
public:
	enum Page {
		MATERIAL = 0,
		POTION,
		KEY
	};
private:
	bool editMode;

	Texture* texture; //패널
	ItemInfo* itemInfo; //아이템 설명
	ItemData* selectItem; //현재 선택한 아이템의 정보
	ItemData* curPotion; //현재 선택된 포션의 정보 (별개로 나눈 이유는 선택이 취소되어도 정보를 유지해야 하기에)
	Page selectdPage; //선택된 페이지 번호
	int selectedNum; //선택된 아이템 슬롯의 번호
	bool isSelect; //아이템 선택 여부

	UINT gold; //골드
	ImageFont* goldText; //골드 텍스트

	Page page; //현재 페이지 번호
	InvenTab* invenTabs[3];
	vector<ItemSlot*> materials; //재료 아이템 슬롯
	vector<ItemSlot*> potions; //포션 아이템 슬롯
	vector<ItemSlot*> keys; //중요 아이템 슬롯

	Vector2 mousePos;
	Vector2 mouseOffset;
public:
	Inventory();
	~Inventory();

	void Update();
	void InvenUpdate();
	void ItemInfoUpdate();
	void Edit();

	void Render();
	void ItemInfoRender();

	void SetPage(int value);
	void SelectSlot(int value);
	void ClearSelectItem();
	void SetGold(UINT value) { gold = value; }
	ItemData* GetSelectedItem() { return selectItem; }
	ItemData* GetSelectedPotion() { return curPotion; }
	UIButton* GetInvenTabs(int index) { return invenTabs[index]; }
	void SetSelectedItem(void* value) {
		if (value != NULL) {
			ItemData* temp = (ItemData*)value;
			selectItem = temp;
		}
	}
	void SetSelectedPotion(ItemData* value) {
		if (value != NULL) {
			selectItem = value;
		}
	}
	bool ItemCheck(int key, int stack = 1);
	int ItemStackCheck(int key);
	void OpenInven();
	void CloseInven();
	void DeleteItem(int key, int stack = 1);
	void GetItem(int key, int stack = 1);
	void BuyItem(void* item, UINT stack);
	void SellItem(void* item, UINT stack);
	void InvenSort();
	void Save();
	void Load();
	static bool Compare(ItemData val1, ItemData val2);
};