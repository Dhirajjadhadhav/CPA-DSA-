#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include  "list.h"

/*Declartions : Interface function */
list_t* create_list()
{
   return (list_t*)Xcalloc(1 , sizeof(list_t));
}

status_t insert_start(list_t* p_list, data_t new_data)
{
    generic_insert(p_list, get_node(new_data), p_list->next);
    return (SUCCESS);
}

status_t insert_end(list_t* p_list, data_t new_data)
{
    node_t* p_run = NULL;

    p_run = p_list;
    while(NULL != p_run->next)
        p_run = p_run->next;
    
    generic_insert(p_run, get_node(new_data), p_run->next);
    return (SUCCESS);
}

status_t insert_before(list_t* p_list, data_t e_data, data_t new_data)
{
   node_t* p_enode = NULL;

    p_enode = search_node(p_list, e_data);
    if(NULL == p_enode)
        return (LIST_DATA_NOT_FOUND);
    
    generic_insert(p_enode->prev, get_node(new_data), p_enode);
    return (SUCCESS);
}

status_t insert_after(list_t* p_list, data_t e_data,  data_t new_data)
{
    node_t* p_enode = NULL;

    p_enode = search_node(p_list, e_data);
    if(NULL == p_enode)
        return (LIST_DATA_NOT_FOUND);
    
    generic_insert(p_enode, get_node(new_data), p_enode->next);
    return (SUCCESS);
}


status_t get_start(list_t* p_list, data_t* p_start_data)
{
    if(NULL == p_list->next)
        return (LIST_EMPTY);
    *p_start_data = p_list->next->data;
    return (SUCCESS);

}

status_t get_end(list_t* p_list, data_t* p_end_data)
{
    node_t* p_run = NULL;
    
    if(NULL == p_list->next)
        return(LIST_EMPTY);

    p_run = p_list->next;
    while(NULL != p_run->next)
        p_run = p_run->next;
    
    *p_end_data = p_run->data;
    return (SUCCESS);
}

status_t pop_start(list_t* p_list, data_t* p_start_data)
{
    node_t* p_start_node = NULL;

    if(NULL == p_list->next)
        return (LIST_EMPTY);
    
    p_start_node = p_list->next;
    *p_start_data = p_start_node->data;
    printf("before the generic delete");
    generic_delete(p_start_node);
    return(SUCCESS);
}
status_t pop_end(list_t* p_list, data_t* p_end_data)
{
    node_t* p_run = NULL;

    if(NULL == p_list->next)
        return (LIST_EMPTY);
    
    p_run = p_list->next;
    while(NULL != p_run->next)
        p_run = p_run->next;
    
    *p_end_data = p_run->data;
    
    generic_delete(p_run);
    return (SUCCESS);
}

status_t remove_start(list_t* p_list)
{
    if(NULL == p_list->next)
        return (LIST_EMPTY);
    generic_delete(p_list->next);
}

status_t remove_end(list_t* p_list)
{
    node_t* p_run = NULL;
    
    if(NULL == p_list->next)
        return (LIST_EMPTY);
    
    p_run = p_list->next;
    while(NULL != p_run->next)
        p_run = p_run->next;

    generic_delete(p_run);
    return (SUCCESS);
}

status_t remove_data(list_t* p_list, data_t r_data)
{
    node_t* p_enode = NULL;
    printf("in theseacrhc node\n");
    p_enode = search_node(p_list, r_data);
    if(NULL == p_enode)
        return (LIST_DATA_NOT_FOUND);
 

    generic_delete(p_enode);
    return (SUCCESS);
}

Bool is_empty(list_t* p_list)
{
    return (NULL == p_list->next && NULL == p_list->prev);

}

Bool is_memeber(list_t* p_list, data_t e_data)
{
    return (NULL != search_node(p_list, e_data));
}

len_t get_length(list_t* p_list)
{
    len_t len = 0;
    node_t* p_run = NULL;
    p_run = p_list->next;
    while(NULL != p_run)
            len++;
    return (len);
}

void show(list_t* p_list, const char* msg)
{
    node_t* p_run = NULL;
    
    if(msg)
        puts(msg);

    printf("[START]<->");
    p_run = p_list->next;
    while(NULL != p_run)
    {   
        printf("[%d]<->", p_run->data);
        p_run = p_run->next;
    }
    puts("[END]");
}

void to_array(list_t* p_list, data_t** pp_array, size_t* p_size)
{
    node_t* p_run = NULL;
    data_t* p_array = NULL;
    size_t size = 0;
    len_t  len = 0;
    size_t i;
    
    len = get_length(p_list);
    size = len;
    if(!len)
    {
        *pp_array = p_array;
        *p_size = size;
        return;
    }

    p_array = (data_t*)Xcalloc(len, sizeof(data_t));

    for(p_run = p_list->next, i = 0; NULL != p_run; p_run = p_run->next, ++i)
        p_array[i] = p_run->data;

    *pp_array = p_array;
    *p_size = size; 
}

