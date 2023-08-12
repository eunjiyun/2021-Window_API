#include<Windows.h>
#include"resource.h"
#include<TCHAR.H>
#include<iostream>
#include<random>
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
using namespace std;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int>b5x6(0, 4);
uniform_int_distribution<int>b6x8(0, 5);
uniform_int_distribution<int>b7x9(0, 6);

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = _T("Window Class Name");

	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("≈◊∆Æ∏ÆΩ∫"),
		WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_HSCROLL | WS_VSCROLL,
		0,
		0,
		600,
		800,
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
class block
{
public:
	int xpos = 0;
	int ypos = 35;
};
HDC hdc;
PAINTSTRUCT ps;
HPEN pen;
block crush[63];

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	static bool stop = FALSE;
	static int whatBoard = -1;
	static int blockLocation = -1;
	static int filled5x6[5] = { 710,710,710,710,710 };
	static int filled6x8[6] = { 710,710,710,710,710,710 };
	static int filled7x9[7] = { 710,710,710,710,710,710,710 };

	switch (iMsg)
	{
	case WM_CREATE:
		pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		break;
	case WM_COMMAND:
		hdc = GetDC(hwnd);
		if (LOWORD(wParam) == ID_BOARD_5X6)
		{
			whatBoard = 0;
			blockLocation = b5x6(gen);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == ID_BOARD_6X8)
		{
			whatBoard = 1;
			blockLocation = b6x8(gen);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == ID_BOARD_7X9)
		{
			whatBoard = 2;
			blockLocation = b7x9(gen);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == ID_GOAL_512)
		{
		}
		else if (LOWORD(wParam) == ID_GOAL_1024)
		{
		}
		else if (LOWORD(wParam) == ID_GOAL_2048)
		{
		}
		else if (LOWORD(wParam) == ID_GOAL_4096)
		{
		}
		else if (LOWORD(wParam) == ID_GOAL_8192)
		{
		}
		else if (LOWORD(wParam) == ID_SPEED_FAST)
		{
		}
		else if (LOWORD(wParam) == ID_SPEED_SLOW)
		{
		}
		else if (LOWORD(wParam) == ID_SPEED_MEDIUM)
		{
		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 0x53://s Ω√¿€ ∏ÿ√„
			if (stop == FALSE)
			{
				SetTimer(hwnd, 1, 500, NULL);
				stop = TRUE;
			}
			else
			{
				KillTimer(hwnd, 1);
				stop = FALSE;
			}
			break;
		case 0x51://q ¡æ∑·
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_TIMER:
		GetDC(hwnd);
		if (wParam == 1)
		{
			for (int i = 0; i < 5; ++i)
			{
				if (blockLocation == i)
				{
					if (crush[i].ypos < 615)
						crush[i].ypos += 50;
					else
						crush[i].ypos = 615;
					InvalidateRect(hwnd, NULL, TRUE);
					Rectangle(hdc, i * 100 + 40, crush[i].ypos, i * 100 + 120, crush[i].ypos + 95);
				}
			}
		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, pen);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, 200, 30, L"Next Block: ", 12);
		switch (whatBoard)
		{
		case 0://5x6
			for (int i = 0; i < 6; ++i)
			{
				MoveToEx(hdc, 30 + i * 100, 80, nullptr);
				LineTo(hdc, 30 + i * 100, 710);
			}
			for (int i = 0; i < 7; ++i)
			{
				MoveToEx(hdc, 30, 80 + i * 105, nullptr);
				LineTo(hdc, 530, 80 + i * 105);
			}
			for (int i = 0; i < 5; ++i)
				if (blockLocation == i)
					Rectangle(hdc, i * 100 + 40, filled5x6[i] - 100, i * 100 + 120, filled5x6[i] - 5);
			break;
		case 1://6x8
			for (int i = 0; i < 7; ++i)
			{
				MoveToEx(hdc, 35 + i * 83, 70, nullptr);
				LineTo(hdc, 35 + i * 83, 710);
			}
			for (int i = 0; i < 9; ++i)
			{
				MoveToEx(hdc, 35, 70 + i * 80, nullptr);
				LineTo(hdc, 533, 70 + i * 80);
			}
			break;
		case 2://7x9
			for (int i = 0; i < 8; ++i)
			{
				MoveToEx(hdc, 30 + i * 71, 62, nullptr);
				LineTo(hdc, 30 + i * 71, 710);
			}
			for (int i = 0; i < 10; ++i)
			{
				MoveToEx(hdc, 30, 62 + i * 72, nullptr);
				LineTo(hdc, 527, 62 + i * 72);
			}
			break;
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(pen);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
