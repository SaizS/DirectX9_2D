#pragma once

class InvenTab : public UIButton {
private:
	ItemImage* image;
	bool isSelect;

public:
	InvenTab(Vector2 pos, int imageNumber = -1, Vector2 offset = { 0, 0 });
	~InvenTab();
	void Update();
	void Render();
};