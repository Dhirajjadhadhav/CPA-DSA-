#ifndef _STACK_H

#define _STACK_H

#define SUCCESS 1
#define FAILURE  0
#define TRUE    1
#define FALSE   0
#define E_STACK_EMPTY   2
#define E_STACK_FULL    3


typedef long long int ssize_t;
typedef struct stack    stack_t;
typedef int status_t;
typedef int data_t;
typedef int Bool;

struct stack
{
    data_t* arr;
    ssize_t size;
    ssize_t top;
};


stack_t* create_stack(int size); 
status_t stack_push(stack_t *p_stack, data_t data);
status_t stack_top(stack_t *p_stack, data_t* top_data);
status_t stack_pop(stack_t *p_stack, data_t* pop_data);
Bool is_stack_empty(stack_t *p_stack);
Bool is_stack_full(stack_t *p_stack);
status_t destroy_stack(stack_t **pp_stack);
void* xcalloc(size_t nr_element, size_t nr_size_per_element);

#endif; /* _STACK_H*/