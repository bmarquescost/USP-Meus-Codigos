// Bernardo Marques Costa
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "element.h"

// Every node in the stack -> have an element and points to the previous node.
struct _no {
    ELEMENT *current_element;
    NO *prev;
};

// Original stack, with the pointer for the top and the counter of nodes inside the stack.
struct _stack {
    NO *top;
    int size;
};


// Initialize a instance, a new empty stack
STACK *create_stack(void){
	STACK *stack_init = (STACK*)calloc(1, sizeof(STACK));
	if(stack_init){
		stack_init->top = NULL;
		stack_init->size = 0;
	}
	return stack_init;
}

// Delete all the nodes in the stack and free the memory.
void stack_delete(STACK **stack){
	if(stack){
		if(*stack){
			while((*stack)->top){
				NO *tmp = (*stack)->top;
				(*stack)->top = (*stack)->top->prev;

				element_delete(&tmp->current_element);
				tmp->prev = NULL;

				free(tmp);
				tmp = NULL;
			}
		}
		free(*stack);
		*stack = NULL;
	}
}


// Return if the stack is empty.
boolean stack_empty(STACK *stack){
	if(stack){
		return (stack->size == 0) ? TRUE : FALSE;
	}

	return ERROR;
}

// Return if the stack is full.
boolean stack_full(STACK *stack){
	return FALSE; // since is an dinamic and linked stack, it will not get full
}

// Return the size of the stack.
int stack_size(STACK *stack){
	if(stack){
		return stack->size;
	}
	return ERROR;
}

// STUFF BASED IN THE ELEMENT THAT STACK CONTAINS

// Append a new item into the stack (it will be the new top of the stack).
boolean stack_append(STACK *stack, ELEMENT *elem){
    NO *node = (NO*) calloc(1, sizeof(NO));
    
    if (stack == NULL || elem == NULL || node == NULL)
        return FALSE;

    node->current_element = element_create(element_get_key(elem));
    
    node->prev = stack->top;
    
    stack->top = node;

    (stack->size)++;

    return TRUE;   
}

// Return the item that is in the top of the stack.
ELEMENT *stack_top(STACK *stack){
	if(stack) return stack->top->current_element;
	return NULL;
}

// Remove the top of the stack, backing the top pointer of the stack for it previous node.
// Also return the removed element.
ELEMENT *stack_pop(STACK *stack){

	if(stack == NULL)
		return NULL;
	
	NO *tmp = stack->top;
    
    stack->top = stack->top->prev;
    (stack->size)--;
    
    ELEMENT *deleted_element = tmp->current_element;
    
    tmp->prev = NULL;  
    
    free(tmp);
    tmp = NULL;

    return deleted_element;
}