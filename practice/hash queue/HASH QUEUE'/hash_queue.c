#include "hash_queue.h"
#include <stdlib.h>
#include <stdio.h>

hashq_t* create_hashq(size_t bucket_size)
{
    size_t i;
    hashq_t* p_hashq = NULL;
    if(bucket_size == 0)
        return (NULL);

    p_hashq = (hashq_t*)xcalloc(1, sizeof(hashq_t));
    p_hashq->pp_list_arr  = (list_t**)xcalloc(bucket_size, sizeof(list_t*));
    p_hashq->bucket_size = bucket_size;

    for(i = 0; i<bucket_size; ++i)
        p_hashq->pp_list_arr[i] = create_list();

    return (p_hashq);
}

status_t add_key(hashq_t* p_hashq, key_t key)
{
    size_t bucket_number;
    status_t status;

    bucket_number = hash(key, p_hashq->bucket_size);
    status = insert_end(p_hashq->pp_list_arr[bucket_number], key);
    if(status != SUCCESS)
    {
        fprintf(stderr, "unexpected error");
        exit(EXIT_FAILURE);
    }

    return (SUCCESS);
}

status_t remove_key(hashq_t* p_hashq, key_t key)
{
    size_t bucket_number;
    node_t* p_node = NULL;

    status_t status;
    bucket_number = hash(key, p_hashq->bucket_size);
    p_node = search_node(p_hashq->pp_list_arr[bucket_number], key);
    if(NULL == p_node)
       return (BAD_KEY);
    generic_delete(p_node);
    return (SUCCESS);
}   

status_t search_key(hashq_t* p_hashq, key_t key)
{
    return (search_data(p_hashq->pp_list_arr[hash(key, p_hashq->bucket_size)], key));
}

status_t destroy_hashq(hashq_t** pp_hashq)
{
    hashq_t* p_hashq = *pp_hashq;
    status_t status;
    size_t i;
    for(i = 0; i<p_hashq->bucket_size; ++i)
    {
        status = destroy_list(p_hashq->pp_list_arr[i]);
        if(SUCCESS != status)
        {
            fprintf(stderr, "unexpected error");
            exit(EXIT_FAILURE);
        }
    }

    free(p_hashq->pp_list_arr);
    free(p_hashq);
    *pp_hashq = NULL;
    return (SUCCESS);
}
void hash_stat(hashq_t* p_hashq)
{
    size_t i;
    printf("Bucket size = %llu\n", p_hashq->bucket_size);
    for(i = 0; i<p_hashq->bucket_size; ++i)
        printf("MODULO(%llu) : %llu\n", i, get_list_length(p_hashq->pp_list_arr[i]));
}

list_t* create_list(void)
{
    list_t* p_new_list = NULL;

    p_new_list = (list_t*)xcalloc(1, sizeof(list_t));
    p_new_list->key = -1;
    p_new_list->next = p_new_list;
    p_new_list->prev = p_new_list;
    
    return (p_new_list);
}

status_t insert_end(list_t* p_list, key_t key)
{
    generic_insert(p_list->prev, get_node(key), p_list);
    return (SUCCESS);
}
status_t remove_data(list_t* p_list, key_t key)
{
    node_t* p_search = NULL;
    p_search = search_node(p_list, key);
    if(NULL == p_search)
    {
        return (LIST_DATA_NOT_FOUND);
    }
    generic_delete(p_search);
    return (SUCCESS);
}
status_t search_data(list_t* p_list , key_t key)
{
    node_t* p_search_node = NULL;
    p_search_node = search_node(p_list, key);
    if(NULL == p_search_node)
    {
        return (LIST_DATA_NOT_FOUND);
    }
    return  TRUE;
}
len_t get_list_length(list_t* p_list)
{
    len_t i = 0;
    node_t* p_run = p_list->next;
    while(p_list!= p_run)
    {
        i = i+1;
        p_run = p_run->next;
    }
    return (i);
}
status_t destroy_list(list_t* p_list)
{
    node_t* p_run = NULL;
    node_t* p_run_next = NULL;
    
    p_run = p_list->next;
    while(p_run!= p_list)
    {
        p_run_next = p_run->next;
        free(p_run);
        p_run = p_run_next;
    }

    free(p_list);
    p_list = NULL;
    return (SUCCESS);
}

void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end)
{
    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next= p_mid;
    p_end->prev = p_mid;
}
void generic_delete(node_t* p_delete_node)
{
    p_delete_node->next->prev = p_delete_node->prev;
    p_delete_node->prev->next = p_delete_node->next;
    free(p_delete_node);
}
node_t* search_node(list_t* p_list, key_t key)
{

    node_t* p_run = NULL;

    p_run = p_list->next;
    while(p_run!=p_list)
    {
        if(p_run->key == key)
            return  (p_run);
        p_run = p_run->next;
    }

    return (NULL);
}

node_t* get_node(key_t key)
{
    node_t* p_new_node = NULL;

    p_new_node = (node_t*)xcalloc(1, sizeof(node_t));
    p_new_node->key =key;
    return (p_new_node);
}

void* xcalloc(size_t nr_element, size_t size_per_element)
{
    void* p = NULL;

    p = calloc(nr_element,size_per_element);
    if(NULL == p)
    {
        fprintf(stderr, "calloc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }
    return (p);
}

inline size_t hash(key_t key, size_t bucket_size)
{
    return (key%bucket_size);
}