#include<Windows.h>
#include<TCHAR.H>
#include <random>
std::random_device rd;// random_device 를 통해 난수 생성 엔진을 초기화 한다.
std::mt19937 gen(rd());
// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
std::uniform_int_distribution<int> xpos(0, 700);
std::uniform_int_distribution<int> ypos(0, 500);
std::uniform_int_distribution<int> npos(48, 57);
std::uniform_int_distribution<int> countpos(20, 100);
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
		_T("windows program 2-2"),
		WS_OVERLAPPEDWINDOW,
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x = xpos(gen);
	static int y = ypos(gen);
	static SIZE size;
	static int count = countpos(gen);
	static char n = npos(gen);
	static TCHAR str[2];
	static int tc1 = col(gen);
	static int tc2 = col(gen);
	static int tc3 = col(gen);
	static int bc1 = col(gen);
	static int bc2 = col(gen);
	static int bc3 = col(gen);

	switch (iMsg)
	{
	case WM_CREATE:
		str[0] = n;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, RGB(tc1, tc2, tc3));
		SetBkColor(hdc, RGB(bc1, bc2, bc3));
		for (int i = 0; i < count; ++i)
			for (int j = 0; j < count; ++j)
				TextOut(hdc, x + j * 7, y + i * 13, str, lstrlen(str));
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}