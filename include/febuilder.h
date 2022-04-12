#ifndef FEBUILDER_H
#define FEBUILDER_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "ngf/zaml_structs.h"

void InitFrameworkElements(HINSTANCE hInst);
//HWND BuildFrameworkElement(HINSTANCE hInst, HWND hParent, FrameworkElement *pFe);

HWND fe_build(HINSTANCE hInst, HWND hParent, FrameworkElement *pFe);
HWND fe_build_ex(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, FrameworkElement *pFe);

#endif
