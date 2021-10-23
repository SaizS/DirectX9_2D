#pragma once

class SellWindow : public UIObject {
private:
	Texture* panel; //�г�
	ItemImage* image; //������ �̹���
	ImageFont* stackText; //������ ���� ��¿� �̹��� ��Ʈ
	ImageFont* takeText; //ȹ�� �ݾ� ��¿� �̹��� ��Ʈ
	UIButton* sellBtn; //�Ǹ� ��ư
	UIButton* cancelBtn; //��� ��ư

	UINT takeGold; // ��ǰ�� �Ǹ��ϰ� ��� ���
	int sellStack; // ��ǰ�� �Ǹ��� ����


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