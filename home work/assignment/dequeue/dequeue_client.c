#include <stdio.h>
#include <stdlib.h>
#include "dequeue.h"

#define MAX_SIZE  10
#define MAX_OPERATION 100

int main()
{
    dequeue_t* p_dq = NULL;
    data_t data;
    status_t status;

    p_dq = (dequeue_t*)create_dequeue(MAX_SIZE);
    int operation;
    srand(time(0));

    for(int i = 0; i<MAX_OPERATION; ++i)
    {
        operation = rand()%6;
        switch (operation)
        {
        case 0:
            data = rand();
            status = push_front(p_dq, data);
            if(status == SUCCESS)
            {
                printf("push back :%d\n", data);
            }
            else if(status ==E_DEQUEUE_FULL)
            {
                printf("dequeue full!!\n");
            }
            else
            {
                printf("unexpected error");
            }
            break;
         
        case 1:
            data = rand();
            status = push_back(p_dq, data);
            if(status == SUCCESS)
            {
                printf("push back :%d\n", data);
            }
            else if(status ==E_DEQUEUE_FULL)
            {
                printf("dequeue full!!\n");
            }
            else
            {
                printf("unexpected error");
            }
            break;

        case 2:
            status = front(p_dq, &data);
            if(status == SUCCESS)
            {
                printf("front data  = %d\n", data);
            }
            else if(status ==E_DEQUEUE_FULL)
            {
                printf("dequeue empty!!\n");
            }
            else
            {
                printf("unexpected error");
            }
            break;
        case 3:
            status = back(p_dq, &data);
            if(status == SUCCESS)
            {
                printf("rear data  = %d\n", data);
            }
            else if(status ==E_DEQUEUE_FULL)
            {
                printf("dequeue empty!!\n");
            }
            else
            {
                printf("unexpected error");
            }
            break;
        case 4:
            status = pop_front(p_dq, &data);
            if(status == SUCCESS)
            {
                printf("front data :%d\n", data);
            }
            else if(status ==E_DEQUEUE_FULL)
            {
                printf("dequeue full!!\n");
            }
            else
            {
                printf("unexpected error");
            }
            break;
            
        case 5:
            status = pop_back(p_dq, &data);
            if(status == SUCCESS)
            {
                printf("rear data = :%d\n", data);
            }
            else if(status ==E_DEQUEUE_FULL)
            {
                printf("dequeue full!!\n");
            }
            else
            {
                printf("unexpected error");
            }
            break;
        
        default:
            printf("bad choice\n");
            break;
        }   
    }

    status = destroy_dequeue(&p_dq);
    if(status = SUCCESS && p_dq == NULL)
    {
        printf("dequeue destroy successfully.\n");
    }
    return (EXIT_SUCCESS);
}