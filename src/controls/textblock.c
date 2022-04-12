#include "textblock.h"

static const wchar_t *szTextBlockClass = L"textblock";

static void textchanged_callback(char *pEvtArg)
{
    HWND *phWnd = (HWND*)pEvtArg;
    if (phWnd != NULL)
        InvalidateRect(*phWnd, NULL, TRUE);
}

static void _init(HWND hWnd, FrameworkElement *pFe)
{
    SetWindowLong(hWnd, GWL_USERDATA, (LONG)pFe);
    tb_sub_textchanged_evt(pFe, textchanged_callback, (char*)&hWnd, sizeof(HWND));
}

static LRESULT CALLBACK TextBlockWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    //RECT sRect;

    switch (nMsg)
    {
    case WM_CREATE:
    {
        CREATESTRUCT *pCreateStruct = (CREATESTRUCT*)lParam;
        _init(hWnd, (FrameworkElement*)(pCreateStruct->lpCreateParams));
        return 0;
    }

    case WM_PAINT:
    {
        FrameworkElement *pFe = (FrameworkElement*)GetWindowLong(hWnd, GWL_USERDATA);
        if (pFe != NULL)
        {
            hdc = BeginPaint(hWnd, &ps);
            wchar_t *szText = textblock_get_text(pFe);
            if (szText != NULL)
            {
                UINT uHorAlign = DT_LEFT;
                HorizontalAlignmentType eHorAlign = textblock_get_contenthorizontal(pFe);
                if (eHorAlign == HorizontalAlignment_Right)
                    uHorAlign = DT_RIGHT;
                else if (eHorAlign == HorizontalAlignment_Center)
                    uHorAlign = DT_CENTER;
                DrawText(hdc, szText, wcslen(szText), &(ps.rcPaint), DT_VCENTER | uHorAlign);
            }

            EndPaint(hWnd, &ps);
        }
        return 0;
    }
    default:
        break;
    }
    
    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

HWND create_textblock_ex(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, FrameworkElement *pFe)
{
    return CreateWindow(szTextBlockClass,
                        L"",
                        WS_CHILD | WS_VISIBLE,
                        x,
                        y,
                        width,
                        height,
                        hParent,
                        (HMENU)0,
                        hInst,
                        pFe);
}

void InitTextBlock(HINSTANCE hInst)
{
    WNDCLASS tbClass;
    memset(&tbClass, 0, sizeof(WNDCLASS));
    tbClass.lpszClassName = szTextBlockClass;
    tbClass.style = 0;
    tbClass.lpfnWndProc = TextBlockWndProc;
    tbClass.cbWndExtra = sizeof(long);
    tbClass.hInstance = hInst;
    tbClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    tbClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    tbClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&tbClass);
}
