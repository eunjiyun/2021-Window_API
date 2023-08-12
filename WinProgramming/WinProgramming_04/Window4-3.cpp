#include<Windows.h>
#include<TCHAR.H>
#include<random>
#include "resource4-3.h"
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#include<iostream>
using namespace std;

#define MAXSIZE 100
std::default_random_engine gen;
std::uniform_int_distribution<int> col(0, 255);
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
class monster
{
public:
	int leftX, topY, rightX, bottomY;
	bool lazy = FALSE;
	bool shape = FALSE;
	COLORREF col;
};

HBRUSH orange, hbrush2, oldpen;
HPEN off, soli, dott;
monster wantToSee[30];

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("windows program 4-3"),
		WS_SYSMENU,
		0,
		0,
		1200,
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
//^V^
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int leftX, topY, rightX, bottomY, oldRightX, oldBottomY;
	static int mx, my, moveMx, moveMy, rightXlen, rightYlen, leftXlen, leftYlen;
	static bool lDrag = FALSE;
	static bool rDrag = FALSE;
	static int count = -1;
	static int select = -1;

	switch (iMsg)
	{
	case WM_CREATE:
		off = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		soli = CreatePen(PS_SOLID, 5, RGB(255, 127, 0));
		dott = CreatePen(PS_DASH, 1, RGB(255, 127, 0));
		break;
	case WM_COMMAND:
		hdc = GetDC(hwnd);
		if (LOWORD(wParam) == ID_GRID_40001)//1 ½Ç¼±
			wantToSee[count + 1].shape = FALSE;
		else if (LOWORD(wParam) == ID_GRID_40002)//2 Á¡¼±
			wantToSee[count + 1].shape = TRUE;
		else if (LOWORD(wParam) == ID_COLOR_RED)//»ö±ò 1
			wantToSee[count + 1].col = RGB(255, 0, 0);
		else if (LOWORD(wParam) == ID_COLOR_BLUE)//»ö±ò2
			wantToSee[count + 1].col = RGB(0, 0, 255);
		else if (LOWORD(wParam) == ID_COLOR_GREEN)//»ö±ò 3
			wantToSee[count + 1].col = RGB(0, 255, 0);
		else if (LOWORD(wParam) == ID_COLOR_YELLOW)//»ö±ò 4
			wantToSee[count + 1].col = RGB(255, 255, 0);
		else if (LOWORD(wParam) == ID_COLOR_PURPLE)//»ö±ò 5
			wantToSee[count + 1].col = RGB(255, 0, 255);
		else if (LOWORD(wParam) == ID_COLOR_ORANGE)//»ö±ò 6
			wantToSee[count + 1].col = RGB(0, 255, 255);
		else if (LOWORD(wParam) == ID_BORDER_ON)//Å×µÎ¸® ÀÖ´Â µµÇü
			wantToSee[count + 1].lazy = TRUE;
		else if (LOWORD(wParam) == ID_BORDER_OFF)//Å×µÎ¸® ¾ø´Â µµÇü
			wantToSee[count + 1].lazy = FALSE;
		ReleaseDC(hwnd, hdc);
		break;
	case WM_LBUTTONDOWN:
		++count;
		oldRightX = wantToSee[count].leftX = LOWORD(lParam);
		oldBottomY = wantToSee[count].topY = HIWORD(lParam);
		lDrag = TRUE;
		break;
	case WM_LBUTTONUP:
		lDrag = FALSE;

		for (int i = 0; i < 25; ++i)
			if (50 + 40 * i < wantToSee[count].leftX && wantToSee[count].leftX < 50 + 40 * (i + 1))
				wantToSee[count].leftX = 50 + 40 * i;
		for (int i = 0; i < 26; ++i)
			if (50 + 40 * i < wantToSee[count].rightX && wantToSee[count].rightX < 50 + 40 * (i + 1))
				wantToSee[count].rightX = 50 + 40 * (i + 1);
		for (int i = 0; i < 26; ++i)
			if (25 * i < wantToSee[count].topY && wantToSee[count].topY < 25 * (i + 1))
				wantToSee[count].topY = 25 * i;
		for (int i = 0; i < 26; ++i)
			if (25 * i < wantToSee[count].bottomY && wantToSee[count].bottomY < 25 * (i + 1))
				wantToSee[count].bottomY = 25 * (i + 1);
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		if (lDrag)
		{
			SetROP2(hdc, R2_XORPEN);
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
			wantToSee[count].rightX = LOWORD(lParam);
			wantToSee[count].bottomY = HIWORD(lParam);

			Rectangle(hdc, wantToSee[count].leftX, wantToSee[count].topY, oldRightX, oldBottomY);
			Rectangle(hdc, wantToSee[count].leftX, wantToSee[count].topY, wantToSee[count].rightX, wantToSee[count].bottomY);

			oldRightX = wantToSee[count].rightX;
			oldBottomY = wantToSee[count].bottomY;
		}
		else if (rDrag)
		{
			moveMx = LOWORD(lParam);
			moveMy = HIWORD(lParam);

			oldRightX = wantToSee[select].rightX;
			oldBottomY = wantToSee[select].bottomY;

			wantToSee[select].leftX = moveMx - leftXlen;
			wantToSee[select].topY = moveMy - leftYlen;
			wantToSee[select].rightX = moveMx + rightXlen;
			wantToSee[select].bottomY = moveMy + rightYlen;

			InvalidateRect(hwnd, NULL, TRUE);
		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		for (int i = 0; i <= count; ++i)
		{
			if (wantToSee[i].leftX <= mx && mx <= wantToSee[i].rightX && wantToSee[i].topY <= my && my <= wantToSee[i].bottomY)
			{
				rDrag = TRUE;
				leftXlen = mx - wantToSee[i].leftX;
				leftYlen = my - wantToSee[i].topY;
				rightXlen = wantToSee[i].rightX - mx;
				rightYlen = wantToSee[i].bottomY - my;
				select = i;
				break;
			}
		}
		break;
	case WM_RBUTTONUP:
		rDrag = FALSE;

		for (int i = 0; i < 25; ++i)
			if (50 + 40 * i < wantToSee[select].leftX && wantToSee[select].leftX < 50 + 40 * (i + 1))
				wantToSee[select].leftX = 50 + 40 * i;
		for (int i = 0; i < 26; ++i)
			if (50 + 40 * i < wantToSee[select].rightX && wantToSee[select].rightX < 50 + 40 * (i + 1))
				wantToSee[select].rightX = 50 + 40 * i;
		for (int i = 0; i < 26; ++i)
			if (25 * i < wantToSee[select].topY && wantToSee[select].topY < 25 * (i + 1))
				wantToSee[select].topY = 25 * i;
		for (int i = 0; i < 26; ++i)
			if (25 * i < wantToSee[select].bottomY && wantToSee[select].bottomY < 25 * (i + 1))
				wantToSee[select].bottomY = 25 * i;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0; i < 26; ++i)
		{
			MoveToEx(hdc, 50 + 40 * i, 0, NULL);
			LineTo(hdc, 50 + 40 * i, 625);
		}
		for (int i = 0; i < 26; ++i)
		{
			MoveToEx(hdc, 50, 25 * i, NULL);
			LineTo(hdc, 1050, 25 * i);
		}
		for (int i = 0; i <= count; ++i)
		{
			if (wantToSee[i].lazy == TRUE)
			{
				if (wantToSee[i].shape == TRUE)
					SelectObject(hdc, dott);
				else
					SelectObject(hdc, soli);
			}
			else
				SelectObject(hdc, off);
			orange = CreateSolidBrush(wantToSee[i].col);
			oldpen = (HBRUSH)SelectObject(hdc, orange);
			Rectangle(hdc, wantToSee[i].leftX, wantToSee[i].topY, wantToSee[i].rightX, wantToSee[i].bottomY);
			SelectObject(hdc, oldpen);
			DeleteObject(orange);
		}
		for (int i = 0; i <= count; ++i)
		{
			for (int j = 0; j <= count; ++j)
			{
				hbrush2 = CreateSolidBrush(wantToSee[i].col + wantToSee[j].col);
				oldpen = (HBRUSH)SelectObject(hdc, hbrush2);

				if (wantToSee[i].leftX < wantToSee[j].rightX && wantToSee[j].rightX < wantToSee[i].rightX)//iÁÂ¿ì
				{
					if (wantToSee[j].topY <= wantToSee[i].topY && wantToSee[i].topY < wantToSee[j].bottomY)
					{
						if (wantToSee[j].bottomY <= wantToSee[i].bottomY)
						{
							if (wantToSee[j].leftX <= wantToSee[i].leftX)
								Rectangle(hdc, wantToSee[i].leftX, wantToSee[i].topY, wantToSee[j].rightX, wantToSee[j].bottomY);
							else
								Rectangle(hdc, wantToSee[j].leftX, wantToSee[i].topY, wantToSee[j].rightX, wantToSee[j].bottomY);
						}
						else
						{
							if (wantToSee[j].leftX <= wantToSee[i].leftX)
								Rectangle(hdc, wantToSee[i].leftX, wantToSee[i].topY, wantToSee[j].rightX, wantToSee[i].bottomY);
							else
								Rectangle(hdc, wantToSee[j].leftX, wantToSee[i].topY, wantToSee[j].rightX, wantToSee[i].bottomY);
						}
					}
					else if (wantToSee[i].topY <= wantToSee[j].topY && wantToSee[j].topY < wantToSee[i].bottomY)
					{
						if (wantToSee[j].bottomY <= wantToSee[i].bottomY)
						{
							if (wantToSee[i].leftX <= wantToSee[j].leftX)
								Rectangle(hdc, wantToSee[j].leftX, wantToSee[j].topY, wantToSee[j].rightX, wantToSee[j].bottomY);
							else
								Rectangle(hdc, wantToSee[i].leftX, wantToSee[j].topY, wantToSee[j].rightX, wantToSee[j].bottomY);
						}
						else
						{
							if (wantToSee[i].leftX <= wantToSee[j].leftX)
								Rectangle(hdc, wantToSee[j].leftX, wantToSee[j].topY, wantToSee[j].rightX, wantToSee[i].bottomY);
							else
								Rectangle(hdc, wantToSee[i].leftX, wantToSee[j].topY, wantToSee[j].rightX, wantToSee[i].bottomY);
						}
					}
				}
				SelectObject(hdc, oldpen);
				DeleteObject(hbrush2);
			}
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == 0x51)
			PostQuitMessage(0);
		break;
	case WM_DESTROY:
		DeleteObject(off);
		DeleteObject(soli);
		DeleteObject(dott);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

