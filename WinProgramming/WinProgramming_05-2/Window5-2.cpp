#include<Windows.h>
#include<TCHAR.H>
#include<iostream>
#include<random>
#include"resource.h"
#pragma comment(lib, "msimg32.lib")
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
using namespace std;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int>suddenly(0, 8);

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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");

	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("windows program 5-4"),
		WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_HSCROLL | WS_VSCROLL,
		0,
		0,
		1280,//1121 649
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
class charac
{
public:
	int xpos, ypos;
	int hor, ver;
};
HDC hdc, memdc;
PAINTSTRUCT ps;
charac cubi[2] = { {200,300,210,180},{600,300,210,180} };
int howMany = 1;

void animation(int xPos, int yPos, HDC hdc, HDC memdc)
{
	HDC memdc2;
	HBITMAP runBit[10], hBit, hBit2, oldBit, oldBit2, mask[10];
	static int count;
	int i;
	++count;
	count %= 10;
	for (i = 0; i < 10; ++i)
		runBit[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1 + i));
	for (i = 0; i < 10; ++i)
		mask[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP11 + i));
	hBit2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP21));

	memdc = CreateCompatibleDC(hdc);
	memdc2 = CreateCompatibleDC(memdc);

	hBit = CreateCompatibleBitmap(hdc, 1280, 800);
	oldBit = (HBITMAP)SelectObject(memdc, hBit);
	oldBit2 = (HBITMAP)SelectObject(memdc2, hBit2);

	StretchBlt(memdc, 0, 0, 1280, 800, memdc2, 0, 0, 900, 675, SRCCOPY);//900 675

	for (i = 0; i < howMany; ++i)
	{

		SelectObject(memdc2, mask[count]);
		StretchBlt(memdc, cubi[i].xpos, cubi[i].ypos, cubi[0].hor, cubi[0].ver, memdc2, 0, 0, 35, 30, SRCAND);
		SelectObject(memdc2, runBit[count]);
		StretchBlt(memdc, cubi[i].xpos, cubi[i].ypos, cubi[0].hor, cubi[0].ver, memdc2, 0, 0, 35, 30, SRCPAINT);


		/*SelectObject(memdc2, runBit[count]);
		TransparentBlt(memdc, cubi[i].xpos, cubi[i].ypos, cubi[0].hor, cubi[0].ver, memdc2, 0, 0, 35, 30, RGB(255,255,255));*/
	}

	StretchBlt(hdc, 0, 0, 1280, 800, memdc, 0, 0, 900, 675, SRCCOPY);//900 675

	SelectObject(memdc, oldBit);
	SelectObject(memdc2, oldBit2);
	for (i = 0; i < 10; ++i)
	{
		DeleteObject(runBit[i]);
		DeleteObject(mask[i]);
	}
	DeleteDC(memdc2);
	DeleteObject(hBit2);
	DeleteObject(hBit);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	static RECT rectView;
	static bool click = FALSE;
	static int expansion = 0;
	static int collapse = 0;
	static int mx, my;

	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		SetTimer(hwnd, 1, 100, NULL);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP://이동ㅋ
			for (int i = 0; i < 2; ++i)
				cubi[i].ypos -= 10;
			InvalidateRect(hwnd, NULL, false);
			break;
		case VK_DOWN:
			for (int i = 0; i < 2; ++i)
				cubi[i].ypos += 10;
			InvalidateRect(hwnd, NULL, false);
			break;
		case VK_RIGHT:
			for (int i = 0; i < 2; ++i)
				cubi[i].xpos += 10;
			InvalidateRect(hwnd, NULL, false);
			break;
		case VK_LEFT:
			for (int i = 0; i < 2; ++i)
				cubi[i].xpos -= 10;
			InvalidateRect(hwnd, NULL, false);
			break;
		case 0x4A://j 스트라이프가 점프
			for (int i = 0; i < 2; ++i)
				cubi[i].ypos -= 200;
			InvalidateRect(hwnd, NULL, false);
			break;
		case 0x45://e 스트라이프 확대 후 복구
			SetTimer(hwnd, 2, 1000, NULL);
			break;
		case 0x53://s 스트라이프 축소 후 복구
			SetTimer(hwnd, 3, 1000, NULL);
			break;
		case 0x54://t 트윈 생성
			cubi[1].xpos = cubi[0].xpos + 400;
			cubi[1].ypos = cubi[0].ypos;
			++howMany;
			break;
		case 0x51://q 프로그램 종료
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		cout << "mx: " << mx << endl;
		cout << "my: " << my << endl;
		cout << cubi[0].xpos << endl;
		cout << cubi[0].xpos + 210 << endl;
		cout << cubi[0].ypos << endl;
		cout << cubi[0].ypos + 180 << endl;
		if (mx > cubi[0].xpos && mx<cubi[0].xpos + 210 && my>cubi[0].ypos && my < cubi[0].ypos + 180)
		{
			if (cubi[0].ypos + 90 > 400)
			{
				if (cubi[0].xpos + 105 > 640)
				{
					cubi[0].xpos -= 200;
					cubi[1].xpos -= 200;
				}
				else
				{
					cubi[0].xpos += 200;
					cubi[1].xpos += 200;
				}
				cubi[0].ypos -= 100;
				cubi[1].ypos -= 100;
			}
			else
			{
				if (cubi[0].xpos + 105 > 640)
				{
					cubi[0].xpos -= 200;
					cubi[1].xpos -= 200;
				}
				else
				{
					cubi[0].xpos += 200;
					cubi[1].xpos += 200;
				}
				cubi[0].ypos += 100;
				cubi[1].ypos += 100;
			}
		}
		else if (mx > cubi[1].xpos && mx<cubi[1].xpos + 210 && my>cubi[1].ypos && my < cubi[1].ypos + 180)
		{

			if (cubi[1].ypos + 90 > 400)
			{
				if (cubi[1].xpos + 105 > 640)
					cubi[1].xpos -= 200;
				else
					cubi[1].xpos += 200;
				cubi[1].ypos -= 100;
			}
			else
			{
				if (cubi[1].xpos + 105 > 640)
					cubi[1].xpos -= 200;
				else
					cubi[1].xpos += 200;
				cubi[1].ypos += 100;
			}
		}
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			InvalidateRect(hwnd, NULL, false);
			break;
		case 2:
			if (expansion < 4)
			{
				for (int i = 0; i < 2; ++i)
				{
					if (cubi[i].hor == 210 && cubi[i].ver == 180)
					{
						cubi[i].hor += 140;
						cubi[i].ver += 120;
					}
					else
					{
						cubi[i].hor -= 140;
						cubi[i].ver -= 120;
					}
					++expansion;
					InvalidateRect(hwnd, NULL, false);
				}
			}
			else
			{
				expansion = 0;
				KillTimer(hwnd, 2);
			}
			break;
		case 3:
			if (collapse < 4)
			{
				for (int i = 0; i < 2; ++i)
				{
					if (cubi[i].hor == 210 && cubi[i].ver == 180)
					{
						cubi[i].hor -= 140;
						cubi[i].ver -= 120;
					}
					else
					{
						cubi[i].hor += 140;
						cubi[i].ver += 120;
					}
					++collapse;
					InvalidateRect(hwnd, NULL, false);
				}
			}
			else
			{
				collapse = 0;
				KillTimer(hwnd, 3);
			}
			break;
		default:
			break;
		}
		return 0;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0; i < howMany; ++i)
			animation(cubi[i].xpos, cubi[i].ypos, hdc, memdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		DeleteDC(memdc);
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
