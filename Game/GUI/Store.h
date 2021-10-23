#pragma once

class Store : public UIObject {
private:
	Texture* texture; //패널
	ItemInfo* itemInfo; //아이템 설명
	ItemData* selectItem; //현재 선택한 아이템의 정보
	ItemData* invenSelectItem; //인벤토리에서 현재 선택한 아이템의 정보

	bool* invenActive; //인벤토리 활성화 여부

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