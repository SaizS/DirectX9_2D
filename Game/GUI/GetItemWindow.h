#pragma once

class GetItemWindow : public UIObject {
private:
	Texture* panel; //판때기
	ItemImage* itemImage; //아이템 사진
	Shader* shader;
	float startFlick;
	float endFlick;
public:
	float duration;
	Color color;

	GetItemWindow(int key, float duration);
	~GetItemWindow();
	void Update();
	void PanelRender();
	void ItemImageRender();
	void SetItemImage(int key) { itemImage->ChangeImage(key); }
	Texture* GetPanel() { return panel; }
};