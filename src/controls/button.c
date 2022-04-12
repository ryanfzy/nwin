#include "button.h"

static const wchar_t *szButtonClass = L"rbutton";

FrameworkElement* _get_fe(HWND hWnd)
{
    return  (FrameworkElement*)GetWindowLong(hWnd, GWL_USERDATA);
}

static HWND DoCreateButton(HWND hWnd, wchar_t *pName, int iOffsetX, int iOffsetY, int iWidth, int iHeight, int iButtonId, HINSTANCE hInstance)
{
    HWND hWndButton = CreateWindow(
        L"BUTTON",
        pName,
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

static LRESULT CALLBACK ButtonWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    switch (nMsg)
    {
        case WM_CREATE:
        {
            CREATESTRUCT *pCreateStruct = (CREATESTRUCT*)lParam;
            FrameworkElement *pBtnFe = (FrameworkElement*)(pCreateStruct->lpCreateParams);
            SetWindowLong(hWnd, GWL_USERDATA, (LONG)pBtnFe);

            //ButtonInfo *pBtnInfo = (ButtonInfo*)(pBtnFe->pElement);
            wchar_t *szText = button_get_text(pBtnFe);
            DoCreateButton(hWnd, 
                    szText,
                    0,
                    0,
                    pCreateStruct->cx,
                    pCreateStruct->cy,
                    0,
                    pCreateStruct->hInstance);


            return 0;
        }
        case WM_COMMAND:
        {
            if (HIWORD(wParam) == BN_CLICKED)
            {
                FrameworkElement *pFe = _get_fe(hWnd);
                if (pFe != NULL)
                {
                    ButtonInfo *pInfo = (ButtonInfo*)(pFe->pElement);
                    if (pInfo != NULL)
                        btn_raise_click_evt(pFe);
                }
                /*
                ButtonInfo *pBtnInfo = (ButtonInfo*)GetWindowLong(hWnd, GWL_USERDATA);
                if (pBtnInfo->szCommand != NULL && wcslen(pBtnInfo->szCommand) > 0)
                {
                    DataContext_run_command(pBtnInfo->controlInfo.pDc, pBtnInfo->szCommand);
                }
                */
            }
            return 0;
        }

    }
    
    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

HWND CreateButton(HINSTANCE hInst, HWND hParent, ButtonInfo *pButtonInfo)
{
    return CreateWindow(szButtonClass,
                        L"",
                        WS_CHILD|WS_VISIBLE,
                        pButtonInfo->controlInfo.visualInfo.x,
                        pButtonInfo->controlInfo.visualInfo.y,
                        pButtonInfo->controlInfo.visualInfo.width,
                        pButtonInfo->controlInfo.visualInfo.height,
                        hParent,
                        0,//(HMENU)pButtonInfo->controlInfo.iId,
                        hInst,
                        pButtonInfo);
}

void InitButton(HINSTANCE hInst)
{
    WNDCLASS btnClass;
    memset(&btnClass, 0, sizeof(WNDCLASS));
    btnClass.lpszClassName = szButtonClass;
    btnClass.style = 0;
    btnClass.lpfnWndProc = ButtonWndProc;
    btnClass.cbWndExtra = sizeof(long);
    btnClass.hInstance = hInst;
    btnClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    btnClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    btnClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&btnClass);
}

HWND create_button_ex(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, FrameworkElement *pFe)
{
    return CreateWindow(szButtonClass,
                        L"",
                        WS_CHILD|WS_VISIBLE,
                        x,
                        y,
                        width,
                        height,
                        hParent,
                        0,
                        hInst,
                        pFe);
}
