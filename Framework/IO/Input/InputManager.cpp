#include "framework.h"

InputManager* InputManager::instance = NULL;

InputManager::InputManager() : wheelTime(0.0f), mouseWheel(0), isTalk(false), isAttack(false), isGet(false)
{
	ZeroMemory(keyState, MAXKEY);
	ZeroMemory(keyOldState, MAXKEY);
	ZeroMemory(keyMap, MAXKEY);
}

InputManager::~InputManager()
{
}

InputManager* InputManager::Get()
{
	return instance;
}

void InputManager::Create()
{
	instance = new InputManager();
}

void InputManager::Delete()
{
	delete instance;
}

void InputManager::Update()
{
	memcpy(keyOldState, keyState, MAXKEY);

	ZeroMemory(keyState, MAXKEY);
	ZeroMemory(keyMap, MAXKEY);

	GetKeyboardState(keyState);

	for (int i = 0; i < MAXKEY; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		byte old = keyOldState[i];
		byte cur = keyState[i];

		if (old == 0 && cur == 1)
		{
			keyMap[i] = DOWN;
		}
		else if (old == 1 && cur == 0)
		{
			keyMap[i] = UP;
		}
		else if (old == 1 && cur == 1)
		{
			keyMap[i] = PRESS;
		}
		else
		{
			keyMap[i] = NONE;
		}
	}

	if (KEYDOWN(VK_LBUTTON))
		mouseWheel = 0;

	if (wheelTime > 0) {
		wheelTime -= DELTATIME;
		if (wheelTime < 0) {
			wheelTime = 0.0f;
		}
	}
}

bool InputManager::WheelUp()
{
	if (wheelTime > 0)
		return false;
	if (mouseWheel > 0) {
		wheelTime = 0.05f;
		mouseWheel = 0;
		return true;
	}
	return false;
}

bool InputManager::WheelDown()
{
	if (wheelTime > 0)
		return false;
	if (mouseWheel < 0) {
		wheelTime = 0.05f;
		mouseWheel = 0;
		return true;
	}
	return false;
}
