#include "framework.h"

Timer* Timer::instance = NULL; //전역 변수는 초기화 필수

Timer::Timer() 
	: ticksPerSecond(0), curTime(0),
	frameRate(0), frameCount(0), timeElapsed(0.0f), 
	oneSecCount(0.0f), playTime(0.0f), lockFPS(60.0f), isLockFPS(true)
{
	D3DXFONT_DESC desc = {};
	desc.Width = 20;
	desc.Height = 20;
	desc.CharSet = HANGEUL_CHARSET;
	wstring str = L"배달의민족 한나는 열한살";
	wcscpy_s(desc.FaceName, str.c_str());
	D3DXCreateFontIndirect(DEVICE, &desc, &font);

	QueryPerformanceFrequency((LARGE_INTEGER*)& ticksPerSecond);
	timeScale = 1.0f / ticksPerSecond;

	QueryPerformanceCounter((LARGE_INTEGER*)& lastTime);
}

Timer::~Timer()
{
	font->Release();
}

Timer* Timer::GetInstance()
{
	return instance;
}

void Timer::Delete()
{
	delete instance;
}

void Timer::Create()
{
	instance = new Timer();
}

void Timer::Update()
{
	if (isStop)
		return;

	QueryPerformanceCounter((LARGE_INTEGER*)& curTime);
	timeElapsed = (float)(curTime - lastTime) * timeScale;
	
	if (isLockFPS) {
		while (timeElapsed < (1.0f / lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)& curTime);
			timeElapsed = (curTime - lastTime) * timeScale;
		}
	}
	lastTime = curTime;
	
	frameCount++; 
	oneSecCount += timeElapsed; 
	if (oneSecCount >= 1.0f) {
		oneSecCount = 0.0f;
		frameRate = frameCount;
		frameCount = 0;
	}
	playTime += timeElapsed; 
}

void Timer::Render()
{
	wstring str = to_wstring((int)GetFPS());
	RECT rect = { WIN_WIDTH - 100, 5, WIN_WIDTH, 25 };
	font->DrawText(NULL, str.c_str(), -1, &rect, DT_LEFT, 0xffffffff);
}
