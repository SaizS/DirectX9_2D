#pragma once
class UIButton : public World
{
protected:
	enum State {
		NONE = 0,
		OVER,
		DOWN
	} state;
	bool isPress; //��ư�� ���� ����
	function<void()> Event;
	function<void(int)> IntEvent;
	function<void(Texture*)> TextureEvent;
	function<void(wstring)> WstringEvent;
	function<void(void*)> VoidEvent;
	function<void(void*, int)> VoidIntEvent;

	Vector2 mouseOffset; //UI�� ��ġ�� ���� �νĵǴ� ���콺 ��ġ�� �޶� Offset�� �����Ͽ���

	Texture* texture;
	wstring filePath;
	void* voidPtr;
	int intValue;
public:
	bool canClick; //��ư�� Ȱ��ȭ ����
	UIButton(Texture* texture, Vector2 pos, Vector2 offset = { 0, 0 }, function<void()> func = NULL);
	~UIButton();
	void BtnPress();
	void SetIntValue(int value) { this->intValue = value; }
	void SetEvent(function<void()> func) { Event = func; }
	void SetIntEvent(function<void(int)> func) { IntEvent = func; }
	void SetTextureEvent(function<void(Texture*)> func) { TextureEvent = func; }
	void SetWstringEvent(function<void(wstring)> func) { WstringEvent = func; }
	void SetVoidEvent(function<void(void*)> func) { VoidEvent = func; }
	void SetVoidIntEvent(function<void(void*, int)> func) { VoidIntEvent = func; }

	void SetVoidPtr(void* value) { voidPtr = value; }
	void* GetVoidPtr() { return voidPtr; }

	bool IsClicked() { return isPress; }
	void Update();
	void Render();

	void SetMouseOffset(Vector2 value) { mouseOffset = value; }
	void SetFilePath(wstring path) { filePath = path; }
};