#include<Windows.h>
#include<TCHAR.H>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("windows program 2-1"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		863,
		705,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	RECT rect2;
	RECT rect3;
	RECT rect4;
	RECT rect5;

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		rect.left = 0;
		rect.top = 0;
		rect.right = 150;
		rect.bottom = 80;
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(0, 255, 0));
		DrawText(hdc, _T("Left-top (0,0)"), 14, &rect,
			DT_SINGLELINE | DT_LEFT | DT_TOP);

		rect2.left = 700;
		rect2.top = 0;
		rect2.right = 850;
		rect2.bottom = 80;
		SetTextColor(hdc, RGB(0, 0, 255));
		SetBkColor(hdc, RGB(255, 0, 255));
		DrawText(hdc, _T("Right-top (700,0)"), 17, &rect2,
			DT_SINGLELINE | DT_LEFT | DT_TOP);

		rect3.left = 0;
		rect3.top = 650;
		rect3.right = 150;
		rect3.bottom = 730;
		SetTextColor(hdc, RGB(180, 255, 0));
		SetBkColor(hdc, RGB(0, 100, 255));
		DrawText(hdc, _T("Left-bottom (0,650)"), 19, &rect3,
			DT_SINGLELINE | DT_LEFT | DT_TOP);

		rect4.left = 700;
		rect4.top = 650;
		rect4.right = 850;
		rect4.bottom = 730;
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(255, 255, 0));
		DrawText(hdc, _T("Right-bottom (700,650)"), 22, &rect4,
			DT_SINGLELINE | DT_LEFT | DT_TOP);

		rect5.left = 350;
		rect5.top = 300;
		rect5.right = 500;
		rect5.bottom = 380;
		SetTextColor(hdc, RGB(180, 0, 50));
		SetBkColor(hdc, RGB(0, 255, 255));
		DrawText(hdc, _T("Center (350,300)"), 16, &rect5,
			DT_SINGLELINE | DT_LEFT | DT_TOP);

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
