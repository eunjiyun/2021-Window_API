#include<Windows.h>
#include<random>
#include<TCHAR.H>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> col(0, 255);
//#ifdef _DEBUG
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif
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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("windows program 3-2"),
		WS_SYSMENU,
		0,
		0,
		1200,
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
struct brick
{
	int xpos = 80;
	int ypos = 0;
};
brick crush0[10] = { {80,0},{180,0},{280,0},{380,0},{480,0},{580,0},{680,0},{780,0},{880,0},{980,0} };
brick crush1[10] = { {80,20},{180,20},{280,20},{380,20},{480,20},{580,20},{680,20},{780,20},{880,20},{980,20} };
brick crush2[10] = { {80,40},{180,40},{280,40},{380,40},{480,40},{580,40},{680,40},{780,40},{880,40},{980,40} };
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hbrush, oldbrush;
	static int cirx = 0;
	static int ciry = 0;
	static int rex = 545;
	static int rey = 730;
	static RECT rectView;
	static int location = 0;
	static int prevLoca = 0;
	int mx = 0;
	int my = 0;
	bool flag = FALSE;
	static int fir2 = 255;
	static int sec2 = 255;
	static int thi2 = 0;
	static int fir1 = 255;
	static int sec1 = 255;
	static int thi1 = 0;
	static int fir0 = 255;
	static int sec0 = 255;
	static int thi0 = 0;
	static bool check2 = FALSE;
	static bool check1 = FALSE;
	static bool check0 = FALSE;
	static int stop = TRUE;
	static int speed = 175;
	static int tmpi0 = 15;
	static int tmpi1 = 15;
	static int tmpi2 = 15;

	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		cirx = 505; ciry = 630;
		SetTimer(hwnd, 2, 350, NULL);
		SetTimer(hwnd, 3, 1, NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hbrush = CreateSolidBrush(RGB(fir0, sec0, thi0));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		for (int i = 0; i < 10; ++i)
			Rectangle(hdc, crush0[i].xpos, crush0[i].ypos, crush0[i].xpos + 100, crush0[i].ypos + 20);

		hbrush = CreateSolidBrush(RGB(fir1, sec1, thi1));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		for (int i = 0; i < 10; ++i)
			Rectangle(hdc, crush1[i].xpos, crush1[i].ypos, crush1[i].xpos + 100, crush1[i].ypos + 20);

		hbrush = CreateSolidBrush(RGB(fir2, sec2, thi2));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		for (int i = 0; i < 10; ++i)
			Rectangle(hdc, crush2[i].xpos, crush2[i].ypos, crush2[i].xpos + 100, crush2[i].ypos + 20);

		hbrush = CreateSolidBrush(RGB(255, 255, 0));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Rectangle(hdc, rex - 165, rey - 20, rex + 165, rey + 20);

		hbrush = CreateSolidBrush(RGB(0, 0, 255));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Ellipse(hdc, cirx, ciry, cirx + 80, ciry + 80);

		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'S':
		case 's':
			//공튀기기 랜덤좌우 대각선으로
			SetTimer(hwnd, 1, speed, NULL);
			break;
		case 'P':
		case 'p':
			//스탑 다시시작
			if (stop == TRUE)
			{
				KillTimer(hwnd, 1);
				KillTimer(hwnd, 2);
				--stop;
			}
			else
			{
				SetTimer(hwnd, 1, speed, NULL);
				SetTimer(hwnd, 2, 350, NULL);
				++stop;
			}
			break;
		case VK_OEM_PLUS:
			//이동속도증가
			speed /= 2;
			KillTimer(hwnd, 1);
			SetTimer(hwnd, 1, speed, NULL);
			break;
		case VK_OEM_MINUS:
			//	//이동속도 감소
			speed *= 2;
			KillTimer(hwnd, 1);
			SetTimer(hwnd, 1, speed, NULL);
			break;
		case 'N':
		case 'n':
			//게임 리셋
			InvalidateRgn(hwnd, NULL, TRUE);
			KillTimer(hwnd, 1);
			rex = 545;
			rey = 730;
			cirx = rex - 40;
			ciry = rey - 100;
			location = 0;
			prevLoca = 0;
			flag = FALSE;
			fir2 = 255;
			sec2 = 255;
			thi2 = 0;
			fir1 = 255;
			sec1 = 255;
			thi1 = 0;
			fir0 = 255;
			sec0 = 255;
			thi0 = 0;
			check2 = FALSE;
			check1 = FALSE;
			check0 = FALSE;
			stop = TRUE;
			speed = 175;
			tmpi0 = 15;
			tmpi1 = 15;
			tmpi2 = 15;

			for (int i = 0; i < 10; ++i)
			{
				crush0[i].xpos = 80 + i * 100;
				crush0[i].ypos = 0;
			}
			for (int i = 0; i < 10; ++i)
			{
				crush1[i].xpos = 80 + i * 100;
				crush1[i].ypos = 20;
			}
			for (int i = 0; i < 10; ++i)
			{
				crush2[i].xpos = 80 + i * 100;
				crush2[i].ypos = 40;
			}
			break;
		case 'Q':
		case 'q':
			//프로그램 종료
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (mx < rex + 165 && mx > rex - 165 && my < rey + 20 && my > rey - 20)
		{
			flag = TRUE;
			goto hoho;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
	hoho:
		if (flag == TRUE)
		{
			rex = mx;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONUP:
		InvalidateRect(hwnd, NULL, TRUE);
		flag = FALSE;
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (cirx + 80 > rectView.right)
			{
				prevLoca = location;
				location = 1;
			}
			if (ciry < 60)//2행 벽돌
			{
				for (int i = 0; i < 10; ++i)
				{
					if (crush2[i].xpos < cirx && crush2[i].xpos + 100>cirx && crush2[i].ypos == 40 || crush2[i].xpos < cirx + 80 && crush2[i].xpos + 100>cirx + 80 && crush2[i].ypos == 40)
					{
						if (check2 == FALSE)
						{
							fir2 = col(gen);
							sec2 = col(gen);
							thi2 = col(gen);
						}
						check2 = TRUE;
						tmpi2 = i;
						prevLoca = location;
						location = 2;
					}
				}
			}
			if (ciry < 40)//1행 벽돌
			{
				for (int i = 0; i < 10; ++i)
				{
					if (crush1[i].xpos < cirx && crush1[i].xpos + 100>cirx && crush1[i].ypos == 20 || crush1[i].xpos < cirx + 80 && crush1[i].xpos + 100>cirx + 80 && crush1[i].ypos == 20)
					{
						if (check1 == FALSE)
						{
							fir1 = col(gen);
							sec1 = col(gen);
							thi1 = col(gen);
						}
						check1 = TRUE;
						tmpi1 = i;
						prevLoca = location;
						location = 2;
					}
				}
			}
			if (ciry < 20)//0행 벽돌
			{
				for (int i = 0; i < 10; ++i)
				{
					if (crush0[i].xpos < cirx && crush0[i].xpos + 100>cirx && crush0[i].ypos == 0 || crush0[i].xpos < cirx + 80 && crush0[i].xpos + 100>cirx + 80 && crush0[i].ypos == 0)
					{
						if (check0 == FALSE)
						{
							fir0 = col(gen);
							sec0 = col(gen);
							thi0 = col(gen);
						}
						check0 = TRUE;
						tmpi0 = i;
						prevLoca = location;
						location = 2;
					}
				}
			}
			if (ciry < rectView.top)//천장 빈곳
			{
				prevLoca = location;
				location = 2;
			}
			if (cirx < rectView.left)
			{
				prevLoca = location;
				location = 3;
			}
			if (ciry + 80 > rectView.bottom)
			{
				prevLoca = location;
				location = 4;
			}
			if (ciry + 80 > rey - 20 && cirx + 80 < rex + 165 && cirx > rex - 165)
			{
				prevLoca = location;
				location = 0;
			}
			if (ciry > 900)
			{
				cirx = rex;
				ciry = rey - 100;
				prevLoca = location;
				location = 0;
			}
			switch (location)
			{
			case 0:
				cirx += 40;
				ciry -= 20;
				break;
			case 1:
				cirx -= 40;
				if (prevLoca == 2 || prevLoca == 3)
					ciry += 20;
				else
					ciry -= 20;
				break;
			case 2:
				ciry += 20;
				if (prevLoca == 3)
					cirx += 40;
				else
					cirx -= 40;
				break;
			case 3:
				cirx += 40;
				if (prevLoca == 1)
					ciry -= 20;
				else
					ciry += 20;
				break;
			case 4:
				ciry += 100;
				break;
			default:
				break;
			}
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 2:
			if (crush0[0].xpos <= rectView.left)
			{
				crush0[0].xpos += 80;
				crush1[0].xpos += 80;
				crush2[0].xpos += 80;
			}
			else
			{
				crush0[0].xpos -= 80;
				crush1[0].xpos -= 80;
				crush2[0].xpos -= 80;
			}
			if (crush0[9].xpos + 100 > rectView.right)
			{
				crush0[9].xpos -= 120;
				crush1[9].xpos -= 120;
				crush2[9].xpos -= 120;
			}
			else
			{
				crush0[9].xpos += 120;
				crush1[9].xpos += 120;
				crush2[9].xpos += 120;
			}
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 3:
			if (tmpi2 != 15)
				crush2[tmpi2].ypos += 20;
			if (crush2[tmpi2].ypos > 800)
				tmpi2 = 15;

			if (tmpi1 != 15)
				crush1[tmpi1].ypos += 20;
			if (crush1[tmpi1].ypos > 800)
				tmpi1 = 15;

			if (tmpi0 != 15)
				crush0[tmpi0].ypos += 20;
			if (crush0[tmpi0].ypos > 800)
				tmpi0 = 15;
			break;
		}
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		KillTimer(hwnd, 2);
		KillTimer(hwnd, 3);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
