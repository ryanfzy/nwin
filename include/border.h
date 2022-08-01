#ifndef BORDER_H
#define BORDER_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>
#include "ngf/zaml_structs.h"

void InitBorder(HINSTANCE hInst);
HWND create_border_ex(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, FrameworkElement *pBorderFe);

#endif
