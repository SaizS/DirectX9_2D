#pragma once

class ItemSlot : public UIButton {
private:
	ItemImage* image; //아이템 이미지
	ItemData data; //아이템 데이터
	Texture* selectTexture; //선택 시 보여질 이미지
	ImageFont* itemStackText; //아이템 보유 갯수 출력
	//커서 올리면 출력될 아이템 이미지 선언

public:
	bool isSelected; //선택 여부
	bool isActive; //활성화 여부

	ItemSlot(ItemData data, Vector2 pos, Vector2 offset = { 0, 0 });
	~ItemSlot();
	void Update();
	void Render();
	void* GetVoidItemData() { return (void*)&data; }
	ItemData GetData() { return data; }
	ItemData* GetDataRef() { return &data; }
	void SetData(int key = -1, int image = -1, int type = 0, int effect = 0, int amount = 0, UINT stack = 0, UINT price = 0);
	void SetData(ItemData value) { data = value; }
	void SetKey(int value) { data.key = value; }
	void SetImage(int value) { data.image = value; }
	void SetType(int value) { data.type = value; }
	void SetEffect(int value) { data.effect = value; }
	void SetAmount(int value) { data.amount = value; }
	void SetStack(UINT value) { data.stack = value; }
	void AddStack(UINT value) { data.stack += value; }
	void SetPrice(UINT value) { data.price = value; }
};