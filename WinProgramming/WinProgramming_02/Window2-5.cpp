#include<Windows.h>
#include<TCHAR.H>
#include <random>
std::default_random_engine gen;
std::uniform_int_distribution<int> split(2, 10);
std::uniform_int_distribution<int> shape(0, 5);
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
		_T("windows program 2-5"),
		WS_SYSMENU,
		0,
		0,
		800,
		600,
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
struct color
{
	int fir = 0;
	int sec = 0;
	int thi = 0;
};
HBRUSH orange, oldpen;
HPEN MyPen, OldPen;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	//역삼각형 나비 마름모 모래시계 사각형 X
	HDC hdc;
	PAINTSTRUCT ps;
	POINT inverTri[3];//역삼각형
	POINT butFly[5];//나비
	POINT rhombus[4];//마름모
	POINT hourgl[5];//모래시계
	color unique[6];
	int ver = 7;
	int hor = 7;
	int baseSide = 0;
	int height = 0;
	for (int i = 0; i < 6; ++i)
	{
		unique[i].fir = col(gen);
		unique[i].sec = col(gen);
		unique[i].thi = col(gen);
	}
	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		ver = split(gen);//800
		hor = split(gen);//600
		baseSide = 800 / ver;
		height = 570 / hor;
		hdc = BeginPaint(hwnd, &ps);
		MyPen = CreatePen(PS_SOLID, 5, RGB(unique[4].fir, unique[4].sec, unique[4].thi));
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		for (int i = 0; i < hor; ++i)
		{
			for (int j = 0; j < ver; ++j)
			{
				switch (shape(gen))
				{
				case 0:
					inverTri[0] = { 20 + j * baseSide,i * height + height - 20 };
					inverTri[1] = { j * baseSide + baseSide - 20,i * height + height - 20 };
					inverTri[2] = { j * baseSide + baseSide / 2,20 + i * height };
					orange = CreateSolidBrush(RGB(unique[0].fir, unique[0].sec, unique[0].thi));
					oldpen = (HBRUSH)SelectObject(hdc, orange);
					Polygon(hdc, inverTri, 3);
					break;
				case 1:
					butFly[0] = { 20 + j * baseSide, 20 + i * height };
					butFly[1] = { 20 + j * baseSide, i * height + height - 20 };
					butFly[2] = { j * baseSide + baseSide / 2,i * height + height / 2 };
					butFly[3] = { j * baseSide + baseSide - 20, 20 + i * height };
					butFly[4] = { j * baseSide + baseSide - 20 , i * height + height - 20 };
					orange = CreateSolidBrush(RGB(unique[1].fir, unique[1].sec, unique[1].thi));
					oldpen = (HBRUSH)SelectObject(hdc, orange);
					Polygon(hdc, butFly, 5);
					break;
				case 2:
					rhombus[0] = { j * baseSide + baseSide / 2,20 + i * height };
					rhombus[1] = { 20 + j * baseSide,i * height + height / 2 };
					rhombus[2] = { j * baseSide + baseSide / 2,i * height + height - 20 };
					rhombus[3] = { j * baseSide + baseSide - 20,i * height + height / 2 , };
					orange = CreateSolidBrush(RGB(unique[2].fir, unique[2].sec, unique[2].thi));
					oldpen = (HBRUSH)SelectObject(hdc, orange);
					Polygon(hdc, rhombus, 4);
					break;
				case 3:
					hourgl[0] = { 20 + j * baseSide, 20 + i * height };
					hourgl[1] = { j * baseSide + baseSide - 20, 20 + i * height };
					hourgl[2] = { j * baseSide + baseSide / 2,i * height + height / 2 };
					hourgl[3] = { 20 + j * baseSide, i * height + height - 20 };
					hourgl[4] = { j * baseSide + baseSide - 20 , i * height + height - 20 };
					orange = CreateSolidBrush(RGB(unique[3].fir, unique[3].sec, unique[3].thi));
					oldpen = (HBRUSH)SelectObject(hdc, orange);
					Polygon(hdc, hourgl, 5);
					break;
				case 4:
					MoveToEx(hdc, 20 + j * baseSide, 20 + i * height, nullptr);
					LineTo(hdc, j * baseSide + baseSide - 20, i * height + height - 20);
					MoveToEx(hdc, j * baseSide + baseSide - 20, 20 + i * height, nullptr);
					LineTo(hdc, 20 + j * baseSide, i * height + height - 20);
					break;
				case 5:
					orange = CreateSolidBrush(RGB(unique[5].fir, unique[5].sec, unique[5].thi));
					oldpen = (HBRUSH)SelectObject(hdc, orange);
					Rectangle(hdc, 10 + j * baseSide, 20 + i * height, j * baseSide + baseSide - 20, i * height + height - 20);
					break;
				default:
					break;
				}
			}
		}
		/*SelectObject(hdc, oldbrush);
		DeleteObject(hbrush);*/
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
