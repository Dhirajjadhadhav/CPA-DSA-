#include <stdio.h>
#include <stdlib.h>
#include "dcll.h"


list_t* create_list(void)
{
    list_t* p_list = NULL;

    p_list = (list_t*)xcalloc(1, sizeof(list_t));
    p_list->data = -1;
    p_list->prev = p_list;
    p_list->next = p_list;
    return (p_list);
}

status_t insert_start(list_t* p_list, data_t new_data)
{
    generic_insert(p_list, get_node(new_data), p_list->next);
    return(SUCCESS);
}

status_t insert_end(list_t* p_list, data_t new_data)
{
    generic_insert(p_list->prev, get_node(new_data), p_list);
    return(SUCCESS);
}

status_t insert_after(list_t* p_list, data_t e_data, data_t new_data)
{
    node_t* e_node = NULL;

    e_node = search_node(p_list, e_data);
    if(NULL == e_node)
        return (LIST_DATA_NOT_FOUND);
    
    generic_insert(e_node, get_node(new_data), e_node->next);
    return (SUCCESS);
}

status_t insert_before(list_t* p_list, data_t e_data, data_t new_data)
{
    node_t* e_node = NULL;

    e_node = search_node(p_list, e_data);
    if(NULL == e_node)
        return (LIST_DATA_NOT_FOUND);
    generic_insert(e_node->prev, get_node(new_data), e_node);
    return (SUCCESS);
}

status_t get_start(list_t* p_list, data_t* p_start_data)
{
    if(is_empty(p_list) == TRUE)
        return (LIST_EMPTY);
    *p_start_data = p_list->next->data;
    return (SUCCESS);
}

status_t get_end(list_t* p_list, data_t* p_end_data)
{
    if(is_empty(p_list) == TRUE)
        return (LIST_EMPTY);
    *p_end_data = p_list->prev->data;
    return (SUCCESS);
}

status_t pop_start(list_t* p_list, data_t* p_start_data)
{
    if(is_empty(p_list) ==TRUE)
        return (LIST_EMPTY);
    *p_start_data = p_list->next->data;
    generic_delete(p_list->next);
    return (SUCCESS);
}

status_t pop_end(list_t* p_list, data_t* p_end_data)
{
    if(is_empty(p_list) == TRUE)
        return (LIST_EMPTY);
    *p_end_data = p_list->prev->data;
    generic_delete(p_list->prev);
    return (SUCCESS);
}

status_t remove_start(list_t* p_list)
{
    if(is_empty(p_list) == TRUE)
        return (LIST_EMPTY);
    generic_delete(p_list->next);
    return (SUCCESS);    
}

status_t remove_end(list_t* p_list)
{
    if(is_empty(p_list) == TRUE)
        return (LIST_EMPTY);
    generic_delete(p_list->prev);
    return(SUCCESS);
}

status_t remove_data(list_t* p_list, data_t e_data)
{
    node_t* e_node = NULL;

    e_node = search_node(p_list, e_data);
    if(NULL == e_node)
        return (LIST_DATA_NOT_FOUND);
    generic_delete(e_node);
    return (SUCCESS);
}

Bool is_empty(list_t* p_list)
{
    return (p_list->next == p_list && p_list->prev == p_list);
}

Bool is_member(list_t* p_list, data_t data)
{
    return (NULL != search_node(p_list, data));
}

len_t get_len(list_t* p_list)
{
    node_t* p_run = NULL;
    len_t len = 0;

    p_run = p_list->next;
    while(p_run != p_list)
    {
        ++len;
        p_run = p_run->next;
    }
    return (len);
}

void show(list_t* p_list, const char* msg)
{
    node_t* p_run = NULL;

    if(msg)
        puts(msg);
    

    printf("[start]<->");
    p_run = p_list->next;
    while(p_run!=p_list)
    {
        printf("[%d]<->",p_run->data);
        p_run = p_run->next;
    }
    puts("[end]");
}

void to_array(list_t* p_list, data_t** pp_array, size_t* p_size)
{
    data_t* p_array = NULL;
    node_t* p_run = NULL;
    len_t len = 0;
    int i;

    len = get_len(p_list);
    p_array = (data_t*)xcalloc(len, sizeof(data_t));

    
    for(p_run = p_list->next, i = 0; p_run != p_list; p_run= p_run->next,++i)
        p_array[i] = p_run->data;

    *pp_array = p_array;
    *p_size = len;
}

list_t* to_list(data_t* p_array, size_t size)
{
    list_t* p_list = NULL;

    p_list = create_list();

    for(size_t i = 0;i<size; ++i)
        insert_end(p_list, p_array[i]);
    return (p_list);
}


