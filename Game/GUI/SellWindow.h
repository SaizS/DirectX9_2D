#pragma once

class SellWindow : public UIObject {
private:
	Texture* panel; //패널
	ItemImage* image; //아이템 이미지
	ImageFont* stackText; //아이템 갯수 출력용 이미지 폰트
	ImageFont* takeText; //획득 금액 출력용 이미지 폰트
	UIButton* sellBtn; //판매 버튼
	UIButton* cancelBtn; //취소 버튼

	UINT takeGold; // 상품을 판매하고 얻는 골드
	int sellStack; // 상품을 판매할 갯수


	Vector2 mouseOffset;

	ItemData* selectedItem;
public:
	SellWindow();
	~SellWindow();
	void Update();
	void Render();

	void SetActive(Vector2 pos, ItemData* item);
	void Inactive();
	void SetMouseOffset(Vector2 value) { mouseOffset = value; }
	void SetSelectedItem(ItemData* value) { selectedItem = value; }
	ItemData* GetSelectedItem() { return selectedItem; }
};