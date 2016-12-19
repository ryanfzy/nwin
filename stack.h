#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct _stackNode
{
	char *cargo;
    size_t iSize;
	struct _stackNode *next;
} StackNode;

typedef struct _stack
{
	StackNode *top;
	int size;
} StrStack;

StrStack* StrStack_new();
void StrStack_init(StrStack *pStack);
int StrStack_push(StrStack* pStack, char *szStr, size_t iSize);
bool StrStack_pop(StrStack* pStack, char *szStr, size_t iSize);
bool StrStack_isEmpty(StrStack *pStack);
void StrStack_delete(StrStack *pStack);

//void StrStack_print(StrStack *pStack);
#endif
