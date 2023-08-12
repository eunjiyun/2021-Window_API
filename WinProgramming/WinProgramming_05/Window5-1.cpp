#include<Windows.h>
#include<TCHAR.H>
#include<iostream>
#include<cstdlib>
#include"resource.h"
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
using namespace std;
class magnifier
{
public:
	int leftX, topY, rightX, bottomY;
	int whereX, whereY, hor, ver;
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = _T("Window Class Name");

	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("windows program 5-3"),
		WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_HSCROLL | WS_VSCROLL,
		0,
		0,
		1280,//1121 649
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
HDC hdc, memdc, memdc2, memdc11;
PAINTSTRUCT ps;
HBITMAP hBitmap1, hBitmap2, hBitmap3, oldBit, oldBit2, oldBit3;
magnifier wantToSee[2];
magnifier clon = { wantToSee[1].leftX,wantToSee[1].topY, wantToSee[1].rightX, wantToSee[1].bottomY, wantToSee[1].whereX, wantToSee[1].whereY, wantToSee[1].hor, wantToSee[1].ver };

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	static RECT rectView;
	static int whatPicture = 2;
	static bool click = FALSE;
	static int leftX, topY, rightX, bottomY, oldRightX, oldBottomY;
	static bool drag = FALSE;
	static int count = -1;
	static int expansion = 0;
	static bool moving = FALSE;
	static int tmpWhereX, tmpWhereY, tmpHor, tmpVer, tmpLeftX, tmpTopY, tmpRightX, tmpBottomY;
	static bool dupl = FALSE;
	static bool wholeSize = FALSE;
	static bool selectArea = FALSE;
	static RECT rect[2];
	static bool LRinversion = FALSE;
	static bool UDinversion = FALSE;
	static int location = 0;
	static int prevLoca = 0;
	static bool bounce = FALSE;
	static bool pressX = FALSE;
	static bool pressx = FALSE;

	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		//hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		//hBitmap2 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));

		//memdc = CreateCompatibleDC(hdc);
		//memdc2 = CreateCompatibleDC(memdc);
		//hBitmap3 = CreateCompatibleBitmap(hdc, 1280, 800);

		//oldBit3=(HBITMAP)SelectObject(memdc, hBitmap3);
		//oldBit2 = (HBITMAP)SelectObject(memdc2, hBitmap2);
		//oldBit = (HBITMAP)SelectObject(memdc2, hBitmap1);

		//if (whatPicture == 1)
		//	StretchBlt(memdc, 0, 0, 1280, 800, memdc2, 0, 0, 640, 426, SRCCOPY);//640   426 
		//else if (whatPicture == 2)
		//{

