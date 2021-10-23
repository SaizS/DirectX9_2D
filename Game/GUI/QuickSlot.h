#pragma once
#define QUICKSLOTCOUNT 5

class QuickSlot : public UIObject {
private:
	Texture* panel; //�г�
	vector<Texture*> selectImages; //���� �̹��� (5��)
	vector<ItemImage*> potionImages; //���� �̹��� (5��)

	Shader* shader; //���̴�
	Color color; //���İ� ������ �÷�

	int selectedNum;
	vector<ItemData*> selectedPotions; //�����Կ� ��ϵ� ������ ���� (5��)
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