#include "febuilder.h"
#include "button.h"
#include "border.h"
#include "textblock.h"
#include "tvitem.h"
#include "grid.h"
#include "treeview.h"
#include "messages.h"

void InitFrameworkElements(HINSTANCE hInst)
{
    InitGrid(hInst);
    InitTreeView(hInst);
    InitButton(hInst);
    InitBorder(hInst);
    InitTextBlock(hInst);
    //InitTreeViewItem(hInst);
}

/*
HWND BuildFrameworkElement(HINSTANCE hInst, HWND hParent, FrameworkElement *pFe)
{
    HWND hChild = NULL;
    if (pFe != NULL)
    {
        if (pFe->iType == FE_GRID)
            hChild = CreateGrid(hInst, hParent, (GridInfo*)(pFe->pElement));
        else if (pFe->iType == FE_TREEVIEW)
            hChild = CreateTreeView(hInst, hParent, (TreeViewInfo*)(pFe->pElement));
        else if (pFe->iType == FE_BUTTON)
            hChild = CreateButton(hInst, hParent, (ButtonInfo*)(pFe->pElement));
        else if (pFe->iType == FE_TEXTBLOCK)
            hChild = CreateTextBlock(hInst, hParent, (TextBlockInfo*)(pFe->pElement));
        else if (pFe->iType == FE_BORDER)
            hChild = CreateBorder(hInst, hParent, (BorderInfo*)(pFe->pElement));
        else if (pFe->iType == FE_TVITEM)
            hChild = CreateTreeViewItem(hInst, hParent, (TvItemInfo*)(pFe->pElement));

        //for (int i = 0; i < zaml_get_children_count(pFe); i++)
            //SendMessage(hChild, FE_ADDCHILD, (WPARAM)zaml_get_child(pFe, i), 0);
            //BuildFrameworkElement(hInst, hChild, zaml_get_child(pFe, i));
    }

    return hChild;
}
*/

HWND fe_build_ex(HINSTANCE hInst, HWND hParent, int x, int y, int width, int height, FrameworkElement *pFe)
{
    HWND hChild = NULL;
    if (pFe != NULL)
    {
        if (pFe->iType == FE_GRID)
            hChild = create_grid_ex(hInst, hParent, x, y, width, height, pFe);
        //else if (pFe->iType == FE_TREEVIEW)
            //hChild = CreateTreeView(hInst, hParent, (TreeViewInfo*)(pFe->pElement));
        else if (pFe->iType == FE_BUTTON)
            hChild = create_button_ex(hInst, hParent, x, y, width, height, pFe);
        else if (pFe->iType == FE_TEXTBLOCK)
            hChild = create_textblock_ex(hInst, hParent, x, y, width, height, pFe);
        else if (pFe->iType == FE_BORDER)
            hChild = create_border_ex(hInst, hParent, x, y, width, height, pFe);
        //else if (pFe->iType == FE_TVITEM)
            //hChild = CreateTreeViewItem(hInst, hParent, (TvItemInfo*)(pFe->pElement));
    }
    return hChild;
}

HWND fe_build(HINSTANCE hInst, HWND hParent, FrameworkElement *pFe)
{
    HWND hChild = NULL;
    if (pFe != NULL)
    {
        FePos pos = fe_get_pos(pFe);
        FeSize size = fe_get_size(pFe);
        hChild = fe_build_ex(hInst, hParent, pos.x, pos.y, size.width, size.height, pFe);
    }
    return hChild;
}

