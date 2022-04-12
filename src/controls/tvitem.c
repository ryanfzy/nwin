#include "tvitem.h"
#include "tvItem-togglebtn.h"
#include "../messages.h"
#include "../febuilder.h"

static const wchar_t *szTvItemClass = L"treeviewitem";

static LRESULT CALLBACK TvItemWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    /*
    HDC hdc;
    PAINTSTRUCT ps;
    RECT sRect;
    */

    switch (nMsg)
    {
    case WM_CREATE:
    {
        CREATESTRUCT *pCreateStruct = (CREATESTRUCT*)lParam;
        TvItemInfo *pInfo = (TvItemInfo*)(pCreateStruct->lpCreateParams);
        SetWindowLong(hWnd, GWL_USERDATA, (LONG)pInfo);

        CreateTvItemToggleBtn(pCreateStruct->hInstance, hWnd, pInfo);
        //if (pInfo->pHeaderFe != NULL)
            //BuildFrameworkElement(pCreateStruct->hInstance, hWnd, pInfo->pHeaderFe);

        return 0;
    }
    /*
    case WM_PAINT:
    {
        TvItemInfo *pInfo = (TvItemInfo*)GetWindowLong(hWnd, GWL_USERDATA);
        if (pInfo != NULL)
        {
            hdc = BeginPaint(hWnd, &ps);

            sRect.left = ps.rcPaint.left + 12;
            sRect.top = ps.rcPaint.top;
            sRect.right = ps.rcPaint.right;
            sRect.bottom = ps.rcPaint.bottom;

            DrawText(hdc, pInfo->szHeader, wcslen(pInfo->szHeader), &sRect, DT_VCENTER);
            EndPaint(hWnd, &ps);
        }
        return 0;
    }
    */
    case WM_COMMAND:
    {
        switch (wParam)
        {
        case TVITEMTOGGLEBTN:
        {
            if (lParam == TRUE)
                MessageBox(NULL, L"true", L"true", MB_OK);
            else
                MessageBox(NULL, L"false", L"false", MB_OK);
        }
        }
    }
    }

    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

void InitTreeViewItem(HINSTANCE hInst)
{
    WNDCLASS cls;
    memset(&cls, 0, sizeof(WNDCLASS));
    cls.lpszClassName = szTvItemClass;
    cls.style = 0;
    cls.lpfnWndProc = TvItemWndProc;
    cls.cbWndExtra = sizeof(long);
    cls.hInstance = hInst;
    cls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    cls.hCursor = LoadCursor(NULL, IDC_ARROW);
    cls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&cls);

    InitTvItemToggleBtn(hInst);
}

HWND CreateTreeViewItem(HINSTANCE hInst, HWND hParent, TvItemInfo *pInfo)
{
    return CreateWindow(szTvItemClass,
                        L"",
                        WS_CHILD|WS_VISIBLE,
                        pInfo->controlInfo.visualInfo.x,
                        pInfo->controlInfo.visualInfo.y,
                        pInfo->controlInfo.visualInfo.width,
                        pInfo->controlInfo.visualInfo.height,
                        hParent,
                        (HMENU)0,
                        hInst,
                        pInfo);
}

