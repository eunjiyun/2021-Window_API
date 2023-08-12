#include <Windows.h>
#include<random>
#define BSIZE 10
#define onecount 80
#include"resource2.h"
std::default_random_engine dre;
std::uniform_int_distribution<int> uid{ 2, 10 };
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#include<iostream>
using namespace std;
class head
{
public:
	int xpos;
	int ypos;
	int data;
	int sturn; // 스턴범위
	int type;
	bool check = false; // 연결여부 
};
class dMinus
{
public:
	int xpos;
	int ypos;
};

float LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
BOOL InCircle(int x, int y, int x2, int y2)
{
	if (LengthPts(x, y, x2, y2) < BSIZE)
		return TRUE;
	else
		return FALSE;
}

HINSTANCE g_hlnst;
LPCTSTR IpszClass = L"windows Class Name";
LPCTSTR IpszWindowName = L"windows program 4-2";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrebInstance, LPSTR IpszCmdParm, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hlnst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(101);
	WndClass.lpszClassName = IpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW,
		0,
		0,
		850,
		850,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH board, FirstOne, Twice;
	static RECT MOVE;
	int i, t, meetnum = 0, mx, my, tailnum;
	static int num = 0, maknum = 0;
	static int meet_two[10];
	static int Ntime = 10, Mtime = 10;
	static bool selection = FALSE;
	static int whatCol = 0;

	FirstOne = CreateSolidBrush(RGB(100, 155, 255));
	board = CreateSolidBrush(RGB(255, 255, 255));
	Twice = CreateSolidBrush(RGB(255, 100, 100));

	static head nomarlOne;
	static head makeOne[onecount];
	static dMinus failed[30];
	static bool shape = FALSE;

	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &MOVE);
		nomarlOne.xpos = nomarlOne.ypos = 0;
		nomarlOne.data = 1;
		selection = FALSE;
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == 40001)
		{
			SetTimer(hwnd, 1, Ntime, NULL);
			SetTimer(hwnd, 2, 4800, NULL);//두번째 생성
			SetTimer(hwnd, 3, Mtime, NULL);// 두번째 움직이기
			SetTimer(hwnd, 4, Mtime, NULL);// 첫번쨰 원과 부딪힌거 검사 및 꼬리원으로 만들어 움직이기 
		}
		if (LOWORD(wParam) == 40002)
		{
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			KillTimer(hwnd, 4);
			i = 0;
			t = 0;
			meetnum = 0;
			mx = 0;
			my = 0;
			tailnum = 0;
			num = 0;
			maknum = 0;
			meet_two[10] = {};
			Ntime = 10;
			Mtime = 10;
			selection = FALSE;
			whatCol = 0;
			board = CreateSolidBrush(RGB(255, 255, 255));
			FirstOne = CreateSolidBrush(RGB(100, 155, 255));
			Twice = CreateSolidBrush(RGB(255, 100, 100));
			makeOne[onecount] = {};
			failed[30] = {};
			nomarlOne.xpos = nomarlOne.ypos = 0;
			nomarlOne.data = 1;
			selection = FALSE;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wParam) == 40003)
			PostQuitMessage(0);
		if (LOWORD(wParam) == 40004)
		{
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			KillTimer(hwnd, 4);
			Ntime = 1;
			Mtime = 1;
			SetTimer(hwnd, 1, Ntime, NULL);
			SetTimer(hwnd, 2, 4800, NULL);//두번째 생성
			SetTimer(hwnd, 3, Mtime, NULL);// 두번째 움직이기
			SetTimer(hwnd, 4, Mtime, NULL);// 첫번쨰 원과 부딪힌거 검사 및 꼬리원으로 만들어 움직이기 
		}
		if (LOWORD(wParam) == 40005)
		{
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			KillTimer(hwnd, 4);
			Ntime = 500;
			Mtime = 500;
			SetTimer(hwnd, 1, Ntime, NULL);
			SetTimer(hwnd, 2, 4800, NULL);//두번째 생성
			SetTimer(hwnd, 3, Mtime, NULL);// 두번째 움직이기
			SetTimer(hwnd, 4, Mtime, NULL);// 첫번쨰 원과 부딪힌거 검사 및 꼬리원으로 만들어 움직이기 
		}
		if (LOWORD(wParam) == 40006)
		{
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			KillTimer(hwnd, 4);
			Ntime = 1000;
			Mtime = 1000;
			SetTimer(hwnd, 1, Ntime, NULL);
			SetTimer(hwnd, 2, 4800, NULL);//두번째 생성
			SetTimer(hwnd, 3, Mtime, NULL);// 두번째 움직이기
			SetTimer(hwnd, 4, Mtime, NULL);// 첫번쨰 원과 부딪힌거 검사 및 꼬리원으로 만들어 움직이기 
		}
		if (LOWORD(wParam) == 40007)
			whatCol = 2;
		if (LOWORD(wParam) == 40008)
			whatCol = 0;
		if (LOWORD(wParam) == 40009)
			whatCol = 1;
		if (LOWORD(wParam) == 40010)
			shape = FALSE;
		if (LOWORD(wParam) == 40011)
			shape = TRUE;
		if (LOWORD(wParam) == 40012)///////////////////////////////////////////////////////////////////////////////////////////////////////꼬리원20
			tailnum = 20;
		if (LOWORD(wParam) == 40013)///////////////////////////////////////////////////////////////////////////////////////////////////////꼬리원25
			tailnum = 25;
		if (LOWORD(wParam) == 40014)///////////////////////////////////////////////////////////////////////////////////////////////////////꼬리원30
			tailnum = 30;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		if (whatCol == 1)
			FirstOne = CreateSolidBrush(RGB(255, 255, 0));
		else if (whatCol == 2)
			FirstOne = CreateSolidBrush(RGB(255, 100, 100));
		nomarlOne.data = 0; //1번째 원 방향 data 
		SelectObject(hdc, FirstOne);
		if (shape == FALSE)
			Ellipse(hdc, nomarlOne.xpos * 20, nomarlOne.ypos * 20, (nomarlOne.xpos + 1) * 20, (nomarlOne.ypos + 1) * 20);//1번째 원 이동출력
		else
			Rectangle(hdc, nomarlOne.xpos * 20, nomarlOne.ypos * 20, (nomarlOne.xpos + 1) * 20, (nomarlOne.ypos + 1) * 20);//1번째 원 이동출력
		//두번째 원 이동출력
		for (i = 0; i < maknum; i++)
		{
			SelectObject(hdc, Twice);
			Ellipse(hdc, makeOne[i].xpos * 20, makeOne[i].ypos * 20, (makeOne[i].xpos + 1) * 20, (makeOne[i].ypos + 1) * 20);
		}
		// 겹친거 검사 및 출력
		for (i = 0; i < maknum; i++)
		{
			for (t = i + 1; t < maknum; t++)
			{
				if (makeOne[i].xpos == makeOne[t].xpos && makeOne[i].ypos == makeOne[t].ypos)
				{
					Ellipse(hdc, (makeOne[t].xpos - 1) * 20, (makeOne[t].ypos - 1) * 20, (makeOne[t].xpos + 2) * 20, (makeOne[t].ypos + 2) * 20);
					break;
				}
			}
		}
		// 1번째 원 2번째 원 만나면 붙게 만들기 
		for (i = 0; i < maknum; i++)
		{
			if (nomarlOne.xpos == makeOne[i].xpos && nomarlOne.ypos == makeOne[i].ypos)
				makeOne[i].check = true;
		}
		for (i = 0; i < 30; i++)
		{
			for (t = 0; t < 30; t++)
			{
				RECT nomarl{ (t * 20), (i * 20), (t + 1) * 20, (i + 1) * 20 };

				SelectObject(hdc, board);
				FrameRect(hdc, &nomarl, board); //배경출력
			}
		}
		DeleteObject(board);
		DeleteObject(FirstOne);
		DeleteObject(Twice);
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		switch (wParam)
		{
		case'J':
		case'j':
			nomarlOne.ypos++;
			nomarlOne.ypos++;
			break;
		case'T':
		case't':
			nomarlOne.ypos++;
			break;

		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		for (i = 0; i < maknum; i++)
		{
			if (InCircle((makeOne[i].xpos * 20) + 10, (makeOne[i].ypos * 20) + 10, mx, my))
			{
				makeOne[i].check = false;
				break;
			}
		}
		if (InCircle((nomarlOne.xpos * 20) + 10, (nomarlOne.ypos * 20) + 10, mx, my))
			selection = TRUE;
		InvalidateRect(hwnd, NULL, TRUE);// 느려지게 하는걸로 바꿈
		// nomarlOne 범위일때 떨어지게해야함 -> 붙어있는 꼬리 해제해야함 
		break;
	case WM_LBUTTONUP:
		InvalidateRect(hwnd, NULL, TRUE);
		selection = FALSE;
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1: //오른쪽 data 로 방향구별하기 
			if (nomarlOne.ypos % 2 == 0)
			{
				if (nomarlOne.xpos == 29)
				{
					nomarlOne.ypos++;
					break;
				}
				if (nomarlOne.ypos == 29)
					nomarlOne.ypos = 0;
				nomarlOne.xpos++;
			}
			else
			{
				if (nomarlOne.xpos == 0)
				{
					nomarlOne.ypos++;
					break;
				}
				if (nomarlOne.ypos == 29)
					nomarlOne.ypos = 0;
				nomarlOne.xpos--;
			} break;// 다른방향 다 만들기 (case로 방향 한번 저장하는 코드 만들어야함 ) 

		case 2: // 새로만들어지는 원
			if (num == onecount || maknum == onecount)
				break;
			makeOne[num].xpos = rand() % 20 - 5;//
			makeOne[num].ypos = rand() % 20 + 5; // 범위를 10~30으로
			makeOne[num].sturn = rand() % 4;  // 방향 
			makeOne[num].data = 1; // 도는거, 직선인거 구분 
			makeOne[num].type = 0; // 2번쨰 원 
			makeOne[num].data = false;
			if (num % 2 == 0)
				makeOne[num].data = 1;
			else
				makeOne[num].data = 0;
			num++;
			maknum++;
			break;
		case 3:
			tailnum = 1;
			for (i = 0; i < maknum; i++)
			{
				if (makeOne[i].check == false)
				{ // 붙어있는지 검사 
					switch (makeOne[i].data)
					{
					case 1://빙글빙글
						if (makeOne[i].sturn < 5)
						{
							makeOne[i].xpos++;
							makeOne[i].sturn++;
						}
						else if (makeOne[i].sturn >= 5 && makeOne[i].sturn < 12)
						{
							makeOne[i].ypos--;
							makeOne[i].sturn++;
						}
						else if (makeOne[i].sturn >= 12 && makeOne[i].sturn < 17)
						{
							makeOne[i].xpos--;
							makeOne[i].sturn++;
						}
						else if (makeOne[i].sturn >= 17 && makeOne[i].sturn < 24)
						{
							makeOne[i].sturn++;
							makeOne[i].ypos++;
						}
						else if (makeOne[i].sturn > 23)
							makeOne[i].sturn = 0;
						break;
					case 0://직선방향 
						switch (makeOne[i].sturn)
						{
						case 0:
							if (makeOne[i].xpos == 29)
							{
								makeOne[i].sturn = rand() % 4;
								break;
							}
							makeOne[i].xpos++;
							break;
						case 1:
							if (makeOne[i].ypos == 29)
							{
								makeOne[i].sturn = rand() % 4;
								break;
							}
							makeOne[i].ypos++;
							break;
						case 2:
							if (makeOne[i].xpos == 0)
							{
								makeOne[i].sturn = rand() % 4;
								break;
							}
							makeOne[i].xpos--;
							break;
						case 3:
							if (makeOne[i].ypos == 0) {
								makeOne[i].sturn = rand() % 4;
								break;
							}
							makeOne[i].ypos--;
							break;
						}
						break;
					}
				}
				else if (makeOne[i].check == true)
				{
					makeOne[i].type = tailnum;
					tailnum++;

					if (nomarlOne.ypos % 2 == 0)
					{
						if (makeOne[i].xpos <= 3 && makeOne[i].xpos > 0)
							makeOne[i].xpos--;

						if (makeOne[i].xpos == 0 && nomarlOne.xpos == makeOne[i].type - 1)
							makeOne[i].ypos++;

						if (nomarlOne.xpos >= makeOne[i].type && nomarlOne.xpos <= 29)
						{
							makeOne[i].xpos = nomarlOne.xpos - makeOne[i].type;
							makeOne[i].ypos = nomarlOne.ypos;
						}
					}
					else
					{
						if (makeOne[i].xpos >= 27 && makeOne[i].xpos < 29)
							makeOne[i].xpos++;

						if (makeOne[i].xpos == 29 && nomarlOne.xpos == 29 - makeOne[i].type)
							makeOne[i].ypos++;

						if (nomarlOne.xpos < (29 - makeOne[i].type) && nomarlOne.xpos >= 0)
						{
							makeOne[i].xpos = nomarlOne.xpos + makeOne[i].type;
							makeOne[i].ypos = nomarlOne.ypos;
						}
					}
				}

			} break;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	}
	DeleteObject(Twice);
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}