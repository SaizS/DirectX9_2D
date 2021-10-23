#pragma once

class HotBar : public UIObject {
private:
	Texture* panel; //�г�
	ItemImage* image; //������ �̹���
	ImageFont* stackText; //������ ���� ��¿� �̹��� ��Ʈ

	ItemData* selectedPotion;
public:
	HotBar();
	~HotBar();
	void Update();
	void Render();

	void SetSelectedPotion(ItemData* value) { selectedPotion = value; }

	ItemData* GetSelectedPotion() { return selectedPotion; }
};