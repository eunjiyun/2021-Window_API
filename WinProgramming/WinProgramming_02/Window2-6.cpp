#include <windows.h>
#include<TCHAR.H>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND   hwnd;
	MSG   msg;
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
		_T("½Ç½À2-6"),
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
	HDC   hdc;
	PAINTSTRUCT ps;
	static TCHAR memo[10][81];
	static int rows, ypos, column;
	int count;
	static SIZE size;

	switch (iMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 3, 15);
		ShowCaret(hwnd);
		rows = 0;
		column = 0;
		ypos = 0;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (count = 0; count < 10; ++count)
		{
			GetTextExtentPoint(hdc, *(memo + count), _tcslen(*(memo + count)), &size);
			TextOut(hdc, 0, count * 20, *(memo + count), _tcslen(*(memo + count)));
			SetCaretPos(rows * 8, column * 20);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		if (wParam == VK_BACK)
			--rows;
		else if (wParam == VK_RETURN)
		{
			rows = 0;
			++column;
			if (column == 10)
				PostQuitMessage(0);
		}
		else
		{
			if (rows == 80)
			{
				++column;
				if (column == 10)
				{
					column = 0;
					rows = 0;
				}
				else
					rows = 0;
			}
			memo[column][rows++] = (TCHAR)wParam;
			memo[column][rows] = 0;
			InvalidateRgn(hwnd, NULL, FALSE);
		}
		break;
	case WM_DESTROY:
		HideCaret(hwnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}