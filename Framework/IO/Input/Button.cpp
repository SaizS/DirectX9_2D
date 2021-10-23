#include "framework.h"

Button::Button(Texture* texture, Vector2 pos, function<void()> func) : texture(texture), isActive(true), isPress(false), Event(func), IntEvent(NULL), TextureEvent(NULL), WstringEvent(NULL), state(NONE), objectTexture(NULL)
{
	this->pos = pos;
	SetCollider(texture->GetSize());
	SOUND->Add("btnPress", "Resource/SoundFx/btnPress.wav");
}

Button::Button(Texture* texture, Texture* objectTexture, Vector2 pos, function<void()> func) : texture(texture), isActive(true), isPress(false), Event(func), IntEvent(NULL), TextureEvent(NULL), WstringEvent(NULL), state(NONE),
objectTexture(objectTexture)
{
	this->pos = pos;
	SetCollider(texture->GetSize());
	SOUND->Add("btnPress", "Resource/SoundFx/btnPress.wav");
}

Button::~Button()
{
}

void Button::BtnPress()
{
	if (isActive) {
		if (Collision(TOOLMOUSEPOS)) {
			if (!isPress) {
				state = OVER;
				SetScale(1.1f, 1.1f);
			}
			if (KEYDOWN(VK_LBUTTON) && !isPress) {
				state = DOWN;
				isPress = true;
				SOUND->Play("btnPress");
				SetScale(0.9f, 0.9f);
				if (Event != NULL)
					Event();
				if (IntEvent != NULL)
					IntEvent(value);
				if (TextureEvent != NULL)
					TextureEvent(objectTexture);
				if (WstringEvent != NULL)
					WstringEvent(filePath);
			}
			else if (!KEYPRESS(VK_LBUTTON) && isPress) {
				state = NONE;
				isPress = false;
				SetScale(1, 1);
				if (Collision(TOOLMOUSEPOS)) {
					state = OVER;
					SetScale(1.1f, 1.1f);
				}
			}
		}
		else {
			state = NONE;
			SetScale(1, 1);
		}
	}
}

void Button::Update()
{
	World::Update();
	BtnPress();
}

void Button::Render()
{
	SetWorld();
	if (isActive) {
		texture->AlphaRender();
	}
}
