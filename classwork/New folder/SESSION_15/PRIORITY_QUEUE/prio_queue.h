#ifndef _PRIO_QUEUE_H
#define _PRIO_QUEUE_H


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS             1
#define TRUE                1
#define FALSE               0
#define LIST_DATA_NOT_FOUND 2
#define LIST_EMPTY          3
#define QUEUE_EMPTY         LIST_EMPTY

typedef int data_t;
typedef int status_t;

typedef struct node node_t;
typedef node_t list_t;
typedef list_t prio_queue_t;

struct node
{
    int data;
    struct node* prev;
    struct node* next;
};

prio_queue_t* create_prio_queue(void);
status_t prio_enqueue(prio_queue_t* p_prio_queue, data_t p_data);
status_t prio_dequeue()

#endif  /* _PRIO_QUEUE_H */