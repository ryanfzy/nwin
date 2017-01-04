#include <windows.h>
#include <stdio.h>
#include "lib/stack.h"

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
#define BUTTON_CLEAR 1018

#define NUM_BUTTON_ROWS 5
#define NUM_BUTTON_COLS 5

static const char *szCalScreenClass = "CalScreen";

typedef struct tagCalButton
{
    int iId;
    char szName[8];
    int iRowSpan;
    int iColSpan;
} CalButton;

typedef enum
{
    CALITEMTYPE_NUM,
    CALITEMTYPE_PLUS,
    CALITEMTYPE_MINUS,
    CALITEMTYPE_DIVIDE,
    CALITEMTYPE_MULTIPLY,
} CalItemType;

typedef struct tagCalItemInfo
{
    long lnum;
    CalItemType etype;
} CalItemInfo;

static const CalButton CalButtons[NUM_BUTTON_ROWS][NUM_BUTTON_COLS] = { 
    {
        {BUTTON_CLEAR, "Clear", NUM_BUTTON_COLS, 1}, {BUTTON_NONE, "", 0, 0}, {BUTTON_NONE, "", 0, 0}, {BUTTON_NONE, "", 0, 0}, {BUTTON_NONE, "", 0, 0}
    },
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

// this only takes prefix expression
static long do_get_result(Stack *ps)
{
    CalItemInfo sinfo;
    stack_pop(ps, (char*)&sinfo, sizeof(CalItemInfo));
    if (sinfo.etype == CALITEMTYPE_NUM)
        return sinfo.lnum;
    else
    {
        long num1;
        long num2;

        if (((CalItemInfo*)ps->ptop->pdata)->etype == CALITEMTYPE_NUM)
        {
            CalItemInfo sinfo2;
            stack_pop(ps, (char*)&sinfo2, sizeof(CalItemInfo));
            num1 = sinfo2.lnum;
        }
        else
            num1 = do_get_result(ps);

        if (((CalItemInfo*)ps->ptop->pdata)->etype == CALITEMTYPE_NUM)
        {
            CalItemInfo sinfo2;
            stack_pop(ps, (char*)&sinfo2, sizeof(CalItemInfo));
            num2 = sinfo2.lnum;
        }
        else
            num2 = do_get_result(ps);

        switch (sinfo.etype)
        {
            case CALITEMTYPE_PLUS:
                return num1 + num2;
            case CALITEMTYPE_MINUS:
                return num1 - num2;
            case CALITEMTYPE_MULTIPLY:
                return num1 * num2;
            case CALITEMTYPE_DIVIDE:
                return num1 / num2;
        }
    }
    return 0;
}

static long GetResult(Stack *ps, char *pret)
{
    long ret = 0;
    if (ps->icount >0)
    {
        Stack s1, s2, s3;
        stack_init(&s1);
        stack_init(&s2);
        stack_init(&s3);

        CalItemInfo sinfo;
        while (ps->icount > 0)
        {
            stack_pop(ps, (char*)&sinfo, sizeof(CalItemInfo));
            if (sinfo.etype == CALITEMTYPE_NUM)
            {
                stack_push(&s1, (char*)&sinfo, sizeof(CalItemInfo));
                stack_push(&s3, (char*)&sinfo, sizeof(CalItemInfo));
            }
            else if (sinfo.etype == CALITEMTYPE_PLUS || sinfo.etype == CALITEMTYPE_MINUS)
            {
                if (s2.icount > 0)
                {
                    CalItemInfo *psinfo = (CalItemInfo*)s2.ptop->pdata;
                    while (psinfo != NULL && (psinfo->etype == CALITEMTYPE_MULTIPLY || psinfo->etype == CALITEMTYPE_DIVIDE))
                    {
                        CalItemInfo sinfo2;
                        stack_pop(&s2, (char*)&sinfo2, sizeof(CalItemInfo));
                        stack_push(&s1, (char*)&sinfo2, sizeof(CalItemInfo));
                        stack_push(&s3, (char*)&sinfo2, sizeof(CalItemInfo));
                        psinfo = s2.icount > 0 ? (CalItemInfo*)s2.ptop->pdata : NULL;
                    }
                }
                stack_push(&s2, (char*)&sinfo, sizeof(CalItemInfo));
            }
            else if (sinfo.etype == CALITEMTYPE_MULTIPLY || sinfo.etype == CALITEMTYPE_DIVIDE)
            {
                stack_push(&s2, (char*)&sinfo, sizeof(CalItemInfo));
            }
        }

        while (s2.icount > 0)
        {
            stack_pop(&s2, (char*)&sinfo, sizeof(CalItemInfo));
            stack_push(&s1, (char*)&sinfo, sizeof(CalItemInfo));
            stack_push(&s3, (char*)&sinfo, sizeof(CalItemInfo));
        }

        while (s1.icount > 0)
        {
            stack_pop(&s1, (char*)&sinfo, sizeof(CalItemInfo));
            if (sinfo.etype == CALITEMTYPE_NUM)
                sprintf(pret + strlen(pret), "%ld ", sinfo.lnum);
            else if (sinfo.etype == CALITEMTYPE_PLUS)
                strcat(pret, "+ ");
            else if (sinfo.etype == CALITEMTYPE_MINUS)
                strcat(pret, "- ");
            else if (sinfo.etype == CALITEMTYPE_MULTIPLY)
                strcat(pret, "* ");
            else if (sinfo.etype == CALITEMTYPE_DIVIDE)
                strcat(pret, "/ ");
        }

        ret = do_get_result(&s3);
    }
    return ret;
}

LRESULT CALLBACK CalScreenWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;
    RECT rcText1, rcText2;
    static char szText1[128] = { '\0' };
    static char szText2[128] = { '\0' };
    static int iText2Length = 0;
    static Stack s;

    switch (nMsg)
    {
        case WM_CREATE:
        {
            stack_init(&s);
            strcpy(szText2, "0");
            return 0;
        }
        case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            Rectangle(hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom);

            rcText1.left = ps.rcPaint.left;
            rcText1.top = ps.rcPaint.top + 5;
            rcText1.right = ps.rcPaint.right - 5;
            rcText1.bottom = ps.rcPaint.bottom / 2;
            DrawText(hdc, szText1, strlen(szText1), &rcText1, DT_VCENTER | DT_RIGHT);

            rcText2.left = ps.rcPaint.left;
            rcText2.top = ps.rcPaint.bottom / 2 + 5;
            rcText2.right = ps.rcPaint.right - 5;
            rcText2.bottom = ps.rcPaint.bottom;
            DrawText(hdc, szText2, strlen(szText2), &rcText2, DT_VCENTER | DT_RIGHT);

            EndPaint(hWnd, &ps);
            return 0;
        }
        case WM_COMMAND:
        {
            int iButton = (int)lParam;

            if (iButton >= BUTTON_ZERO && iButton <= BUTTON_NINE)
            {
                sprintf(szText2 + iText2Length, "%d", iButton - BUTTON_ZERO);
                iText2Length++;
            }
            else if (iButton == BUTTON_PLUS || iButton == BUTTON_MINUS ||
                     iButton == BUTTON_DIVIDE || iButton == BUTTON_MULTIPLY)
            {
                CalItemInfo num, oper;
                char *ptr;
                char szOp[2];

                num.lnum = strtol(szText2, &ptr, 10);
                num.etype = CALITEMTYPE_NUM;
                stack_push(&s, (char*)&num, sizeof(CalItemInfo));

                if (iButton == BUTTON_PLUS)
                {
                    oper.etype = CALITEMTYPE_PLUS;
                    strcpy(szOp, "+");
                }
                else if (iButton == BUTTON_MINUS)
                {
                    oper.etype = CALITEMTYPE_MINUS;
                    strcpy(szOp, "-");
                }
                else if (iButton == BUTTON_DIVIDE)
                {
                    oper.etype = CALITEMTYPE_DIVIDE;
                    strcpy(szOp, "/");
                }
                else if (iButton == BUTTON_MULTIPLY)
                {
                    oper.etype = CALITEMTYPE_MULTIPLY;
                    strcpy(szOp, "*");
                }

                stack_push(&s, (char*)&oper, sizeof(CalItemInfo));

                if (strlen(szText1) > 0)
                    strcat(szText1, " ");
                strcat(szText1, szText2);
                strcat(szText1, " ");
                strcat(szText1, szOp);
                szText2[0] = '0';
                szText2[1] = '\0';
                iText2Length = 0; 
            }
            else if (iButton == BUTTON_EQUAL)
            {
                CalItemInfo num;
                char *ptr;
                num.lnum = strtol(szText2, &ptr, 10);
                num.etype = CALITEMTYPE_NUM;
                stack_push(&s, (char*)&num, sizeof(CalItemInfo));

                szText1[0] = '\0';
                long ret = GetResult(&s, szText1);
                sprintf(szText2, "%ld", ret);
            }
            else if (iButton == BUTTON_CLEAR)
            {
                szText1[0] = '\0';
                szText2[0] = '0';
                szText2[1] = '\0';
                iText2Length = 0;
            }
            InvalidateRect(hWnd, NULL, TRUE);
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
    static HWND hWndButton[9], hWndCalScreen;
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

            hWndCalScreen = CreateWindow(
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
                /*
                if (iButtonId >= BUTTON_ZERO && iButtonId <= BUTTON_DOT)
                {
                    char szMsg[2];
                    sprintf(szMsg, "%d", iButtonId - BUTTON_ZERO);
                    MessageBox(hWnd, szMsg, "Button", MB_OKCANCEL | MB_ICONINFORMATION);
                }*/
                SendMessage(hWndCalScreen, WM_COMMAND, 0, iButtonId);
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
