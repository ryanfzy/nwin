#include "treeview.h"
#include "febuilder.h"
#include "messages.h"

static const wchar_t *szTreeViewClass = L"treeview";

static LRESULT CALLBACK TreeViewWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    switch (nMsg)
    {
    case WM_CREATE:
    {
        CREATESTRUCT *pCreateStruct = (CREATESTRUCT*)lParam;
        TreeViewInfo *pInfo = (TreeViewInfo*)(pCreateStruct->lpCreateParams);
        SetWindowLong(hWnd, GWL_USERDATA, (LONG)pInfo);
        return 0;
    }
    /*
    case FE_ADDCHILD:
    {
        FrameworkElement *pChildFe = (FrameworkElement*)wParam;
        if (pChildFe != NULL)
        {
            HINSTANCE hInst = GetModuleHandle(NULL);
            BuildFrameworkElement(hInst, hWnd, pChildFe);
        }
        return 0;
    }
    */
    }

    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

void InitTreeView(HINSTANCE hInst)
{
    WNDCLASS cls;
    memset(&cls, 0, sizeof(WNDCLASS));
    cls.lpszClassName = szTreeViewClass;
    cls.style = 0;
    cls.lpfnWndProc = TreeViewWndProc;
    cls.cbWndExtra = sizeof(long);
    cls.hInstance = hInst;
    cls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    cls.hCursor = LoadCursor(NULL, IDC_ARROW);
    cls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&cls);
}

HWND CreateTreeView(HINSTANCE hInst, HWND hParent, TreeViewInfo *pInfo)
{
    return CreateWindow(szTreeViewClass,
                        L"",
                        WS_CHILD|WS_VISIBLE,
                        pInfo->layoutInfo.visualInfo.x,
                        pInfo->layoutInfo.visualInfo.y,
                        pInfo->layoutInfo.visualInfo.width,
                        pInfo->layoutInfo.visualInfo.height,
                        hParent,
                        (HMENU)0,
                        hInst,
                        pInfo);
}
