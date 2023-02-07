#include <iostream>
#include "singly_linked_list.hpp"


node::node(data_t new_data)
{
    this->data = new_data;
    this->next = NULL;
}

list:: static void generic_insert(node* p_beg, node* p_mid, node* p_end)
{
    p_mid->next = p_end;
    p_beg->next = p_mid;
}

list:: static void generic_delete(node* p_prev_node, node* p_delete)
{
    p_prev_node->next = p_delete->next;
    delete(p_delete);
}

list:: node* search_node(data_t s_data)
{
    node* p_run  = NULL;
    for(p_run = list->next; NULL != p_run; p_run = p_run->next)
    {
        if(p_run->data == s_data)
            break;
    }

    return (p_run);
}

list:: void get_node_and_prev(data_t data, node** pp_node, node* pp_prev_node)
{
    node* p_run = NULL;
    node* p_run_prev = NULL;

    p_run = list->next;
    p_run_prev = list;
    while(NULL != p_run)
    {
        if(p_run->data == data)
        {
            *pp_node = p_run;
            *pp_prev_node = p_run_prev;
            return;
        }
        p_run_prev = p_run;
        p_run = p_run->next;
    }   
    *pp_node = NULL;
    *pp_prev_node = NULL;
}

list:: void get_last_node()
{
    node* p_run = NULL;

    p_run = list->next;
    while(NULL != p_run->next)
        p_run = p_run->next;
    
    *pp_last_node = p_run;
}

list:: void get_last_node_and_prev(node** pp_node, node** pp_prev_node)
{
    node* p_run = NULL;
    node* p_run_prev = NULL;

    p_run = list->next;
    p_run_prev = list;
    while(NULL != p_run->next)
    {
        p_run_prev = p_run;
        p_run = p_run->next;
    }

    *pp_node = p_run;
    *pp_prev_node = p_run_prev;
}

list ::list()
{
    p_head_node = new node();
}

list :: ~list()
{
    node* p_run = NULL;
    node* p_run_next = NULL;
    if(NULL != this->p_head_node)
    {
        if(NULL != this->p_head_node->next)
        {
            p_run =  this->next;
            while(NULL != p_run)
            {
                p_run_next = p_run->next;
                delete(p_run);
                p_run = p_run_next;
            }
            delete(p_head_node);
        }
    }
}

list:: status_t insert_after(data_t s_data, data_t new_data)
{
    node* p_ext_node = NULL;
    node* p_new_node = NULL;

    p_ext_node = search_node(s_data);
    
    if(NULL == p_ext_node)
        return (DATA_NOT_FOUND);
    
    p_new_node = new node(new_data);
    p_new_node->next = p_ext_node->next;
    p_ext_node->next = p_new_node;

    return (SUCCESS);
}

list :: status_t insert_before(data_t s_data, data_t new_data)
{
    node* p_ext_node = NULL;
    node* p_ext_prev_node = NULL;
    node* p_new_node = NULL;

    get_node_and_prev(s_data, &p_ext_node, &p_ext_prev_node);
    if(NULL == p_ext_node || NULL == p_ext_prev_node)
    {
        return (DATA_NOT_FOUND);
    }

    p_new_node = new node(new_data);

    p_new_node->next = p_ext_node;
    p_ext_prev_node->next = p_new_node;

    return (SUCCESS);

}