#pragma once

class Item : public Button {
public:
	enum State {
		INVEN
	};
private:
	State state;

	ItemData data; //아이템 데이터
	Texture* selectTexture; //선택 시 보여질 이미지
	ImageFont* countFont; //아이템 보유 갯수 출력

public:
	bool isSelected; //선택 여부
	bool isActive; //활성화 여부

	Item(ItemData data, Vector2 pos);
	~Item();
	void Update();
	void Render();
	ItemData GetData() { return data; }
};