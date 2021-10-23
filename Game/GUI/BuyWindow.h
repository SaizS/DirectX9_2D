#pragma once

class BuyWindow : public UIObject {
private:
	Texture* panel; //패널
	ItemImage* image; //아이템 이미지
	ImageFont* stackText; //아이템 갯수 출력용 이미지 폰트
	ImageFont* costText; //지불 금액 출력용 이미지 폰트
	UIButton* buyBtn; //구입 버튼
	UIButton* cancelBtn; //취소 버튼

	UINT cost; // 상품의 구매하기 위해 지불하는 비용
	int buyStack; // 상품을 구매할 갯수
	
	Vector2 mouseOffset;

	ItemData* selectedItem;
public:
	BuyWindow();
	~BuyWindow();
	void Update();
	void Render();

	void SetActive(Vector2 pos, ItemData* item);
	void Inactive();
	void SetMouseOffset(Vector2 value) { mouseOffset = value; }
	void SetSelectedItem(ItemData* value) { selectedItem = value; }
	ItemData* GetSelectedItem() { return selectedItem; }
};