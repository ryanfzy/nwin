#ifndef TVITEM_TOGGLEBTN_H
#define TVITEM_TOGGLEBTN_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>
#include "../ngf/zaml_structs.h"

void InitTvItemToggleBtn(HINSTANCE hInst);
HWND CreateTvItemToggleBtn(HINSTANCE hInst, HWND hParent, TvItemInfo *pInfo);

#endif
