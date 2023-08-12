#include <windows.h>		//--- 윈도우 헤더 파일
#include <tchar.h>
#include<random>
std::default_random_engine gen;
std::uniform_int_distribution<int>bad(0, 20);
std::uniform_int_distribution<int>location(0, 3);
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"2021-1 Windows Programming Midterm";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);		// 윈도우 크기 변경 가능

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
class me
{
public:
	int x = 375;
	int y = 250;
	int size = 25;
};
class badguy
{
public:
	int x;
	int y;
};
me circle;
badguy itsyou[20];
HBRUSH mycol, yourcol, erase;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	bool stop = FALSE;
	static int tmp;

	switch (iMessage)
	{
	case WM_CREATE:
		mycol = CreateSolidBrush(RGB(0, 255, 0));
		yourcol = CreateSolidBrush(RGB(0, 0, 255));
		erase = CreateSolidBrush(RGB(255, 255, 255));
		break;
	case WM_DESTROY:
		DeleteObject(mycol);
		DeleteObject(yourcol);
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			break;
		case 'T':
		case 't':
			if (stop == FALSE)
			{
				SetTimer(hWnd, 1, 2000, NULL);
				stop = TRUE;
			}
			else
			{
				KillTimer(hWnd, 1);
				stop = FALSE;
			}
			break;
		case VK_RETURN://////////////////////////////////////////////////////////////////////////////////////////총알
			break;
		case VK_UP:
			circle.y -= 25;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_DOWN:
			circle.y += 25;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_RIGHT:
			circle.x += 35;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_LEFT:
			circle.x -= 35;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			for (int i = 0; i < 20; ++i)
			{
				if (location(gen) == 0)
					itsyou[i].y -= 25;
				else if (location(gen) == 1)
					itsyou[i].y += 25;
				else if (location(gen) == 2)
					itsyou[i].x -= 35;
				else
					itsyou[i].x += 35;
			}
			break;
		}
	case WM_COMMAND:
		//if(LOWORD(wParam)==ID_40001)
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int j = 0; j < 21; ++j)
		{
			MoveToEx(hdc, 20 + 35 * j, 0, nullptr);
			LineTo(hdc, 20 + 35 * j, 500);
		}
		for (int i = 0; i < 21; ++i)
		{
			MoveToEx(hdc, 20, 25 * i, nullptr);
			LineTo(hdc, 720, 25 * i);
		}
		SelectObject(hdc, mycol);
		Rectangle(hdc, circle.x, circle.y, circle.x + circle.size, circle.y + circle.size);
		SelectObject(hdc, yourcol);
		for (int i = 0; i < 20; ++i)
		{
			int tmp = bad(gen);
			int tmp2 = location(gen);
			if (location(gen) == 0)
			{
				itsyou[i].x = 20;
				itsyou[i].y = tmp;
			}
			else if (location(gen) == 1)
			{
				itsyou[i].x = 690;
				itsyou[i].y = tmp + location(gen);
			}
			else if (location(gen) == 2)
			{
				itsyou[i].y = 0;
				itsyou[i].x = location(gen);
			}
			else
			{
				itsyou[i].y = 470;
				itsyou[i].x = location(gen);
			}
			Ellipse(hdc, itsyou[i].x, itsyou[i].y, itsyou[i].x + 30, itsyou[i].y + 30);
		}
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

