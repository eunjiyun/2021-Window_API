#include<random>
#include <Windows.h>
#define MAX 100
using namespace std;
default_random_engine gen;
uniform_int_distribution<int> clo{ 1, 10 };
uniform_int_distribution<int> uy{ 0, 255 };

HINSTANCE hinst;
LPCTSTR IpszClass = L"windows Class Name";
LPCTSTR IpszWindowName = L"windows program 3-3";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrebInstance, LPSTR IpszCmdParm, int nCmdShow)
{
	HWND hwnd;
	MSG message;
	WNDCLASSEX wndclass;
	hinst = hInstance;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = (WNDPROC)WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszMenuName = NULL; wndclass.lpszClassName = IpszClass;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	hwnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 800, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}
struct eye
{
	HBRUSH colorful;
	int ypos;
	int xpos;
	int clock;
	bool flag;
};
struct pol4
{
	int ypos;
	int xpos;
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int xr, yr, Xor, Yor, xer, yer;
	static int xc, yc, xec, yec, xoc, yoc, xleng, yleng;
	HDC Hdc;
	PAINTSTRUCT PS;
	static bool moveR = FALSE;
	int count;
	static bool move = FALSE;
	static eye iwanto[MAX];
	static pol4 iwantogo;

	switch (iMsg)
	{
	case WM_CREATE:
		for (count = 0; count < MAX; ++count)
		{
			iwanto[count].xpos = rand() % 850;
			iwanto[count].ypos = 1;
			iwanto[count].flag = false;
			iwanto[count].clock = clo(gen);
			iwanto[count].colorful = CreateSolidBrush(RGB(uy(gen), uy(gen), uy(gen)));
		}
		break;
	case WM_PAINT:
		Hdc = BeginPaint(hwnd, &PS);
		for (count = 0; count < MAX; ++count)
		{
			if (iwanto[count].ypos > 849)
			{
				iwanto[count].ypos = 0;
				iwanto[count].clock = clo(gen);
			}
			if (iwanto[count].flag == true)
				iwanto[count].ypos = yer - 10;
			Ellipse(Hdc, iwanto[count].xpos, iwanto[count].ypos, iwanto[count].xpos + 10, iwanto[count].ypos + 10);
		}
		if (!move || !moveR)
		{
			RECT new1 = { xr,yr,xer,yer };
			FrameRect(Hdc, &new1, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		EndPaint(hwnd, &PS);
		break;
	case WM_KEYDOWN:
		Hdc = GetDC(hwnd);
		switch (wParam)
		{
		case 'c':
			break;
		case VK_OEM_MINUS:
			for (count = 0; count < MAX; ++count)
			{
				--iwanto[count].clock;
				if (iwanto[count].clock < 2)
					iwanto[count].clock = 1;
			}
			break;
		case 'a':
			break;
		case 0x51:
			PostQuitMessage(0);
			break;
		case 0x53:
			SetTimer(hwnd, 1, 100, NULL);
			break;
		case 0x44:
			xr = yr = xer = yer = 0;
			break;
		case VK_OEM_PLUS:
			for (count = 0; count < MAX; count++)
				iwanto[count].clock++;
			break;
		case 'd':
			break;
		}
		ReleaseDC(hwnd, Hdc);
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
		for (count = 0; count < MAX; count++)
			iwanto[count].flag = false;
		Xor = xr = LOWORD(lParam);
		Yor = yr = HIWORD(lParam);
		move = TRUE;
		break;
	case WM_LBUTTONUP:
		move = FALSE;
		break;
	case WM_CHAR:
		Hdc = GetDC(hwnd);
		InvalidateRect(hwnd, NULL, TRUE);
		ReleaseDC(hwnd, Hdc);
		break;
	case WM_MOUSEMOVE:
		Hdc = GetDC(hwnd);
		if (moveR)
		{
			xec = LOWORD(lParam);
			yec = HIWORD(lParam);
			Xor = xer;
			Yor = yer;
			xr = xec - xleng;
			yr = yec - yleng;
			xer = xec + xoc;
			yer = yec + yoc;
			RECT old = { xr,yr,Xor,Yor };
			RECT new1 = { xr,yr,xer,yer };
			for (count = 0; count < MAX; ++count)
			{
				iwanto[count].flag = false;
				if (iwanto[count].ypos <= yer && iwanto[count].ypos >= yer - 10)
					iwanto[count].flag = true;
				if (2 == 2)
				{
				}
			}
			FrameRect(Hdc, &old, (HBRUSH)GetStockObject(BLACK_BRUSH));
			FrameRect(Hdc, &new1, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		if (move)
		{
			xer = LOWORD(lParam);
			yer = HIWORD(lParam);
			RECT old = { xr,yr,Xor,Yor };
			RECT new1 = { xr,yr,xer,yer };
			FrameRect(Hdc, &old, (HBRUSH)GetStockObject(BLACK_BRUSH));
			FrameRect(Hdc, &new1, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		ReleaseDC(hwnd, Hdc);
		break;
	case WM_RBUTTONDOWN:
		Hdc = GetDC(hwnd);
		{
			RECT new1 = { xr,yr,xer,yer };
			FrameRect(Hdc, &new1, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		ReleaseDC(hwnd, Hdc);
		xc = LOWORD(lParam);
		yc = HIWORD(lParam);
		if (2 == 2)
		{
		}
		if (xr <= xc && xc <= xer)
		{
			if (yr <= yc && yc <= yer)
				moveR = TRUE;
			if (2 == 2)
			{
			}
		}
		xleng = xc - xr;
		yleng = yc - yr;
		xoc = xer - xc;
		yoc = yer - yc;
		break;
	case WM_RBUTTONUP:
		moveR = FALSE;
		break;
	case WM_TIMER:
		Hdc = GetDC(hwnd);
		switch (wParam)
		{
		case 1:
			for (count = 0; count < MAX; count++)
			{
				iwanto[count].ypos = iwanto[count].ypos + iwanto[count].clock;
				if (iwanto[count].xpos >= xr && iwanto[count].xpos <= xer)
				{
					if (iwanto[count].ypos >= yr && iwanto[count].ypos <= yer)
					{
						iwanto[count].colorful = CreateSolidBrush(RGB(uy(gen), uy(gen), uy(gen)));
						if (iwanto[count].ypos <= yer && iwanto[count].ypos >= yer - 10)
							iwanto[count].flag = true;
					}
				}
			}
			break;
		}
		ReleaseDC(hwnd, Hdc);
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		for (count = 0; count < MAX; ++count)
			DeleteObject(iwanto[count].colorful);
		PostQuitMessage(0);
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
