#include "demo_ui.h"
#include <windows.h>

/*
FrameworkElement* get_demo_ui(DataContext *pDc)
{
    FrameworkElement *pMinGridFe = grid_create_ex(5, 5, 290, 390);
    
    FrameworkElement *pCalScrnGridFe = border_create_ex(0, 0, 270, 50);

    PropertyInfo *pTextProp1 = propinfo_create_ex(PropertyType_Str);
    propinfo_set_binding(pTextProp1, binding_create(L"text1", pDc));
    FrameworkElement *pTbFe1 = textblock_create_ex(5, 5, 280, 20, pTextProp1);

    PropertyInfo *pTextProp2 = propinfo_create_ex(PropertyType_Str);
    propinfo_set_binding(pTextProp2, binding_create(L"text2", pDc));
    FrameworkElement *pTbFe2 = textblock_create_ex(5, 25, 280, 20, pTextProp2);

    fe_add_child(pCalScrnGridFe, pTbFe1);
    fe_add_child(pCalScrnGridFe, pTbFe2);

    fe_add_child(pMinGridFe, pCalScrnGridFe);

    FrameworkElement *pGridFe = grid_create_ex(0, 55, 270, 335);

    fe_add_child(pGridFe, button_create_ex(0, 0, 270, 50, L"Clear", L"ClickClearCommand", pDc));
    fe_add_child(pGridFe, button_create_ex(0, 55, 50, 50, L"7", L"Click7Command", pDc));
    fe_add_child(pGridFe, button_create_ex(55, 55, 50, 50, L"8", L"Click8Command", pDc));
    fe_add_child(pGridFe, button_create_ex(110, 55, 50, 50, L"9", L"Click9Command", pDc));
    fe_add_child(pGridFe, button_create_ex(165, 55, 50, 50, L"/", L"ClickDivideCommand", pDc));
    fe_add_child(pGridFe, button_create_ex(220, 55, 50, 50, L"%", L"", pDc));
    fe_add_child(pGridFe, button_create_ex(0, 110, 50, 50, L"4", L"Click4Command", pDc));
    fe_add_child(pGridFe, button_create_ex(55, 110, 50, 50, L"5", L"Click5Command", pDc));
    fe_add_child(pGridFe, button_create_ex(110, 110, 50, 50, L"6", L"Click6Command", pDc));
    fe_add_child(pGridFe, button_create_ex(165, 110, 50, 50, L"*", L"ClickMultiCommand", pDc));
    fe_add_child(pGridFe, button_create_ex(220, 110, 50, 50, L"1/X", L"", pDc));
    fe_add_child(pGridFe, button_create_ex(0, 165, 50, 50, L"1", L"Click1Command", pDc));
    fe_add_child(pGridFe, button_create_ex(55, 165, 50, 50, L"2", L"Click2Command", pDc));
    fe_add_child(pGridFe, button_create_ex(110, 165, 50, 50, L"3", L"Click3Command", pDc));
    fe_add_child(pGridFe, button_create_ex(165, 165, 50, 50, L"-", L"ClickMinusCommand", pDc));
    fe_add_child(pGridFe, button_create_ex(220, 165, 50, 105, L"=", L"ClickEqCommand", pDc));
    fe_add_child(pGridFe, button_create_ex(0, 220, 105, 50, L"0", L"Click0Command", pDc));
    fe_add_child(pGridFe, button_create_ex(110, 220, 50, 50, L".", L"", pDc));
    fe_add_child(pGridFe, button_create_ex(165, 220, 50, 50, L"+", L"ClickPlusCommand", pDc));

    fe_add_child(pMinGridFe, pGridFe);

    return pMinGridFe;
}

FrameworkElement* get_demo_ui2(DataContext *pDc)
{
    //FrameworkElement *pTvFe = treeview_create_ex(5, 5, 290, 390, pDc);
    FrameworkElement *pTvFe = treeview_create_ex(5, 5, 0, 0);

    PropertyInfo *pTextProp = propinfo_create_ex(PropertyType_Str);
    propinfo_set(pTextProp, (char*)L"tree1");
    FrameworkElement *pTbFe1 = textblock_create(15, 0, 100, 20, pTextProp);
    FrameworkElement *pTviFe1 = tvitem_create_ex(0, 0, 100, 20, pTbFe1);

    PropertyInfo *pTextProp2 = propinfo_create_ex(PropertyType_Str);
    propinfo_set(pTextProp2, (char*)L"tree2");
    FrameworkElement *pTbFe2 = textblock_create(15, 0, 100, 20, pTextProp2);
    FrameworkElement *pTviFe2 = tvitem_create_ex(0, 0, 100, 20, pTbFe2);

    //treeview_add_item(pTvFe, pTviFe1);
    //treeview_add_item(pTvFe, pTviFe2);
    fe_add_child(pTvFe, pTviFe1);
    fe_add_child(pTvFe, pTviFe2);
    //fe_add_child(pTviFe2, pTviFe3);

    return pTvFe;
}
*/

