#include "grid.h"
#include "febuilder.h"
#include "messages.h"

static const wchar_t *szGridClass = L"grid";

void _grid_build_children(HINSTANCE hInst, HWND hParent, FrameworkElement *pFe)
{
    int iChildren = zaml_get_children_count(pFe);
    if (iChildren > 0)
    {
        for (int iChild = 0; iChild < iChildren; iChild++)
        {
            FrameworkElement *pChildFe = zaml_get_child(pFe, iChild);
            if (pChildFe != NULL)
            {
                FePos pos = fe_get_pos(pChildFe);
                FeSize size = fe_get_size(pChildFe);
                fe_build_ex(hInst, hParent, pos.x, pos.y, size.width, size.height, pChildFe);
            }
        }
    }
}

static LRESULT CALLBACK GridWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    switch (nMsg)
    {
    case WM_CREATE:
    {
        CREATESTRUCT *pCreateStruct = (CREATESTRUCT*)lParam;
        FrameworkElement *pGridFe = (FrameworkElement*)(pCreateStruct->lpCreateParams);
        SetWindowLong(hWnd, GWL_USERDATA, (LONG)pGridFe);

        _grid_build_children(pCreateStruct->hInstance, hWnd, pGridFe);
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
    default:
        break;
    }

    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

void InitGrid(HINSTANCE hInst)
{
    WNDCLASS gridClass;
    memset(&gridClass, 0, sizeof(WNDCLASS));
    gridClass.lpszClassName = szGridClass;
    gridClass.style = 0;
    gridClass.lpfnWndProc = GridWndProc;
    gridClass.cbWndExtra = sizeof(long);
    gridClass.hInstance = hInst;
    gridClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    gridClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    gridClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&gridClass);
}

HWND CreateGrid(HINSTANCE hInst, HWND hParent, GridInfo *pGridInfo)
{
    return CreateWindow(szGridClass,
                        L"",
                        WS_CHILD|WS_VISIBLE,
                        pGridInfo->layoutInfo.visualInfo.x,
                        pGridInfo->layoutInfo.visualInfo.y,
                        max(pGridInfo->layoutInfo.visualInfo.width, 0),
                        max(pGridInfo->layoutInfo.visualInfo.height, 0),
                        hParent,
                        (HMENU)0,
                        hInst,
                        pGridInfo);
}

HWND create_grid_ex(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, FrameworkElement *pGridFe) 
{
    wchar_t buf[1024] = {0};
    wsprintf(buf, L"x(%d),y(%d),width(%d),height(%d)", x, y, width, height);
    MessageBox(NULL, buf, buf, MB_OK);
    return CreateWindow(szGridClass,
                        L"",
                        WS_CHILD|WS_VISIBLE,
                        x,
                        y,
                        width,
                        height,
                        hParent,
                        (HMENU)0,
                        hInst,
                        pGridFe);
}
