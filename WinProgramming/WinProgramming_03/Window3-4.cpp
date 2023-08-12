#include<Windows.h>
#include<TCHAR.H>
#include<iostream>
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
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
        _T("windows program 3-4"),
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
class car
{
public:
    int xpos;
    int ypos;
};
car upDown = { 485,30 };
car rightLeft = { 830,285 };
car Updown = { 680,505 };
car Rightleft = { 190,390 };
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
    WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HBRUSH hbrush, oldbrush;
    HPEN hpen, oldpen;
    static RECT rectView;
    static int xSignal = 820;
    static int ySignal = 20;
    static int xSignal2 = 1150;
    static int ySignal2 = 500;
    static int stop = 0;
    static int upDownSpeed = 80;
    static int rightLeftSpeed = 80;
    static bool preroad = TRUE;
    static int mx = 0;
    static int my = 0;
    static bool flag = FALSE;

    switch (iMsg)
    {
    case WM_CREATE:
        GetClientRect(hwnd, &rectView);
        SetTimer(hwnd, 6, upDownSpeed, NULL);//신호등
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        for (int i = 0; i < 4; ++i)
        {
            MoveToEx(hdc, i * 400 + 20, 20, nullptr);
            LineTo(hdc, i * 400 + 20, 740);
        }
        Rectangle(hdc, 820, 20, 1030, 90);//210 70
        Rectangle(hdc, 1010, 500, 1220, 570);
        hbrush = CreateSolidBrush(RGB(255, 0, 0));
        oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
        Ellipse(hdc, 820, 20, 890, 90);
        Ellipse(hdc, 1010, 500, 1080, 570);
        hbrush = CreateSolidBrush(RGB(255, 255, 0));
        oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
        Ellipse(hdc, 890, 20, 960, 90);
        Ellipse(hdc, 1080, 500, 1150, 570);
        hbrush = CreateSolidBrush(RGB(0, 0, 255));
        oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
        Ellipse(hdc, 960, 20, 1030, 90);
        Ellipse(hdc, 1150, 500, 1220, 570);
        for (int i = 0; i < 4; ++i)
        {
            MoveToEx(hdc, 20, i * 240 + 20, nullptr);
            LineTo(hdc, 1220, i * 240 + 20);
        }
        hbrush = CreateSolidBrush(RGB(80, 188, 223));
        oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
        Rectangle(hdc, upDown.xpos, upDown.ypos, upDown.xpos + 70, upDown.ypos + 210);
        Rectangle(hdc, rightLeft.xpos, rightLeft.ypos, rightLeft.xpos + 210, rightLeft.ypos + 70);
        Rectangle(hdc, Updown.xpos, Updown.ypos, Updown.xpos + 70, Updown.ypos + 210);
        Rectangle(hdc, Rightleft.xpos, Rightleft.ypos, Rightleft.xpos + 210, Rightleft.ypos + 70);
        hpen = CreatePen(PS_SOLID, 1, RGB(80, 188, 223));
        oldpen = (HPEN)SelectObject(hdc, hpen);
        MoveToEx(hdc, 620, 20, nullptr);//420 620
        LineTo(hdc, 620, 740);
        MoveToEx(hdc, 20, 380, nullptr);//380 260
        LineTo(hdc, 1220, 380);
        hpen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
        oldpen = (HPEN)SelectObject(hdc, hpen);
        if (xSignal != 1080)
        {
            hbrush = CreateSolidBrush(RGB(255, 0, 0));
            oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
            Ellipse(hdc, xSignal, ySignal, xSignal + 70, ySignal + 70);
            hbrush = CreateSolidBrush(RGB(0, 0, 255));
            oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
            Ellipse(hdc, xSignal2, ySignal2, xSignal2 + 70, ySignal2 + 70);
        }
        else
        {
            hbrush = CreateSolidBrush(RGB(255, 255, 0));
            oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
            Ellipse(hdc, xSignal, ySignal, xSignal + 70, ySignal + 70);
            Ellipse(hdc, xSignal2, ySignal2, xSignal2 + 70, ySignal2 + 70);
        }
        EndPaint(hwnd, &ps);
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case WM_LBUTTONDOWN:
            mx = LOWORD(lParam);
            my = HIWORD(lParam);
            //std::cout << mx << " " << my;
             //Rectangle(hdc, 820, 20, 1030, 90);//210 70
            if (mx < 1030 && mx >820 && my < 90 && my > 20)
            {
                flag = TRUE;
                //xSignal2 = 890;//노
                //ySignal2 = 20;
                //xSignal = 1080;
                //ySignal = 500;
                //SetTimer(hwnd, 1, upDownSpeed, NULL);
                //SetTimer(hwnd, 2, rightLeftSpeed, NULL);
                //preroad = TRUE;
            }
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case 'A'://신호 자동 바꿈
        case 'a':
            KillTimer(hwnd, 6);
            if (stop == 0)
            {
                ++stop;
                SetTimer(hwnd, 3, 2000, NULL);//신호등
            }
            else
            {
                --stop;
                KillTimer(hwnd, 3);
            }
            break;
        case VK_OEM_PLUS://이동속도 증가
            upDownSpeed /= 2;
            rightLeftSpeed /= 2;
            KillTimer(hwnd, 6);
            SetTimer(hwnd, 6, upDownSpeed, NULL);
            break;
        case VK_OEM_MINUS://이동속도 감소
            upDownSpeed *= 2;
            rightLeftSpeed *= 2;
            KillTimer(hwnd, 6);
            SetTimer(hwnd, 6, upDownSpeed, NULL);
            break;
        case 'Q'://종료
        case 'q':
            SendMessage(hwnd, WM_CLOSE, 0, 0);
            break;
        }
        break;
    case WM_TIMER:
        switch (wParam)
        {
        case 1:
            if (upDown.ypos + 210 > rectView.bottom)
                upDown.ypos = 30;
            else
                upDown.ypos += 20;
            if (Updown.ypos + 210 < rectView.top)
                Updown.ypos = 800;
            else
                Updown.ypos -= 20;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case 2:
            if (rightLeft.xpos < rectView.left)
                rightLeft.xpos = 980;
            else
                rightLeft.xpos -= 20;
            if (Rightleft.xpos + 210 > rectView.right)
                Rightleft.xpos = 0;
            else
                Rightleft.xpos += 20;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case 3:
            if (xSignal == 820 || flag == TRUE)//빨
            {
                xSignal2 = 890;//노
                ySignal2 = 20;
                xSignal = 1080;
                ySignal = 500;
                SetTimer(hwnd, 1, upDownSpeed, NULL);
                SetTimer(hwnd, 2, rightLeftSpeed, NULL);
                preroad = TRUE;
            }
            else if (xSignal == 1010 || flag == TRUE)//파
            {
                xSignal2 = 890;//노
                ySignal2 = 20;
                xSignal = 1080;
                ySignal = 500;
                SetTimer(hwnd, 1, upDownSpeed, NULL);
                SetTimer(hwnd, 2, rightLeftSpeed, NULL);
                preroad = FALSE;
            }
            else//노
            {
                if (preroad == TRUE)
                {
                    xSignal = 1010;//파
                    ySignal = 500;
                    xSignal2 = 960;
                    ySignal2 = 20;
                    SetTimer(hwnd, 1, upDownSpeed, NULL);//상하차
                    KillTimer(hwnd, 2);
                }
                else
                {
                    xSignal = 820;//빨
                    ySignal = 20;
                    xSignal2 = 1150;
                    ySignal2 = 500;
                    SetTimer(hwnd, 2, rightLeftSpeed, NULL);//좌우차
                    KillTimer(hwnd, 1);
                }
            }
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case 6:
            if (rightLeft.xpos < rectView.left)
                rightLeft.xpos = 980;
            else
                rightLeft.xpos -= 20;
            if (Rightleft.xpos + 210 > rectView.right)
                Rightleft.xpos = 0;
            else
                Rightleft.xpos += 20;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        break;
    case WM_DESTROY:
        KillTimer(hwnd, 1);
        KillTimer(hwnd, 2);
        KillTimer(hwnd, 3);
        KillTimer(hwnd, 6);
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}


