#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>
#include "../ngf/zaml_structs.h"

void InitGrid(HINSTANCE hInst);
HWND CreateGrid(HINSTANCE hInst, HWND hParent, GridInfo *pGridInfo);
HWND create_grid_ex(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, FrameworkElement *pGridFe);

#endif
