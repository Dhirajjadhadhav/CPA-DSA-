#ifndef _HASH_H
#define _HASH_H

#define TRUE                    1
#define FALSE                   0
#define SUCCESS                 1
#define LIST_DATA_NOT_FOUND     2
#define BAD_KEY         LIST_DATA_NOT_FOUND

typedef size_t key_t;
typedef size_t len_t;
typedef int status_t;
typedef struct node node_t;
typedef node_t list_t;
typedef struct hashq hashq_t;

struct node
{
    key_t ket;
    struct node* prev;
    struct node* next;
};

struct  hashq
{
    list_t** pp_list_arr;
    size_t bucket_size;
};


#endif /*_HASH_H */