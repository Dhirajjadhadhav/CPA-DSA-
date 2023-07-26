#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_SIZE    100

int main()
{

    queue_t* p_queue = NULL;
    int operation;
    data_t data;
    status_t status;

    p_queue = create_queue(MAX_SIZE);
   
    srand(time(0));

    for(int i = 0; i<100; ++i)
    {
        operation = rand()%4;
       switch (operation)
       {
       case 0:
            data =  rand();
            status = Enqueue(p_queue, data);
            if(status == SUCCESS)
                printf("Enqueue %d\n",data);
            else if(status == E_QUEUE_FULL)
                printf("queue full \n");
            else
                printf("unexpected error\n");
        break;

       case 1:
            status = front(p_queue, &data);
            if(status == SUCCESS)
                printf("front data = %d\n", data);
            else if(status == E_QUEUE_EMPTY)
                printf("queue empty\n");
            else    
                printf("unexpected error\n");
        break;
        case 2:
            status = rear(p_queue, &data);
            if(status == SUCCESS)
                printf("rear data = %d\n", data);
            else if(status == E_QUEUE_EMPTY)
                printf("queue empty\n");
            
            else    
                printf("unexpected error\n");
            break;
        case 3:
            status = Dequeue(p_queue, &data);
            if(status == SUCCESS)
                printf("Dequeued = %d\n", data);
            else if(status == E_QUEUE_EMPTY)
                printf("queue empty\n");
            else    
                printf("unexpected error\n");
            break;
       default:
            printf("invalid case");
        break;
       }
    }
      
    status = destroy_queue(&p_queue);
    if(status == SUCCESS &&  p_queue == NULL)
    {
        printf("queue destroyed\n");
    }

    return  (EXIT_SUCCESS);
}