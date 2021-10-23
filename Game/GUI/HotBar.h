#pragma once

class HotBar : public UIObject {
private:
	Texture* panel; //패널
	ItemImage* image; //아이템 이미지
	ImageFont* stackText; //아이템 갯수 출력용 이미지 폰트

	ItemData* selectedPotion;
public:
	HotBar();
	~HotBar();
	void Update();
	void Render();

	void SetSelectedPotion(ItemData* value) { selectedPotion = value; }

	ItemData* GetSelectedPotion() { return selectedPotion; }
};