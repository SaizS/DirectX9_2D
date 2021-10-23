#pragma once

class Store : public UIObject {
private:
	Texture* texture; //�г�
	ItemInfo* itemInfo; //������ ����
	ItemData* selectItem; //���� ������ �������� ����
	ItemData* invenSelectItem; //�κ��丮���� ���� ������ �������� ����

	bool* invenActive; //�κ��丮 Ȱ��ȭ ����

	vector<ItemSlot*> goods;

	Vector2 mousePos;
	Vector2 mouseOffset;

	BuyWindow* buyWindow;
	SellWindow* sellWindow;
public:
	Store();
	~Store();

	void Update();
	void ItemInfoUpdate();
	void GoodsChange();

	void OpenStore();

	void Render();
	void ItemInfoRender();
	void WindowRender();

	void SetSelectedItem(void* value) {
		if (value != NULL) {
			ItemData* temp = (ItemData*)value;
			selectItem = temp;
			printf("key : %d, type : %d, stack : %d\n", selectItem->key, selectItem->type, selectItem->stack);
		}
	}
	void SelectSlot(int value);
	ItemData* GetSelectedItem() { return selectItem; }
	void SetInvenActive(bool* value) { invenActive = value; }
	BuyWindow* GetBuyWindow() { return buyWindow; }
	SellWindow* GetSellWindow() { return sellWindow; }
};