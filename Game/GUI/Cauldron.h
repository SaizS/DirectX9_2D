#pragma once

class Cauldron : public UIObject {
private:
	Texture* texture; //패널
	ItemInfo* itemInfo; //포션 설명

	int curBottle; //현재 선택된 병의 종류(0 플라스크 1 병)
	vector<int> curEffect; //현재 도가니에 들어있는 효과들
	ItemData* selectItem; //현재 선택한 아이템의 정보
	float pollutionGauge; //도가니의 오염도
	UINT quantity; //도가니의 분량

	ImageFont* pollutionText; //오염도 텍스트
	ImageFont* quantityText; //분량 텍스트

	UIButton* helpBtn; //도움말 버튼
	Texture* helpTexture; //도움말 이미지
	World* helpWorld; //도움말 월드
	bool helpActive; //도움말 활성화 여부

	ItemData* invenSelectItem; //인벤토리에서 현재 선택한 아이템의 정보 (재료 투입용)
	vector<ItemSlot*> selectBottle; //병 선택에 사용될 아이템 슬롯
	ItemSlot* resultPotion; //현재 결과물 포션

	bool* invenActive; //인벤토리 활성화 여부

	Vector2 mousePos;
	Vector2 mouseOffset;
public:
	Cauldron();
	~Cauldron();

	void Update();
	void ResultUpdate();
	void ItemInfoUpdate();
	void Render();
	void ItemInfoRender();

	void OpenCauldron();
	void SelectBottle(int value);
	void InsertMaterial(ItemData* item);
	ItemData* GetSelectedItem() { return selectItem; }
	void SetInvenActive(bool* value) { invenActive = value; }
	void ExtractPotion(void* value);

	//void Save();
	//void Load();

	static bool Compare(int val1, int val2);
};