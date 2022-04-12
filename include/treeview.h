#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>
#include "../ngf/zaml_structs.h"

void InitTreeView(HINSTANCE hInst);
HWND CreateTreeView(HINSTANCE hInst, HWND hParent, TreeViewInfo *pTvInfo);

#endif