		//	StretchBlt(memdc, 0, 0, 1280, 800, memdc2, 0, 0, 1121, 649, SRCCOPY);//1121 649
		//}

		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_PICTURE_1)//그림1
		{
			whatPicture = 1;
			InvalidateRect(hwnd, NULL, FALSE);
		}
		else if (LOWORD(wParam) == ID_PICTURE_2)//그림2
		{
			whatPicture = 2;
			InvalidateRect(hwnd, NULL, FALSE);
		}
		else if (LOWORD(wParam) == ID_MAC_3)//돋보기1: 돋보기 내의 그림이 1.2배 확대
		{
			expansion = 2;
			InvalidateRect(hwnd, NULL, FALSE);
		}
		else if (LOWORD(wParam) == ID_MAC_4)//돋보기2: 돋보기 내의 그림이 1.4배 확대
		{
			expansion = 4;
			InvalidateRect(hwnd, NULL, FALSE);
		}
		else if (LOWORD(wParam) == ID_SIZE_ORIGIN)//o 돋보기 내의 그림이 원래 크기로 
		{
			expansion = 0;
			InvalidateRect(hwnd, NULL, FALSE);
		}
		else if (LOWORD(wParam) == ID_WHATYOUWANT_DUP)//c 돋보기 내의 그림이 복사
		{
			dupl = TRUE;
			tmpLeftX = wantToSee[count].leftX;
			tmpTopY = wantToSee[count].topY;
			tmpRightX = wantToSee[count].rightX;
			tmpBottomY = wantToSee[count].bottomY;
			tmpWhereX = wantToSee[count].whereX;
			tmpWhereY = wantToSee[count].whereY;
			tmpHor = wantToSee[count].hor;
			tmpVer = wantToSee[count].ver;
		}
		else if (LOWORD(wParam) == ID_WHATYOUWANT_PAS)//p (0,0)을 좌측상단으로 같은 크기로 붙여넣기 
		{
			wantToSee[++count].leftX = 0;
			wantToSee[count].topY = 0;
			wantToSee[count].rightX = tmpRightX - tmpLeftX;
			wantToSee[count].bottomY = tmpBottomY - tmpTopY;
			wantToSee[count].whereX = tmpWhereX;
			wantToSee[count].whereY = tmpWhereY;
			wantToSee[count].hor = tmpHor;
			wantToSee[count].ver = tmpVer;
			rect[count] = { 0,0,wantToSee[count].rightX ,wantToSee[count].bottomY };
			InvalidateRect(hwnd, NULL, FALSE);
		}
		else if (LOWORD(wParam) == ID_SIZE_WHOLE)//f 돋보기 내의 그림을 화면 전체로 붙여넣기//다시 누르면 원래 크기
		{
			expansion = 3;
			if (wholeSize == FALSE)
				wholeSize = TRUE;
			else
				wholeSize = FALSE;
			InvalidateRect(hwnd, NULL, FALSE);
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
			/// <returns></returns>    메뉴도 만들기
		case '1'://그림1
			whatPicture = 1;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case '2'://그림2
			whatPicture = 2;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case '3'://돋보기1: 돋보기 내의 그림이 1.2배 확대
			expansion = 2;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case '4'://돋보기2: 돋보기 내의 그림이 1.4배 확대
			expansion = 4;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 0x4F://o 돋보기 내의 그림이 원래 크기로 
			expansion = 0;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 0x43://c 돋보기 내의 그림이 복사
			dupl = TRUE;
			tmpLeftX = wantToSee[count].leftX;
			tmpTopY = wantToSee[count].topY;
			tmpRightX = wantToSee[count].rightX;
			tmpBottomY = wantToSee[count].bottomY;
			tmpWhereX = wantToSee[count].whereX;
			tmpWhereY = wantToSee[count].whereY;
			tmpHor = wantToSee[count].hor;
			tmpVer = wantToSee[count].ver;
			break;
		case 0x50://p (0,0)을 좌측상단으로 같은 크기로 붙여넣기 
			wantToSee[++count].leftX = 0;
			wantToSee[count].topY = 0;
			wantToSee[count].rightX = tmpRightX - tmpLeftX;
			wantToSee[count].bottomY = tmpBottomY - tmpTopY;
			wantToSee[count].whereX = tmpWhereX;
			wantToSee[count].whereY = tmpWhereY;
			wantToSee[count].hor = tmpHor;
			wantToSee[count].ver = tmpVer;
			rect[count] = { 0,0,wantToSee[count].rightX ,wantToSee[count].bottomY };
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 0x46://f 돋보기 내의 그림을 화면 전체로 붙여넣기//다시 누르면 원래 크기
			expansion = 3;
			if (wholeSize == FALSE)
				wholeSize = TRUE;
			else
				wholeSize = FALSE;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
			/// ///////////////////////////////////////////////////////////////////////////////////
		case VK_UP://돋보기 위치 이동
			wantToSee[0].topY -= 100;
			wantToSee[0].bottomY -= 100;
			if (whatPicture == 2)
				wantToSee[0].whereY -= 80;
			else if (whatPicture == 1)
				wantToSee[0].whereY -= 50;
			rect[0] = { wantToSee[0].leftX,wantToSee[0].topY,wantToSee[0].rightX,wantToSee[0].bottomY };
			moving = TRUE;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case VK_DOWN:
			wantToSee[0].topY += 100;
			wantToSee[0].bottomY += 100;
			if (whatPicture == 2)
				wantToSee[0].whereY += 80;
			else if (whatPicture == 1)
				wantToSee[0].whereY += 50;
			rect[0] = { wantToSee[0].leftX,wantToSee[0].topY,wantToSee[0].rightX,wantToSee[0].bottomY };
			moving = TRUE;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case VK_LEFT:
			wantToSee[0].leftX -= 100;
			wantToSee[0].rightX -= 100;
			if (whatPicture == 2)
				wantToSee[0].whereX -= 80;
			else if (whatPicture == 1)
				wantToSee[0].whereX -= 50;
			rect[0] = { wantToSee[0].leftX,wantToSee[0].topY,wantToSee[0].rightX,wantToSee[0].bottomY };
			moving = TRUE;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case VK_RIGHT:
			wantToSee[0].leftX += 100;
			wantToSee[0].rightX += 100;
			if (whatPicture == 2)
				wantToSee[0].whereX += 80;
			else if (whatPicture == 1)
				wantToSee[0].whereX += 50;
			rect[0] = { wantToSee[0].leftX,wantToSee[0].topY,wantToSee[0].rightX,wantToSee[0].bottomY };
			moving = TRUE;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 0x4D://m 돋보기 사각형 작아져
			wantToSee[0].rightX *= 0.9;
			wantToSee[0].bottomY *= 0.9;
			wantToSee[1].rightX = wantToSee[0].rightX - wantToSee[0].leftX;
			wantToSee[1].bottomY = wantToSee[0].bottomY - wantToSee[0].topY;

			rect[0].right = wantToSee[0].rightX;
			rect[0].bottom = wantToSee[0].bottomY;
			rect[1].right = wantToSee[1].rightX;
			rect[1].bottom = wantToSee[1].bottomY;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 0x4E://n 돋보기 사각형 커져
			wantToSee[0].rightX *= 1.1;
			wantToSee[0].bottomY *= 1.1;
			wantToSee[1].rightX = wantToSee[0].rightX - wantToSee[0].leftX;
			wantToSee[1].bottomY = wantToSee[0].bottomY - wantToSee[0].topY;

			rect[0].right = wantToSee[0].rightX;
			rect[0].bottom = wantToSee[0].bottomY;
			rect[1].right = wantToSee[1].rightX;
			rect[1].bottom = wantToSee[1].bottomY;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 0x48://h 붙여넣기한 곳의 그림이 좌우 반전
			LRinversion = TRUE;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 0x56://v 붙여넣기한 곳의 그림이 상하 반전
			UDinversion = TRUE;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 0x41://a 돋보기 사각형이 튕긴다//사각형내의 그림도 같이 튕긴다
			if (bounce == FALSE)
			{
				bounce = TRUE;
				SetTimer(hwnd, 1, 70, NULL);//신호등
			}
			else
			{
				bounce = FALSE;
				KillTimer(hwnd, 1);
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 0x52://r 리셋//돋보기 사각형이 없어지고 다시 돋보기 사각형을 입력 받아야 해
			for (int i = 0; i < 2; ++i)
			{
				rect[i] = { 0,0,0,0 };
				wantToSee[i].leftX = 0;
				wantToSee[i].topY = 0;
				wantToSee[i].rightX = 0;
				wantToSee[i].bottomY = 0;
				wantToSee[i].whereX = 0;
				wantToSee[i].whereY = 0;
				wantToSee[i].hor = 0;
				wantToSee[i].ver = 0;
			}
			click = FALSE;
			drag = FALSE;
			count = -1;
			expansion = 0;
			moving = FALSE;
			location = 0;
			prevLoca = 0;
			dupl = FALSE;
			wholeSize = FALSE;
			selectArea = FALSE;
			LRinversion = FALSE;
			UDinversion = FALSE;
			location = 0;
			prevLoca = 0;
			bounce = FALSE;
			KillTimer(hwnd, 1);
			InvalidateRect(hwnd, NULL, FALSE);/////////????
			break;
		case 0x51://q 프로그램 종료
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_CHAR:
		if (wParam == 'x')//붙여넣기한 그림이 오른쪽 
		{
			pressx = TRUE;
			if (whatPicture == 2)//1121, 649
			{
				wantToSee[1].leftX += 10;
				wantToSee[1].hor -= 8.76;
				wantToSee[1].whereX += 8.76;
			}
			else if (whatPicture == 1)//640, 426
			{
				wantToSee[1].leftX += 10;
				wantToSee[1].hor -= 5;
				wantToSee[1].whereX += 5;
			}
			clon.leftX = 0;
			clon.rightX = wantToSee[1].leftX - 100;
			clon.whereX = wantToSee[0].whereX + wantToSee[1].hor;
			clon.hor = wantToSee[0].hor - wantToSee[1].hor;

			if (whatPicture == 2)
			{
				if (abs(clon.rightX - tmpRightX) - 800 < 10)
				{
					clon = { 0,0, wantToSee[1].leftX, wantToSee[1].bottomY, tmpWhereX,tmpWhereY, tmpHor,tmpVer };
					wantToSee[1].leftX = 0;
					wantToSee[1].hor = wantToSee[0].hor;
					wantToSee[1].whereX = tmpWhereX;
				}
			}
			else
			{
				if (abs(clon.rightX - tmpRightX) - 834 < 10)
				{
					clon = { 0,0, wantToSee[1].leftX, wantToSee[1].bottomY, tmpWhereX,tmpWhereY, tmpHor,tmpVer };
					wantToSee[1].leftX = 0;
					wantToSee[1].hor = wantToSee[0].hor;
					wantToSee[1].whereX = tmpWhereX;
				}
			}
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == 'X')//붙여넣기한 그림이 왼쪽 
		{
			pressX = TRUE;
			if (whatPicture == 2)//1121, 649
			{
				wantToSee[1].rightX -= 10;
				wantToSee[1].hor -= 8.76;
				wantToSee[1].whereX += 8.76;
			}
			else if (whatPicture == 1)//640, 426
			{
				wantToSee[1].rightX -= 10;
				wantToSee[1].hor -= 5;
				wantToSee[1].whereX += 5;

			}
			clon.leftX = wantToSee[1].rightX;
			clon.hor = wantToSee[0].hor - wantToSee[1].hor;
			clon.rightX = wantToSee[0].rightX - wantToSee[0].leftX - wantToSee[1].rightX;
			if (whatPicture == 2)
			{
				if (abs(clon.rightX - tmpRightX) - 803 < 10)
				{
					clon = { wantToSee[1].leftX,0, wantToSee[1].rightX, wantToSee[1].bottomY, tmpWhereX,tmpWhereY, tmpHor,tmpVer };
					wantToSee[1].rightX = wantToSee[0].rightX - wantToSee[0].leftX;
					wantToSee[1].hor = wantToSee[0].hor;
					wantToSee[1].whereX = tmpWhereX;
				}
			}
			else
			{
				if (abs(clon.rightX - tmpRightX) - 834 < 10)// && pressX == TRUE)834
				{
					clon = { wantToSee[1].leftX,0, wantToSee[1].rightX, wantToSee[1].bottomY, tmpWhereX,tmpWhereY, tmpHor,tmpVer };
					wantToSee[1].rightX = wantToSee[0].rightX - wantToSee[0].leftX;
					wantToSee[1].hor = wantToSee[0].hor;
					wantToSee[1].whereX = tmpWhereX;
				}
			}
			InvalidateRect(hwnd, NULL, false);
		}
		break;
	case WM_LBUTTONDOWN:
		count = 0;
		oldRightX = wantToSee[count].leftX = LOWORD(lParam);
		oldBottomY = wantToSee[count].topY = HIWORD(lParam);
		drag = TRUE;
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		if (drag)
		{
			SetROP2(hdc, R2_XORPEN);
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
			wantToSee[count].rightX = LOWORD(lParam);
			wantToSee[count].bottomY = HIWORD(lParam);

			Rectangle(hdc, wantToSee[count].leftX, wantToSee[count].topY, oldRightX, oldBottomY);
			Rectangle(hdc, wantToSee[count].leftX, wantToSee[count].topY, wantToSee[count].rightX, wantToSee[count].bottomY);

			oldRightX = wantToSee[count].rightX;
			oldBottomY = wantToSee[count].bottomY;
		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_LBUTTONUP:
		drag = FALSE;
		selectArea = TRUE;
		if (expansion == 0)
			InvalidateRect(hwnd, NULL, FALSE);
		rect[count] = { wantToSee[count].leftX, wantToSee[count].topY, wantToSee[count].rightX, wantToSee[count].bottomY };
		break;
	case WM_TIMER:
		if (wParam == 1)
		{
			if (wantToSee[0].rightX > rectView.right)
			{
				prevLoca = location;
				location = 1;
			}
			if (wantToSee[0].topY < rectView.top)//2행 벽돌
			{
				prevLoca = location;
				location = 2;
			}
			if (wantToSee[0].leftX < rectView.left)
			{
				prevLoca = location;
				location = 3;
			}
			if (wantToSee[0].bottomY > rectView.bottom)
			{
				prevLoca = location;
				location = 4;
			}
			switch (location)
			{
			case 0:
				wantToSee[0].leftX += 40;
				wantToSee[0].rightX += 40;
				wantToSee[0].topY -= 20;
				wantToSee[0].bottomY -= 20;
				rect[0] = { wantToSee[0].leftX,wantToSee[0].topY,wantToSee[0].rightX,wantToSee[0].bottomY };
				break;
			case 1:
				wantToSee[0].leftX -= 40;
				wantToSee[0].rightX -= 40;
				if (prevLoca == 2 || prevLoca == 3)
				{
					wantToSee[0].topY += 20;
					wantToSee[0].bottomY += 20;
				}
				else
				{
					wantToSee[0].topY -= 20;
					wantToSee[0].bottomY -= 20;
				}
				rect[0] = { wantToSee[0].leftX,wantToSee[0].topY,wantToSee[0].rightX,wantToSee[0].bottomY };
				break;
			case 2:
				wantToSee[0].topY += 20;
				wantToSee[0].bottomY += 20;
				if (prevLoca == 3)
				{
					wantToSee[0].leftX += 40;
					wantToSee[0].rightX += 40;
				}
				else
				{
					wantToSee[0].leftX -= 40;
					wantToSee[0].rightX -= 40;
				}
				rect[0] = { wantToSee[0].leftX,wantToSee[0].topY,wantToSee[0].rightX,wantToSee[0].bottomY };
				break;
			case 3:
				wantToSee[0].leftX += 40;
				wantToSee[0].rightX += 40;
				if (prevLoca == 1)
				{
					wantToSee[0].topY -= 20;
					wantToSee[0].bottomY -= 20;
				}
				else
				{
					wantToSee[0].topY += 20;
					wantToSee[0].bottomY += 20;
				}
				rect[0] = { wantToSee[0].leftX,wantToSee[0].topY,wantToSee[0].rightX,wantToSee[0].bottomY };
				break;
			case 4:
				wantToSee[0].leftX += 40;
				wantToSee[0].rightX += 40;
				wantToSee[0].topY -= 20;
				wantToSee[0].bottomY -= 20;
				rect[0] = { wantToSee[0].leftX,wantToSee[0].topY,wantToSee[0].rightX,wantToSee[0].bottomY };
				break;
			default:
				break;
			}
			InvalidateRect(hwnd, NULL, FALSE);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBitmap1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		hBitmap2 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));

		memdc = CreateCompatibleDC(hdc);
		memdc2 = CreateCompatibleDC(memdc);


		hBitmap3 = CreateCompatibleBitmap(hdc, 1280, 800);//1280 800
		oldBit3 = (HBITMAP)SelectObject(memdc, hBitmap3);

		if (whatPicture == 1)
			StretchBlt(memdc, 0, 0, 1280, 800, memdc2, 0, 0, 640, 426, SRCCOPY);//640   426 
		else if (whatPicture == 2)
			StretchBlt(memdc, 0, 0, 1280, 800, memdc2, 0, 0, 1280, 800, SRCCOPY);//1121 649
		if (whatPicture == 1)
			StretchBlt(memdc, 0, 0, 1280, 800, memdc2, 0, 0, 640, 426, SRCCOPY);//640   426 
		else
			StretchBlt(memdc, 0, 0, 1280, 800, memdc2, 0, 0, 1121, 649, SRCCOPY);//1121 649

		if (whatPicture == 1)
		{
			oldBit = (HBITMAP)SelectObject(memdc2, hBitmap1);
			StretchBlt(memdc, 0, 0, rectView.right, rectView.bottom, memdc2, 0, 0, 640, 426, SRCCOPY);
		}
		else
		{
			oldBit2 = (HBITMAP)SelectObject(memdc2, hBitmap2);
			StretchBlt(memdc, 0, 0, rectView.right, rectView.bottom, memdc2, 0, 0, 1127, 649, SRCCOPY);
		}
		if (moving == TRUE)
		{
			if (whatPicture == 2)
			{
				if (expansion == 2)
				{
					wantToSee[1].whereX = wantToSee[0].leftX * 0.9 + 0.09 * (wantToSee[0].rightX - wantToSee[0].leftX);
					wantToSee[1].whereY = wantToSee[0].topY * 0.8 + 0.08 * (wantToSee[0].bottomY - wantToSee[0].topY);
					wantToSee[1].hor = 0.7 * (wantToSee[0].rightX - wantToSee[0].leftX);
					wantToSee[1].ver = 0.6 * (wantToSee[0].bottomY - wantToSee[0].topY);
				}
				else if (expansion == 4)
				{
					wantToSee[1].whereX = wantToSee[0].leftX * 0.9 + 0.12 * (wantToSee[0].rightX - wantToSee[0].leftX);
					wantToSee[1].whereY = 0.8 * wantToSee[0].topY + 0.11 * (wantToSee[0].bottomY - wantToSee[0].topY);//0.12
					wantToSee[1].hor = 0.6 * (wantToSee[0].rightX - wantToSee[0].leftX);
					wantToSee[1].ver = 0.5 * (wantToSee[0].bottomY - wantToSee[0].topY);//0.6
				}
				else if (expansion == 0)
				{
					wantToSee[1].whereX = wantToSee[0].leftX * 0.9;
					wantToSee[1].whereY = wantToSee[0].topY * 0.8;
					wantToSee[1].hor = 0.9 * (wantToSee[0].rightX - wantToSee[0].leftX);
					wantToSee[1].ver = 0.8 * (wantToSee[0].bottomY - wantToSee[0].topY);
				}
			}
			else if (whatPicture == 1)
			{
				if (expansion == 2)
				{
					wantToSee[1].whereX = wantToSee[0].leftX * 0.5 + 0.05 * (wantToSee[0].rightX - wantToSee[0].leftX);
					wantToSee[1].whereY = 0.5 * wantToSee[0].topY + 0.05 * (wantToSee[0].bottomY - wantToSee[0].topY);
					wantToSee[1].hor = 0.4 * (wantToSee[0].rightX - wantToSee[0].leftX);
					wantToSee[1].ver = 0.4 * (wantToSee[0].bottomY - wantToSee[0].topY);
				}
				else if (expansion == 4)
				{
					wantToSee[1].whereX = wantToSee[0].leftX * 0.9 + 0.12 * (wantToSee[0].rightX - wantToSee[0].leftX);
					wantToSee[1].whereY = 0.8 * wantToSee[0].topY + 0.11 * (wantToSee[0].bottomY - wantToSee[0].topY);//0.12
					wantToSee[1].hor = 0.6 * (wantToSee[0].rightX - wantToSee[0].leftX);
					wantToSee[1].ver = 0.5 * (wantToSee[0].bottomY - wantToSee[0].topY);//0.6
				}
				else if (expansion == 0)
				{
					wantToSee[1].whereX = wantToSee[0].leftX * 0.5;
					wantToSee[1].whereY = wantToSee[0].topY * 0.5;
					wantToSee[1].hor = 0.5 * (wantToSee[0].rightX - wantToSee[0].leftX);
					wantToSee[1].ver = 0.5 * (wantToSee[0].bottomY - wantToSee[0].topY);
				}
			}
			SetROP2(memdc, R2_XORPEN);
			SelectObject(memdc, (HPEN)GetStockObject(WHITE_PEN));
			Rectangle(memdc, wantToSee[count].leftX, wantToSee[count].topY, wantToSee[count].rightX, wantToSee[count].bottomY);
		}
		if (selectArea == TRUE)
		{
			FrameRect(memdc, &rect[count], (HBRUSH)GetStockObject(BLACK_PEN));
			SetROP2(memdc, R2_XORPEN);
			SelectObject(memdc, (HPEN)GetStockObject(WHITE_PEN));
			if (whatPicture == 2)//1121 649
			{
				if (expansion == 2)
				{
					if (dupl == FALSE)
					{
						wantToSee[count].whereX = wantToSee[count].leftX * 0.9 + 0.09 * (wantToSee[count].rightX - wantToSee[count].leftX);
						wantToSee[count].whereY = wantToSee[count].topY * 0.8 + 0.08 * (wantToSee[count].bottomY - wantToSee[count].topY);
					}
					wantToSee[count].hor = 0.7 * (wantToSee[count].rightX - wantToSee[count].leftX);
					wantToSee[count].ver = 0.6 * (wantToSee[count].bottomY - wantToSee[count].topY);
				}
				else if (expansion == 4)
				{
					if (dupl == FALSE)
					{
						wantToSee[count].whereX = wantToSee[count].leftX * 0.9 + 0.12 * (wantToSee[count].rightX - wantToSee[count].leftX);
						wantToSee[count].whereY = 0.8 * wantToSee[count].topY + 0.11 * (wantToSee[count].bottomY - wantToSee[count].topY);//0.12
					}
					wantToSee[count].hor = 0.6 * (wantToSee[count].rightX - wantToSee[count].leftX);
					wantToSee[count].ver = 0.5 * (wantToSee[count].bottomY - wantToSee[count].topY);//0.6
				}
				else if (expansion == 0)//1121 649
				{
					if (dupl == FALSE)
					{
						wantToSee[count].whereX = wantToSee[count].leftX * 0.9;
						wantToSee[count].whereY = wantToSee[count].topY * 0.8;
					}
					wantToSee[count].hor = 0.9 * (wantToSee[count].rightX - wantToSee[count].leftX);
					wantToSee[count].ver = 0.8 * (wantToSee[count].bottomY - wantToSee[count].topY);
				}
				else if (expansion == 3)
				{
					if (wholeSize == TRUE)
					{
						tmpLeftX = wantToSee[count].leftX;
						tmpTopY = wantToSee[count].topY;
						tmpRightX = wantToSee[count].rightX;
						tmpBottomY = wantToSee[count].bottomY;

						wantToSee[count].leftX = 0;
						wantToSee[count].topY = 0;
						wantToSee[count].rightX = rectView.right;
						wantToSee[count].bottomY = rectView.bottom;
					}
					else
					{
						wantToSee[count].leftX = tmpLeftX;
						wantToSee[count].topY = tmpTopY;
						wantToSee[count].rightX = tmpRightX;
						wantToSee[count].bottomY = tmpBottomY;
					}
				}
			}
			else if (whatPicture == 1)//640   426
			{
				if (expansion == 2)
				{
					if (dupl == FALSE)
					{
						wantToSee[count].whereX = wantToSee[count].leftX * 0.5 + 0.05 * (wantToSee[count].rightX - wantToSee[count].leftX);
						wantToSee[count].whereY = 0.5 * wantToSee[count].topY + 0.05 * (wantToSee[count].bottomY - wantToSee[count].topY);
					}
					wantToSee[count].hor = 0.4 * (wantToSee[count].rightX - wantToSee[count].leftX);
					wantToSee[count].ver = 0.4 * (wantToSee[count].bottomY - wantToSee[count].topY);
				}
				else if (expansion == 4)
				{
					if (dupl == FALSE)
					{
						wantToSee[count].whereX = wantToSee[count].leftX * 0.5 + 0.075 * (wantToSee[count].rightX - wantToSee[count].leftX);
						wantToSee[count].whereY = 0.5 * wantToSee[count].topY + 0.075 * (wantToSee[count].bottomY - wantToSee[count].topY);
					}
					wantToSee[count].hor = 0.35 * (wantToSee[count].rightX - wantToSee[count].leftX);
					wantToSee[count].ver = 0.35 * (wantToSee[count].bottomY - wantToSee[count].topY);
				}
				else if (expansion == 0)
				{
					if (dupl == FALSE)
					{
						wantToSee[count].whereX = wantToSee[count].leftX * 0.5;
						wantToSee[count].whereY = wantToSee[count].topY * 0.5;
					}
					wantToSee[count].hor = 0.5 * (wantToSee[count].rightX - wantToSee[count].leftX);
					wantToSee[count].ver = 0.5 * (wantToSee[count].bottomY - wantToSee[count].topY);
				}
				else if (expansion == 3)
				{
					if (wholeSize == TRUE)
					{
						tmpLeftX = wantToSee[count].leftX;
						tmpTopY = wantToSee[count].topY;
						tmpRightX = wantToSee[count].rightX;
						tmpBottomY = wantToSee[count].bottomY;

						wantToSee[count].leftX = 0;
						wantToSee[count].topY = 0;
						wantToSee[count].rightX = rectView.right;
						wantToSee[count].bottomY = rectView.bottom;
					}
					else
					{
						wantToSee[count].leftX = tmpLeftX;
						wantToSee[count].topY = tmpTopY;
						wantToSee[count].rightX = tmpRightX;
						wantToSee[count].bottomY = tmpBottomY;
					}
				}
			}
			if (pressX == TRUE || pressx == TRUE)
				StretchBlt(memdc, clon.leftX, clon.topY, clon.rightX, clon.bottomY, memdc2, clon.whereX, clon.whereY, clon.hor, clon.ver, SRCCOPY);

			for (int i = 0; i <= count; ++i)
			{
				FrameRect(memdc, &rect[count], (HBRUSH)GetStockObject(BLACK_PEN));
				if (expansion == 0 && dupl == FALSE)
				{
				}
				else
				{
					if (expansion == 0 && i == 0)
						continue;
					else
					{
						if (LRinversion == TRUE && UDinversion == TRUE && i == 1)
							StretchBlt(memdc, wantToSee[i].rightX, wantToSee[i].bottomY, wantToSee[i].leftX - wantToSee[i].rightX, wantToSee[i].topY - wantToSee[i].bottomY, memdc2, wantToSee[i].whereX, wantToSee[i].whereY, wantToSee[i].hor, wantToSee[i].ver, SRCCOPY);
						else if (LRinversion == TRUE && i == 1)
							StretchBlt(memdc, wantToSee[i].rightX, wantToSee[i].topY, wantToSee[i].leftX - wantToSee[i].rightX, wantToSee[i].bottomY - wantToSee[i].topY, memdc2, wantToSee[i].whereX, wantToSee[i].whereY, wantToSee[i].hor, wantToSee[i].ver, SRCCOPY);
						else if (UDinversion == TRUE && i == 1)
							StretchBlt(memdc, wantToSee[i].leftX, wantToSee[i].bottomY, wantToSee[i].rightX - wantToSee[i].leftX, wantToSee[i].topY - wantToSee[i].bottomY, memdc2, wantToSee[i].whereX, wantToSee[i].whereY, wantToSee[i].hor, wantToSee[i].ver, SRCCOPY);
						else
						{
							StretchBlt(memdc, wantToSee[i].leftX, wantToSee[i].topY, wantToSee[i].rightX - wantToSee[i].leftX, wantToSee[i].bottomY - wantToSee[i].topY, memdc2, wantToSee[i].whereX, wantToSee[i].whereY, wantToSee[i].hor, wantToSee[i].ver, SRCCOPY);
						}
					}
				}
			}
		}
		if (pressx == FALSE)
			clon = { wantToSee[1].leftX,0, wantToSee[1].rightX, wantToSee[1].bottomY, tmpWhereX,tmpWhereY, tmpHor,tmpVer };
		else
			clon = { 0,0, wantToSee[1].leftX, wantToSee[1].bottomY, tmpWhereX,tmpWhereY, tmpHor,tmpVer };

		if (whatPicture == 1)
			StretchBlt(hdc, 0, 0, 1280, 800, memdc, 0, 0, 1280, 800, SRCCOPY);//640   426 
		else if (whatPicture == 2)
			StretchBlt(hdc, 0, 0, 1280, 800, memdc, 0, 0, 1280, 800, SRCCOPY);//1121 649
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		DeleteDC(memdc2);
		DeleteObject(hBitmap1);
		DeleteObject(hBitmap2);
		DeleteObject(hBitmap3);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
