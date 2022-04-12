#ifndef DEMO_DATACONTEXT_H
#define DEMO_DATACONTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "lib/stack.h"
#include "ngf/dcitem.h"

typedef struct _dataContext
{
    StrItem Text1;
    StrItem Text2;
    CmdItem ClearCommand;
    CmdItem OneCommand;
    CmdItem TwoCommand;
    CmdItem ThreeCommand;
    CmdItem FourCommand;
    CmdItem FiveCommand;
    CmdItem SixCommand;
    CmdItem SevenCommand;
    CmdItem EightCommand;
    CmdItem NineCommand;
    CmdItem ZeroCommand;
    CmdItem PlusCommand;
    CmdItem MinusCommand;
    CmdItem MultiCommand;
    CmdItem DivideCommand;
    CmdItem EqCommand;

    Stack calstack;
} AppDataContext;

AppDataContext* appdc_create();
void appdc_free(AppDataContext *pDc);

#endif
