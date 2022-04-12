#include "tvitem-togglebtn.h"
#include "../messages.h"

static const wchar_t *szTvItemToggleBtnClass = L"treeview-togglebutton";

static LRESULT CALLBACK TvItemToggleBtnWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (nMsg)
    {
    case WM_CREATE:
    {
        CREATESTRUCT *pCreateStruct = (CREATESTRUCT*)lParam;
        TvItemInfo *pInfo = (TvItemInfo*)(pCreateStruct->lpCreateParams);
        SetWindowLong(hWnd, GWL_USERDATA, (LONG)pInfo);
        return 0;
    }
    case WM_PAINT:
    {
        TvItemInfo *pInfo = (TvItemInfo*)GetWindowLong(hWnd, GWL_USERDATA);
        if (pInfo)
        {
            hdc = BeginPaint(hWnd, &ps);
            Rectangle(hdc, 0, 0, 10, 10);
            MoveToEx(hdc, 0, 5, NULL);
            LineTo(hdc, 10, 5);
            if (!pInfo->bExpanded)
            {
                MoveToEx(hdc, 5, 0, NULL);
                LineTo(hdc, 5, 10);
            }
            EndPaint(hWnd, &ps);
        }
        return 0;
    }
    case WM_LBUTTONUP:
    {
        TvItemInfo *pInfo = (TvItemInfo*)GetWindowLong(hWnd, GWL_USERDATA);
        if (pInfo != NULL)
        {
            pInfo->bExpanded = !pInfo->bExpanded;
            SendMessage(GetParent(hWnd), WM_COMMAND, TVITEMTOGGLEBTN, pInfo->bExpanded ? TRUE : FALSE);
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    }

    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

void InitTvItemToggleBtn(HINSTANCE hInst)
{
    WNDCLASS cls;
    memset(&cls, 0, sizeof(WNDCLASS));
    cls.lpszClassName = szTvItemToggleBtnClass;
    cls.style = 0;
    cls.lpfnWndProc = TvItemToggleBtnWndProc;
    cls.cbWndExtra = 0;
    cls.hInstance = hInst;
    cls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    cls.hCursor = LoadCursor(NULL, IDC_ARROW);
    cls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&cls);
}

HWND CreateTvItemToggleBtn(HINSTANCE hInst, HWND hParent, TvItemInfo *pInfo)
{
    return CreateWindow(szTvItemToggleBtnClass,
                        L"",
                        WS_CHILD|WS_VISIBLE,
                        0, 0, 10, 10,
                        //pInfo->controlInfo.visualInfo.x,
                        //pInfo->controlInfo.visualInfo.y,
                        //pInfo->controlInfo.visualInfo.width,
                        //pInfo->controlInfo.visualInfo.height,
                        hParent,
                        (HMENU)0,
                        hInst,
                        pInfo);
}
