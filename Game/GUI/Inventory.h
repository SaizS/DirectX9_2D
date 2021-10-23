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

	Texture* texture; //�г�
	ItemInfo* itemInfo; //������ ����
	ItemData* selectItem; //���� ������ �������� ����
	ItemData* curPotion; //���� ���õ� ������ ���� (������ ���� ������ ������ ��ҵǾ ������ �����ؾ� �ϱ⿡)
	Page selectdPage; //���õ� ������ ��ȣ
	int selectedNum; //���õ� ������ ������ ��ȣ
	bool isSelect; //������ ���� ����

	UINT gold; //���
	ImageFont* goldText; //��� �ؽ�Ʈ

	Page page; //���� ������ ��ȣ
	InvenTab* invenTabs[3];
	vector<ItemSlot*> materials; //��� ������ ����
	vector<ItemSlot*> potions; //���� ������ ����
	vector<ItemSlot*> keys; //�߿� ������ ����

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