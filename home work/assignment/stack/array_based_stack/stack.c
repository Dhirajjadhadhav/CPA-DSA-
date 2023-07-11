#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

stack_t* create_stack(int size)
{
    stack_t *p_stack = NULL;

    p_stack = (stack_t*)xcalloc(1, sizeof(stack_t));
    p_stack->arr = xcalloc(size, sizeof(data_t));
    p_stack->size = size;
    p_stack->top = -1;

    return (p_stack);
}

status_t stack_push(stack_t *p_stack, data_t data)
{
    if(is_stack_full(p_stack) == TRUE)
        return (E_STACK_FULL);
    
    p_stack->arr[p_stack->top+1] = data;
    p_stack->top += 1;

    return (SUCCESS);
}

status_t stack_top(stack_t *p_stack, data_t* top_data)
{
    if(is_stack_empty(p_stack) == TRUE)
        return (E_STACK_EMPTY);
    
    *top_data = p_stack->arr[p_stack->top];

    return (SUCCESS);
}

status_t stack_pop(stack_t *p_stack, data_t* pop_data)
{
    if(is_stack_empty(p_stack) == TRUE)
        return (E_STACK_EMPTY);
    
    *pop_data = p_stack->arr[p_stack->top];
     p_stack->top -= 1;

    return (SUCCESS);
}

inline Bool is_stack_empty(stack_t *p_stack)
{
    return (p_stack->top == -1);
}

 inline Bool is_stack_full(stack_t *p_stack)
{
    return (p_stack->top == p_stack->size-1);
}

status_t destroy_stack(stack_t ** pp_stack)
{
    stack_t* p_stack = NULL;

    p_stack = *pp_stack;

    free(p_stack->arr);
    free(p_stack);
    *pp_stack = NULL;

    return (SUCCESS);
}

void* xcalloc(size_t nr_element, size_t nr_size_per_element)
{
    void *p = NULL;

    p = calloc(nr_element, nr_size_per_element);
    if(p == NULL)
    {
        fprintf(stderr, "calloc():fatal out of memory\n");
        exit(EXIT_FAILURE);
    }

    return (p);
}
