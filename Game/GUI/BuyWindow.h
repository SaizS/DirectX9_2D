#pragma once

class BuyWindow : public UIObject {
private:
	Texture* panel; //�г�
	ItemImage* image; //������ �̹���
	ImageFont* stackText; //������ ���� ��¿� �̹��� ��Ʈ
	ImageFont* costText; //���� �ݾ� ��¿� �̹��� ��Ʈ
	UIButton* buyBtn; //���� ��ư
	UIButton* cancelBtn; //��� ��ư

	UINT cost; // ��ǰ�� �����ϱ� ���� �����ϴ� ���
	int buyStack; // ��ǰ�� ������ ����
	
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