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

#define BUTTON_NONE -1
#define BUTTON_ZERO 1000
#define BUTTON_ONE 1001
#define BUTTON_TWO 1002
#define BUTTON_THREE 1003
#define BUTTON_FOUR 1004
#define BUTTON_FIVE 1005
#define BUTTON_SIX 1006
#define BUTTON_SEVEN 1007
#define BUTTON_EIGHT 1008
#define BUTTON_NINE 1009
#define BUTTON_DOT 1010
#define BUTTON_DIVIDE 1011
#define BUTTON_MULTIPLY 1012
#define BUTTON_MINUS 1013
#define BUTTON_PLUS 1014
#define BUTTON_PERCENTAGE 1015
#define BUTTON_ONE_OVER_X 1016
#define BUTTON_EQUAL 1017

#define NUM_BUTTON_ROWS 4
#define NUM_BUTTON_COLS 5

static const char *szCalScreenClass = "CalScreen";

typedef struct tagCalButton
{
    int iId;
    char szName[4];
    int iRowSpan;
    int iColSpan;
} CalButton;

static const CalButton CalButtons[NUM_BUTTON_ROWS][NUM_BUTTON_COLS] = { 
    {
        {BUTTON_SEVEN, "7", 1, 1}, {BUTTON_EIGHT, "8", 1, 1}, {BUTTON_NINE, "9", 1, 1}, {BUTTON_DIVIDE, "/", 1, 1}, {BUTTON_PERCENTAGE, "%", 1, 1}
    },
    {
        {BUTTON_FOUR, " 4", 1, 1}, {BUTTON_FIVE, "5", 1, 1}, {BUTTON_SIX, "6", 1, 1}, {BUTTON_MULTIPLY, "*", 1, 1}, {BUTTON_ONE_OVER_X, "1/x", 1, 1}
    },
    {
        {BUTTON_ONE, "1", 1, 1}, {BUTTON_TWO, "2", 1, 1}, {BUTTON_THREE, "3", 1, 1}, {BUTTON_MINUS, "-", 1, 1}, {BUTTON_EQUAL, "=", 1, 2}
    },
    {
        {BUTTON_ZERO, "0", 2, 1}, {BUTTON_DOT, ".", 1, 1}, {BUTTON_NONE, "", 0, 0}, {BUTTON_PLUS, "+", 1, 1}, {BUTTON_NONE, "", 0, 0}
    }
};

LRESULT CALLBACK CalScreenWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;

    switch (nMsg)
    {
        case WM_CREATE:
            return 0;
        case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            Rectangle(hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom);
            EndPaint(hWnd, &ps);
            return 0;
        }
        default:
            break;
    }
    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

static void InitWindowClasses(HINSTANCE hInst)
{
    WNDCLASS calScreenClass;
    memset(&calScreenClass, 0, sizeof(WNDCLASS));
    calScreenClass.lpszClassName = szCalScreenClass;
    calScreenClass.style = 0;
    calScreenClass.lpfnWndProc = CalScreenWndProc;
    calScreenClass.hInstance = hInst;
    calScreenClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    calScreenClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    calScreenClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&calScreenClass);
}

int STDCALL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
    InitWindowClasses(hInst);

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

            int iOffsetX = MainWindowMargin;
            int iOffsetY = MainWindowMargin;

            CreateWindow(
                    szCalScreenClass,
                    "",
                    WS_CHILD | WS_VISIBLE,
                    iOffsetX,
                    iOffsetY,
                    ButtonWidth * 5 + ButtonGap * 4,
                    ButtonHeight,
                    hWnd,
                    (HMENU)0,
                    ((LPCREATESTRUCT)lParam)->hInstance,
                    NULL
            );

            iOffsetY = iOffsetY + ButtonHeight + ButtonGap;

            for (int iRow = 0; iRow < NUM_BUTTON_ROWS; iRow++)
            {
                iOffsetX = MainWindowMargin;
                for (int iCol = 0; iCol < NUM_BUTTON_COLS; iCol++)
                {
                    CalButton sButton = CalButtons[iRow][iCol];
                    if (sButton.iId == BUTTON_NONE)
                        continue;

                    int iButtonWidth = sButton.iRowSpan > 1 ? sButton.iRowSpan * (ButtonWidth + ButtonGap) - ButtonGap : ButtonWidth;
                    int iButtonHeight = sButton.iColSpan > 1 ? sButton.iColSpan * (ButtonHeight + ButtonGap) - ButtonGap : ButtonHeight;
                    CreateButton(
                            hWnd,
                            sButton.szName,
                            iOffsetX,
                            iOffsetY,
                            iButtonWidth, 
                            iButtonHeight,
                            sButton.iId,
                            ((LPCREATESTRUCT)lParam)->hInstance
                    );
                    iOffsetX = iOffsetX + iButtonWidth + ButtonGap;
                }
                iOffsetY = iOffsetY + ButtonHeight + ButtonGap;
            }
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
                if (iButtonId >= BUTTON_ZERO && iButtonId <= BUTTON_DOT)
                {
                    char szMsg[2];
                    sprintf(szMsg, "%d", iButtonId - BUTTON_ZERO);
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
