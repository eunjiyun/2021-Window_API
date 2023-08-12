#include<Windows.h>
#include<TCHAR.H>
#include<iostream>
#include<random>
#include<cstdlib> 
#include"resource.h"
#pragma comment(lib, "msimg32.lib")
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
using namespace std;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int>direction(0, 3);
class charac
{
public:
	int xpos, ypos;
	int hor, ver;
};
class bullet
{
public:
	int xpos, ypos;
	bool bang;
};
HINSTANCE hInst;
HWND hwnd;
HDC hdc, memdc;
PAINTSTRUCT ps;
charac youCantGo = { 400,400,0,0 };
charac youCantGo2 = { 500,0,0,0 };
charac youCantGo3 = { 0,200,0,0 };
charac cubi = { 0,0,0,0 };
charac bad = { youCantGo.xpos,youCantGo.ypos,0,0 };
bullet ouch[50];
HBRUSH hpen;
int bullCount = -1;
bool die = FALSE;
int gone = 0;
int crush3 = 0;
int crush2[4] = {};
int crush[6] = {};

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
void animation(HDC hdc, HDC memdc);

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
		_T("windows program 5-5"),
		WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_HSCROLL | WS_VSCROLL,
		0,
		0,
		1280,
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	static RECT rectView;
	static int myDirec = direction(gen);
	static int yourDirec = direction(gen);
	static bool up = FALSE;
	static bool down = FALSE;
	static bool left = FALSE;
	static bool right = FALSE;
	static int bullLocation = -1;

	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		SetTimer(hwnd, 1, 100, NULL);
		SetTimer(hwnd, 2, 50, NULL);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP://이동ㅋ
			up = TRUE;
			myDirec = 0;
			cubi.ypos -= 10;
			InvalidateRect(hwnd, NULL, false);
			break;
		case VK_DOWN:
			down = TRUE;
			myDirec = 1;
			cubi.ypos += 10;
			InvalidateRect(hwnd, NULL, false);
			break;
		case VK_LEFT:
			left = TRUE;
			myDirec = 2;
			cubi.xpos -= 10;
			InvalidateRect(hwnd, NULL, false);
			break;
		case VK_RIGHT:
			right = TRUE;
			myDirec = 3;
			cubi.xpos += 10;
			InvalidateRect(hwnd, NULL, false);
			break;
		case VK_SPACE://주인공이 총을 쏘는데 몬스터가 맞으면 죽어요
			SetTimer(hwnd, 3, 5, NULL);
			++bullCount;
			break;
		case 0x51://q 프로그램 종료
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1://커비
			if (cubi.ypos - youCantGo3.ypos > -100 && cubi.ypos - youCantGo3.ypos < 100)//3번 블록 1
			{
				if (cubi.xpos == youCantGo3.xpos + 100)
				{
					if (left == TRUE)
					{
						cubi.xpos += 10;
						left = FALSE;
					}
					myDirec = 4;
				}
				else if (cubi.xpos + 100 == youCantGo3.xpos)
				{
					if (right == TRUE)
					{
						cubi.xpos -= 10;
						right = FALSE;
					}
					myDirec = 4;
				}
			}
			else if (cubi.xpos - youCantGo3.xpos > -100 && cubi.xpos - youCantGo3.xpos < 100)
			{
				if (cubi.ypos == youCantGo3.ypos + 100)
				{
					if (up == TRUE)
					{
						cubi.ypos += 10;
						up = FALSE;
					}
					myDirec = 4;
				}
				else if (cubi.ypos + 100 == youCantGo3.ypos)
				{
					if (down == TRUE)
					{
						cubi.ypos -= 10;
						down = FALSE;
					}
					myDirec = 4;
				}
			}

			if (cubi.ypos - youCantGo2.ypos < 200 && cubi.ypos - youCantGo2.ypos >= 0 || youCantGo2.ypos - cubi.ypos < 100 && youCantGo2.ypos - cubi.ypos>0)//2번 블록 4
			{
				if (cubi.xpos == youCantGo2.xpos + 200)
				{
					if (left == TRUE)
					{
						cubi.xpos += 10;
						left = FALSE;
					}
					myDirec = 4;
				}
				else if (cubi.xpos + 100 == youCantGo2.xpos)
				{
					if (right == TRUE)
					{
						cubi.xpos -= 10;
						right = FALSE;
					}
					myDirec = 4;
				}
			}
			else if (cubi.xpos - youCantGo2.xpos < 200 && cubi.xpos - youCantGo2.xpos >0 || youCantGo2.xpos - cubi.xpos < 100 && youCantGo2.xpos - cubi.xpos>0)
			{
				if (cubi.ypos == youCantGo2.ypos + 200)
				{
					if (up == TRUE)
					{
						cubi.ypos += 10;
						up = FALSE;
					}
					myDirec = 4;
				}
				else if (cubi.ypos + 100 == youCantGo2.ypos)
				{
					if (down == TRUE)
					{
						cubi.ypos -= 10;
						down = FALSE;
					}
					myDirec = 4;
				}
			}

			if (cubi.ypos - youCantGo.ypos < 200 && cubi.ypos - youCantGo.ypos >= 0 || youCantGo.ypos - cubi.ypos < 100 && youCantGo.ypos - cubi.ypos>0)//1번 블록 6
			{
				if (cubi.xpos == youCantGo.xpos + 300)
				{
					if (left == TRUE)
					{
						cubi.xpos += 10;
						left = FALSE;
					}
					myDirec = 4;
				}
				else if (cubi.xpos + 100 == youCantGo.xpos)
				{
					if (right == TRUE)
					{
						cubi.xpos -= 10;
						right = FALSE;
					}
					myDirec = 4;
				}
			}
			else if (cubi.xpos - youCantGo.xpos < 300 && cubi.xpos - youCantGo.xpos >= 0 || youCantGo.xpos - cubi.xpos < 100 && youCantGo.xpos - cubi.xpos>0)
			{
				if (cubi.ypos == youCantGo.ypos + 200)
				{
					if (up == TRUE)
					{
						cubi.ypos += 10;
						up = FALSE;
					}
					myDirec = 4;
				}
				else if (cubi.ypos + 100 == youCantGo.ypos)
				{
					if (down == TRUE)
					{
						cubi.ypos -= 10;
						down = FALSE;
					}
					myDirec = 4;
				}
			}

			if (cubi.xpos < rectView.left)
			{

				myDirec = 3;
			}
			else if (cubi.xpos + 450 > rectView.right)
			{
				myDirec = 2;
			}
			else if (cubi.ypos + 200 > rectView.bottom)
			{
				myDirec = 0;
			}
			else if (cubi.ypos < rectView.top)
			{
				myDirec = 1;
			}
			switch (myDirec)
			{
			case 0:
				cubi.ypos -= 10;
				break;
			case 1:
				cubi.ypos += 10;
				break;
			case 2:
				cubi.xpos -= 10;
				break;
			case 3:
				cubi.xpos += 10;
				break;
			}
			InvalidateRect(hwnd, NULL, false);
			break;
		case 2://팬텀
			if (bad.xpos < rectView.left)
			{
				yourDirec = 3;
			}
			else if (bad.xpos + 650 > rectView.right)
			{
				yourDirec = 2;
			}
			else if (bad.ypos + 200 > rectView.bottom)
			{
				yourDirec = 0;
			}
			else if (bad.ypos <= rectView.top)
			{
				yourDirec = 1;
			}
			switch (yourDirec)
			{
			case 0:
				bad.ypos -= 10;
				break;
			case 1:
				bad.ypos += 10;
				break;
			case 2:
				bad.xpos -= 10;
				break;
			case 3:
				bad.xpos += 10;
				break;
			}
			InvalidateRect(hwnd, NULL, false);
			break;
		case 3://총알
			for (int i = 0; i <= bullCount; ++i)
			{
				if (ouch[bullCount].bang == FALSE)
				{
					if (abs(cubi.xpos - bad.xpos) > abs(cubi.ypos - bad.ypos))
					{
						if (cubi.xpos >= bad.xpos)
							bullLocation = 2;
						else
							bullLocation = 3;
					}
					else
					{
						if (cubi.ypos >= bad.ypos)
							bullLocation = 0;
						else
							bullLocation = 1;
					}
					ouch[bullCount].xpos = cubi.xpos + 50;
					ouch[bullCount].ypos = cubi.ypos + 50;
					ouch[bullCount].bang = TRUE;
				}

				switch (bullLocation)
				{
				case 0:
					ouch[bullCount].ypos -= 5;
					break;
				case 1:
					ouch[bullCount].ypos += 5;
					break;
				case 2:
					ouch[bullCount].xpos -= 5;
					break;
				case 3:
					ouch[bullCount].xpos += 5;
					break;
				}
				InvalidateRect(hwnd, NULL, false);
			}
			break;
		default:
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		animation(hdc, memdc);
		/*for (int i = 0; i <= bullCount; ++i)
		{*/
		if (ouch[bullCount].bang == TRUE)
		{
			hpen = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hpen);

			Ellipse(hdc, ouch[bullCount].xpos, ouch[bullCount].ypos, ouch[bullCount].xpos + 10, ouch[bullCount].ypos + 10);

		}
		//}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		DeleteDC(memdc);
		KillTimer(hwnd, 1);
		KillTimer(hwnd, 2);
		DeleteObject(hpen);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
