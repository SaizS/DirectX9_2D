#pragma once

class Cauldron : public UIObject {
private:
	Texture* texture; //�г�
	ItemInfo* itemInfo; //���� ����

	int curBottle; //���� ���õ� ���� ����(0 �ö�ũ 1 ��)
	vector<int> curEffect; //���� �����Ͽ� ����ִ� ȿ����
	ItemData* selectItem; //���� ������ �������� ����
	float pollutionGauge; //�������� ������
	UINT quantity; //�������� �з�

	ImageFont* pollutionText; //������ �ؽ�Ʈ
	ImageFont* quantityText; //�з� �ؽ�Ʈ

	UIButton* helpBtn; //���� ��ư
	Texture* helpTexture; //���� �̹���
	World* helpWorld; //���� ����
	bool helpActive; //���� Ȱ��ȭ ����

	ItemData* invenSelectItem; //�κ��丮���� ���� ������ �������� ���� (��� ���Կ�)
	vector<ItemSlot*> selectBottle; //�� ���ÿ� ���� ������ ����
	ItemSlot* resultPotion; //���� ����� ����

	bool* invenActive; //�κ��丮 Ȱ��ȭ ����

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