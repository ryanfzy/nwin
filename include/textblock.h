#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>
#include "ngf/zaml_structs.h"

void InitTextBlock(HINSTANCE hInst);
//HWND CreateTextBlock(HINSTANCE hInst, HWND hParent, TextBlockInfo *pTextBlockInfo);

HWND create_textblock_ex(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, FrameworkElement *pFe);

#endif
