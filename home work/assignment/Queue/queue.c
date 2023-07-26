#include <stdlib.h>
#include <stdio.h>
#include "queue.h"


queue_t* create_queue(ssize_t capacity)
{
    queue_t* p_queue = NULL;
    p_queue = (queue_t*)xcalloc(1, sizeof(queue_t));
    p_queue->arr = (data_t*)xcalloc(capacity, sizeof(data_t));
    p_queue->capacity = capacity;
    p_queue->front = 0;
    p_queue->size = 0;
    p_queue->rear = capacity-1;
    
    return (p_queue);
}

status_t Enqueue(queue_t *p_queue, data_t data)
{
    if(IsFull(p_queue) == TRUE)
        return (E_QUEUE_FULL);
    
    p_queue->rear = (p_queue->rear+1)%p_queue->capacity;

    p_queue->arr[p_queue->rear] = data;
    p_queue->size = p_queue->size+1;
    return (SUCCESS);
}
status_t Dequeue(queue_t *p_queue, data_t *data)
{
    if(IsEmpty(p_queue) == TRUE)
        return (E_QUEUE_EMPTY);

    *data = p_queue->arr[p_queue->front];
    p_queue->front = (p_queue->front+1)%p_queue->capacity;
    p_queue->size =  p_queue->size -1;
    return (SUCCESS);
}
status_t front(queue_t *p_queue, data_t* front_data)
{
    if(IsEmpty(p_queue) == TRUE)
        return (E_QUEUE_EMPTY);
    
    *front_data = p_queue->arr[p_queue->front];
    return (SUCCESS);
}

status_t rear(queue_t *p_queue, data_t *rear_data)
{
    if(IsEmpty(p_queue) == TRUE)
        return (E_QUEUE_EMPTY);
    
    *rear_data = p_queue->arr[p_queue->rear];
    return (SUCCESS);
}


Bool IsFull(queue_t *p_queue)
{       
    return  (p_queue->size == p_queue->capacity);
}

Bool IsEmpty(queue_t *p_queue)
{
    return  (p_queue->size == 0);
}
status_t destroy_queue(queue_t** pp_queue)
{   
    queue_t* p_queue = *pp_queue;

    free(p_queue->arr);
    free(p_queue);
    *pp_queue = NULL;
    return (SUCCESS);
}

void* xcalloc(size_t nr_element, size_t nr_size_per_element)
{
    void *p = NULL;

    p = calloc(nr_element, nr_size_per_element);
    if(NULL == p)
    {
        fprintf(stderr, "calloc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }

    return (p);
}

