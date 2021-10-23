#include "framework.h"

UIButton::UIButton(Texture* texture, Vector2 pos, Vector2 offset, function<void()> func) : texture(texture), canClick(true), isPress(false), Event(func), IntEvent(NULL), TextureEvent(NULL), WstringEvent(NULL), state(NONE), mouseOffset(offset)
{
	this->pos = pos;
	SetCollider(texture->GetSize());
}

UIButton::~UIButton()
{
}

void UIButton::BtnPress()
{
	if (canClick) {
		if (Collision(WINMOUSEPOS - mouseOffset)) { 
			if (!isPress) {
				state = OVER;
			}
			if (KEYDOWN(VK_LBUTTON) && !isPress) { 
				state = DOWN;
		 		isPress = true;
				if (Event != NULL)
					Event();
				if (VoidEvent != NULL && voidPtr != NULL)
					VoidEvent(voidPtr);
				if (IntEvent != NULL)
					IntEvent(intValue);
				if (VoidIntEvent != NULL && voidPtr != NULL)
					VoidIntEvent(voidPtr, intValue);
				if (TextureEvent != NULL)
					TextureEvent(texture);
				if (WstringEvent != NULL)
					WstringEvent(filePath);
			}
			else if (!KEYPRESS(VK_LBUTTON) && isPress) {
				state = NONE;
				isPress = false;
				if (Collision(WINMOUSEPOS - mouseOffset)) {
					state = OVER;
				}
			}
		}
		else {
			state = NONE;
		}
	}
}

void UIButton::Update()
{
	World::Update();
	BtnPress();
}

void UIButton::Render()
{
	SetWorld();
	texture->AlphaRender();
}