list_t* to_list(data_t* p_array, size_t size)
{
    list_t* p_list= NULL;
    size_t i;

    p_list = create_list();
    for(i = 0; i<size; ++i)
         insert_end(p_list, p_array[i]);
        
    return (p_list);
}

list_t* concat(list_t* p_list_1, list_t* p_list_2)
{
    list_t* p_cat_list = NULL;
    node_t* p_run = NULL;
    
    p_cat_list = create_list(); 
    for(p_run = p_list_1->next; NULL != p_run; p_run = p_run->next)
        insert_end(p_cat_list, p_run->data);
    for(p_run = p_list_2->next; NULL != p_run; p_run = p_run->next)
        insert_end(p_cat_list, p_run->data);
    
    return (p_cat_list);
}

list_t* merge(list_t* p_list_1, list_t* p_list_2)
{
    list_t* p_merged_list = NULL;
    node_t* p_run1 = NULL;
    node_t* p_run2 = NULL;
    status_t status;
    
    p_run1 = p_list_1->next;
    p_run2 = p_list_2->next;
    p_merged_list = create_list();

    while (TRUE)
    {
        if(NULL == p_run1)
        {
            while (NULL != p_run2)
            {
               insert_end(p_merged_list, p_run2->data);
                p_run2 = p_run2->next;
            }
            break;
        }    
        if(NULL == p_run2)
        {
            while(NULL != p_run1)
            {
                insert_end(p_merged_list, p_run1->data);
                p_run1 = p_run1->next;
            }
            break;
        }
        if(p_run1->data<=p_run2->data)
        {
            insert_end(p_merged_list, p_run1->data);
            p_run1 = p_run1->next;
        }
        else
        {
            insert_end(p_merged_list, p_run2->data);
            p_run2 = p_run2->next;
        }
    }
    return (p_merged_list);
}

list_t* get_reversed_list(list_t* p_list)
{
    list_t* p_reversed_list = NULL;
    node_t* p_run = NULL;

    p_reversed_list = create_list();
    p_run = p_list->next;
    while(NULL != p_run)
    {
        insert_start(p_reversed_list, p_run->data);
        p_run = p_run->next;
    }

    return (p_reversed_list);
}

status_t append(list_t* p_list_1, list_t* p_list_2)
{
    node_t* p_run = NULL;

    if(NULL == p_list_2->next)
        goto out;

    p_run = p_list_1->next;
    while(NULL != p_run->next)
        p_run = p_run->next;
    p_run->next = p_list_2->next;
    p_list_2->next->prev= p_run;

out:
    free(p_list_2);
    p_list_2 = NULL;
    return(SUCCESS);
}

status_t reversed_list(list_t* p_list)
{
    node_t* p_run = NULL;
    node_t* p_run_next = NULL;

    if(NULL == p_list->next ||NULL == p_list->next->next)
        return (SUCCESS);


    p_run = p_list->next->next;
    p_list->next->next = NULL;
    while(NULL != p_run)
    {
        p_run_next = p_run->next;
        generic_insert(p_list, p_run, p_list->next);
        p_run = p_run_next;
    }

    return (SUCCESS);

}

status_t destroy_list(list_t** pp_list)
{
    list_t* p_list = NULL;
    node_t* p_run = NULL;
    node_t* p_run_next = NULL;
   
    p_list = *pp_list;
    if(NULL != p_list)
    {
        
        if(NULL != p_list->next)
        {
            p_run = p_list->next;
            while (NULL != p_run)
            {
                 p_run_next = p_run->next;
                 free(p_run);
                 p_run = p_run_next;
            }    
        }
        free(p_list);
        p_list =  NULL;
    }
    *pp_list = NULL;
    return (SUCCESS);
}


/* Declaration: helper function */
void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end)
{
    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    if(p_end != NULL)
        p_end->prev = p_mid;
}

void generic_delete(node_t* p_delete)
{
    p_delete->prev->next = p_delete->next;
    if(NULL != p_delete->next)
        p_delete->next->prev = p_delete->prev;
    free(p_delete);
    p_delete = NULL;
}

node_t* search_node(list_t* p_list, data_t s_data)
{
    node_t* p_run = NULL;
    p_run = p_list->next;

    while(NULL != p_run)
    {
        if(p_run->data == s_data)
            break;
        p_run = p_run->next;
    }
    return (p_run);
}

node_t* get_node(data_t new_data)
{
    node_t* p_node = NULL;

    p_node = (node_t*)Xcalloc(1, sizeof(node_t));
    p_node->data = new_data;
    return (p_node); 
}

void* Xcalloc(size_t nr_element, size_t size_per_element)
{
    void* p = NULL;
    
    p = calloc(nr_element, size_per_element);
    if(NULL == p)
    {
        fprintf(stderr, "calloc(): fatal out of memeory\n");
        exit(EXIT_FAILURE);
    }
    return (p);
}