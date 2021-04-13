#ifndef _STACK_H_
#define _STACK_H_

#include "element.h"

typedef struct _stack STACK;
typedef struct _no NO;

#define SIZE 100
#define ERROR -320000

// Original and generic stack functions 
STACK *create_stack(void);
void stack_delete(STACK **stack);
boolean stack_empty(STACK *stack);
boolean stack_full(STACK *stack);
int stack_size(STACK *stack);

// Based in the element that it contains
boolean stack_append(STACK *stack, ELEMENT *elem);
ELEMENT *stack_pop(STACK *stack);
ELEMENT *stack_top(STACK *stack);

void stack_print(STACK *stack);
void stack_reverse(STACK *stack);

#endif