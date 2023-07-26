    #include <stdio.h>
    #include <stdlib.h>
    #include "dequeue.h"


    dequeue_t* create_dequeue(int capacity)
    {
        dequeue_t* p_new_dq = NULL;

        p_new_dq = (dequeue_t*)xcalloc(1, sizeof(dequeue_t));
        p_new_dq->arr = (data_t*)xcalloc(capacity, sizeof(data_t));
        p_new_dq->capacity = capacity;
        p_new_dq->front = capacity;
        p_new_dq->rear = 0;
        p_new_dq->size = 0;

        return (p_new_dq);
    }

    status_t push_front(dequeue_t* p_dq, data_t data)
    {
        if(is_full(p_dq) == TRUE)
            return E_DEQUEUE_FULL;
        
        p_dq->front = (p_dq->front+1)%p_dq->capacity;
        p_dq->arr[p_dq->front] = data;
        p_dq->size += 1;
        return (SUCCESS);
    }

    status_t push_back(dequeue_t* p_dq, data_t data)
    {
        if(is_full(p_dq) == TRUE)
            return E_DEQUEUE_FULL;
        
        p_dq->rear = (p_dq->capacity + p_dq->rear-1)%p_dq->capacity;
        p_dq->arr[p_dq->rear]  = data;
        p_dq->size += 1;
        return (SUCCESS);
    }

    status_t pop_front(dequeue_t* p_dq, data_t* p_front_data)
    {   
        if(is_empty(p_dq) == TRUE)
            return  (E_DEQUEUE_EMPTY);
        
        *p_front_data = p_dq->arr[p_dq->front];
        p_dq->front = (p_dq->capacity + p_dq->front -1)%p_dq->capacity;
        p_dq->size -= 1;

        return (SUCCESS);
    }   

    status_t pop_back(dequeue_t* p_dq, data_t* p_back_data)
    {
        if(is_empty(p_dq) == TRUE)
            return (E_DEQUEUE_EMPTY);
        
        *p_back_data = p_dq->arr[p_dq->rear];
        p_dq->rear = (p_dq->rear+1)%p_dq->capacity;
        return (SUCCESS);
    }

    status_t front(dequeue_t* p_dq, data_t* p_front_data)
    {
        if(is_empty(p_dq) == TRUE)
            return (E_DEQUEUE_EMPTY);
        *p_front_data = p_dq->arr[p_dq->front];
        
        return (SUCCESS);
    }

    status_t back(dequeue_t* p_dq, data_t* p_back_data)
    {
        if(is_empty(p_dq) == TRUE)
                return (E_DEQUEUE_EMPTY);

        *p_back_data = p_dq->arr[p_dq->rear];
        return (SUCCESS);
    }

    Bool is_empty(dequeue_t* p_dq)
    {
        if(p_dq->size == 0)
        {
            p_dq->rear = 0;
            p_dq->front = p_dq->capacity;
            return (TRUE);
        }
        return (FALSE);
    }

    Bool is_full(dequeue_t* p_dq)
    {
        return  (p_dq->size == p_dq->capacity) ? TRUE : FALSE;
    }

    status_t destroy_dequeue(dequeue_t** pp_dq)
    {
        dequeue_t *p_dq= *pp_dq;

        free(p_dq->arr);
        free(p_dq);
        *pp_dq = NULL;
        return (SUCCESS);
    }

    void* xcalloc(size_t nr_element, size_t size_per_element)
    {
        void* p = NULL;

        p = calloc(nr_element,size_per_element);
        if(NULL == p)
        {
            fprintf(stderr, "calloc(): fatal: out of memory");  
            exit(EXIT_FAILURE);
        }

        return (p);
    }