#include "framework.h"

TweakBar* TweakBar::instance = NULL;

TweakBar* TweakBar::Get()
{
	return instance;
}

void TweakBar::Create()
{
	instance = new TweakBar();
}

void TweakBar::Delete()
{
	delete instance;
}

void TweakBar::Start()
{
	isDraw = true;

	TwInit(TW_DIRECT3D9, DEVICE);

	bar = TwNewBar("Map Inspector");
	TwDefine("TweakBar color='0 128 255' alpha=128");
	TwDefine("TweakBar size='250 500'");
	TwDefine("TweakBar valueswidth=120");
	TwDefine("TweakBar movable=false");
}

void TweakBar::InputProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TwEventWin(wnd, msg, wParam, lParam);
}

void TweakBar::Render()
{
	TwDraw();
}

TweakBar::TweakBar()
{
}

TweakBar::~TweakBar()
{
	TwTerminate();
}