#pragma once
#define QUICKSLOTCOUNT 5

class QuickSlot : public UIObject {
private:
	Texture* panel; //패널
	vector<Texture*> selectImages; //선택 이미지 (5장)
	vector<ItemImage*> potionImages; //포션 이미지 (5장)

	Shader* shader; //쉐이더
	Color color; //알파값 조정용 컬러

	int selectedNum;
	vector<ItemData*> selectedPotions; //퀵슬롯에 등록된 포션의 정보 (5개)
public:
	QuickSlot();
	~QuickSlot();
	void ChangeSlot();
	void SlotCheck();
	void Update();
	void Render();

	void SetSelectedPotion(ItemData* value, int index) { selectedPotions[index] = value; }
	ItemData* GetSelectedPotion(int index) { return selectedPotions[index]; }
};