void animation(HDC hdc, HDC memdc)
{
	HDC memdc2;
	HBITMAP  main[20], badguy[9], badKill[9], block, hBit, hBit2, oldBit, oldBit2;
	static int countCubi, countBad, countBadKill;
	int i;
	++countCubi;
	countCubi %= 20;
	++countBad;
	countBad %= 9;
	++countBadKill;
	countBadKill %= 9;
	for (i = 0; i < 20; ++i)
		main[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP20 + i));
	for (i = 0; i < 9; ++i)
		badguy[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2 + i));
	for (i = 0; i < 9; ++i)
		badKill[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10 + i));

	hBit2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP40));
	block = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));

	memdc = CreateCompatibleDC(hdc);
	memdc2 = CreateCompatibleDC(memdc);

	hBit = CreateCompatibleBitmap(hdc, 1280, 800);
	oldBit = (HBITMAP)SelectObject(memdc, hBit);
	oldBit2 = (HBITMAP)SelectObject(memdc2, hBit2);

	StretchBlt(memdc, 0, 0, 1280, 800, memdc2, 0, 0, 900, 675, SRCCOPY);//900 675


	SelectObject(memdc2, main[countCubi]);
	//StretchBlt(memdc, cubi.xpos, cubi.ypos, 100, 100, memdc2, 0, 0, 55, 65, SRCCOPY);
	TransparentBlt(memdc, cubi.xpos, cubi.ypos, 100, 100, memdc2, 0, 0, 48, 61, RGB(192, 192, 192));


	if (ouch[bullCount].ypos >= youCantGo3.ypos && ouch[bullCount].ypos <= youCantGo3.ypos + 90 && (ouch[bullCount].xpos == youCantGo3.xpos || ouch[bullCount].xpos == youCantGo3.xpos + 90))
	{
		++crush3;
	}
	else if (ouch[bullCount].xpos >= youCantGo3.xpos && ouch[bullCount].xpos <= youCantGo3.xpos + 90 && (ouch[bullCount].ypos == youCantGo3.ypos || ouch[bullCount].ypos == youCantGo3.ypos + 90))
	{
		++crush3;
	}

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (ouch[bullCount].ypos >= youCantGo2.ypos + i * 100 && ouch[bullCount].ypos <= youCantGo2.ypos + 90 + i * 100 && (ouch[bullCount].xpos == youCantGo2.xpos + j * 100 || ouch[bullCount].xpos + j * 100 == youCantGo2.xpos + 90 + j * 100))
			{
				++crush2[i * 2 + j];
			}
			else if (ouch[bullCount].xpos >= youCantGo2.xpos + j * 100 && ouch[bullCount].xpos <= youCantGo2.xpos + 90 + j * 100 && (ouch[bullCount].ypos == youCantGo2.ypos + i * 100 || ouch[bullCount].ypos == youCantGo2.ypos + 90 + i * 100))
			{
				++crush2[i * 2 + j];
			}
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (ouch[bullCount].ypos >= youCantGo.ypos + i * 100 && ouch[bullCount].ypos <= youCantGo.ypos + 90 + i * 100 && (ouch[bullCount].xpos == youCantGo.xpos + j * 100 || ouch[bullCount].xpos == youCantGo.xpos + 90 + j * 100))
			{
				++crush[i * 2 + j];
			}
			else if (ouch[bullCount].xpos >= youCantGo.xpos + j * 100 && ouch[bullCount].xpos <= youCantGo.xpos + 90 + j * 100 && (ouch[bullCount].ypos == youCantGo.ypos + i * 100 || ouch[bullCount].ypos == youCantGo.ypos + 90 + i * 100))
			{
				++crush[i * 2 + j];
			}
		}
	}

	if (ouch[bullCount].ypos >= bad.ypos && ouch[bullCount].ypos <= bad.ypos + 90 && (ouch[bullCount].xpos == bad.xpos || ouch[bullCount].xpos == bad.xpos + 290))
	{
		SelectObject(memdc2, badKill[countBad]);
		die = TRUE;
	}
	else if (ouch[bullCount].xpos >= bad.xpos && ouch[bullCount].xpos <= bad.xpos + 290 && (ouch[bullCount].ypos == bad.ypos || ouch[bullCount].ypos == bad.ypos + 90))
	{
		SelectObject(memdc2, badKill[countBad]);
		die = TRUE;
	}
	else
	{
		if (die == FALSE)
			SelectObject(memdc2, badguy[countBad]);
		else
			SelectObject(memdc2, badKill[countBad]);
	}

	if (gone != 10 && gone > -1)
	{
		for (i = 0; i < 3; ++i)
			//StretchBlt(memdc, bad.xpos + i * 100, bad.ypos, 100, 100, memdc2, 0, 0, 60, 50, SRCCOPY);
			TransparentBlt(memdc, bad.xpos + i * 100, bad.ypos, 100, 100, memdc2, 0, 0, 51, 41, RGB(192, 192, 192));
	}

	if (die == TRUE)
	{
		if (gone != 10 && gone != -1)
			++gone;
		else
			gone = -1;
	}

	SelectObject(memdc2, block);


	for (i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (crush[i * 2 + j] < 4)
				TransparentBlt(memdc, youCantGo.xpos + 100 * j, youCantGo.ypos + 105 * i, 100, 100, memdc2, 0, 0, 110, 105, RGB(128, 128, 128));
		}
	}

	for (i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (crush2[i * 2 + j] < 4)
				TransparentBlt(memdc, youCantGo2.xpos + 100 * j, youCantGo2.ypos + 105 * i, 100, 100, memdc2, 0, 0, 110, 105, RGB(128, 128, 128));
		}
	}

	if (crush3 < 4)
		TransparentBlt(memdc, youCantGo3.xpos, youCantGo3.ypos, 100, 100, memdc2, 0, 0, 110, 105, RGB(128, 128, 128));

	StretchBlt(hdc, 0, 0, 1280, 800, memdc, 0, 0, 900, 675, SRCCOPY);//900 675

	SelectObject(memdc, oldBit);
	SelectObject(memdc2, oldBit2);
	for (i = 0; i < 20; ++i)
		DeleteObject(main[i]);
	for (i = 0; i < 9; ++i)
		DeleteObject(badguy[i]);
	for (i = 0; i < 9; ++i)
		DeleteObject(badKill[i]);

	DeleteObject(block);
	DeleteObject(hBit2);

	DeleteDC(memdc2);
	DeleteObject(hBit);
}

