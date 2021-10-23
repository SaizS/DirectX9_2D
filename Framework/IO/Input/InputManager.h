#pragma once

#define INPUTMANAGER InputManager::Get()
#define MAXKEY 255
#define KEYDOWN(key) InputManager::Get()->keyDown(key)
#define KEYUP(key) InputManager::Get()->keyUp(key)
#define KEYPRESS(key) InputManager::Get()->keyPress(key)
#define MOUSEPOS InputManager::Get()->GetMousePos()
#define WINMOUSEPOS InputManager::Get()->GetWinMousePos()
#define TOOLMOUSEPOS InputManager::Get()->GetToolMousePos()
#define MOUSEWHEEL InputManager::Get()->GetMouseWheel()
#define WHEELUP InputManager::Get()->WheelUp()
#define WHEELDOWN InputManager::Get()->WheelDown()
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35 
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

class InputManager
{
private:
	enum KeyState
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};

	byte keyState[MAXKEY];
	byte keyOldState[MAXKEY];
	byte keyMap[MAXKEY];

	Vector2 mousePos;
	Vector2 winMousePos;

	Vector2 toolMousePos;
	Vector2 toolPos;
	short mouseWheel;
	float wheelTime;

	bool isTalk;
	bool isAttack;
	bool isGet;

	static InputManager* instance;
	InputManager();
	~InputManager();
public:
	static InputManager* Get();
	static void Create();
	static void Delete();

	void Update();

	void SetMousePos(LPARAM lParam) { mousePos.x = (float)LOWORD(lParam) - CAM->GetPos().x, mousePos.y = (float)HIWORD(lParam) - CAM->GetPos().y; }
	void SetToolMousePos(LPARAM lParam) { toolMousePos.x = (float)LOWORD(lParam) + toolPos.x, toolMousePos.y = (float)HIWORD(lParam) + toolPos.y; }
	void SetWinMousePos(POINT value) {
		winMousePos.x = (float)value.x;
		winMousePos.y = (float)value.y;
	}
	void SetMouseWheel(WPARAM wParam) { mouseWheel = (short)HIWORD(wParam); }
	void SetToolPos(Vector2 pos) { toolPos = pos; }

	Vector2 GetMousePos() { return mousePos; }
	Vector2 GetWinMousePos() { return winMousePos; }
	Vector2 GetToolMousePos() { return toolMousePos; }

	short GetMouseWheel() { return mouseWheel; }
	bool keyDown(DWORD key) { return keyMap[key] == DOWN; }
	bool keyUp(DWORD key) { return keyMap[key] == UP; }
	bool keyPress(DWORD key) { return keyMap[key] == PRESS; }
	bool WheelUp();
	bool WheelDown();

	void SetIsTalk(bool value) { isTalk = value; }
	void SetIsAttack(bool value) { isAttack = value; }
	void SetIsGet(bool value) { isGet = value; }

	bool GetIsTalk() { return isTalk; }
	bool GetIsAttack() { return isAttack; }
	bool GetIsGet() { return isGet; }
};