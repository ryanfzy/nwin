#ifndef TVITEM_H
#define TVITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>
#include "../ngf/zaml_structs.h"

void InitTreeViewItem(HINSTANCE hInst);
HWND CreateTreeViewItem(HINSTANCE hInst, HWND hParent, TvItemInfo *pInfo);

#endif

