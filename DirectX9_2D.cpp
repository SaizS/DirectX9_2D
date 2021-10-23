// DirectX9_2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DirectX9_2D.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
POINT tempMouse;
HCURSOR hcur;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DIRECTX92D, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIRECTX92D));

	MSG msg;

	//싱글톤 클래스 생성
	srand((UINT)time(0));
	ShowCursor(FALSE);
	Device::Create();

	Timer::Create();
	Camera::Create();
	InputManager::Create();
	SoundManager::Create();
	TextureManager::Create();
	EffectManager::Create();
	DataManager::Create();
	SceneManager::Create();
	NpcManager::Create();
	EnemyManager::Create();
	PaticleManager::Create();
	MapEditor::Create();

	GameManager* gm = new GameManager();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//Update
			TIMER->Update();
			INPUTMANAGER->Update();
			SOUND->Update();
			CAM->Update();
			gm->Update();
			MAP->Update();
			//
			DEVICE->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BLACK, 1.0f, 0); //화면 배경 색 설정
			DEVICE->BeginScene();
			//Render
			gm->Render();
			TIMER->Render();

			DEVICE->EndScene();
			DEVICE->Present(NULL, NULL, NULL, NULL);
		}
	}
	//싱글톤 클래스 소멸
	delete gm;
	SceneManager::Delete();
	DataManager::Delete();
	EffectManager::Delete();
	TextureManager::Delete();
	Shader::Delete();
	SoundManager::Delete();
	InputManager::Delete();
	Camera::Delete();
	Timer::Delete();
	Device::Delete();
	NpcManager::Delete();
	EnemyManager::Delete();
	PaticleManager::Delete();
	MapEditor::Delete();

	_CrtDumpMemoryLeaks();
	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECTX92D));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DIRECTX92D);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	RECT rect = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	hWnd = CreateWindowW(szWindowClass, L"Sage's Stone", WS_OVERLAPPEDWINDOW,
		WIN_START_X, WIN_START_Y,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr, nullptr, hInstance, nullptr);
	SetMenu(hWnd, false); //메뉴 제거

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	/*
	case WM_SETCURSOR:
	{
		if (InputManager::Get() != NULL)
		{
			if (INPUTMANAGER->GetIsAttack())
				hcur = LoadCursorFromFile(L"Data/Attack.cur");
			else if (INPUTMANAGER->GetIsGet())
				hcur = LoadCursorFromFile(L"Data/Get.cur");
			else if (INPUTMANAGER->GetIsTalk())
				hcur = LoadCursorFromFile(L"Data/Talk.cur");
			else
				hcur = LoadCursorFromFile(L"Data/Idle.cur");

			SetCursor(hcur);
		}
	}
	*/
	break;
	case WM_MOUSEMOVE:
		INPUTMANAGER->SetMousePos(lParam);
		INPUTMANAGER->SetToolMousePos(lParam);
		GetCursorPos(&tempMouse);
		ScreenToClient(hWnd, &tempMouse);
		INPUTMANAGER->SetWinMousePos(tempMouse);
		break;
	case WM_MOUSEWHEEL:
		INPUTMANAGER->SetMouseWheel(wParam);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}