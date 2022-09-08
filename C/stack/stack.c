#include "stack.h"
#include <stddef.h>

void stackInit(Stack* stack)
{
	stack->l.head = stack->l.tail = NULL;
	stack->l.len = 0;
}

void stackPush(Stack* stack, int val)
{
	listAppend(&stack->l, val);
}

int stackEmpty(Stack* stack)
{
	return stack->l.len == 0;
}

int stackPop(Stack* stack)
{
	return listRemoveTail(&stack->l);
}
