#include<Windows.h>
#include<TCHAR.H>
#include <random>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> col(0, 255);

int p1x = 20;
int p1y = 20;
int p2x = 720;
int p2y = 720;
int turn = 0;
int size1 = 0;
int size2 = 0;
int rockfir1 = 0;
int rockfir2 = 0;
int rocksec1 = 30;
int rocksec2 = 30;
int p1col1 = 0;
int p1col2 = 0;
int p1col3 = 255;
int p2col1 = 255;
int p2col2 = 0;
int p2col3 = 255;

int fir1 = col(gen);
int fir2 = col(gen);
int fir3 = col(gen);
int sec1 = col(gen);
int sec2 = col(gen);
int sec3 = col(gen);
int thi1 = col(gen);
int thi2 = col(gen);
int thi3 = col(gen);
int fou1 = col(gen);
int fou2 = col(gen);
int fou3 = col(gen);
int fif1 = col(gen);
int fif2 = col(gen);
int fif3 = col(gen);
int six1 = col(gen);
int six2 = col(gen);
int six3 = col(gen);
int sev1 = col(gen);
int sev2 = col(gen);
int sev3 = col(gen);

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
		_T("windows program 2-8"),
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

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hbrush = CreateSolidBrush(RGB(255, 255, 255));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				Rectangle(hdc, 10 + j * 50, 10 + i * 50, 10 + (j + 1) * 50, 10 + (i + 1) * 50);

		hbrush = CreateSolidBrush(RGB(255, 0, 0));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		Rectangle(hdc, 10 + 2 * 50, 10 + 2 * 50, 10 + (2 + 1) * 50, 10 + (2 + 1) * 50);//2 2  +10  +10
		Rectangle(hdc, 10 + 0 * 50, 10 + 1 * 50, 10 + (0 + 1) * 50, 10 + (1 + 1) * 50);//0 1
		Rectangle(hdc, 10 + 13 * 50, 10 + 2 * 50, 10 + (13 + 1) * 50, 10 + (2 + 1) * 50);
		Rectangle(hdc, 10 + 7 * 50, 10 + 8 * 50, 10 + (7 + 1) * 50, 10 + (8 + 1) * 50);
		Rectangle(hdc, 10 + 9 * 50, 10 + 14 * 50, 10 + (9 + 1) * 50, 10 + (14 + 1) * 50);
		Rectangle(hdc, 10 + 7 * 50, 10 + 13 * 50, 10 + (7 + 1) * 50, 10 + (13 + 1) * 50);

		hbrush = CreateSolidBrush(RGB(0, 255, 0));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Rectangle(hdc, 10 + 11 * 50, 10 + 11 * 50, 10 + (11 + 1) * 50, 10 + (11 + 1) * 50);//11 11     570 570
		Rectangle(hdc, 10 + 12 * 50, 10 + 1 * 50, 10 + (12 + 1) * 50, 10 + (1 + 1) * 50);//12 1        620  70
		Rectangle(hdc, 10 + 13 * 50, 10 + 9 * 50, 10 + (13 + 1) * 50, 10 + (9 + 1) * 50);//13 9        670   470
		Rectangle(hdc, 10 + 7 * 50, 10 + 14 * 50, 10 + (7 + 1) * 50, 10 + (14 + 1) * 50);//7 14        370     720
		Rectangle(hdc, 10 + 9 * 50, 10 + 12 * 50, 10 + (9 + 1) * 50, 10 + (12 + 1) * 50);//9 12        470    620
		Rectangle(hdc, 10 + 6 * 50, 10 + 6 * 50, 10 + (6 + 1) * 50, 10 + (6 + 1) * 50);//6 6           320     320
		Rectangle(hdc, 10 + 5 * 50, 10 + 5 * 50, 10 + (5 + 1) * 50, 10 + (5 + 1) * 50);//5 5            270   270
		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);

		hbrush = CreateSolidBrush(RGB(fir1, fir2, fir3));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Rectangle(hdc, 10 + 5 * 50, 10 + 8 * 50, 10 + (5 + 1) * 50, 10 + (8 + 1) * 50);//5 8             270  420
		hbrush = CreateSolidBrush(RGB(sec1, sec2, sec3));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Rectangle(hdc, 10 + 4 * 50, 10 + 6 * 50, 10 + (4 + 1) * 50, 10 + (6 + 1) * 50);//4 6        220      320
		hbrush = CreateSolidBrush(RGB(thi1, thi2, thi3));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Rectangle(hdc, 10 + 4 * 50, 10 + 9 * 50, 10 + (4 + 1) * 50, 10 + (9 + 1) * 50);//4 9        220     470
		hbrush = CreateSolidBrush(RGB(fou1, fou2, fou3));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Rectangle(hdc, 10 + 8 * 50, 10 + 5 * 50, 10 + (8 + 1) * 50, 10 + (5 + 1) * 50);//8 5         420     270
		hbrush = CreateSolidBrush(RGB(fif1, fif2, fif3));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Rectangle(hdc, 10 + 9 * 50, 10 + 3 * 50, 10 + (9 + 1) * 50, 10 + (3 + 1) * 50);//9 3          470     170
		hbrush = CreateSolidBrush(RGB(six1, six2, six3));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Rectangle(hdc, 10 + 3 * 50, 10 + 8 * 50, 10 + (3 + 1) * 50, 10 + (8 + 1) * 50);//3 8          170     420
		hbrush = CreateSolidBrush(RGB(sev1, sev2, sev3));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Rectangle(hdc, 10 + 6 * 50, 10 + 2 * 50, 10 + (6 + 1) * 50, 10 + (2 + 1) * 50);//6 2          320     120

		hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

		hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

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
		case 'W':
			if (turn % 2 != 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p1y -= 50;
				if (p1y < 20)
				{
					p1y = 720;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p1x == 120 && p1y == 120 || p1x == 20 && p1y == 70 || p1x == 370 && p1y == 420 || p1x == 670 && p1y == 120 || p1x == 470 && p1y == 720 || p1x == 370 && p1y == 670)
					p1y += 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case 'w':
			if (turn % 2 != 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p1y -= 50;
				if (p1y < 20)
				{
					p1y = 720;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p1x == 120 && p1y == 120 || p1x == 20 && p1y == 70 || p1x == 370 && p1y == 420 || p1x == 670 && p1y == 120 || p1x == 470 && p1y == 720 || p1x == 370 && p1y == 670)

					p1y += 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case 'A':
			if (turn % 2 != 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p1x -= 50;
				if (p1x < 20)
				{
					p1x = 720;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p1x == 120 && p1y == 120 || p1x == 20 && p1y == 70 || p1x == 370 && p1y == 420 || p1x == 670 && p1y == 120 || p1x == 470 && p1y == 720 || p1x == 370 && p1y == 670)
					p1x += 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case 'a':
			if (turn % 2 != 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p1x -= 50;
				if (p1x < 20)
				{
					p1x = 720;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p1x == 120 && p1y == 120 || p1x == 20 && p1y == 70 || p1x == 370 && p1y == 420 || p1x == 670 && p1y == 120 || p1x == 470 && p1y == 720 || p1x == 370 && p1y == 670)

					p1x += 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case 'S':
			if (turn % 2 != 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p1y += 50;
				if (p1y > 720)
				{
					p1y = 20;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p1x == 120 && p1y == 120 || p1x == 20 && p1y == 70 || p1x == 370 && p1y == 420 || p1x == 670 && p1y == 120 || p1x == 470 && p1y == 720 || p1x == 370 && p1y == 670)

					p1y -= 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case 's':
			if (turn % 2 != 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p1y += 50;
				if (p1y > 720)
				{
					p1y = 20;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p1x == 120 && p1y == 120 || p1x == 20 && p1y == 70 || p1x == 370 && p1y == 420 || p1x == 670 && p1y == 120 || p1x == 470 && p1y == 720 || p1x == 370 && p1y == 670)
					p1y -= 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case 'D':
			if (turn % 2 != 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p1x += 50;
				if (p1x > 720)
				{
					p1x = 20;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p1x == 120 && p1y == 120 || p1x == 20 && p1y == 70 || p1x == 370 && p1y == 420 || p1x == 670 && p1y == 120 || p1x == 470 && p1y == 720 || p1x == 370 && p1y == 670)
					p1x -= 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case 'd':
			if (turn % 2 != 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p1x += 50;
				if (p1x > 720)
				{
					p1x = 20;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p1x == 120 && p1y == 120 || p1x == 20 && p1y == 70 || p1x == 370 && p1y == 420 || p1x == 670 && p1y == 120 || p1x == 470 && p1y == 720 || p1x == 370 && p1y == 670)
					p1x -= 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case VK_UP:
			if (turn % 2 == 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p2y -= 50;
				if (p2y < 20)
				{
					p2y = 720;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p2x == 120 && p2y == 120 || p2x == 20 && p2y == 70 || p2x == 370 && p2y == 420 || p2x == 670 && p2y == 120 || p2x == 470 && p2y == 720 || p2x == 370 && p2y == 670)
					p2y += 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case VK_DOWN:
			if (turn % 2 == 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p2y += 50;
				if (p2y > 720)
				{
					p2y = 20;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p2x == 120 && p2y == 120 || p2x == 20 && p2y == 70 || p2x == 370 && p2y == 420 || p2x == 670 && p2y == 120 || p2x == 470 && p2y == 720 || p2x == 370 && p2y == 670)

					p2y -= 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case VK_RIGHT:
			if (turn % 2 == 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p2x += 50;
				if (p2x > 720)
				{
					p2x = 20;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p2x == 120 && p2y == 120 || p2x == 20 && p2y == 70 || p2x == 370 && p2y == 420 || p2x == 670 && p2y == 120 || p2x == 470 && p2y == 720 || p2x == 370 && p2y == 670)
					p2x -= 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case VK_LEFT:
			if (turn % 2 == 0)
			{
				InvalidateRgn(hwnd, NULL, FALSE);
				TextOut(hdc, 800, 0, _T("error"), 5);
			}
			else
			{
				p2x -= 50;
				if (p2x < 20)
				{
					p2x = 720;
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
				else if (p2x == 120 && p2y == 120 || p2x == 20 && p2y == 70 || p2x == 370 && p2y == 420 || p2x == 670 && p2y == 120 || p2x == 470 && p2y == 720 || p2x == 370 && p2y == 670)
					p2x += 50;
				else
				{
					++turn;
					InvalidateRgn(hwnd, NULL, TRUE);
				}
			}
			break;
		case 'R':
			p1x = 20;
			p1y = 20;
			p2x = 720;
			p2y = 720;
			turn = 0;
			InvalidateRgn(hwnd, NULL, TRUE);
			fir1 = col(gen);
			fir2 = col(gen);
			fir3 = col(gen);
			sec1 = col(gen);
			sec2 = col(gen);
			sec3 = col(gen);
			thi1 = col(gen);
			thi2 = col(gen);
			thi3 = col(gen);
			fou1 = col(gen);
			fou2 = col(gen);
			fou3 = col(gen);
			fif1 = col(gen);
			fif2 = col(gen);
			fif3 = col(gen);
			six1 = col(gen);
			six2 = col(gen);
			six3 = col(gen);
			sev2 = col(gen);
			sev3 = col(gen);
			rockfir1 = 0;
			rockfir2 = 0;
			rocksec1 = 30;
			rocksec2 = 30;
			p1col1 = 0;
			p1col2 = 0;
			p1col3 = 255;
			p2col1 = 255;
			p2col2 = 0;
			p2col3 = 255;
			break;
		case 'r':
			p1x = 20;
			p1y = 20;
			p2x = 720;
			p2y = 720;
			InvalidateRgn(hwnd, NULL, TRUE);
			fir1 = col(gen);
			fir2 = col(gen);
			fir3 = col(gen);
			sec1 = col(gen);
			sec2 = col(gen);
			sec3 = col(gen);
			thi1 = col(gen);
			thi2 = col(gen);
			thi3 = col(gen);
			fou1 = col(gen);
			fou2 = col(gen);
			fou3 = col(gen);
			fif1 = col(gen);
			fif2 = col(gen);
			fif3 = col(gen);
			six1 = col(gen);
			six2 = col(gen);
			six3 = col(gen);
			sev2 = col(gen);
			sev3 = col(gen);
			rockfir1 = 0;
			rockfir2 = 0;
			rocksec1 = 30;
			rocksec2 = 30;
			p1col1 = 0;
			p1col2 = 0;
			p1col3 = 255;
			p2col1 = 255;
			p2col2 = 0;
			p2col3 = 255;
			break;
		case 'Q':
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
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
		hbrush = CreateSolidBrush(RGB(col(gen), col(gen), col(gen)));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		switch (wParam)
		{
		case 'W':
			if (turn % 2 != 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (p1x == 570 && p1y == 570 || p1x == 620 && p1y == 70 || p1x == 670 && p1y == 470 || p1x == 370 && p1y == 720 || p1x == 470 && p1y == 620 || p1x == 320 && p1y == 320 || p1x == 270 && p1y == 270)
				{
					if (size1 % 2 == 0)
					{
						rockfir1 = -5;
						rocksec1 = 35;
					}
					else
					{
						rockfir1 = 5;
						rocksec1 = 25;
					}
					++size1;
				}
				else if (p1x == 270 && p1y == 420)//5 8
				{
					p1col1 = fir1;
					p1col2 = fir2;
					p1col3 = fir3;
				}
				else if (p1x == 220 && p1y == 320)//4 6
				{
					p1col1 = sec1;
					p1col2 = sec2;
					p1col3 = sec3;
				}
				else if (p1x == 220 && p1y == 470)//4 9
				{
					p1col1 = thi1;
					p1col2 = thi2;
					p1col3 = thi3;
				}
				else if (p1x == 420 && p1y == 270)//8 5
				{
					p1col1 = fou1;
					p1col2 = fou2;
					p1col3 = fou3;
				}
				else if (p1x == 470 && p1y == 170)//9 3
				{
					p1col1 = fif1;
					p1col2 = fif2;
					p1col3 = fif3;
				}
				else if (p1x == 170 && p1y == 420)//3 8
				{
					p1col1 = six1;
					p1col2 = six2;
					p1col3 = six3;
				}
				else if (p1x == 320 && p1y == 120)//6 2
				{
					p1col1 = sev1;
					p1col2 = sev2;
					p1col3 = sev3;
				}
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		case 'w':
			if (turn % 2 != 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (p1x == 570 && p1y == 570 || p1x == 620 && p1y == 70 || p1x == 670 && p1y == 470 || p1x == 370 && p1y == 720 || p1x == 470 && p1y == 620 || p1x == 320 && p1y == 320 || p1x == 270 && p1y == 270)
				{
					if (size1 % 2 == 0)
					{
						rockfir1 = -5;
						rocksec1 = 35;
					}
					else
					{
						rockfir1 = 5;
						rocksec1 = 25;
					}
					++size1;
				}
				else if (p1x == 270 && p1y == 420)//5 8
				{
					p1col1 = fir1;
					p1col2 = fir2;
					p1col3 = fir3;
				}
				else if (p1x == 220 && p1y == 320)//4 6
				{
					p1col1 = sec1;
					p1col2 = sec2;
					p1col3 = sec3;
				}
				else if (p1x == 220 && p1y == 470)//4 9
				{
					p1col1 = thi1;
					p1col2 = thi2;
					p1col3 = thi3;
				}
				else if (p1x == 420 && p1y == 270)//8 5
				{
					p1col1 = fou1;
					p1col2 = fou2;
					p1col3 = fou3;
				}
				else if (p1x == 470 && p1y == 170)//9 3
				{
					p1col1 = fif1;
					p1col2 = fif2;
					p1col3 = fif3;
				}
				else if (p1x == 170 && p1y == 420)//3 8
				{
					p1col1 = six1;
					p1col2 = six2;
					p1col3 = six3;
				}
				else if (p1x == 320 && p1y == 120)//6 2
				{
					p1col1 = sev1;
					p1col2 = sev2;
					p1col3 = sev3;
				}
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		case 'A':
			if (turn % 2 != 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (p1x == 570 && p1y == 570 || p1x == 620 && p1y == 70 || p1x == 670 && p1y == 470 || p1x == 370 && p1y == 720 || p1x == 470 && p1y == 620 || p1x == 320 && p1y == 320 || p1x == 270 && p1y == 270)
				{
					if (size1 % 2 == 0)
					{
						rockfir1 = -5;
						rocksec1 = 35;
					}
					else
					{
						rockfir1 = 5;
						rocksec1 = 25;
					}
					++size1;
				}
				else if (p1x == 270 && p1y == 420)//5 8
				{
					p1col1 = fir1;
					p1col2 = fir2;
					p1col3 = fir3;
				}
				else if (p1x == 220 && p1y == 320)//4 6
				{
					p1col1 = sec1;
					p1col2 = sec2;
					p1col3 = sec3;
				}
				else if (p1x == 220 && p1y == 470)//4 9
				{
					p1col1 = thi1;
					p1col2 = thi2;
					p1col3 = thi3;
				}
				else if (p1x == 420 && p1y == 270)//8 5
				{
					p1col1 = fou1;
					p1col2 = fou2;
					p1col3 = fou3;
				}
				else if (p1x == 470 && p1y == 170)//9 3
				{
					p1col1 = fif1;
					p1col2 = fif2;
					p1col3 = fif3;
				}
				else if (p1x == 170 && p1y == 420)//3 8
				{
					p1col1 = six1;
					p1col2 = six2;
					p1col3 = six3;
				}
				else if (p1x == 320 && p1y == 120)//6 2
				{
					p1col1 = sev1;
					p1col2 = sev2;
					p1col3 = sev3;
				}
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		case 'a':
			if (turn % 2 != 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (p1x == 570 && p1y == 570 || p1x == 620 && p1y == 70 || p1x == 670 && p1y == 470 || p1x == 370 && p1y == 720 || p1x == 470 && p1y == 620 || p1x == 320 && p1y == 320 || p1x == 270 && p1y == 270)
				{
					if (size1 % 2 == 0)
					{
						rockfir1 = -5;
						rocksec1 = 35;
					}
					else
					{
						rockfir1 = 5;
						rocksec1 = 25;
					}
					++size1;
				}
				else if (p1x == 270 && p1y == 420)//5 8
				{
					p1col1 = fir1;
					p1col2 = fir2;
					p1col3 = fir3;
				}
				else if (p1x == 220 && p1y == 320)//4 6
				{
					p1col1 = sec1;
					p1col2 = sec2;
					p1col3 = sec3;
				}
				else if (p1x == 220 && p1y == 470)//4 9
				{
					p1col1 = thi1;
					p1col2 = thi2;
					p1col3 = thi3;
				}
				else if (p1x == 420 && p1y == 270)//8 5
				{
					p1col1 = fou1;
					p1col2 = fou2;
					p1col3 = fou3;
				}
				else if (p1x == 470 && p1y == 170)//9 3
				{
					p1col1 = fif1;
					p1col2 = fif2;
					p1col3 = fif3;
				}
				else if (p1x == 170 && p1y == 420)//3 8
				{
					p1col1 = six1;
					p1col2 = six2;
					p1col3 = six3;
				}
				else if (p1x == 320 && p1y == 120)//6 2
				{
					p1col1 = sev1;
					p1col2 = sev2;
					p1col3 = sev3;
				}
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		case 'S':
			if (turn % 2 != 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (p1x == 570 && p1y == 570 || p1x == 620 && p1y == 70 || p1x == 670 && p1y == 470 || p1x == 370 && p1y == 720 || p1x == 470 && p1y == 620 || p1x == 320 && p1y == 320 || p1x == 270 && p1y == 270)
				{
					if (size1 % 2 == 0)
					{
						rockfir1 = -5;
						rocksec1 = 35;
					}
					else
					{
						rockfir1 = 5;
						rocksec1 = 25;
					}
					++size1;
				}
				else if (p1x == 270 && p1y == 420)//5 8
				{
					p1col1 = fir1;
					p1col2 = fir2;
					p1col3 = fir3;
				}
				else if (p1x == 220 && p1y == 320)//4 6
				{
					p1col1 = sec1;
					p1col2 = sec2;
					p1col3 = sec3;
				}
				else if (p1x == 220 && p1y == 470)//4 9
				{
					p1col1 = thi1;
					p1col2 = thi2;
					p1col3 = thi3;
				}
				else if (p1x == 420 && p1y == 270)//8 5
				{
					p1col1 = fou1;
					p1col2 = fou2;
					p1col3 = fou3;
				}
				else if (p1x == 470 && p1y == 170)//9 3
				{
					p1col1 = fif1;
					p1col2 = fif2;
					p1col3 = fif3;
				}
				else if (p1x == 170 && p1y == 420)//3 8
				{
					p1col1 = six1;
					p1col2 = six2;
					p1col3 = six3;
				}
				else if (p1x == 320 && p1y == 120)//6 2
				{
					p1col1 = sev1;
					p1col2 = sev2;
					p1col3 = sev3;
				}
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		case 's':
			if (turn % 2 != 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (p1x == 570 && p1y == 570 || p1x == 620 && p1y == 70 || p1x == 670 && p1y == 470 || p1x == 370 && p1y == 720 || p1x == 470 && p1y == 620 || p1x == 320 && p1y == 320 || p1x == 270 && p1y == 270)
				{
					if (size1 % 2 == 0)
					{
						rockfir1 = -5;
						rocksec1 = 35;
					}
					else
					{
						rockfir1 = 5;
						rocksec1 = 25;
					}
					++size1;
				}
				else if (p1x == 270 && p1y == 420)//5 8
				{
					p1col1 = fir1;
					p1col2 = fir2;
					p1col3 = fir3;
				}
				else if (p1x == 220 && p1y == 320)//4 6
				{
					p1col1 = sec1;
					p1col2 = sec2;
					p1col3 = sec3;
				}
				else if (p1x == 220 && p1y == 470)//4 9
				{
					p1col1 = thi1;
					p1col2 = thi2;
					p1col3 = thi3;
				}
				else if (p1x == 420 && p1y == 270)//8 5
				{
					p1col1 = fou1;
					p1col2 = fou2;
					p1col3 = fou3;
				}
				else if (p1x == 470 && p1y == 170)//9 3
				{
					p1col1 = fif1;
					p1col2 = fif2;
					p1col3 = fif3;
				}
				else if (p1x == 170 && p1y == 420)//3 8
				{
					p1col1 = six1;
					p1col2 = six2;
					p1col3 = six3;
				}
				else if (p1x == 320 && p1y == 120)//6 2
				{
					p1col1 = sev1;
					p1col2 = sev2;
					p1col3 = sev3;
				}
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		case 'D':
			if (turn % 2 != 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (p1x == 570 && p1y == 570 || p1x == 620 && p1y == 70 || p1x == 670 && p1y == 470 || p1x == 370 && p1y == 720 || p1x == 470 && p1y == 620 || p1x == 320 && p1y == 320 || p1x == 270 && p1y == 270)
				{
					if (size1 % 2 == 0)
					{
						rockfir1 = -5;
						rocksec1 = 35;
					}
					else
					{
						rockfir1 = 5;
						rocksec1 = 25;
					}
					++size1;
				}
				else if (p1x == 270 && p1y == 420)//5 8
				{
					p1col1 = fir1;
					p1col2 = fir2;
					p1col3 = fir3;
				}
				else if (p1x == 220 && p1y == 320)//4 6
				{
					p1col1 = sec1;
					p1col2 = sec2;
					p1col3 = sec3;
				}
				else if (p1x == 220 && p1y == 470)//4 9
				{
					p1col1 = thi1;
					p1col2 = thi2;
					p1col3 = thi3;
				}
				else if (p1x == 420 && p1y == 270)//8 5
				{
					p1col1 = fou1;
					p1col2 = fou2;
					p1col3 = fou3;
				}
				else if (p1x == 470 && p1y == 170)//9 3
				{
					p1col1 = fif1;
					p1col2 = fif2;
					p1col3 = fif3;
				}
				else if (p1x == 170 && p1y == 420)//3 8
				{
					p1col1 = six1;
					p1col2 = six2;
					p1col3 = six3;
				}
				else if (p1x == 320 && p1y == 120)//6 2
				{
					p1col1 = sev1;
					p1col2 = sev2;
					p1col3 = sev3;
				}
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		case 'd':
			if (turn % 2 != 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (p1x == 570 && p1y == 570 || p1x == 620 && p1y == 70 || p1x == 670 && p1y == 470 || p1x == 370 && p1y == 720 || p1x == 470 && p1y == 620 || p1x == 320 && p1y == 320 || p1x == 270 && p1y == 270)
				{
					if (size1 % 2 == 0)
					{
						rockfir1 = -5;
						rocksec1 = 35;
					}
					else
					{
						rockfir1 = 5;
						rocksec1 = 25;
					}
					++size1;
				}
				else if (p1x == 270 && p1y == 420)//5 8
				{
					p1col1 = fir1;
					p1col2 = fir2;
					p1col3 = fir3;
				}
				else if (p1x == 220 && p1y == 320)//4 6
				{
					p1col1 = sec1;
					p1col2 = sec2;
					p1col3 = sec3;
				}
				else if (p1x == 220 && p1y == 470)//4 9
				{
					p1col1 = thi1;
					p1col2 = thi2;
					p1col3 = thi3;
				}
				else if (p1x == 420 && p1y == 270)//8 5
				{
					p1col1 = fou1;
					p1col2 = fou2;
					p1col3 = fou3;
				}
				else if (p1x == 470 && p1y == 170)//9 3
				{
					p1col1 = fif1;
					p1col2 = fif2;
					p1col3 = fif3;
				}
				else if (p1x == 170 && p1y == 420)//3 8
				{
					p1col1 = six1;
					p1col2 = six2;
					p1col3 = six3;
				}
				else if (p1x == 320 && p1y == 120)//6 2
				{
					p1col1 = sev1;
					p1col2 = sev2;
					p1col3 = sev3;
				}
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		case VK_UP:
			if (turn % 2 == 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);

				if (p2x == 570 && p2y == 570 || p2x == 620 && p2y == 70 || p2x == 670 && p2y == 470 || p2x == 370 && p2y == 720 || p2x == 470 && p2y == 620 || p2x == 320 && p2y == 320 || p2x == 270 && p2y == 270)
				{
					if (size2 % 2 == 0)
					{
						rockfir2 = -5;
						rocksec2 = 35;
					}
					else
					{
						rockfir2 = 5;
						rocksec2 = 25;
					}
					++size2;
				}
				else if (p2x == 270 && p2y == 420)//5 8
				{
					p2col1 = fir1;
					p2col2 = fir2;
					p2col3 = fir3;
				}
				else if (p2x == 220 && p2y == 320)//4 6
				{
					p2col1 = sec1;
					p2col2 = sec2;
					p2col3 = sec3;
				}
				else if (p2x == 220 && p2y == 470)//4 9
				{
					p2col1 = thi1;
					p2col2 = thi2;
					p2col3 = thi3;
				}
				else if (p2x == 420 && p2y == 270)//8 5
				{
					p2col1 = fou1;
					p2col2 = fou2;
					p2col3 = fou3;
				}
				else if (p2x == 470 && p2y == 170)//9 3
				{
					p2col1 = fif1;
					p2col2 = fif2;
					p2col3 = fif3;
				}
				else if (p2x == 170 && p2y == 420)//3 8
				{
					p2col1 = six1;
					p2col2 = six2;
					p2col3 = six3;
				}
				else if (p2x == 320 && p2y == 120)//6 2
				{
					p2col1 = sev1;
					p2col2 = sev2;
					p2col3 = sev3;
				}
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		case VK_DOWN:
			if (turn % 2 == 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (p2x == 570 && p2y == 570 || p2x == 620 && p2y == 70 || p2x == 670 && p2y == 470 || p2x == 370 && p2y == 720 || p2x == 470 && p2y == 620 || p2x == 320 && p2y == 320 || p2x == 270 && p2y == 270)
				{
					if (size2 % 2 == 0)
					{
						rockfir2 = -5;
						rocksec2 = 35;
					}
					else
					{
						rockfir2 = 5;
						rocksec2 = 25;
					}
					++size2;
				}
				else if (p2x == 270 && p2y == 420)//5 8
				{
					p2col1 = fir1;
					p2col2 = fir2;
					p2col3 = fir3;
				}
				else if (p2x == 220 && p2y == 320)//4 6
				{
					p2col1 = sec1;
					p2col2 = sec2;
					p2col3 = sec3;
				}
				else if (p2x == 220 && p2y == 470)//4 9
				{
					p2col1 = thi1;
					p2col2 = thi2;
					p2col3 = thi3;
				}
				else if (p2x == 420 && p2y == 270)//8 5
				{
					p2col1 = fou1;
					p2col2 = fou2;
					p2col3 = fou3;
				}
				else if (p2x == 470 && p2y == 170)//9 3
				{
					p2col1 = fif1;
					p2col2 = fif2;
					p2col3 = fif3;
				}
				else if (p2x == 170 && p2y == 420)//3 8
				{
					p2col1 = six1;
					p2col2 = six2;
					p2col3 = six3;
				}
				else if (p2x == 320 && p2y == 120)//6 2
				{
					p2col1 = sev1;
					p2col2 = sev2;
					p2col3 = sev3;
				}
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		case VK_RIGHT:
			if (turn % 2 == 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (p2x == 570 && p2y == 570 || p2x == 620 && p2y == 70 || p2x == 670 && p2y == 470 || p2x == 370 && p2y == 720 || p2x == 470 && p2y == 620 || p2x == 320 && p2y == 320 || p2x == 270 && p2y == 270)
				{
					if (size2 % 2 == 0)
					{
						rockfir2 = -5;
						rocksec2 = 35;
					}
					else
					{
						rockfir2 = 5;
						rocksec2 = 25;
					}
					++size2;
				}
				else if (p2x == 270 && p2y == 420)//5 8
				{
					p2col1 = fir1;
					p2col2 = fir2;
					p2col3 = fir3;
				}
				else if (p2x == 220 && p2y == 320)//4 6
				{
					p2col1 = sec1;
					p2col2 = sec2;
					p2col3 = sec3;
				}
				else if (p2x == 220 && p2y == 470)//4 9
				{
					p2col1 = thi1;
					p2col2 = thi2;
					p2col3 = thi3;
				}
				else if (p2x == 420 && p2y == 270)//8 5
				{
					p2col1 = fou1;
					p2col2 = fou2;
					p2col3 = fou3;
				}
				else if (p2x == 470 && p2y == 170)//9 3
				{
					p2col1 = fif1;
					p2col2 = fif2;
					p2col3 = fif3;
				}
				else if (p2x == 170 && p2y == 420)//3 8
				{
					p2col1 = six1;
					p2col2 = six2;
					p2col3 = six3;
				}
				else if (p2x == 320 && p2y == 120)//6 2
				{
					p2col1 = sev1;
					p2col2 = sev2;
					p2col3 = sev3;
				}
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		case VK_LEFT:
			if (turn % 2 == 0)
			{
				hbrush = CreateSolidBrush(RGB(p1col1, p1col2, p1col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, p1x + rockfir1, p1y + rockfir1, p1x + rocksec1, p1y + rocksec1);
				hbrush = CreateSolidBrush(RGB(p2col1, p2col2, p2col3));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (p2x == 570 && p2y == 570 || p2x == 620 && p2y == 70 || p2x == 670 && p2y == 470 || p2x == 370 && p2y == 720 || p2x == 470 && p2y == 620 || p2x == 320 && p2y == 320 || p2x == 270 && p2y == 270)
				{
					if (size2 % 2 == 0)
					{
						rockfir2 = -5;
						rocksec2 = 35;
					}
					else
					{
						rockfir2 = 5;
						rocksec2 = 25;
					}
					++size2;
				}
				else if (p2x == 270 && p2y == 420)//5 8
				{
					p2col1 = fir1;
					p2col2 = fir2;
					p2col3 = fir3;
				}
				else if (p2x == 220 && p2y == 320)//4 6
				{
					p2col1 = sec1;
					p2col2 = sec2;
					p2col3 = sec3;
				}
				else if (p2x == 220 && p2y == 470)//4 9
				{
					p2col1 = thi1;
					p2col2 = thi2;
					p2col3 = thi3;
				}
				else if (p2x == 420 && p2y == 270)//8 5
				{
					p2col1 = fou1;
					p2col2 = fou2;
					p2col3 = fou3;
				}
				else if (p2x == 470 && p2y == 170)//9 3
				{
					p2col1 = fif1;
					p2col2 = fif2;
					p2col3 = fif3;
				}
				else if (p2x == 170 && p2y == 420)//3 8
				{
					p2col1 = six1;
					p2col2 = six2;
					p2col3 = six3;
				}
				else if (p2x == 320 && p2y == 120)//6 2
				{
					p2col1 = sev1;
					p2col2 = sev2;
					p2col3 = sev3;
				}
				Ellipse(hdc, p2x + rockfir2, p2y + rockfir2, p2x + rocksec2, p2y + rocksec2);
			}
			break;
		}
		ReleaseDC(hwnd, hdc);
		SelectObject(hdc, oldbrush);
		DeleteObject(hbrush);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}