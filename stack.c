#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

static StackNode* StackNode_new()
{
    StackNode *pNode = malloc(sizeof(StackNode));
    pNode->cargo = NULL;
    pNode->next = NULL;
    pNode->iSize = 0;
    return pNode;
}

static void StackNode_delete(StackNode *pNode)
{
    free(pNode->cargo);
    free(pNode);
}

StrStack* StrStack_new(){
	StrStack *pStack = malloc(sizeof(StrStack));
    StrStack_init(pStack);
	//pStack->top = NULL;
	//pStack->size = 0;
	return pStack;
}

void StrStack_init(StrStack *pStack)
{
    pStack->top = NULL;
    pStack->size = 0;
}

void StrStack_delete(StrStack *pStack)
{
    StackNode *pTopNode = pStack->top;
    for (int i = 0; i < pStack->size; i++)
    {
        StackNode *pNextNode = pTopNode->next;
        StackNode_delete(pTopNode);
        pTopNode = pNextNode;
    }
    free(pStack);
    pStack = NULL;
}

int StrStack_push(StrStack* pStack, char *szStr, size_t iLength){
	StackNode *pNewNode = StackNode_new();

    pNewNode->iSize = iLength + 1;
	pNewNode->cargo = malloc(pNewNode->iSize);
    memcpy(pNewNode->cargo, szStr, iLength);
    pNewNode->cargo[pNewNode->iSize] = '\0';

	if(pStack->size == 0)
        pNewNode->next = NULL;
	else
		pNewNode->next = pStack->top;

    pStack->top = pNewNode;
	pStack->size++;

	return pStack->size;
}

bool StrStack_pop(StrStack *pStack, char *szStr, size_t iSize){
	if(pStack->size == 0)
		return false; 

	StackNode *pNode = pStack->top;
    int iMinSize = iSize > pNode->iSize ? pNode->iSize : iSize;
    memcpy(szStr, pNode->cargo, iMinSize - 1);
    szStr[iMinSize] = '\0';

	pStack->top = pNode->next;
	pStack->size--;

    StackNode_delete(pNode); 
    return true;
}

bool StrStack_isEmpty(StrStack *pStack){
	return pStack->size == 0;
}

/*
void Stack_print(Stack *stack){
	StackNode *node;
	node = stack->top;
	printf("[%d]", stack->size);
	while(node){
		printf("(%d)", *((int*)(node->cargo)));
		node = node->next;
	}
	printf("\n");
}*/

