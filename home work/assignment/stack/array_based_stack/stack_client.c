#include <stdio.h>
#include "stack.h"

#define MAX_SIZE    10000

int main()
{

    stack_t* p_stack = NULL;
    int operation;
    data_t data;
    status_t status;

    p_stack = create_stack(MAX_SIZE);
    srand(time(0));

    for(int i = 0; i<100; ++i)
    {
        operation = rand()%3;
       switch (operation)
       {
       case 0:
            data =  rand();
            status = stack_push(p_stack, data);
            if(status == SUCCESS)
                printf("stack push %d\n",data);
            else if(status == E_STACK_FULL)
                printf("stack full\n");
            else
                printf("unexpected error\n");
        break;

       case 1:
            status = stack_top(p_stack, &data);
            if(status == SUCCESS)
                printf("top data = %d\n", data);
            else if(status == E_STACK_EMPTY)
                printf("stack empty\n");
            
            else    
                printf("unexpected error\n");
        break;
        case 2:
            status = stack_pop(p_stack, &data);
            if(status == SUCCESS)
                printf("pop data = %d\n", data);
            else if(status == E_STACK_EMPTY)
                printf("stack empty\n");
            
            else    
                printf("unexpected error\n");
            break;
       default:
            printf("invalid case");
        break;
       }
    }
      
    status = destroy_stack(&p_stack);
    if(status == SUCCESS &&  p_stack == NULL)
    {
        printf("stack destroyed\n");
    }
}