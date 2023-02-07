#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>

#define SUCCESS  1
#define DATA_NOT_FOUND 2

struct node
{
    int data;
    struct node* next;
};

/*Interface functions-> called by the user of linked list */

struct node* create_list(void);

int insert_start(struct node* p_list, int new_data);

int insert_end(struct node* p_list, int new_data);

int insert_after(struct node* p_list, int ext_data, int new_data);

int insert_before(struct node* p_list, int ext_data, int new_data);

void show_list(struct node* p_list, const char* msg);

void destory_list(struct node* p_list);

/* Helper function of interface */


struct node* get_node(int new_data);

struct node* search_node(struct node* p_list, int search_data);

void get_node_and_previous(struct node* p_list, int search_data, 
                            struct node** pp_node, struct node** pp_prev_node);

void* xcalloc(size_t nr_of_elements, size_t size_per_element);

#endif  /* _LIST_H*/

