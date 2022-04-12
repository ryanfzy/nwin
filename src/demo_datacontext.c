#include <windows.h>
#include "demo_datacontext.h"
#include "lib/stack.h"
#include "calculation.h"
#include "ngf/evthandler.h"

static void add_number(AppDataContext *pDc, int iNum)
{
    if (pDc != NULL)
    {
        wchar_t *pText = stritem_get(&(pDc->Text2));
        wchar_t szText[128] = {0};
        wchar_t szNum[2] = {0};

        if (pText != NULL)
            wmemcpy(szText, pText, wcslen(pText));
        _snwprintf(szNum, 2, L"%d", iNum);
        wcscat(szText, szNum);

        stritem_set(&(pDc->Text2), szText);
    }
}

static void do_push_number(Stack *pStack, wchar_t *pText)
{
    if (pStack != NULL && pText != NULL)
    {
        CalItemInfo num;
        wchar_t *ptr;

        num.lnum = wcstol(pText, &ptr, 10);
        num.etype = CALITEMTYPE_NUM;
        stack_push(pStack, (char*)&num, sizeof(CalItemInfo));
    }
}

static void do_push_operator(Stack *pStack, CalItemType eType)
{
    if (pStack != NULL)
    {
        CalItemInfo oper;
        oper.etype = eType;

        stack_push(pStack, (char*)&oper, sizeof(CalItemInfo));
    }
}

static void push_operator(AppDataContext *pDc, CalItemType eType)
{
    wchar_t *pText1 = stritem_get(&(pDc->Text1));
    wchar_t *pText2 = stritem_get(&(pDc->Text2));

    Stack *pStack = &(pDc->calstack);
    if (pStack != NULL && pText2 != NULL)
    {
        do_push_number(pStack, pText2);
        do_push_operator(pStack, eType);

        wchar_t szText1[128] = {0};
        wchar_t szText2[128] = {0};
        wchar_t szOp[2] = {0};

        if (pText1 != NULL)
            wmemcpy(szText1, pText1, wcslen(pText1));
        wmemcpy(szText2, pText2, wcslen(pText2));

        switch (eType)
        {
        case CALITEMTYPE_PLUS:
            wcscpy(szOp, L"+");
            break;
        case CALITEMTYPE_MINUS:
            wcscpy(szOp, L"-");
            break;
        case CALITEMTYPE_DIVIDE:
            wcscpy(szOp, L"/");
            break;
        case CALITEMTYPE_MULTIPLY:
            wcscpy(szOp, L"*");
            break;
        default:
            break;
        }
    
        if (wcslen(szText1) > 0)
            wcscat(szText1, L" ");
        wcscat(szText1, szText2);
        wcscat(szText1, L" ");
        wcscat(szText1, szOp);
        
        stritem_set(&(pDc->Text1), szText1);
        stritem_set(&(pDc->Text2), NULL);
    }

}

void ClearCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
    {
        stritem_set(&(pDc->Text1), NULL);
        stritem_set(&(pDc->Text2), NULL);
        // stack need a clear method
        stack_destroy(&(pDc->calstack));
    }
} 

void OneCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        add_number(pDc, 1);
}

void TwoCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        add_number(pDc, 2);
}

void ThreeCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        add_number(pDc, 3);
}

void FourCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        add_number(pDc, 4);
}

void FiveCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        add_number(pDc, 5);
}

void SixCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        add_number(pDc, 6);
}

void SevenCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        add_number(pDc, 7);
}

void EightCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        add_number(pDc, 8);
}

void NineCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        add_number(pDc, 9);
}

void ZeroCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        add_number(pDc, 0);
}

void PlusCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        push_operator(pDc, CALITEMTYPE_PLUS);
}

void MinusCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        push_operator(pDc, CALITEMTYPE_MINUS);
}

void DivideCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        push_operator(pDc, CALITEMTYPE_DIVIDE);
}

void MultiCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
        push_operator(pDc, CALITEMTYPE_MULTIPLY);
}

