#ifndef _DEQUEUE_H_
#define _DEQUEUE_H_

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS    1
#define TRUE    1
#define FALSE   0
#define E_DEQUEUE_EMPTY  2
#define E_DEQUEUE_FULL  3


typedef int data_t;
typedef int status_t;
typedef int Bool;
typedef long long int ssize_t;

typedef struct dequeue dequeue_t;

struct dequeue
{
    data_t* arr;
    ssize_t size;
    ssize_t capacity;
    ssize_t front;
    ssize_t rear;
    
};

dequeue_t* create_dequeue(int size);
status_t push_front(dequeue_t* p_dq, data_t data);
status_t push_back(dequeue_t* p_dq, data_t data);
status_t pop_front(dequeue_t* p_dq, data_t* p_front_data);
status_t pop_back(dequeue_t* p_dq, data_t* p_back_data);
status_t front(dequeue_t* p_dq, data_t* p_front_data);
status_t back(dequeue_t* p_dq, data_t* p_back_data);
Bool is_empty(dequeue_t* p_dq);
Bool is_full(dequeue_t* p_dq);
status_t destroy_dequeue(dequeue_t** pp_dq);
void* xcalloc(size_t nr_element, size_t size_per_element);

#endif /*  _DEQUEUE_H_ */