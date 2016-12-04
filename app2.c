#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
static HWND CreateButton(HWND, LPCTSTR, int, int, int, int, int, HINSTANCE);

static const int MainWindowWidth = 300;
static const int MainWindowHeight = 400;

static const int ButtonWidth = 50;
static const int ButtonHeight = 50;
static const int ButtonGap = 5;

static const int MainWindowMargin = 10;

static const int ButtonZeroId = 1000;
static const int ButtonOneId = 1001;
static const int ButtonTwoId = 1002;
static const int ButtonThreeId = 1003;
static const int ButtonFourId = 1004;
static const int ButtonFiveId = 1005;
static const int ButtonSixId = 1006;
static const int ButtonSevenId = 1007;
static const int ButtonEigthId = 1008;
static const int ButtonNineId = 1009;
static const int ButtonDotId = 1010;

int STDCALL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
    WNDCLASSEX wndClass;
    memset(&wndClass, 0, sizeof(WNDCLASSEX));
    wndClass.lpszClassName = "WinTestApp2Win";
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = MainWndProc;
    wndClass.hInstance = hInst;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

    RegisterClassEx(&wndClass);

    HWND hWndMain = CreateWindow(
        "WinTestApp2Win",
        "Hello",
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        MainWindowWidth,
        MainWindowHeight,
        NULL,
        NULL,
        hInst,
        NULL
    );

    ShowWindow(hWndMain, nShow);
    UpdateWindow(hWndMain);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        // IMPORTANT: this sends messages to MainWndProc
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hWndButton[9];
    static int cx, cy;
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;

    switch (nMsg)
    {
        case WM_CREATE:
        {
            /*
            TEXTMETRIC tm;
            hdc = GetDC(hWnd);
            SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
            GetTextMetrics(hdc, &tm);
            cx = tm.tmAveCharWidth * 30;
            cy = (tm.tmHeight + tm.tmExternalLeading) * 2;
            ReleaseDC(hWnd, hdc);
            */

            // create number 1 to 9
            int iButtonNum = 9;
            int iButton = 0;
            int iButtonId = ButtonNineId;
            int iOffsetX, iOffsetY = MainWindowMargin;
            for (int i = 0; i < 3; i++)
            {
                iOffsetX = MainWindowMargin;
                for (int j = 0; j < 3; j++)
                {
                    char buttonName[2];
                    sprintf(buttonName, "%d", iButtonNum--);
                    hWndButton[iButton++] = CreateButton(hWnd,
                            buttonName,
                            iOffsetX, iOffsetY,
                            ButtonWidth, ButtonHeight,
                            iButtonId--, 
                            ((LPCREATESTRUCT)lParam)->hInstance
                    );
                    iOffsetX = iOffsetX + ButtonWidth + ButtonGap;
                }
                iOffsetY = iOffsetY + ButtonHeight + ButtonGap;
            }

            iOffsetX = MainWindowMargin;
            CreateButton(hWnd,
                    "0",
                    iOffsetX, iOffsetY, 
                    ButtonWidth*2+ButtonGap, ButtonHeight,
                    ButtonZeroId,
                    ((LPCREATESTRUCT)lParam)->hInstance
            );
            
            iButtonId++;
            iOffsetX = iOffsetX + ButtonWidth*2+ButtonGap + ButtonGap;
            CreateButton(hWnd,
                    ".", 
                    iOffsetX, iOffsetY, 
                    ButtonWidth, ButtonHeight, 
                    ButtonDotId,
                    ((LPCREATESTRUCT)lParam)->hInstance
            );
            /*
            hWndButton = CreateButton(hWnd, 10, 10, ((LPCREATESTRUCT)lParam)->hInstance);
            hWndButton = CreateWindow(
                "BUTTON",
                "1",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10, 10,
                ButtonWidth,
                ButtonHeight,
                hWnd,
                (HMENU)1,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );
            */
            return 0;
        }

        case WM_DESTROY:
        {
            // IMPORTANT: this sends WM_QUIT to the message loop in WinMain, which will
            // terminate the loop
            PostQuitMessage(0);
            return 0;
        }

        case WM_PAINT:
        {
            /*
            hdc = BeginPaint(hWnd, &ps);
            GetClientRect(hWnd, &rc);
            rc.bottom = rc.bottom/2;
            DrawText(hdc, "Hello, World", -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            EndPaint(hWnd, &ps);
            return 0;
            */
            break;
        }

        case WM_SIZE:
        {
            /*
            if (hWndButton && (wParam == SIZEFULLSCREEN || wParam == SIZENORMAL))
            {
                rc.left = (LOWORD(wParam) - cx) / 2;
                rc.top = HIWORD(lParam) * 3 / 4 - cy / 2;
                MoveWindow(hWndButton, rc. left, rc.top, cx, cy, TRUE);
            }
            */
            break;
        }

        case WM_COMMAND:
        {
            //if (LOWORD(wParam) == 1 && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == hWndButton)
            if (HIWORD(wParam) == BN_CLICKED)
            {
                int iButtonId = LOWORD(wParam);
                if (iButtonId >= ButtonZeroId && iButtonId <= ButtonDotId)
                {
                    char szMsg[2];
                    sprintf(szMsg, "%d", iButtonId - ButtonZeroId);
                    MessageBox(hWnd, szMsg, "Button", MB_OKCANCEL | MB_ICONINFORMATION);
                }
                //DestroyWindow(hWnd);
            }
            return 0;
        }
    }

    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

static HWND CreateButton(HWND hWnd, LPCTSTR lpName, int iOffsetX, int iOffsetY, int iWidth, int iHeight, int iButtonId, HINSTANCE hInstance)
{
    HWND hWndButton = CreateWindow(
        "BUTTON",
        lpName,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        iOffsetX, 
        iOffsetY,
        iWidth,
        iHeight,
        hWnd,
        (HMENU)iButtonId,
        hInstance,
        NULL
    );

    return hWndButton;
}
