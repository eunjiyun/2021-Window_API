#include<Windows.h>
#include<TCHAR.H>
#include <random>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> col(0, 255);
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
		_T("windows program 2-7"),
		WS_SYSMENU,
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
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hbrush, oldbrush;
	HPEN MyPen, OldPen;
	static int fir = 0;
	static int sec = 0;
	static int thi = 0;
	POINT tri[] =
	{ {120,260},{220,460},{20,460} };
	POINT centri[] =
	{ {640,260},{540,460},{740,460} };
	POINT penta[] =
	{ {1160,260},{1060,330} ,{1085,460},{1235,460},{1260,330}, };
	POINT cenpenta[] =
	{ {640,260},{540,330} ,{565,460},{715,460},{740,330}, };
	POINT hourgl[] =
	{ {540,0},{640,100} ,{740,200},{540,200},{740,0}, };
	POINT cenhourgl[] =
	{ {540,260},{640,360} ,{740,460},{540,460},{740,260}, };
	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hbrush = CreateSolidBrush(RGB(0, 0, 255));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Polygon(hdc, tri, 3);

		hbrush = CreateSolidBrush(RGB(255, 180, 0));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Polygon(hdc, penta, 5);

		hbrush = CreateSolidBrush(RGB(0, 255, 0));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Pie(hdc, 540, 530, 740, 730, 640, 530, 740, 630);

		hbrush = CreateSolidBrush(RGB(255, 0, 0));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Polygon(hdc, hourgl, 5);

		hbrush = CreateSolidBrush(RGB(255, 255, 255));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Rectangle(hdc, 500, 220, 780, 500);

		SelectObject(hdc, oldbrush);
		DeleteObject(hbrush);
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		hbrush = CreateSolidBrush(RGB(col(gen), col(gen), col(gen)));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		switch (wParam)
		{
		case VK_UP:
			fir = col(gen);
			sec = col(gen);
			thi = col(gen);
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Rectangle(hdc, 500, 220, 780, 500);
			hbrush = CreateSolidBrush(RGB(fir, sec, thi));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			Polygon(hdc, cenhourgl, 5);
			Polygon(hdc, hourgl, 5);
			SelectObject(hdc, OldPen);
			DeleteObject(MyPen);
			break;
		case VK_DOWN:
			fir = col(gen);
			sec = col(gen);
			thi = col(gen);
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Rectangle(hdc, 500, 220, 780, 500);
			hbrush = CreateSolidBrush(RGB(fir, sec, thi));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			Pie(hdc, 540, 260, 740, 460, 640, 260, 740, 360);
			Pie(hdc, 540, 530, 740, 730, 640, 530, 740, 630);
			SelectObject(hdc, OldPen);
			DeleteObject(MyPen);
			break;
		case VK_RIGHT:
			fir = col(gen);
			sec = col(gen);
			thi = col(gen);
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Rectangle(hdc, 500, 220, 780, 500);
			hbrush = CreateSolidBrush(RGB(fir, sec, thi));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			Polygon(hdc, cenpenta, 5);
			Polygon(hdc, penta, 5);
			SelectObject(hdc, OldPen);
			DeleteObject(MyPen);
			break;
		case VK_LEFT:
			fir = col(gen);
			sec = col(gen);
			thi = col(gen);
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Rectangle(hdc, 500, 220, 780, 500);
			hbrush = CreateSolidBrush(RGB(fir, sec, thi));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			Polygon(hdc, centri, 3);
			Polygon(hdc, tri, 3);
			SelectObject(hdc, OldPen);
			DeleteObject(MyPen);
			break;
		case 'T':
		case 't':
			Polygon(hdc, tri, 3);
			break;
		case 'S':
		case 's':
			Polygon(hdc, hourgl, 5);
			break;
		case 'P':
		case 'p':
			Polygon(hdc, penta, 5);
			break;
		case 'E':
		case 'e':
			Pie(hdc, 540, 530, 740, 730, 640, 530, 740, 630);
			break;
		case 'Q':
		case 'q':
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}
		ReleaseDC(hwnd, hdc);
		SelectObject(hdc, oldbrush);
		DeleteObject(hbrush);
		break;
	case WM_KEYUP:
		hdc = GetDC(hwnd);
		switch (wParam)
		{
		case VK_UP:
			MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			hbrush = CreateSolidBrush(RGB(fir, sec, thi));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Polygon(hdc, cenhourgl, 5);
			SelectObject(hdc, OldPen);
			DeleteObject(MyPen);
			Polygon(hdc, hourgl, 5);
			break;
		case VK_DOWN:
			MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			hbrush = CreateSolidBrush(RGB(fir, sec, thi));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Pie(hdc, 540, 260, 740, 460, 640, 260, 740, 360);
			SelectObject(hdc, OldPen);
			DeleteObject(MyPen);
			Pie(hdc, 540, 530, 740, 730, 640, 530, 740, 630);
			break;
		case VK_RIGHT:
			MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			hbrush = CreateSolidBrush(RGB(fir, sec, thi));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Polygon(hdc, cenpenta, 5);
			SelectObject(hdc, OldPen);
			DeleteObject(MyPen);
			Polygon(hdc, penta, 5);
			break;
		case VK_LEFT:
			MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			hbrush = CreateSolidBrush(RGB(fir, sec, thi));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Polygon(hdc, centri, 3);
			SelectObject(hdc, OldPen);
			DeleteObject(MyPen);
			Polygon(hdc, tri, 3);
			break;
		case 'T':
		case 't':
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Polygon(hdc, tri, 3);
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Rectangle(hdc, 500, 220, 780, 500);
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Polygon(hdc, centri, 3);
			break;
		case 'P':
		case 'p':
			hbrush = CreateSolidBrush(RGB(255, 180, 0));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Polygon(hdc, penta, 5);
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Rectangle(hdc, 500, 220, 780, 500);
			hbrush = CreateSolidBrush(RGB(255, 180, 0));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Polygon(hdc, cenpenta, 5);
			break;
		case 'E':
		case 'e':
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Pie(hdc, 540, 530, 740, 730, 640, 530, 740, 630);
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Rectangle(hdc, 500, 220, 780, 500);
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Pie(hdc, 540, 260, 740, 460, 640, 260, 740, 360);
			break;
		case 'S':
		case 's':
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Polygon(hdc, hourgl, 5);
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Rectangle(hdc, 500, 220, 780, 500);
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
			Polygon(hdc, cenhourgl, 5);
			break;
		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
