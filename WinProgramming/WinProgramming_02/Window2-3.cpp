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
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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
	static TCHAR str[100];
	static int x = 0;
	static int y = 0;
	static int N;
	static int count;
	static int check = 1;
	static SIZE size;
	TCHAR lpOut[1000];

	switch (iMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 5, 15);
		ShowCaret(hwnd);
		count = 0;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextExtentPoint(hdc, str, _tcslen(str), &size);
		TextOut(hdc, 0, 0, str, _tcslen(str));
		SetCaretPos(size.cx, 0);
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == VK_BACK && count > 0)count--;
		else if (wParam == VK_RETURN)
		{
			count = 0;
			for (int i = 1; i < 10; ++i)
				wsprintf(lpOut, L"%d * %d = %d", N, i, N * i);
			TextOut(hdc, x, y, lpOut, lstrlen(lpOut));
			SetCaretPos(0, 0);
		}
		else
		{
			str[count++] = wParam;
		}
		str[count] = NULL;
		InvalidateRgn(hwnd, NULL, TRUE);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_DESTROY:
		HideCaret(hwnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

