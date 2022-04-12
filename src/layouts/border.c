#include "border.h"
#include "febuilder.h"
#include "messages.h"

static const wchar_t *szBorderClass = L"border";

static LRESULT CALLBACK BorderWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    switch (nMsg)
    {
    case WM_CREATE:
    {
        CREATESTRUCT *pCreateStruct = (CREATESTRUCT*)lParam;
        FrameworkElement *pFe = (FrameworkElement*)(pCreateStruct->lpCreateParams);
        SetWindowLong(hWnd, GWL_USERDATA, (LONG)pFe);

        FrameworkElement *pChildFe = border_get_child(pFe);
        if (pChildFe != NULL)
            fe_build(pCreateStruct->hInstance, hWnd, pChildFe);
        return 0;
    }
    }

    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

void InitBorder(HINSTANCE hInst)
{
    WNDCLASS bdrClass;
    memset(&bdrClass, 0, sizeof(WNDCLASS));
    bdrClass.lpszClassName = szBorderClass;
    bdrClass.style = 0;
    bdrClass.lpfnWndProc = BorderWndProc;
    bdrClass.cbWndExtra = sizeof(long);
    bdrClass.hInstance = hInst;
    bdrClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    bdrClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    bdrClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&bdrClass);
}

HWND create_border_ex(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, FrameworkElement *pBorderFe)
{
    return CreateWindow(szBorderClass,
                        L"",
                        WS_BORDER | WS_CHILD | WS_VISIBLE,
                        x,
                        y,
                        width,
                        height,
                        hParent,
                        (HMENU)0,
                        hInst,
                        pBorderFe);
}
