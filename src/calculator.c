#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include "lib/stack.h"
#include "lib/list.h"
#include "calculation.h"
#include "ngf/zaml_structs.h"
#include "demo_datacontext.h"
#include "demo_ui.h"
#include "febuilder.h"

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

static const int MainWindowWidth = 300;
static const int MainWindowHeight = 400;

int STDCALL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
    //InitWindowClasses(hInst);
    InitFrameworkElements(hInst);

    WNDCLASSEX wndClass;
    memset(&wndClass, 0, sizeof(WNDCLASSEX));
    wndClass.lpszClassName = L"WinTestApp2Win";
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
        L"WinTestApp2Win",
        L"Hello",
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
    //static HWND hWndButton[9];//, hWndCalScreen;
    //static int cx, cy;
    //HDC hdc;
    //PAINTSTRUCT ps;
    //RECT rc;
    static FrameworkElement *pFe = NULL;

    switch (nMsg)
    {
        case WM_CREATE:
        {
            LPCREATESTRUCT pCreateStruct = (LPCREATESTRUCT)lParam;
            AppDataContext *pDc = appdc_create();
            //pFe = get_demo_ui(get_demo_dc());
            pFe = get_demo_ui3(pDc);
            MessageBox(NULL, L"app3", L"app3", MB_OK);
            FeSize size = fe_get_size(pFe);
            /*
            wchar_t buf[1024] = {0};
            wsprintf(buf, L"width(%d),height(%d)", size.width, size.height);
            MessageBox(NULL, buf, buf, MB_OK);
            */

            //BuildFrameworkElement(((LPCREATESTRUCT)lParam)->hInstance, hWnd, pFe);
            fe_build_ex(pCreateStruct->hInstance, hWnd, 0, 0, size.width, size.height, pFe);
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
            return 0;
        }
    }

    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

