#pragma once

class Item : public Button {
public:
	enum State {
		INVEN
	};
private:
	State state;

	ItemData data; //������ ������
	Texture* selectTexture; //���� �� ������ �̹���
	ImageFont* countFont; //������ ���� ���� ���

public:
	bool isSelected; //���� ����
	bool isActive; //Ȱ��ȭ ����

	Item(ItemData data, Vector2 pos);
	~Item();
	void Update();
	void Render();
	ItemData GetData() { return data; }
};