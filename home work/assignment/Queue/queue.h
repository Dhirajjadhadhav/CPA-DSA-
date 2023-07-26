#ifndef _QUEUE_H
#define _QUEUE_H

#define TRUE    1
#define FALSE   0
#define SUCCESS    1
#define E_QUEUE_EMPTY   2
#define E_QUEUE_FULL    3

typedef int data_t;
typedef int status_t;
typedef int Bool;
typedef long long int ssize_t;
typedef struct queue queue_t;


struct queue
{
    data_t *arr; 
    ssize_t front;
    ssize_t  rear;
    ssize_t size;
    ssize_t capacity;
};


queue_t* create_queue(ssize_t size);
status_t Enqueue(queue_t *p_queue,data_t data);
status_t Dequeue(queue_t *p_queue, data_t *data);
status_t front(queue_t *p_queue, data_t* front_data);
status_t rear(queue_t *p_queue, data_t* rear_data);
Bool IsFull(queue_t *p_queue);
Bool IsEmpty(queue_t *p_queue);
status_t destroy_queue(queue_t** pp_queue);
void* xcalloc(size_t nr_element, size_t nr_size_per_element);


#endif /* _QUEUE_H */