#pragma once

class Button : public World
{
protected:
	enum State {
		NONE = 0,
		OVER,
		DOWN
	} state;
	Texture* texture;
	Texture* objectTexture;
	int value;
	bool isActive; 
	bool isPress;
	function<void()> Event;
	function<void(int)> IntEvent;
	function<void(Texture*)> TextureEvent;
	function<void(wstring)> WstringEvent;

	wstring filePath;
public:
	Button(Texture* texture, Vector2 pos, function<void()> func = NULL);
	Button(Texture* texture, Texture* objectTexture, Vector2 pos = { WIN_HALFWIDTH, WIN_HALFHEIGHT }, function<void()> func = NULL);
	~Button();
	void BtnPress();
	void SetValue(int value) { this->value = value; }
	void SetVoidEvent(function<void()> func) { Event = func; }
	void SetIntEvent(function<void(int)> func) { IntEvent = func; }
	void SetTextureEvent(function<void(Texture*)> func) { TextureEvent = func; }
	void SetWstringEvent(function<void(wstring)> func) { WstringEvent = func; }
	bool IsClicked() { return isPress; }
	void Update();
	void Render();

	void SetFilePath(wstring path) { filePath = path; }

	wstring GetFilePath() { return filePath; }
};