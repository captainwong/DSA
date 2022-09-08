#ifndef __STACK_H__
#define __STACK_H__

#pragma once

#include "../list/list.h"

typedef struct Stack {
	List l;
}Stack;

void stackInit(Stack* stack);
void stackPush(Stack* stack, int val);
int stackEmpty(Stack* stack);
int stackPop(Stack* stack);


#endif
