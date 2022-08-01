#ifndef BUTTON_H
#define BUTTON_H

#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include "ngf/zaml_structs.h"

void InitButton(HINSTANCE hInst);
HWND CreateButton(HINSTANCE hInst, HWND hParent, ButtonInfo *pButtonInfo);

HWND create_button_ex(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, FrameworkElement *pFe);

#endif