FrameworkElement* get_demo_ui3(AppDataContext *pDc)
{
    FrameworkElement *pGridFe = grid_create_ex(0, 0, SIZE_AUTO, SIZE_AUTO);

    RowDefinition rowdef1, rowdef2;
    rowdef1.height = SIZE_AUTO;
    rowdef2.height = 5;
    grid_add_rowdef(pGridFe, &rowdef1);
    grid_add_rowdef(pGridFe, &rowdef2);
    grid_add_rowdef(pGridFe, &rowdef1);
    grid_add_rowdef(pGridFe, &rowdef2);
    grid_add_rowdef(pGridFe, &rowdef1);
    grid_add_rowdef(pGridFe, &rowdef2);
    grid_add_rowdef(pGridFe, &rowdef1);
    grid_add_rowdef(pGridFe, &rowdef2);
    grid_add_rowdef(pGridFe, &rowdef1);
    grid_add_rowdef(pGridFe, &rowdef2);
    grid_add_rowdef(pGridFe, &rowdef1);

    ColumnDefinition coldef1, coldef2;
    coldef1.width = SIZE_AUTO;
    coldef2.width = 5;
    grid_add_coldef(pGridFe, &coldef1);
    grid_add_coldef(pGridFe, &coldef2);
    grid_add_coldef(pGridFe, &coldef1);
    grid_add_coldef(pGridFe, &coldef2);
    grid_add_coldef(pGridFe, &coldef1);
    grid_add_coldef(pGridFe, &coldef2);
    grid_add_coldef(pGridFe, &coldef1);
    grid_add_coldef(pGridFe, &coldef2);
    grid_add_coldef(pGridFe, &coldef1);
    
    FrameworkElement *pBorder = border_create_ex(0, 0, 270, 50);
    grid_set_col(pGridFe, pBorder, 0);
    grid_set_colspan(pGridFe, pBorder, 9);
    grid_set_row(pGridFe, pBorder, 0);

    FrameworkElement *pCalGridFe = grid_create_ex(0, 0, 270, 50);
    grid_add_rowdef(pCalGridFe, &rowdef1);
    grid_add_rowdef(pCalGridFe, &rowdef2);
    grid_add_rowdef(pCalGridFe, &rowdef1);

    FrameworkElement *pTbFe1 = textblock_create_ex(0, 0, 270, 20);
    textblock_bind_text(pTbFe1, &(pDc->Text1));
    grid_set_row(pCalGridFe, pTbFe1, 0);

    FrameworkElement *pTbFe2 = textblock_create_ex(0, 0, 270, 20);
    textblock_bind_text(pTbFe2, &(pDc->Text2));
    grid_set_row(pCalGridFe, pTbFe2, 2);

    fe_add_child(pCalGridFe, pTbFe1);
    fe_add_child(pCalGridFe, pTbFe2);

    fe_add_child(pBorder, pCalGridFe);
    fe_add_child(pGridFe, pBorder);

    FrameworkElement *pClrBtn = button_create_ex(0, 0, 270, 50, L"Clear");
    button_bind_command(pClrBtn, &(pDc->ClearCommand));
    button_set_cmdparameter(pClrBtn, (char*)pDc);
    grid_set_col(pGridFe, pClrBtn, 0);
    grid_set_colspan(pGridFe, pClrBtn, 9);
    grid_set_row(pGridFe, pClrBtn, 2);
    fe_add_child(pGridFe, pClrBtn);

    FrameworkElement *p7Btn = button_create_ex(0, 0, 50, 50, L"7");
    button_bind_command(p7Btn, &(pDc->SevenCommand));
    button_set_cmdparameter(p7Btn, (char*)pDc);
    grid_set_col(pGridFe, p7Btn, 0);
    grid_set_row(pGridFe, p7Btn, 4);
    fe_add_child(pGridFe, p7Btn);

    FrameworkElement *p8Btn = button_create_ex(0, 0, 50, 50, L"8");
    button_bind_command(p8Btn, &(pDc->EightCommand));
    button_set_cmdparameter(p8Btn, (char*)pDc);
    grid_set_col(pGridFe, p8Btn, 2);
    grid_set_row(pGridFe, p8Btn, 4);
    fe_add_child(pGridFe, p8Btn);

    FrameworkElement *p9Btn = button_create_ex(0, 0, 50, 50, L"9");
    button_bind_command(p9Btn, &(pDc->NineCommand));
    button_set_cmdparameter(p9Btn, (char*)pDc);
    grid_set_col(pGridFe, p9Btn, 4);
    grid_set_row(pGridFe, p9Btn, 4);
    fe_add_child(pGridFe, p9Btn);

    FrameworkElement *pDivBtn = button_create_ex(0, 0, 50, 50, L"/");
    button_bind_command(pDivBtn, &(pDc->DivideCommand));
    button_set_cmdparameter(pDivBtn, (char*)pDc);
    grid_set_col(pGridFe, pDivBtn, 6);
    grid_set_row(pGridFe, pDivBtn, 4);
    fe_add_child(pGridFe, pDivBtn);

    FrameworkElement *pModBtn = button_create_ex(0, 0, 50, 50, L"%"); 
    //button_bind_command(pModBtn, &(pDc->ModCommand));
    //button_set_cmdparameter(pModBtn, (char*)pDc);
    grid_set_col(pGridFe, pModBtn, 8);
    grid_set_row(pGridFe, pModBtn, 4);
    fe_add_child(pGridFe, pModBtn);

    FrameworkElement *p4Btn = button_create_ex(0, 0, 50, 50, L"4");
    button_bind_command(p4Btn, &(pDc->FourCommand));
    button_set_cmdparameter(p4Btn, (char*)pDc);
    grid_set_col(pGridFe, p4Btn, 0);
    grid_set_row(pGridFe, p4Btn, 6);
    fe_add_child(pGridFe, p4Btn);

    FrameworkElement *p5Btn = button_create_ex(0, 0, 50, 50, L"5");
    button_bind_command(p5Btn, &(pDc->FiveCommand));
    button_set_cmdparameter(p5Btn, (char*)pDc);
    grid_set_col(pGridFe, p5Btn, 2);
    grid_set_row(pGridFe, p5Btn, 6);
    fe_add_child(pGridFe, p5Btn);

    FrameworkElement *p6Btn =button_create_ex(0, 0, 50, 50, L"6"); 
    button_bind_command(p6Btn, &(pDc->SixCommand));
    button_set_cmdparameter(p6Btn, (char*)pDc);
    grid_set_col(pGridFe, p6Btn, 4);
    grid_set_row(pGridFe, p6Btn, 6);
    fe_add_child(pGridFe, p6Btn);

    FrameworkElement *pMulBtn =button_create_ex(0, 0, 50, 50, L"*"); 
    button_bind_command(pMulBtn, &(pDc->MultiCommand));
    button_set_cmdparameter(pMulBtn, (char*)pDc);
    grid_set_col(pGridFe, pMulBtn, 6);
    grid_set_row(pGridFe, pMulBtn, 6);
    fe_add_child(pGridFe, pMulBtn);

    FrameworkElement *p1xBtn =button_create_ex(0, 0, 50, 50, L"1/X"); 
    //button_bind_command(p1xBtn, &(pDc->SevenCommand));
    //button_set_cmdparameter(p1xBtn, (char*)pDc);
    grid_set_col(pGridFe, p1xBtn, 8);
    grid_set_row(pGridFe, p1xBtn, 6);
    fe_add_child(pGridFe, p1xBtn);

    FrameworkElement *p1Btn =button_create_ex(0, 0, 50, 50, L"1"); 
    button_bind_command(p1Btn, &(pDc->OneCommand));
    button_set_cmdparameter(p1Btn, (char*)pDc);
    grid_set_col(pGridFe, p1Btn, 0);
    grid_set_row(pGridFe, p1Btn, 8);
    fe_add_child(pGridFe, p1Btn);

    FrameworkElement *p2Btn =button_create_ex(0, 0, 50, 50, L"2"); 
    button_bind_command(p2Btn, &(pDc->TwoCommand));
    button_set_cmdparameter(p2Btn, (char*)pDc);
    grid_set_col(pGridFe, p2Btn, 2);
    grid_set_row(pGridFe, p2Btn, 8);
    fe_add_child(pGridFe, p2Btn);

    FrameworkElement *p3Btn = button_create_ex(0, 0, 50, 50, L"3");
    button_bind_command(p3Btn, &(pDc->ThreeCommand));
    button_set_cmdparameter(p3Btn, (char*)pDc);
    grid_set_col(pGridFe, p3Btn, 4);
    grid_set_row(pGridFe, p3Btn, 8);
    fe_add_child(pGridFe, p3Btn);

    FrameworkElement *pMinBtn = button_create_ex(0, 0, 50, 50, L"-"); 
    button_bind_command(pMinBtn, &(pDc->MinusCommand));
    button_set_cmdparameter(pMinBtn, (char*)pDc);
    grid_set_col(pGridFe, pMinBtn, 6);
    grid_set_row(pGridFe, pMinBtn, 8);
    fe_add_child(pGridFe, pMinBtn);
    
    FrameworkElement *pEqBtn = button_create_ex(0, 0, 50, 105, L"="); 
    button_bind_command(pEqBtn, &(pDc->EqCommand));
    button_set_cmdparameter(pEqBtn, (char*)pDc);
    grid_set_col(pGridFe, pEqBtn, 8);
    grid_set_row(pGridFe, pEqBtn, 8);
    grid_set_rowspan(pGridFe, pEqBtn, 3);
    fe_add_child(pGridFe, pEqBtn);

    FrameworkElement *p0Btn = button_create_ex(0, 0, 105, 50, L"0");
    button_bind_command(p0Btn, &(pDc->ZeroCommand));
    button_set_cmdparameter(p0Btn, (char*)pDc);
    grid_set_col(pGridFe, p0Btn, 0);
    grid_set_colspan(pGridFe, p0Btn, 3);
    grid_set_row(pGridFe, p0Btn, 10);
    fe_add_child(pGridFe, p0Btn);

    FrameworkElement *pDotBtn = button_create_ex(0, 0, 50, 50, L"."); 
    //button_bind_command(pDotBtn, &(pDc->DotCommand));
    //button_set_cmdparameter(pDotBtn, (char*)pDc);
    grid_set_col(pGridFe, pDotBtn, 4);
    grid_set_row(pGridFe, pDotBtn, 10);
    fe_add_child(pGridFe, pDotBtn);

    FrameworkElement *pPlusBtn = button_create_ex(0, 0, 50, 50, L"+"); 
    button_bind_command(pPlusBtn, &(pDc->PlusCommand));
    button_set_cmdparameter(pPlusBtn, (char*)pDc);
    grid_set_col(pGridFe, pPlusBtn, 6);
    grid_set_row(pGridFe, pPlusBtn, 10);
    fe_add_child(pGridFe, pPlusBtn);

    return pGridFe;
}
