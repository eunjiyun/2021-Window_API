#include<Windows.h>
#include<TCHAR.H>
#include<iostream>
#include"resource.h"
#include<cmath>
#pragma comment(lib, "msimg32.lib")
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
using namespace std;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void animation(HDC hdc, HDC memdc, HWND hwnd);
BOOL CALLBACK DialogProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
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
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = _T("Window Class Name");
    RegisterClass(&WndClass);
    hwnd = CreateWindow(_T("Window Class Name"),
        _T("windows program 6-1"),
        WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_HSCROLL | WS_VSCROLL,
        0,
        0,
        1440,
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
class color
{
public:
    int fir = 0;
    int sec = 0;
    int thi = 0;
    COLORREF whatColor = RGB(fir, sec, thi);
};
class cir
{
public:
    int leftX, topY, rightX, bottomY;
};
class range
{
public:
    int min, max, min2, max2, min3, max3, min4, max4, min5, max5;
    int plusX, plusY, plusY2, plusY3, plusY4, plusY5;
};
HDC hdc, memdc;
PAINTSTRUCT ps;
float fx = -720;
float fy = 0;            // 싸인 곡선
float amplitude = 160;    // 진폭
int draw = 0;
color graph;
bool circle = FALSE;
bool circleMove = TRUE;
cir wantToMove[2];
int iDis = 100;
static int mx, my;
static TCHAR command_line[30] = L"mx: ";
static TCHAR s[5];
static int i = 0;
bool moveX = FALSE;
bool moveY = FALSE;
double gradient = 1;
int zigPlusY = 0;
bool little = FALSE;
int Count = 0;
/*for (int f = -720; f < -480; f++)
                   {
                      fx = (float)f;
                      fy = -(float)f;
                      SetPixel(memdc, (int)fx + 720, (int)fy - 240, graph.whatColor);
                   }
                   for (int f = -480; f < -160; f++)
                   {
                      fx = (float)f;
                      fy = (float)f - 160;
                      SetPixel(memdc, (int)fx + 720, (int)fy + 880, graph.whatColor);
                   }
                   for (int f = -160; f < 160; f++)
                   {
                      fx = (float)f;
                      fy = -(float)f;
                      SetPixel(memdc, (int)fx + 720, (int)fy + 400, graph.whatColor);
                   }
                   for (int f = 160; f < 480; f++)
                   {
                      fx = (float)f;
                      fy = (float)f - 160;
                      SetPixel(memdc, (int)fx + 720, (int)fy + 240, graph.whatColor);
                   }
                   for (int f = 480; f < 720; f++)
                   {
                      fx = (float)f;
                      fy = -(float)f + 480;
                      SetPixel(memdc, (int)fx + 720, (int)fy + 560, graph.whatColor);
                   }*/
range angular[4] = { {-720,720,0,0,0,0,0,0,0,0,720,400} ,
    {-720,-480,-480,-160,-160,160,160,480,480,720,720,-240,880,400,240,560} , {0,6.2,0,0,0,0,0,0,0,0, 620, 400}  , {-720,720} };
bool up = FALSE;
bool decreaseLine = TRUE;
bool expansionY = FALSE;
bool rise = FALSE;
bool firChange = TRUE;
int turn = 0;
int f = -720;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
    WPARAM wParam, LPARAM lParam)
{
    static RECT rectView;
    switch (iMsg)
    {
    case WM_CREATE:
        GetClientRect(hwnd, &rectView);
        SetTimer(hwnd, 1, 100, NULL);
        SetTimer(hwnd, 2, 100, NULL);
        SetTimer(hwnd, 3, 100, NULL);
        SetTimer(hwnd, 4, 100, NULL);
        break;
    case WM_KEYDOWN:
        if (wParam == 0x51)//q 프로그램 종료
            PostQuitMessage(0);
        break;
    case WM_MOUSEMOVE:
        mx = LOWORD(lParam);
        my = HIWORD(lParam);
        break;
    case WM_LBUTTONDOWN:
        DialogBox(hInst, MAKEINTRESOURCE(101), hwnd, (DLGPROC)DialogProc);
        break;
    case WM_TIMER:
        switch (wParam)
        {
        case 1://sin
            if (circleMove == TRUE)
            {
                if (draw == 1)
                {
                    if (wantToMove[0].rightX > rectView.right)
                        wantToMove[0] = { -50,350,50,450 };
                    wantToMove[0].topY = (float)sin((wantToMove[0].leftX + 50) * 3.141592 / 180.0) * amplitude + 400 - 50;
                    wantToMove[0].bottomY = (float)sin((wantToMove[0].leftX + 50) * 3.141592 / 180.0) * amplitude + 400 + 50;
                    if (moveX == FALSE)
                    {
                        /*   wantToMove[0].topY = (float)sin((wantToMove[0].leftX + 50) * 3.141592 / 180.0) * amplitude + 400 - 50;
                           wantToMove[0].bottomY = (float)sin((wantToMove[0].leftX + 50) * 3.141592 / 180.0) * amplitude + 400 + 50;*/
                        wantToMove[0].leftX += 10;
                        wantToMove[0].rightX += 10;
                    }
                }
            }
            if (moveX == TRUE)
            {
                angular[0].min += 10;
                angular[0].max += 10;
                angular[0].plusX -= 10;
            }
            if (moveY == TRUE)
            {
                if (amplitude == 0)
                    expansionY = TRUE;
                if (wantToMove[0].topY < rectView.top)
                    expansionY = FALSE;
                if (expansionY == FALSE)
                    amplitude -= 10;
                else
                    amplitude += 10;
            }
            InvalidateRect(hwnd, NULL, false);
            break;
        case 2://zigzag
            if (circleMove == TRUE)
            {
                if (draw == 2)
                {
                    //if (wantToMove[0].rightX > rectView.right)
                    //    wantToMove[0] = { -50,430,50,530 };
                    //if (wantToMove[0].leftX + 50 >= 0 && wantToMove[0].leftX + 50 < 240)//1
                    //{
                    //    wantToMove[0].topY = -((int)wantToMove[0].leftX + 50) - 240 - 50;
                    //    wantToMove[0].bottomY = -((int)wantToMove[0].leftX + 50) - 240 + 50;
                    //}
                    //else if (wantToMove[0].leftX + 50 >= 240 && wantToMove[0].leftX + 50 < 560)//2
                    //{
                    //    wantToMove[0].topY = ((int)wantToMove[0].leftX + 50 - 160) + 880 - 50;
                    //    wantToMove[0].bottomY = ((int)wantToMove[0].leftX + 50-160) +880 + 50;
                    //}
                    //else if (wantToMove[0].leftX + 50 >= 560 && wantToMove[0].leftX + 50 < 880)//3
                    //{
                    //    wantToMove[0].topY = -((int)wantToMove[0].leftX + 50) +400 - 50;
                    //    wantToMove[0].bottomY = -((int)wantToMove[0].leftX + 50) +400 + 50;
                    //}
                    //else if (wantToMove[0].leftX + 50 >= 880 && wantToMove[0].leftX + 50 < 1200)//4
                    //{
                    //    wantToMove[0].topY = ((int)wantToMove[0].leftX + 50 - 160) + 240 - 50;
                    //    wantToMove[0].bottomY = ((int)wantToMove[0].leftX + 50 - 160) + 240 + 50;
                    //}
                    //else if (wantToMove[0].leftX + 50 >= 1200 && wantToMove[0].leftX + 50 < 1440)//5
                    //{
                    //    wantToMove[0].topY = -((int)wantToMove[0].leftX + 50) +1040 - 50;
                    //    wantToMove[0].bottomY = -((int)wantToMove[0].leftX + 50) +1040 + 50;
                    //}
                 /*   cout << "leftx: " << wantToMove[0].leftX << endl;
                    cout << "rightx: " << wantToMove[0].rightX << endl;
                    cout << "topy: " << wantToMove[0].topY << endl;
                    cout << "bottomy: " << wantToMove[0].bottomY << endl;*/
                    /* wantToMove[0].topY = (float)sin((wantToMove[0].leftX + 50) * 3.141592 / 180.0) * amplitude + 400 - 50;
                     wantToMove[0].bottomY = (float)sin((wantToMove[0].leftX + 50) * 3.141592 / 180.0) * amplitude + 400 + 50;*/
                     /*for (int f = -720; f < -480; f++)
                     {
                        fx = (float)f;
                        fy = -(float)f;
                        SetPixel(memdc, (int)fx + 720, (int)fy - 240, graph.whatColor);
                     }
                     for (int f = -480; f < -160; f++)
                     {
                        fx = (float)f;
                        fy = (float)f - 160;
                        SetPixel(memdc, (int)fx + 720, (int)fy + 880, graph.whatColor);
                     }
                     for (int f = -160; f < 160; f++)
                     {
                        fx = (float)f;
                        fy = -(float)f;
                        SetPixel(memdc, (int)fx + 720, (int)fy + 400, graph.whatColor);
                     }
                     for (int f = 160; f < 480; f++)
                     {
                        fx = (float)f;
                        fy = (float)f - 160;
                        SetPixel(memdc, (int)fx + 720, (int)fy + 240, graph.whatColor);
                     }
                     for (int f = 480; f < 720; f++)
                     {
                        fx = (float)f;
                        fy = -(float)f + 480;
                        SetPixel(memdc, (int)fx + 720, (int)fy + 560, graph.whatColor);
                     }*/
                     //if (moveX == FALSE)
                     //{
                     //    /*   wantToMove[0].topY = (float)sin((wantToMove[0].leftX + 50) * 3.141592 / 180.0) * amplitude + 400 - 50;
                     //       wantToMove[0].bottomY = (float)sin((wantToMove[0].leftX + 50) * 3.141592 / 180.0) * amplitude + 400 + 50;*/
                     //    wantToMove[0].leftX += 10;
                     //    wantToMove[0].rightX += 10;
                     //}
                }
            }
            if (moveX == TRUE)
            {
                angular[1].min -= 10;
                angular[1].max -= 10;
                angular[1].min2 -= 10;
                angular[1].max2 -= 10;
                angular[1].min3 -= 10;
                angular[1].max3 -= 10;
                angular[1].min4 -= 10;
                angular[1].max4 -= 10;
                angular[1].min5 -= 10;
                angular[1].max5 -= 10;
                angular[1].plusX -= 10;
                zigPlusY += 10;
                if (angular[1].max5 == 0)// < rectView.left)
                {
                    angular[1] = { -720, -480, -480, -160, -160, 160, 160, 480, 480, 720, 720, -240, 880, 400, 240, 560 };
                    zigPlusY = 0;
                }
            }
            if (moveY == TRUE)
            {
                /* if (amplitude == 0)
                     expansionY = TRUE;
                 if (wantToMove[0].topY < rectView.top)
                     expansionY = FALSE;
                 if (expansionY == FALSE)
                     amplitude -= 10;
                 else
                     amplitude += 10;*/
                     /* angular[1].min += 10;
                      angular[1].max += 10;
                      angular[1].min2 += 10;
                      angular[1].max2 += 10;
                      angular[1].min3 += 10;
                      angular[1].max3 += 10;
                      angular[1].min4 += 10;
                      angular[1].max4 += 10;
                      angular[1].min5 += 10;
                      angular[1].max5 += 10;*/
                      //angular[1].plusX -= 10;


                if ((Count / 45) % 2 == 0)
                {
                    gradient -= 0.1;
                    ++Count;
                }
                else
                {
                    gradient += 0.1;
                    ++Count;
                }
                /* if (gradient ==4.5)
                     little == TRUE;
                 if (gradient == 1)
                     little == FALSE;*/
                     //zigPlusY =
                    // cout << "타?: " << gradient << endl;
                cout << little << endl;

            }
            InvalidateRect(hwnd, NULL, false);
            break;
        case 3://spring
           /*MoveToEx(memdc, cos(0) * iDis + 620, 400 + sin(0) * iDis, nullptr);
           for (int n = 0; n < 11; ++n)
           {
              for (float fAngle = 0; fAngle < 6.2; fAngle += 0.1)
              {
                 LineTo(memdc, iX + cos(fAngle) * iDis, iY + sin(fAngle) * iDis);
                 iX += 1;
              }
           }*/
           //if (moveX == TRUE)
           //{
           //   angular[0].min += 0.01;
           //   angular[0].max += 0.01;
           //   angular[1].plusX -= 10;
           //   //iX -= 10;
           //}
           //if (moveY == TRUE)
           //{
           //   if (amplitude == 0)
           //      expansionY = TRUE;
           //   if (wantToMove[0].topY < rectView.top)
           //      expansionY = FALSE;
           //   if (expansionY == FALSE)
           //      amplitude -= 10;
           //   else
           //      amplitude += 10;
           //}
           //if(done3==TRUE)
            InvalidateRect(hwnd, NULL, false);
            break;
        case 4://doubleLine
            if (circleMove == TRUE)
            {
                if (wantToMove[1].rightX > rectView.right)
                {
                    if (moveY == TRUE || moveX == TRUE)
                    {
                        wantToMove[0] = { 0,(int)(fy + 150),100,(int)(fy + 250) };
                        wantToMove[1] = { 0,(int)(fy + 550),100,(int)(fy + 650) };
                    }
                }
                wantToMove[0].leftX += 10;
                wantToMove[0].rightX += 10;
                wantToMove[1].leftX += 10;
                wantToMove[1].rightX += 10;
            }
            if (moveX == TRUE)
            {
                if (angular[3].min == angular[3].max)
                    decreaseLine = FALSE;
                if (angular[3].min == -720)
                    decreaseLine = TRUE;
                if (decreaseLine == TRUE)
                {
                    angular[3].min += 10;
                    angular[3].max -= 10;
                }
                else
                {
                    angular[3].min -= 10;
                    angular[3].max += 10;
                }
            }
            if (moveY == TRUE)
            {
                if (fy - 50 < rectView.top)
                    up = FALSE;
                if (wantToMove[1].bottomY > rectView.bottom)
                    up = TRUE;
                if (up == FALSE)
                {
                    fy += 10;
                    wantToMove[0].topY += 10;
                    wantToMove[0].bottomY += 10;
                    wantToMove[1].topY += 10;
                    wantToMove[1].bottomY += 10;
                }
                else
                {
                    fy -= 10;
                    wantToMove[0].topY -= 10;
                    wantToMove[0].bottomY -= 10;
                    wantToMove[1].topY -= 10;
                    wantToMove[1].bottomY -= 10;
                }
            }
            break;
        }
        InvalidateRect(hwnd, NULL, false);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        animation(hdc, memdc, hwnd);
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        DeleteDC(memdc);
        KillTimer(hwnd, 1);
        KillTimer(hwnd, 2);
        KillTimer(hwnd, 3);
        KillTimer(hwnd, 4);
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
BOOL CALLBACK DialogProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
    case WM_INITDIALOG:
        return 1;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case  1001://sin
            draw = 1;
            break;
        case  1002://zigzag
            draw = 2;
            break;
        case  1003://spring
            draw = 3;
            break;
        case  1004://doubleLine
            draw = 4;
            break;
        case  1005://r
            graph.fir = 255;
            break;
        case  1006://g
            graph.sec = 255;
            break;
        case  1007://b
            graph.thi = 255;
            break;
        case  1008://reverse
            graph.fir = 255 - graph.fir;
            graph.sec = 255 - graph.sec;
            graph.thi = 255 - graph.thi;
            break;
        case  1010://moveX
            moveX = TRUE;
            if (draw == 4)
            {
                wantToMove[0] = { 0,(int)(fy + 150),100,(int)(fy + 250) };
                wantToMove[1] = { 0,(int)(fy + 550),100,(int)(fy + 650) };
            }
            break;
        case  1011://moveY
            moveY = TRUE;
            if (draw == 4)
            {
                wantToMove[0] = { 0,(int)(fy - 50),100,(int)(fy + 50) };
                wantToMove[1] = { 0,(int)(fy + 350),100,(int)(fy + 450) };
            }
            break;
        case  1012://stop
            circleMove = FALSE;
            moveY = FALSE;
            moveX = FALSE;
            break;
        case  1013://reset
            draw = 5;
            circle = FALSE;
            circleMove = FALSE;
            break;
        case  1014://circleAnimation
            circle = TRUE;
            switch (draw)
            {
            case 1:
                wantToMove[0] = { -50,350,50,450 };
                break;
            case 2:
                wantToMove[0] = { -50,350,50,450 };
                break;
            case 3:
                break;
            case 4:
                wantToMove[0] = { 0,(int)(fy + 150),100,(int)(fy + 250) };
                wantToMove[1] = { 0,(int)(fy + 550),100,(int)(fy + 650) };
                break;
            }
            break;
        case IDOK://모든걸 리셋하고
            MessageBox(hDlg, L"test", L"test", MB_OK);
            break;
        case IDCANCEL:
            EndDialog(hDlg, 0);
            break;
        }
        break;
    }
    return 0;
}
void animation(HDC hdc, HDC memdc, HWND hwnd)
{
    HDC memdc2;
    HBITMAP hBit, hBit2, oldBit;
    memdc = CreateCompatibleDC(hdc);
    memdc2 = CreateCompatibleDC(memdc);
    hBit = CreateCompatibleBitmap(hdc, 1440, 800);
    oldBit = (HBITMAP)SelectObject(memdc, hBit);
    hBit2 = LoadBitmap(hInst, MAKEINTRESOURCE(104));
    (HBITMAP)SelectObject(memdc2, hBit2);
    HPEN hpen, oldpen;
    graph.whatColor = RGB(graph.fir, graph.sec, graph.thi);
    MoveToEx(memdc2, 720, 0, nullptr);
    LineTo(memdc2, 720, 800);
    MoveToEx(memdc2, 0, 400, nullptr);
    LineTo(memdc2, 1440, 400);
    hpen = CreatePen(PS_SOLID, 3, graph.whatColor);
    oldpen = (HPEN)SelectObject(memdc, hpen);
    TextOut(memdc2, 0, 0, L"mx: ", 4);
    wsprintf(s, L"%d ", mx);
    for (i = 0; i < 5; ++i)
    {
        if (s[i] == '\\0')
            break;
    }
    for (int j = 0; j <= i; ++j)
        TextOut(memdc2, 40, 0, s, 4);
    TextOut(memdc2, 80, 0, L"my: ", 4);
    wsprintf(s, L"%d ", my);
    for (i = 0; i < 5; ++i)
    {
        if (s[i] == '\\0')
            break;
    }
    for (int j = 0; j <= i; ++j)
        TextOut(memdc2, 120, 0, s, 3);
    if (circle == TRUE)
    {
        TextOut(memdc2, 160, 0, L" | ", 3);
        wsprintf(s, L"%d ", wantToMove[0].leftX + 50);
        TextOut(memdc2, 200, 0, s, 4);
    }
    StretchBlt(memdc, 0, 0, 1440, 800, memdc2, 0, 0, 1440, 800, SRCCOPY);//900 675
    switch (draw)
    {
    case 5:
        draw = 0;
        fy = 0;
        moveX = FALSE;
        moveY = FALSE;
        angular[0] = { -720,720,720,400 };
        angular[1] = { -720,720 };
        angular[2] = { -720,720 };
        angular[3] = { -720,720 };
        InvalidateRect(hwnd, NULL, FALSE);
        break;
    case 1://sin
        for (int f = angular[0].min; f < angular[0].max; ++f)
        {
            fx = (float)f;
            fy = (float)sin(f * 3.141592 / 180.0) * amplitude;
            SetPixel(memdc, (int)fx + angular[0].plusX, (int)fy + angular[0].plusY, graph.whatColor);
        }
        break;
    case 2://zigzag
        for (int f = angular[1].min; f < angular[1].max; f++)
        {
            fx = (float)f;
            fy = -gradient * (float)f;
            SetPixel(memdc, (int)fx + angular[1].plusX, (int)fy - 240 - zigPlusY, graph.whatColor);
            // cout << gradient << endl;
            if (gradient == 4.5)
                little == TRUE;
            if (gradient == 1)
                little == FALSE;
        }
        for (int f = angular[1].min2; f < angular[1].max2; f++)
        {
            fx = (float)f;
            fy = gradient * (float)f - 160;
            SetPixel(memdc, (int)fx + angular[1].plusX, (int)fy + 880 + zigPlusY, graph.whatColor);
            if (gradient == 4.5)
                little == TRUE;
            if (gradient == 1)
                little == FALSE;
        }
        for (int f = angular[1].min3; f < angular[1].max3; f++)
        {
            fx = (float)f;
            fy = -gradient * (float)f;
            SetPixel(memdc, (int)fx + angular[1].plusX, (int)fy + 400 - zigPlusY, graph.whatColor);
            if (gradient == 4.5)
                little == TRUE;
            if (gradient == 1)
                little == FALSE;
        }
        for (int f = angular[1].min4; f < angular[1].max4; f++)
        {
            fx = (float)f;
            fy = gradient * (float)f - 160;
            SetPixel(memdc, (int)fx + angular[1].plusX, (int)fy + 240 + zigPlusY, graph.whatColor);
            if (gradient == 4.5)
                little == TRUE;
            if (gradient == 1)
                little == FALSE;
        }
        for (int f = angular[1].min5; f < angular[1].max5; f++)
        {
            fx = (float)f;
            fy = -gradient * (float)f + 480;
            SetPixel(memdc, (int)fx + angular[1].plusX, (int)fy + 560 - zigPlusY, graph.whatColor);
            if (gradient == 4.5)
                little == TRUE;
            if (gradient == 1)
                little == FALSE;
        }
        //2
        if (moveX == TRUE)
        {
            for (int f = angular[1].min + 1280; f < angular[1].max + 1280; f++)
            {
                fx = (float)f;
                fy = -gradient * (float)(f - 1280);
                SetPixel(memdc, (int)fx + angular[1].plusX, (int)fy - 240 - zigPlusY, graph.whatColor);
                // cout << gradient << endl;
            }
            for (int f = angular[1].min2 + 1280; f < angular[1].max2 + 1280; f++)
            {
                fx = (float)f;
                fy = gradient * (float)(f - 1280) - 160;
                SetPixel(memdc, (int)fx + angular[1].plusX, (int)fy + 880 + zigPlusY, graph.whatColor);
            }
            for (int f = angular[1].min3 + 1280; f < angular[1].max3 + 1280; f++)
            {
                fx = (float)f;
                fy = -gradient * (float)(f - 1280);
                SetPixel(memdc, (int)fx + angular[1].plusX, (int)fy + 400 - zigPlusY, graph.whatColor);
            }
            for (int f = angular[1].min4 + 1280; f < angular[1].max4 + 1280; f++)
            {
                fx = (float)f;
                fy = gradient * (float)(f - 1280) - 160;
                SetPixel(memdc, (int)fx + angular[1].plusX, (int)fy + 240 + zigPlusY, graph.whatColor);
            }
            for (int f = angular[1].min5 + 1280; f < angular[1].max5 + 1280; f++)
            {
                fx = (float)f;
                fy = -gradient * (float)(f - 1280) + 480;
                SetPixel(memdc, (int)fx + angular[1].plusX, (int)fy + 560 - zigPlusY, graph.whatColor);
            }
        }
        break;
        //if (zigzag)
        //{
        //    hPen = CreatePen(PS_SOLID, 3, NOW); 
        //    SelectObject(memDC, hPen); MoveToEx(memDC, 0, 300, NULL);
        //    for (i = 0; i < 40; i++) 
        //    { //<---------- MoveToEx(memDC, (i)*movex, y + movey, NULL); LineTo(memDC, (i + 1) * movex, 600 - (y + movey)); i++; LineTo(memDC, (i + 1) * movex, y + movey); } if (One) { hPen = CreatePen(PS_SOLID, 3, RGB(114, 114, 114)); SelectObject(memDC, hPen); A += 5; if (puze) A -= 5;; if ((A / movex) % 2 == 1) {//위 // Ay = y+((A - ((A / movex) * movex)) / movex * movey); Ay = y + (A - (A % movex) * -movey % movex); } else {//아래 Ay = y - (A - (A % movex) * -movey % movex); //<----------여기부터 다시 } Ellipse(memDC, A - 10, Ay - 10, A, Ay); if (A >= 600) A = 0; hPen = CreatePen(PS_SOLID, 3, NOW); SelectObject(memDC, hPen); } if (count >= 5) { if (checkturn) { movey += 10; if (puze) movey -= 10; if (movey >= 190) 
        //        { checkturn = false; } }
        //else { movey -= 10;
        //        if (puze) movey += 10; 
        //        if (movey <= -190) { checkturn = true; } } }
        //        if (count <= 0) 
        //        {
        //        if (checkturn) { movex++; if (puze) movex--; 
        //        if (movex >= 60) { checkturn = false; } } 
        //else { movex--; if (puze) 
        //        movex++; 
        //        if (movex <= 40) 
        //        { checkturn = true; 
        //    } 
        //    } 
        //    } 
        //    }
              //  break;
    case 3://spring
       // for (int i = 0; i < 10000; ++i)
        //{
        MoveToEx(memdc, cos(0) * iDis + 620, 400 + sin(0) * iDis, nullptr);
        for (int n = 0; n < 11; ++n)
        {
            for (float fAngle = angular[2].min; fAngle < angular[2].max; fAngle += 0.1)
            {
                LineTo(memdc, angular[2].plusX + cos(fAngle) * iDis, angular[2].plusY + sin(fAngle) * iDis);
                angular[2].plusX += 1;
            }
        }
        // }
        KillTimer(hwnd, 1);
        KillTimer(hwnd, 2);
        KillTimer(hwnd, 3);
        KillTimer(hwnd, 4);
        break;
    case 4://doubleLine
        for (int f = angular[3].min; f < angular[3].max; ++f)
        {
            fx = (float)f;
            SetPixel(memdc, (int)fx + 720, (int)fy + 200, graph.whatColor);
        }
        for (int f = angular[3].min; f < angular[3].max; ++f)
        {
            fx = (float)f;
            SetPixel(memdc, (int)fx + 720, (int)fy + 600, graph.whatColor);
        }
        break;
    }
    if (draw == 2 && circle == TRUE)
    {
        if (f >= -720 && f < -480)
        {
            for (f = -720; f < -480; f++)
            {
                fx = (float)f;
                fy = -(float)f;
                //SetPixel(memdc, (int)fx + 720, (int)fy - 240, graph.whatColor);
                wantToMove[0].leftX = (int)fx + 720 - 50;
                wantToMove[0].rightX = (int)fx + 720 + 50;
                wantToMove[0].topY = (int)fy - 240 - 50;
                wantToMove[0].topY = (int)fy - 240 + 50;
                if (circle == TRUE)
                    Ellipse(memdc, wantToMove[0].leftX, wantToMove[0].topY, wantToMove[0].rightX, wantToMove[0].bottomY);
            }
        }
        else if (f >= -480 && f < -160)
        {
            for (f = -480; f < -160; f++)
            {
                fx = (float)f;
                fy = (float)f - 160;
                //SetPixel(memdc, (int)fx + 720, (int)fy + 880, graph.whatColor);
                wantToMove[0].leftX = (int)fx + 720 - 50;
                wantToMove[0].rightX = (int)fx + 720 + 50;
                wantToMove[0].topY = (int)fy + 880 - 50;
                wantToMove[0].topY = (int)fy + 880 + 50;
                if (circle == TRUE)
                    Ellipse(hdc, wantToMove[0].leftX, wantToMove[0].topY, wantToMove[0].rightX, wantToMove[0].bottomY);
            }
        }
        else if (f >= -160 && f < 160)
        {
            for (f = -160; f < 160; f++)
            {
                fx = (float)f;
                fy = -(float)f;
                //SetPixel(memdc, (int)fx + 720, (int)fy + 400, graph.whatColor);
                wantToMove[0].leftX = (int)fx + 720 - 50;
                wantToMove[0].rightX = (int)fx + 720 + 50;
                wantToMove[0].topY = (int)fy + 400 - 50;
                wantToMove[0].topY = (int)fy + 400 + 50;
                if (circle == TRUE)
                    Ellipse(hdc, wantToMove[0].leftX, wantToMove[0].topY, wantToMove[0].rightX, wantToMove[0].bottomY);
            }
        }
        else if (f >= 160 && f < 480)
        {
            for (f = 160; f < 480; f++)
            {
                fx = (float)f;
                fy = (float)f - 160;
                //SetPixel(memdc, (int)fx + 720, (int)fy + 240, graph.whatColor);
                wantToMove[0].leftX = (int)fx + 720 - 50;
                wantToMove[0].rightX = (int)fx + 720 + 50;
                wantToMove[0].topY = (int)fy + 240 - 50;
                wantToMove[0].topY = (int)fy + 240 + 50;
                if (circle == TRUE)
                    Ellipse(hdc, wantToMove[0].leftX, wantToMove[0].topY, wantToMove[0].rightX, wantToMove[0].bottomY);
            }
        }
        else if (f >= 480 && f < 720)
        {
            for (f = 480; f < 720; f++)
            {
                fx = (float)f;
                fy = -(float)f + 480;
                //SetPixel(memdc, (int)fx + 720, (int)fy + 560, graph.whatColor);
                wantToMove[0].leftX = (int)fx + 720 - 50;
                wantToMove[0].rightX = (int)fx + 720 + 50;
                wantToMove[0].topY = (int)fy + 560 - 50;
                wantToMove[0].topY = (int)fy + 560 + 50;
                if (circle == TRUE)
                    Ellipse(hdc, wantToMove[0].leftX, wantToMove[0].topY, wantToMove[0].rightX, wantToMove[0].bottomY);
            }
        }
    }
    else if (circle == TRUE)
        Ellipse(memdc, wantToMove[0].leftX, wantToMove[0].topY, wantToMove[0].rightX, wantToMove[0].bottomY);
    if (circle == TRUE && draw == 4)
        Ellipse(memdc, wantToMove[1].leftX, wantToMove[1].topY, wantToMove[1].rightX, wantToMove[1].bottomY);
    DeleteObject(hpen);
    StretchBlt(hdc, 0, 0, 1440, 800, memdc, 0, 0, 1440, 800, SRCCOPY);//900 675
}