void EqCommand(char *pCmdParameter)
{
    AppDataContext *pDc = (AppDataContext*)pCmdParameter;
    if (pDc != NULL)
    {
        wchar_t *pText = stritem_get(&(pDc->Text2));
        Stack *pStack = &(pDc->calstack);
        if (pStack != NULL && pText != NULL)
        {
            do_push_number(pStack, pText);

            wchar_t szText1[128] = {0};
            wchar_t szText2[128] = {0};

            long ret = calculate_result(pStack, szText1);

            _snwprintf(szText2, 128, L"%ld", ret);

            stritem_set(&(pDc->Text1), szText1);
            stritem_set(&(pDc->Text2), szText2);

            // clear the stack
            stack_destroy(pStack);
        }
    }
}

static void appdc_init(AppDataContext *pDc)
{
    if (pDc != NULL)
    {
        stritem_init(&(pDc->Text1));
        stritem_init(&(pDc->Text2));
        cmditem_init(&(pDc->ClearCommand));
        cmditem_init(&(pDc->OneCommand));
        cmditem_init(&(pDc->TwoCommand));
        cmditem_init(&(pDc->ThreeCommand));
        cmditem_init(&(pDc->FourCommand));
        cmditem_init(&(pDc->FiveCommand));
        cmditem_init(&(pDc->SixCommand));
        cmditem_init(&(pDc->SevenCommand));
        cmditem_init(&(pDc->EightCommand));
        cmditem_init(&(pDc->NineCommand));
        cmditem_init(&(pDc->ZeroCommand));
        cmditem_init(&(pDc->PlusCommand));
        cmditem_init(&(pDc->MinusCommand));
        cmditem_init(&(pDc->MultiCommand));
        cmditem_init(&(pDc->DivideCommand));
        cmditem_init(&(pDc->EqCommand));

        stack_init(&(pDc->calstack));
    }
}

static void appdc_destroy(AppDataContext *pDc)
{
    if (pDc != NULL)
    {
        stritem_destroy(&(pDc->Text1));
        stritem_destroy(&(pDc->Text2));
        cmditem_destroy(&(pDc->ClearCommand));
        cmditem_destroy(&(pDc->OneCommand));
        cmditem_destroy(&(pDc->TwoCommand));
        cmditem_destroy(&(pDc->ThreeCommand));
        cmditem_destroy(&(pDc->FourCommand));
        cmditem_destroy(&(pDc->FiveCommand));
        cmditem_destroy(&(pDc->SixCommand));
        cmditem_destroy(&(pDc->SevenCommand));
        cmditem_destroy(&(pDc->EightCommand));
        cmditem_destroy(&(pDc->NineCommand));
        cmditem_destroy(&(pDc->ZeroCommand));
        cmditem_destroy(&(pDc->PlusCommand));
        cmditem_destroy(&(pDc->MinusCommand));
        cmditem_destroy(&(pDc->MultiCommand));
        cmditem_destroy(&(pDc->DivideCommand));
        cmditem_destroy(&(pDc->EqCommand));

        stack_destroy(&(pDc->calstack));
    }
}

static void appdc_set(AppDataContext *pDc)
{
    if (pDc != NULL)
    {
        cmditem_set(&(pDc->ClearCommand), ClearCommand);
        cmditem_set(&(pDc->OneCommand), OneCommand);
        cmditem_set(&(pDc->TwoCommand), TwoCommand);
        cmditem_set(&(pDc->ThreeCommand), ThreeCommand);
        cmditem_set(&(pDc->FourCommand), FourCommand);
        cmditem_set(&(pDc->FiveCommand), FiveCommand);
        cmditem_set(&(pDc->SixCommand), SixCommand);
        cmditem_set(&(pDc->SevenCommand), SevenCommand);
        cmditem_set(&(pDc->EightCommand), EightCommand);
        cmditem_set(&(pDc->NineCommand), NineCommand);
        cmditem_set(&(pDc->ZeroCommand), ZeroCommand);
        cmditem_set(&(pDc->PlusCommand), PlusCommand);
        cmditem_set(&(pDc->MinusCommand), MinusCommand);
        cmditem_set(&(pDc->MultiCommand), MultiCommand);
        cmditem_set(&(pDc->DivideCommand), DivideCommand);
        cmditem_set(&(pDc->EqCommand), EqCommand);
    }
}

AppDataContext* appdc_create()
{
    AppDataContext *pDc = malloc(sizeof(AppDataContext));
    appdc_init(pDc);
    appdc_set(pDc);
    return pDc;
}

void appdc_free(AppDataContext *pDc)
{
    if (pDc != NULL)
    {
        appdc_destroy(pDc);
        free(pDc);
    }
}
