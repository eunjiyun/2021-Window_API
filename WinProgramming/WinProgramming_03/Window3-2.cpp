#include <Windows.h>
#include<random>
#define MAXSIZE 100
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
    WPARAM wParam, LPARAM lParam);
std::default_random_engine gen;
std::uniform_int_distribution<int> uid{ 0, 255 };
std::uniform_int_distribution<int> tim{ 1, 10 };

typedef struct CIRCLE {
    int x;
    int y;
    bool cantGo;
    HBRUSH color;
    int time;
}CIRCLE;

typedef struct FOUR {
    int x;
    int y;

}FOUR;
HINSTANCE g_hlnst;
LPCTSTR IpszClass = L"windows Class Name";
LPCTSTR IpszWindowName = L"windows program 3-3";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrebInstance, LPSTR IpszCmdParm, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASSEX WndClass;
    g_hlnst = hInstance;

    WndClass.cbSize = sizeof(WndClass);
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = (WNDPROC)WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WndClass.lpszMenuName = NULL; WndClass.lpszClassName = IpszClass;
    WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&WndClass);

    hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 800, NULL, (HMENU)NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    HBRUSH hbrush, older;


    static CIRCLE MAKE[MAXSIZE];
    static FOUR STAY;
    static bool Drag = FALSE;
    static bool RDrag = FALSE;
    int i;
    static int rx, ry, orx, ory, erx, ery;
    static int cx, cy, ecx, ecy, ocx, ocy, lengx, lengy;

    switch (iMsg) {
    case WM_CREATE:
        for (i = 0; i < MAXSIZE; i++) {
            MAKE[i].x = rand() % 850;
            MAKE[i].y = 1;
            MAKE[i].cantGo = false;
            MAKE[i].time = tim(gen);
            MAKE[i].color = CreateSolidBrush(RGB(uid(gen), uid(gen), uid(gen)));
        }

        break;
    case WM_CHAR:
        hdc = GetDC(hwnd);
        InvalidateRect(hwnd, NULL, TRUE);
        ReleaseDC(hwnd, hdc);
        break;
    case WM_KEYDOWN:
        hdc = GetDC(hwnd);
        switch (wParam) {
        case 0x53:

            SetTimer(hwnd, 1, 100, NULL);
            break;
        case VK_OEM_MINUS:
            for (i = 0; i < MAXSIZE; i++) {
                MAKE[i].time--;
                if (MAKE[i].time <= 1) {
                    MAKE[i].time = 1;
                }
            }
            break;
        case VK_OEM_PLUS:
            for (i = 0; i < MAXSIZE; i++) {
                MAKE[i].time++;

            }
            break;
        case 0x44:
            rx = ry = erx = ery = 0;
            break;
        }
        ReleaseDC(hwnd, hdc);
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_LBUTTONDOWN:
        for (i = 0; i < MAXSIZE; i++) {
            MAKE[i].cantGo = false;
        }
        orx = rx = LOWORD(lParam);
        ory = ry = HIWORD(lParam);
        Drag = TRUE;
        break;

    case WM_LBUTTONUP:
        Drag = FALSE;
        break;
    case WM_RBUTTONDOWN:
        hdc = GetDC(hwnd);
        {
            RECT new1 = { rx,ry,erx,ery };
            FrameRect(hdc, &new1, (HBRUSH)GetStockObject(BLACK_BRUSH));
        }
        ReleaseDC(hwnd, hdc);
        cx = LOWORD(lParam);
        cy = HIWORD(lParam);
        if (rx <= cx && cx <= erx) {
            if (ry <= cy && cy <= ery) {
                RDrag = TRUE;
            }
        }
        lengx = cx - rx;
        lengy = cy - ry;
        ocx = erx - cx;
        ocy = ery - cy;
        break;
    case WM_RBUTTONUP:
        RDrag = FALSE;
        break;
    case WM_MOUSEMOVE:
        hdc = GetDC(hwnd);
        if (RDrag) {
            ecx = LOWORD(lParam);
            ecy = HIWORD(lParam);
            orx = erx;
            ory = ery;

            rx = ecx - lengx;
            ry = ecy - lengy;
            erx = ecx + ocx;
            ery = ecy + ocy;

            RECT old = { rx,ry,orx,ory };
            RECT new1 = { rx,ry,erx,ery };
            for (i = 0; i < MAXSIZE; i++) {
                MAKE[i].cantGo = false;
                if (MAKE[i].y <= ery && MAKE[i].y >= ery - 10) {
                    MAKE[i].cantGo = true;
                }
            }

            FrameRect(hdc, &old, (HBRUSH)GetStockObject(BLACK_BRUSH));
            FrameRect(hdc, &new1, (HBRUSH)GetStockObject(WHITE_BRUSH));


        }
        if (Drag)
        {

            erx = LOWORD(lParam);
            ery = HIWORD(lParam);
            RECT old = { rx,ry,orx,ory };
            RECT new1 = { rx,ry,erx,ery };

            FrameRect(hdc, &old, (HBRUSH)GetStockObject(BLACK_BRUSH));
            FrameRect(hdc, &new1, (HBRUSH)GetStockObject(WHITE_BRUSH));

        }

        ReleaseDC(hwnd, hdc);
        break;

    case WM_TIMER:
        hdc = GetDC(hwnd);
        switch (wParam) {
        case 1:
            for (i = 0; i < MAXSIZE; i++) {
                MAKE[i].y = MAKE[i].y + MAKE[i].time;
                if (MAKE[i].x >= rx && MAKE[i].x <= erx) {
                    if (MAKE[i].y >= ry && MAKE[i].y <= ery) {
                        MAKE[i].color = CreateSolidBrush(RGB(uid(gen), uid(gen), uid(gen)));
                        if (MAKE[i].y <= ery && MAKE[i].y >= ery - 10) {
                            MAKE[i].cantGo = true;
                        }
                    }
                }

            }
            break;
        }
        ReleaseDC(hwnd, hdc);
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        for (i = 0; i < MAXSIZE; i++) {

            older = (HBRUSH)SelectObject(hdc, MAKE[i].color);
            if (MAKE[i].y >= 850) {
                MAKE[i].y = 0;
                MAKE[i].time = tim(gen);
            }
            if (MAKE[i].cantGo == true) {
                MAKE[i].y = ery - 10;
            }

            Ellipse(hdc, MAKE[i].x, MAKE[i].y, MAKE[i].x + 10, MAKE[i].y + 10);
        }//기본 원 배치 출력 
        if (!Drag || !RDrag) {
            RECT new1 = { rx,ry,erx,ery };
            FrameRect(hdc, &new1, (HBRUSH)GetStockObject(WHITE_BRUSH));
        }

        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);

    }return DefWindowProc(hwnd, iMsg, wParam, lParam);


}