/*inter list routines */
list_t* concat_list(list_t* p_list_1, list_t* p_list_2)
{
    node_t* p_run = NULL;
    list_t* p_cat_list = NULL;

    p_cat_list = create_list();

    for(p_run = p_list_1->next; p_run != p_list_1; p_run = p_run->next)
        insert_end(p_cat_list, p_run->data);
    for(p_run = p_list_2->next; p_run != p_list_2; p_run= p_run->next)
        insert_end(p_cat_list, p_run->data);
    return (p_cat_list);
}

list_t* merge_list(list_t* p_list_1, list_t* p_list_2)
{
    list_t* p_merged_list = NULL;
    node_t* p_run_1 =NULL;
    node_t* p_run_2 = NULL;

    p_merged_list = create_list();
    p_run_1 = p_list_1->next;
    p_run_2 = p_list_2->next;
    while(TRUE)
    {
        if(p_run_1 == p_list_1)
        {
            while(p_run_2!=p_list_2)
            {
                insert_end(p_merged_list,p_run_2->data);
                p_run_2 = p_run_2->next;
            }
            break;
        }
        if(p_run_2 == p_list_2)
        {
            while(p_run_1 != p_list_1)
            {
                insert_end(p_merged_list, p_run_1->data);
                p_run_1 = p_run_1->next;
            }
            break;
        }

        if(p_run_1->data <= p_run_2->data)
        {
            insert_end(p_merged_list, p_run_1->data);
            p_run_1 = p_run_1->next;
        }
        else
        {
            insert_end(p_merged_list, p_run_2->data);
            p_run_2 = p_run_2->next; 
        }
    }

    return (p_merged_list);
}
list_t* get_reversed_list(list_t* p_list)
{
    list_t* p_revserd_list = NULL;  
    node_t* p_run = NULL;

    p_revserd_list = create_list();
    
    for(p_run = p_list->next;p_run!=p_list; p_run = p_run->next)
        insert_start(p_revserd_list, p_run->data);   
    return (p_revserd_list);
}

status_t append_list(list_t* p_list_1, list_t* p_list_2)
{
    if(is_empty(p_list_2) == TRUE)
    {
        free(p_list_2);
        return (SUCCESS);
    }

    p_list_1->prev->next = p_list_2->next;
    p_list_2->next->prev = p_list_1->prev;
    p_list_1->prev = p_list_2->prev;
    p_list_2->prev->next = p_list_1;

    free(p_list_2);
    return(SUCCESS);
}

status_t reverse_list(list_t* p_list)
{
    node_t* original_first_node = NULL;
    node_t* p_run = NULL;
    node_t* p_run_next = NULL;

    if(is_empty(p_list)  == TRUE || p_list->next->next == p_list)
        return (SUCCESS);

    original_first_node = p_list->next;

    for(p_run = p_list->next->next; p_run!=p_list; p_run = p_run_next)
    {
        p_run_next = p_run->next;
        generic_insert(p_list, p_run, p_list->next);
    }

    original_first_node->next = p_list;
    p_list->prev = original_first_node;

    return (SUCCESS);
}

status_t destroy_list(list_t** pp_list)
{
    list_t* p_list;
    node_t* p_run = NULL;
    node_t* p_run_next = NULL; 

    p_list = *pp_list;
    for(p_run = p_list->next; p_run!=p_list; p_run = p_run_next)
    {
        p_run_next = p_run->next;
        free(p_run);
    }
    free(p_list);
    *pp_list = NULL;
    return (SUCCESS);
}


/*helper routines */
static void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end)
{
    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    p_end->prev = p_mid;
}

static void generic_delete(node_t* p_delete_node)
{
    p_delete_node->next->prev = p_delete_node->prev;
    p_delete_node->prev->next =p_delete_node->next;
    free(p_delete_node); 
}
node_t* search_node(list_t* p_list, data_t s_data)
{
    node_t* p_run = NULL;

    for(p_run = p_list->next; p_run!=p_list; p_run = p_run->next)
        if(p_run->data == s_data)
            return (p_run);
        
    return (NULL);
}

node_t* get_node(data_t new_data)
{
    node_t* p_new_node = NULL;

    p_new_node = (node_t*)xcalloc(1, sizeof(node_t));
    p_new_node->data = new_data;
    return (p_new_node);
}

void* xcalloc(size_t nr_element, size_t nr_size_per_element)
{
    void* p = NULL;

    p = calloc(nr_element, nr_size_per_element);
    if(p == NULL)
    {
        fprintf(stderr, "Fatal:calloc():out of memory\n");
        exit(EXIT_FAILURE);
    }
    return (p);
}