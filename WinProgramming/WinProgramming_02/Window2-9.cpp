#include<Windows.h>
#include<TCHAR.H>
#include<random>
std::default_random_engine gen;
std::uniform_int_distribution<int> col(0, 255);
std::uniform_int_distribution<int> sLoc(0, 29);
std::uniform_int_distribution<int> mLoc(0, 39);
std::uniform_int_distribution<int> lLoc(0, 49);
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
		_T("windows program 2-10"),
		WS_OVERLAPPEDWINDOW,
		700,
		0,
		850,
		850,
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
struct pol3
{
	int xpos = 0;
	int ypos = 0;
	int shape = 3;
	int fir = 0;
	int sec = 0;
	int thi = 0;
};
pol3 poly3[10];
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hbrush, oldbrush;
	HPEN MyPen, OldPen;
	POINT tri[3];
	static int preBoard = 0;
	static int countPol = 0;
	static int cirCol = 0;//012
	static int triCol = 0;//120
	static int recCol = 0;//210
	static bool switC = TRUE;
	static int preChoose = 11;
	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0; i < 41; ++i)
		{
			MoveToEx(hdc, i * 18, 0, nullptr);
			LineTo(hdc, i * 18, 720);
		}
		for (int j = 0; j < 41; ++j)
		{
			MoveToEx(hdc, 0, j * 18, nullptr);
			LineTo(hdc, 720, j * 18);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		switch (wParam)
		{
		case 'S'://보드칸을 30으로 나눈다
		case 's':
			if (preBoard == 0 || preBoard == 40)
			{
				MyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				for (int i = 0; i < 41; ++i)
				{
					MoveToEx(hdc, i * 18, 0, nullptr);
					LineTo(hdc, i * 18, 720);
				}
				for (int j = 0; j < 41; ++j)
				{
					MoveToEx(hdc, 0, j * 18, nullptr);
					LineTo(hdc, 720, j * 18);
				}
			}
			else
			{
				MyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				for (int i = 0; i < 51; ++i)
				{
					MoveToEx(hdc, i * 15, 0, nullptr);
					LineTo(hdc, i * 15, 750);
				}
				for (int j = 0; j < 51; ++j)
				{
					MoveToEx(hdc, 0, j * 15, nullptr);
					LineTo(hdc, 750, j * 15);
				}
			}
			MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			for (int i = 0; i < 31; ++i)
			{
				MoveToEx(hdc, i * 26, 0, nullptr);
				LineTo(hdc, i * 26, 780);
			}
			for (int j = 0; j < 31; ++j)
			{
				MoveToEx(hdc, 0, j * 26, nullptr);
				LineTo(hdc, 780, j * 26);
			}
			preBoard = 30;
			break;
		case 'M'://보드칸을 40으로 나눈다
		case 'm':
			if (preBoard == 30)
			{
				MyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				for (int i = 0; i < 31; ++i)
				{
					MoveToEx(hdc, i * 26, 0, nullptr);
					LineTo(hdc, i * 26, 780);
				}
				for (int j = 0; j < 31; ++j)
				{
					MoveToEx(hdc, 0, j * 26, nullptr);
					LineTo(hdc, 780, j * 26);
				}
			}
			else
			{
				MyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				for (int i = 0; i < 51; ++i)
				{
					MoveToEx(hdc, i * 15, 0, nullptr);
					LineTo(hdc, i * 15, 750);
				}
				for (int j = 0; j < 51; ++j)
				{
					MoveToEx(hdc, 0, j * 15, nullptr);
					LineTo(hdc, 750, j * 15);
				}
			}
			MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			for (int i = 0; i < 41; ++i)
			{
				MoveToEx(hdc, i * 18, 0, nullptr);
				LineTo(hdc, i * 18, 720);
			}
			for (int j = 0; j < 41; ++j)
			{
				MoveToEx(hdc, 0, j * 18, nullptr);
				LineTo(hdc, 720, j * 18);
			}
			preBoard = 40;
			break;
		case 'L'://보드칸을 50으로 나눈다
		case 'l':
			if (preBoard == 0 || preBoard == 40)
			{
				MyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				for (int i = 0; i < 41; ++i)
				{
					MoveToEx(hdc, i * 18, 0, nullptr);
					LineTo(hdc, i * 18, 720);
				}
				for (int j = 0; j < 41; ++j)
				{
					MoveToEx(hdc, 0, j * 18, nullptr);
					LineTo(hdc, 720, j * 18);
				}
			}
			else
			{
				MyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				for (int i = 0; i < 31; ++i)
				{
					MoveToEx(hdc, i * 26, 0, nullptr);
					LineTo(hdc, i * 26, 780);
				}
				for (int j = 0; j < 31; ++j)
				{
					MoveToEx(hdc, 0, j * 26, nullptr);
					LineTo(hdc, 780, j * 26);
				}
			}
			MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			for (int i = 0; i < 51; ++i)
			{
				MoveToEx(hdc, i * 15, 0, nullptr);
				LineTo(hdc, i * 15, 750);
			}
			for (int j = 0; j < 51; ++j)
			{
				MoveToEx(hdc, 0, j * 15, nullptr);
				LineTo(hdc, 750, j * 15);
			}
			preBoard = 50;
			break;
		case 'E'://원을 랜덤한 위치에// 색도 랜덤하게
		case 'e':
			if (countPol == 10)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (preBoard == 0 || preBoard == 40)
					Rectangle(hdc, poly3[0].xpos * 18, poly3[0].ypos * 18, (poly3[0].xpos + 1) * 18, (poly3[0].ypos + 1) * 18);
				else if (preBoard == 30)
					Rectangle(hdc, poly3[0].xpos * 26, poly3[0].ypos * 26, (poly3[0].xpos + 1) * 26, (poly3[0].ypos + 1) * 26);
				else if (preBoard == 50)
					Rectangle(hdc, poly3[0].xpos * 15, poly3[0].ypos * 15, (poly3[0].xpos + 1) * 15, (poly3[0].ypos + 1) * 15);
				for (int i = 0; i < 9; ++i)
				{
					poly3[i].xpos = poly3[i + 1].xpos;
					poly3[i].ypos = poly3[i + 1].ypos;
					poly3[i].fir = poly3[i + 1].fir;
					poly3[i].sec = poly3[i + 1].sec;
					poly3[i].thi = poly3[i + 1].thi;
					poly3[i].shape = poly3[i + 1].shape;
				}
				--countPol;
			}
			switch (preBoard)
			{
			case 0:
			case 40:
				poly3[countPol].xpos = mLoc(gen);
				poly3[countPol].ypos = mLoc(gen);
				poly3[countPol].fir = col(gen);
				poly3[countPol].sec = col(gen);
				poly3[countPol].thi = col(gen);
				hbrush = CreateSolidBrush(RGB(poly3[countPol].fir, poly3[countPol].sec, poly3[countPol].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, poly3[countPol].xpos * 18, poly3[countPol].ypos * 18, (poly3[countPol].xpos + 1) * 18, (poly3[countPol].ypos + 1) * 18);
				poly3[countPol].shape = 0;
				++countPol;
				break;
			case 30:
				poly3[countPol].xpos = sLoc(gen);
				poly3[countPol].ypos = sLoc(gen);
				poly3[countPol].fir = col(gen);
				poly3[countPol].sec = col(gen);
				poly3[countPol].thi = col(gen);
				hbrush = CreateSolidBrush(RGB(poly3[countPol].fir, poly3[countPol].sec, poly3[countPol].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, poly3[countPol].xpos * 26, poly3[countPol].ypos * 26, (poly3[countPol].xpos + 1) * 26, (poly3[countPol].ypos + 1) * 26);
				poly3[countPol].shape = 0;
				++countPol;
				break;
			case 50:
				poly3[countPol].xpos = lLoc(gen);
				poly3[countPol].ypos = lLoc(gen);
				poly3[countPol].fir = col(gen);
				poly3[countPol].sec = col(gen);
				poly3[countPol].thi = col(gen);
				hbrush = CreateSolidBrush(RGB(poly3[countPol].fir, poly3[countPol].sec, poly3[countPol].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Ellipse(hdc, poly3[countPol].xpos * 15, poly3[countPol].ypos * 15, (poly3[countPol].xpos + 1) * 15, (poly3[countPol].ypos + 1) * 15);
				poly3[countPol].shape = 0;
				++countPol;
				break;
			}
			break;
		case 'T'://삼각형을 랜덤한 위치에// 색도 랜덤하게
		case 't':
			if (countPol == 10)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (preBoard == 0 || preBoard == 40)
					Rectangle(hdc, poly3[0].xpos * 18, poly3[0].ypos * 18, (poly3[0].xpos + 1) * 18, (poly3[0].ypos + 1) * 18);
				else if (preBoard == 30)
					Rectangle(hdc, poly3[0].xpos * 26, poly3[0].ypos * 26, (poly3[0].xpos + 1) * 26, (poly3[0].ypos + 1) * 26);
				else if (preBoard == 50)
					Rectangle(hdc, poly3[0].xpos * 15, poly3[0].ypos * 15, (poly3[0].xpos + 1) * 15, (poly3[0].ypos + 1) * 15);
				for (int i = 0; i < 9; ++i)
				{
					poly3[i].xpos = poly3[i + 1].xpos;
					poly3[i].ypos = poly3[i + 1].ypos;
					poly3[i].fir = poly3[i + 1].fir;
					poly3[i].sec = poly3[i + 1].sec;
					poly3[i].thi = poly3[i + 1].thi;
					poly3[i].shape = poly3[i + 1].shape;
				}
				--countPol;
			}
			switch (preBoard)
			{
			case 0:
			case 40:
				poly3[countPol].xpos = mLoc(gen);
				poly3[countPol].ypos = mLoc(gen);
				poly3[countPol].fir = col(gen);
				poly3[countPol].sec = col(gen);
				poly3[countPol].thi = col(gen);
				hbrush = CreateSolidBrush(RGB(poly3[countPol].fir, poly3[countPol].sec, poly3[countPol].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				tri[0] = { (poly3[countPol].xpos + 1) * 18, (poly3[countPol].ypos + 1) * 18 };
				tri[1] = { poly3[countPol].xpos * 18, (poly3[countPol].ypos + 1) * 18 };
				tri[2] = { poly3[countPol].xpos * 18 + 9, poly3[countPol].ypos * 18 };
				Polygon(hdc, tri, 3);
				poly3[countPol].shape = 1;
				++countPol;
				break;
			case 30:
				poly3[countPol].xpos = sLoc(gen);
				poly3[countPol].ypos = sLoc(gen);
				poly3[countPol].fir = col(gen);
				poly3[countPol].sec = col(gen);
				poly3[countPol].thi = col(gen);
				hbrush = CreateSolidBrush(RGB(poly3[countPol].fir, poly3[countPol].sec, poly3[countPol].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				tri[0] = { (poly3[countPol].xpos + 1) * 26, (poly3[countPol].ypos + 1) * 26 };
				tri[1] = { poly3[countPol].xpos * 26, (poly3[countPol].ypos + 1) * 26 };
				tri[2] = { poly3[countPol].xpos * 26 + 13, poly3[countPol].ypos * 26 };
				Polygon(hdc, tri, 3);
				poly3[countPol].shape = 1;
				++countPol;
				break;
			case 50:
				poly3[countPol].xpos = mLoc(gen);
				poly3[countPol].ypos = mLoc(gen);
				poly3[countPol].fir = col(gen);
				poly3[countPol].sec = col(gen);
				poly3[countPol].thi = col(gen);
				hbrush = CreateSolidBrush(RGB(poly3[countPol].fir, poly3[countPol].sec, poly3[countPol].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				tri[0] = { (poly3[countPol].xpos + 1) * 15, (poly3[countPol].ypos + 1) * 15 };
				tri[1] = { poly3[countPol].xpos * 15, (poly3[countPol].ypos + 1) * 15 };
				tri[2] = { poly3[countPol].xpos * 15 + 7, poly3[countPol].ypos * 15 };
				Polygon(hdc, tri, 3);
				poly3[countPol].shape = 1;
				++countPol;
				break;
			}
			break;
		case 'R'://사각형을 랜덤한 위치에// 색도 랜덤하게
		case 'r':
			if (countPol == 10)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (preBoard == 0 || preBoard == 40)
					Rectangle(hdc, poly3[0].xpos * 18, poly3[0].ypos * 18, (poly3[0].xpos + 1) * 18, (poly3[0].ypos + 1) * 18);
				else if (preBoard == 30)
					Rectangle(hdc, poly3[0].xpos * 26, poly3[0].ypos * 26, (poly3[0].xpos + 1) * 26, (poly3[0].ypos + 1) * 26);
				else if (preBoard == 50)
					Rectangle(hdc, poly3[0].xpos * 15, poly3[0].ypos * 15, (poly3[0].xpos + 1) * 15, (poly3[0].ypos + 1) * 15);
				for (int i = 0; i < 9; ++i)
				{
					poly3[i].xpos = poly3[i + 1].xpos;
					poly3[i].ypos = poly3[i + 1].ypos;
					poly3[i].fir = poly3[i + 1].fir;
					poly3[i].sec = poly3[i + 1].sec;
					poly3[i].thi = poly3[i + 1].thi;
					poly3[i].shape = poly3[i + 1].shape;
				}
				--countPol;
			}
			switch (preBoard)
			{
			case 0:
			case 40:
				poly3[countPol].xpos = mLoc(gen);
				poly3[countPol].ypos = mLoc(gen);
				poly3[countPol].fir = col(gen);
				poly3[countPol].sec = col(gen);
				poly3[countPol].thi = col(gen);
				hbrush = CreateSolidBrush(RGB(poly3[countPol].fir, poly3[countPol].sec, poly3[countPol].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[countPol].xpos * 18, poly3[countPol].ypos * 18, (poly3[countPol].xpos + 1) * 18, (poly3[countPol].ypos + 1) * 18);
				poly3[countPol].shape = 2;
				++countPol;
				break;
			case 30:
				poly3[countPol].xpos = sLoc(gen);
				poly3[countPol].ypos = sLoc(gen);
				poly3[countPol].fir = col(gen);
				poly3[countPol].sec = col(gen);
				poly3[countPol].thi = col(gen);
				hbrush = CreateSolidBrush(RGB(poly3[countPol].fir, poly3[countPol].sec, poly3[countPol].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[countPol].xpos * 26, poly3[countPol].ypos * 26, (poly3[countPol].xpos + 1) * 26, (poly3[countPol].ypos + 1) * 26);
				poly3[countPol].shape = 2;
				++countPol;
				break;
			case 50:
				poly3[countPol].xpos = lLoc(gen);
				poly3[countPol].ypos = lLoc(gen);
				poly3[countPol].fir = col(gen);
				poly3[countPol].sec = col(gen);
				poly3[countPol].thi = col(gen);
				hbrush = CreateSolidBrush(RGB(poly3[countPol].fir, poly3[countPol].sec, poly3[countPol].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[countPol].xpos * 15, poly3[countPol].ypos * 15, (poly3[countPol].xpos + 1) * 15, (poly3[countPol].ypos + 1) * 15);
				poly3[countPol].shape = 2;
				++countPol;
				break;
			}
			break;
		case 'C'://같은 도형 같은색,다시 누르면 원래 색
		case 'c':
			if (switC == TRUE)
			{
				cirCol = col(gen);
				triCol = col(gen);
				recCol = col(gen);
				for (int i = 0; i < 10; ++i)
				{
					if (poly3[i].shape == 0)
					{
						switch (preBoard)
						{
						case 0:
						case 40:
							hbrush = CreateSolidBrush(RGB(cirCol, triCol, recCol));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Ellipse(hdc, poly3[i].xpos * 18, poly3[i].ypos * 18, (poly3[i].xpos + 1) * 18, (poly3[i].ypos + 1) * 18);
							break;
						case 30:
							hbrush = CreateSolidBrush(RGB(cirCol, triCol, recCol));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Ellipse(hdc, poly3[i].xpos * 26, poly3[i].ypos * 26, (poly3[i].xpos + 1) * 26, (poly3[i].ypos + 1) * 26);
							break;
						case 50:
							hbrush = CreateSolidBrush(RGB(cirCol, triCol, recCol));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Ellipse(hdc, poly3[i].xpos * 15, poly3[i].ypos * 15, (poly3[i].xpos + 1) * 15, (poly3[i].ypos + 1) * 15);
							break;
						}
					}
					else if (poly3[i].shape == 1)
					{
						switch (preBoard)
						{
						case 0:
						case 40:
							hbrush = CreateSolidBrush(RGB(triCol, recCol, cirCol));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							tri[0] = { (poly3[i].xpos + 1) * 18, (poly3[i].ypos + 1) * 18 };
							tri[1] = { poly3[i].xpos * 18, (poly3[i].ypos + 1) * 18 };
							tri[2] = { poly3[i].xpos * 18 + 9, poly3[i].ypos * 18 };
							Polygon(hdc, tri, 3);
							break;
						case 30:
							hbrush = CreateSolidBrush(RGB(triCol, recCol, cirCol));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							tri[0] = { (poly3[i].xpos + 1) * 26, (poly3[i].ypos + 1) * 26 };
							tri[1] = { poly3[i].xpos * 26, (poly3[i].ypos + 1) * 26 };
							tri[2] = { poly3[i].xpos * 26 + 13, poly3[i].ypos * 26 };
							Polygon(hdc, tri, 3);
							break;
						case 50:
							hbrush = CreateSolidBrush(RGB(triCol, recCol, cirCol));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							tri[0] = { (poly3[i].xpos + 1) * 15, (poly3[i].ypos + 1) * 15 };
							tri[1] = { poly3[i].xpos * 15, (poly3[i].ypos + 1) * 15 };
							tri[2] = { poly3[i].xpos * 15 + 15 / 2, poly3[i].ypos * 15 };
							Polygon(hdc, tri, 3);
							break;
						}
					}
					else if (poly3[i].shape == 2)
					{
						switch (preBoard)
						{
						case 0:
						case 40:
							hbrush = CreateSolidBrush(RGB(recCol, cirCol, triCol));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Rectangle(hdc, poly3[i].xpos * 18, poly3[i].ypos * 18, (poly3[i].xpos + 1) * 18, (poly3[i].ypos + 1) * 18);
							break;
						case 30:
							hbrush = CreateSolidBrush(RGB(recCol, cirCol, triCol));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Rectangle(hdc, poly3[i].xpos * 26, poly3[i].ypos * 26, (poly3[i].xpos + 1) * 26, (poly3[i].ypos + 1) * 26);
							break;
						case 50:
							hbrush = CreateSolidBrush(RGB(recCol, cirCol, triCol));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Rectangle(hdc, poly3[i].xpos * 15, poly3[i].ypos * 15, (poly3[i].xpos + 1) * 15, (poly3[i].ypos + 1) * 15);
							break;
						}
					}
				}
				switC = FALSE;
			}
			else
			{
				for (int i = 0; i < 10; ++i)
				{
					if (poly3[i].shape == 0)
					{
						switch (preBoard)
						{
						case 0:
						case 40:
							hbrush = CreateSolidBrush(RGB(poly3[i].fir, poly3[i].sec, poly3[i].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Ellipse(hdc, poly3[i].xpos * 18, poly3[i].ypos * 18, (poly3[i].xpos + 1) * 18, (poly3[i].ypos + 1) * 18);
							break;
						case 30:
							hbrush = CreateSolidBrush(RGB(poly3[i].fir, poly3[i].sec, poly3[i].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Ellipse(hdc, poly3[i].xpos * 26, poly3[i].ypos * 26, (poly3[i].xpos + 1) * 26, (poly3[i].ypos + 1) * 26);
							break;
						case 50:
							hbrush = CreateSolidBrush(RGB(poly3[i].fir, poly3[i].sec, poly3[i].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Ellipse(hdc, poly3[i].xpos * 15, poly3[i].ypos * 15, (poly3[i].xpos + 1) * 15, (poly3[i].ypos + 1) * 15);
							break;
						}
					}
					else if (poly3[i].shape == 1)
					{
						switch (preBoard)
						{
						case 0:
						case 40:
							hbrush = CreateSolidBrush(RGB(poly3[i].fir, poly3[i].sec, poly3[i].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							tri[0] = { (poly3[i].xpos + 1) * 18, (poly3[i].ypos + 1) * 18 };
							tri[1] = { poly3[i].xpos * 18, (poly3[i].ypos + 1) * 18 };
							tri[2] = { poly3[i].xpos * 18 + 9, poly3[i].ypos * 18 };
							Polygon(hdc, tri, 3);
							break;
						case 30:
							hbrush = CreateSolidBrush(RGB(poly3[i].fir, poly3[i].sec, poly3[i].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							tri[0] = { (poly3[i].xpos + 1) * 26, (poly3[i].ypos + 1) * 26 };
							tri[1] = { poly3[i].xpos * 26, (poly3[i].ypos + 1) * 26 };
							tri[2] = { poly3[i].xpos * 26 + 13, poly3[i].ypos * 26 };
							Polygon(hdc, tri, 3);
							break;
						case 50:
							hbrush = CreateSolidBrush(RGB(poly3[i].fir, poly3[i].sec, poly3[i].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							tri[0] = { (poly3[i].xpos + 1) * 15, (poly3[i].ypos + 1) * 15 };
							tri[1] = { poly3[i].xpos * 15, (poly3[i].ypos + 1) * 15 };
							tri[2] = { poly3[i].xpos * 15 + 15 / 2, poly3[i].ypos * 15 };
							Polygon(hdc, tri, 3);
							break;
						}
					}
					else if (poly3[i].shape == 2)
					{
						switch (preBoard)
						{
						case 0:
						case 40:
							hbrush = CreateSolidBrush(RGB(poly3[i].fir, poly3[i].sec, poly3[i].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Rectangle(hdc, poly3[i].xpos * 18, poly3[i].ypos * 18, (poly3[i].xpos + 1) * 18, (poly3[i].ypos + 1) * 18);
							break;
						case 30:
							hbrush = CreateSolidBrush(RGB(poly3[i].fir, poly3[i].sec, poly3[i].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Rectangle(hdc, poly3[i].xpos * 26, poly3[i].ypos * 26, (poly3[i].xpos + 1) * 26, (poly3[i].ypos + 1) * 26);
							break;
						case 50:
							hbrush = CreateSolidBrush(RGB(poly3[i].fir, poly3[i].sec, poly3[i].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Rectangle(hdc, poly3[i].xpos * 15, poly3[i].ypos * 15, (poly3[i].xpos + 1) * 15, (poly3[i].ypos + 1) * 15);
							break;
						}
					}
				}
				switC = TRUE;
			}
			break;
		case 'P'://리셋
		case 'p':
			preBoard = 0;
			countPol = 0;
			cirCol = 0;//012
			triCol = 0;//120
			recCol = 0;//210
			switC = TRUE;
			preChoose = 11;
			InvalidateRgn(hwnd, NULL, TRUE);
			break;
		case 'Q'://이전 도형 출력 후//다음 도형 출력
		case 'q':
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case VK_UP://선택된 도형 이동//가장 자리에 부딪히면 반대편에서 나타난다
			if (preBoard == 40 || preBoard == 0)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				if (poly3[preChoose].ypos == 0)
					poly3[preChoose].ypos = 39;
				else
					poly3[preChoose].ypos -= 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18 };
					tri[1] = { poly3[preChoose].xpos * 18, (poly3[preChoose].ypos + 1) * 18 };
					tri[2] = { poly3[preChoose].xpos * 18 + 9, poly3[preChoose].ypos * 18 };
					Polygon(hdc, tri, 3);
				}
			}
			else if (preBoard == 30)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				if (poly3[preChoose].ypos == 0)
					poly3[preChoose].ypos = 29;
				else
					poly3[preChoose].ypos -= 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26 };
					tri[1] = { poly3[preChoose].xpos * 26, (poly3[preChoose].ypos + 1) * 26 };
					tri[2] = { poly3[preChoose].xpos * 26 + 13, poly3[preChoose].ypos * 26 };
					Polygon(hdc, tri, 3);
				}
			}
			else if (preBoard == 50)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				if (poly3[preChoose].ypos == 0)
					poly3[preChoose].ypos = 49;
				else
					poly3[preChoose].ypos -= 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15 };
					tri[1] = { poly3[preChoose].xpos * 15, (poly3[preChoose].ypos + 1) * 15 };
					tri[2] = { poly3[preChoose].xpos * 15 + 7, poly3[preChoose].ypos * 15 };
					Polygon(hdc, tri, 3);
				}
			}
			break;
		case VK_DOWN:
			if (preBoard == 40 || preBoard == 0)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				if (poly3[preChoose].ypos == 39)
					poly3[preChoose].ypos = 0;
				else
					poly3[preChoose].ypos += 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18 };
					tri[1] = { poly3[preChoose].xpos * 18, (poly3[preChoose].ypos + 1) * 18 };
					tri[2] = { poly3[preChoose].xpos * 18 + 9, poly3[preChoose].ypos * 18 };
					Polygon(hdc, tri, 3);
				}
			}
			else if (preBoard == 30)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				if (poly3[preChoose].ypos == 29)
					poly3[preChoose].ypos = 0;
				else
					poly3[preChoose].ypos += 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26 };
					tri[1] = { poly3[preChoose].xpos * 26, (poly3[preChoose].ypos + 1) * 26 };
					tri[2] = { poly3[preChoose].xpos * 26 + 13, poly3[preChoose].ypos * 26 };
					Polygon(hdc, tri, 3);
				}
			}
			else if (preBoard == 50)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				if (poly3[preChoose].ypos == 49)
					poly3[preChoose].ypos = 0;
				else
					poly3[preChoose].ypos += 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15 };
					tri[1] = { poly3[preChoose].xpos * 15, (poly3[preChoose].ypos + 1) * 15 };
					tri[2] = { poly3[preChoose].xpos * 15 + 7, poly3[preChoose].ypos * 15 };
					Polygon(hdc, tri, 3);
				}
			}
			break;
		case VK_RIGHT:
			if (preBoard == 40 || preBoard == 0)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				if (poly3[preChoose].xpos == 39)
					poly3[preChoose].xpos = 0;
				else
					poly3[preChoose].xpos += 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18 };
					tri[1] = { poly3[preChoose].xpos * 18, (poly3[preChoose].ypos + 1) * 18 };
					tri[2] = { poly3[preChoose].xpos * 18 + 9, poly3[preChoose].ypos * 18 };
					Polygon(hdc, tri, 3);
				}
			}
			else if (preBoard == 30)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				if (poly3[preChoose].xpos == 29)
					poly3[preChoose].xpos = 0;
				else
					poly3[preChoose].xpos += 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26 };
					tri[1] = { poly3[preChoose].xpos * 26, (poly3[preChoose].ypos + 1) * 26 };
					tri[2] = { poly3[preChoose].xpos * 26 + 13, poly3[preChoose].ypos * 26 };
					Polygon(hdc, tri, 3);
				}
			}
			else if (preBoard == 50)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				if (poly3[preChoose].xpos == 49)
					poly3[preChoose].xpos = 0;
				else
					poly3[preChoose].xpos += 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15 };
					tri[1] = { poly3[preChoose].xpos * 15, (poly3[preChoose].ypos + 1) * 15 };
					tri[2] = { poly3[preChoose].xpos * 15 + 7, poly3[preChoose].ypos * 15 };
					Polygon(hdc, tri, 3);
				}
			}
			break;
		case VK_LEFT:
			if (preBoard == 40 || preBoard == 0)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				if (poly3[preChoose].xpos == 0)
					poly3[preChoose].xpos = 39;
				else
					poly3[preChoose].xpos -= 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18 };
					tri[1] = { poly3[preChoose].xpos * 18, (poly3[preChoose].ypos + 1) * 18 };
					tri[2] = { poly3[preChoose].xpos * 18 + 9, poly3[preChoose].ypos * 18 };
					Polygon(hdc, tri, 3);
				}
			}
			else if (preBoard == 30)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				if (poly3[preChoose].xpos == 0)
					poly3[preChoose].xpos = 30;
				poly3[preChoose].xpos -= 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26 };
					tri[1] = { poly3[preChoose].xpos * 26, (poly3[preChoose].ypos + 1) * 26 };
					tri[2] = { poly3[preChoose].xpos * 26 + 13, poly3[preChoose].ypos * 26 };
					Polygon(hdc, tri, 3);
				}
			}
			else if (preBoard == 50)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				if (poly3[preChoose].xpos == 0)
					poly3[preChoose].xpos = 50;
				poly3[preChoose].xpos -= 1;
				hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				if (poly3[preChoose].shape == 0)
					Ellipse(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				else if (poly3[preChoose].shape == 2)
					Rectangle(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				else if (poly3[preChoose].shape == 1)
				{
					tri[0] = { (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15 };
					tri[1] = { poly3[preChoose].xpos * 15, (poly3[preChoose].ypos + 1) * 15 };
					tri[2] = { poly3[preChoose].xpos * 15 + 7, poly3[preChoose].ypos * 15 };
					Polygon(hdc, tri, 3);
				}
			}
			break;
		case VK_DELETE://선택 도형 삭제, 도형 순서 앞으로 당겨진다
			if (preChoose != 11)
			{
				MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				OldPen = (HPEN)SelectObject(hdc, MyPen);
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				if (preBoard == 0 || preBoard == 40)
					Rectangle(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
				else if (preBoard == 30)
					Rectangle(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
				else if (preBoard == 50)
					Rectangle(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
				for (int i = preChoose; i < 9; ++i)
				{
					poly3[i].xpos = poly3[i + 1].xpos;
					poly3[i].ypos = poly3[i + 1].ypos;
					poly3[i].fir = poly3[i + 1].fir;
					poly3[i].sec = poly3[i + 1].sec;
					poly3[i].thi = poly3[i + 1].thi;
					poly3[i].shape = poly3[i + 1].shape;
				}
				--countPol;
			}
			break;
		}
		for (int i = 48; i < 58; ++i)
		{
			if (wParam == i)//도형 번호, 선택된 도형은 둘레에 표시
			{
				if (preBoard == 40 || preBoard == 0)
				{
					if (preChoose != 11)
					{
						if (poly3[preChoose].shape == 0)
						{
							MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
							OldPen = (HPEN)SelectObject(hdc, MyPen);
							hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Ellipse(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
						}
						else if (poly3[preChoose].shape == 1)
						{
							MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
							OldPen = (HPEN)SelectObject(hdc, MyPen);
							hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							tri[0] = { (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18 };
							tri[1] = { poly3[preChoose].xpos * 18, (poly3[preChoose].ypos + 1) * 18 };
							tri[2] = { poly3[preChoose].xpos * 18 + 9, poly3[preChoose].ypos * 18 };
							Polygon(hdc, tri, 3);
						}
						else if (poly3[preChoose].shape == 2)
						{
							MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
							OldPen = (HPEN)SelectObject(hdc, MyPen);
							hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Rectangle(hdc, poly3[preChoose].xpos * 18, poly3[preChoose].ypos * 18, (poly3[preChoose].xpos + 1) * 18, (poly3[preChoose].ypos + 1) * 18);
						}
					}
				}
				else if (preBoard == 30)
				{
					if (preChoose != 11)
					{
						if (poly3[preChoose].shape == 0)
						{
							MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
							OldPen = (HPEN)SelectObject(hdc, MyPen);
							hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Ellipse(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
						}
						else if (poly3[preChoose].shape == 1)
						{
							MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
							OldPen = (HPEN)SelectObject(hdc, MyPen);
							hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							tri[0] = { (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26 };
							tri[1] = { poly3[preChoose].xpos * 26, (poly3[preChoose].ypos + 1) * 26 };
							tri[2] = { poly3[preChoose].xpos * 26 + 13, poly3[preChoose].ypos * 26 };
							Polygon(hdc, tri, 3);
						}
						else if (poly3[preChoose].shape == 2)
						{
							MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
							OldPen = (HPEN)SelectObject(hdc, MyPen);
							hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Rectangle(hdc, poly3[preChoose].xpos * 26, poly3[preChoose].ypos * 26, (poly3[preChoose].xpos + 1) * 26, (poly3[preChoose].ypos + 1) * 26);
						}
					}
				}
				else
				{
					if (preChoose != 11)
					{
						if (poly3[preChoose].shape == 0)
						{
							MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
							OldPen = (HPEN)SelectObject(hdc, MyPen);
							hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Ellipse(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
						}
						else if (poly3[preChoose].shape == 1)
						{
							MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
							OldPen = (HPEN)SelectObject(hdc, MyPen);
							hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							tri[0] = { (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15 };
							tri[1] = { poly3[preChoose].xpos * 15, (poly3[preChoose].ypos + 1) * 15 };
							tri[2] = { poly3[preChoose].xpos * 15 + 7, poly3[preChoose].ypos * 15 };
							Polygon(hdc, tri, 3);
						}
						else if (poly3[preChoose].shape == 2)
						{
							MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
							OldPen = (HPEN)SelectObject(hdc, MyPen);
							hbrush = CreateSolidBrush(RGB(poly3[preChoose].fir, poly3[preChoose].sec, poly3[preChoose].thi));
							oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
							Rectangle(hdc, poly3[preChoose].xpos * 15, poly3[preChoose].ypos * 15, (poly3[preChoose].xpos + 1) * 15, (poly3[preChoose].ypos + 1) * 15);
						}
					}
				}
				if (poly3[i - 48].shape == 0)//원
				{
					switch (preBoard)
					{
					case 0:
					case 40:
						preChoose = i - 48;
						MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
						OldPen = (HPEN)SelectObject(hdc, MyPen);
						hbrush = CreateSolidBrush(RGB(poly3[i - 48].fir, poly3[i - 48].sec, poly3[i - 48].thi));
						oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
						Ellipse(hdc, poly3[i - 48].xpos * 18, poly3[i - 48].ypos * 18, (poly3[i - 48].xpos + 1) * 18, (poly3[i - 48].ypos + 1) * 18);
						break;
					case 30:
						preChoose = i - 48;
						MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
						OldPen = (HPEN)SelectObject(hdc, MyPen);
						hbrush = CreateSolidBrush(RGB(poly3[i - 48].fir, poly3[i - 48].sec, poly3[i - 48].thi));
						oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
						Ellipse(hdc, poly3[i - 48].xpos * 26, poly3[i - 48].ypos * 26, (poly3[i - 48].xpos + 1) * 26, (poly3[i - 48].ypos + 1) * 26);
						break;
					case 50:
						preChoose = i - 48;
						MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
						OldPen = (HPEN)SelectObject(hdc, MyPen);
						hbrush = CreateSolidBrush(RGB(poly3[i - 48].fir, poly3[i - 48].sec, poly3[i - 48].thi));
						oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
						Ellipse(hdc, poly3[i - 48].xpos * 15, poly3[i - 48].ypos * 15, (poly3[i - 48].xpos + 1) * 15, (poly3[i - 48].ypos + 1) * 15);
						break;
					}
				}
				else if (poly3[i - 48].shape == 1)//삼
				{
					switch (preBoard)
					{
					case 0:
					case 40:
						preChoose = i - 48;
						MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
						OldPen = (HPEN)SelectObject(hdc, MyPen);
						hbrush = CreateSolidBrush(RGB(poly3[i - 48].fir, poly3[i - 48].sec, poly3[i - 48].thi));
						oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
						tri[0] = { (poly3[i - 48].xpos + 1) * 18, (poly3[i - 48].ypos + 1) * 18 };
						tri[1] = { poly3[i - 48].xpos * 18, (poly3[i - 48].ypos + 1) * 18 };
						tri[2] = { poly3[i - 48].xpos * 18 + 9, poly3[i - 48].ypos * 18 };
						Polygon(hdc, tri, 3);
						break;
					case 30:
						preChoose = i - 48;
						MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
						OldPen = (HPEN)SelectObject(hdc, MyPen);
						hbrush = CreateSolidBrush(RGB(poly3[i - 48].fir, poly3[i - 48].sec, poly3[i - 48].thi));
						oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
						tri[0] = { (poly3[i - 48].xpos + 1) * 26, (poly3[i - 48].ypos + 1) * 26 };
						tri[1] = { poly3[i - 48].xpos * 26, (poly3[i - 48].ypos + 1) * 26 };
						tri[2] = { poly3[i - 48].xpos * 26 + 13, poly3[i - 48].ypos * 26 };
						Polygon(hdc, tri, 3);
						break;
					case 50:
						preChoose = i - 48;
						MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
						OldPen = (HPEN)SelectObject(hdc, MyPen);
						hbrush = CreateSolidBrush(RGB(poly3[i - 48].fir, poly3[i - 48].sec, poly3[i - 48].thi));
						oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
						tri[0] = { (poly3[i - 48].xpos + 1) * 15, (poly3[i - 48].ypos + 1) * 15 };
						tri[1] = { poly3[i - 48].xpos * 15, (poly3[i - 48].ypos + 1) * 15 };
						tri[2] = { poly3[i - 48].xpos * 15 + 7, poly3[i - 48].ypos * 15 };
						Polygon(hdc, tri, 3);
						break;
					}
				}
				else if (poly3[i - 48].shape == 2)//사
				{
					switch (preBoard)
					{
					case 0:
					case 40:
						preChoose = i - 48;
						MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
						OldPen = (HPEN)SelectObject(hdc, MyPen);
						hbrush = CreateSolidBrush(RGB(poly3[i - 48].fir, poly3[i - 48].sec, poly3[i - 48].thi));
						oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
						Rectangle(hdc, poly3[i - 48].xpos * 18, poly3[i - 48].ypos * 18, (poly3[i - 48].xpos + 1) * 18, (poly3[i - 48].ypos + 1) * 18);
						break;
					case 30:
						preChoose = i - 48;
						MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
						OldPen = (HPEN)SelectObject(hdc, MyPen);
						hbrush = CreateSolidBrush(RGB(poly3[i - 48].fir, poly3[i - 48].sec, poly3[i - 48].thi));
						oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
						Rectangle(hdc, poly3[i - 48].xpos * 26, poly3[i - 48].ypos * 26, (poly3[i - 48].xpos + 1) * 26, (poly3[i - 48].ypos + 1) * 26);
						break;
					case 50:
						preChoose = i - 48;
						MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
						OldPen = (HPEN)SelectObject(hdc, MyPen);
						hbrush = CreateSolidBrush(RGB(poly3[i - 48].fir, poly3[i - 48].sec, poly3[i - 48].thi));
						oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
						Rectangle(hdc, poly3[i - 48].xpos * 15, poly3[i - 48].ypos * 15, (poly3[i - 48].xpos + 1) * 15, (poly3[i - 48].ypos + 1) * 15);
						break;
					}
				}
				break;
			}
		}
		ReleaseDC(hwnd, hdc);
		/*SelectObject(hdc, oldbrush);
		DeleteObject(hbrush);*/
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
