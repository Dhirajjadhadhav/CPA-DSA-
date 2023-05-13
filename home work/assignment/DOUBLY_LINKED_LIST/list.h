/*
*   @file: dll.h
*   @author: Dhiraj Jadhav(dhirajjadhav77777@gmail.com)
*   @brief:This file contains all declaration and type defination about Doubly Circular Linked List
*   @date: 19 feb 2023
*   version : 1.0
*   
*   @copyright: Copyrighs (c) 2023
*/

#ifndef _DOUBLY_LINKED_LIST_H
#define _DOUBLY_LINKED_LIST_H

//Constant Litrals
#define SUCCESS     1
#define TRUE        1
#define FALSE       0

#define LIST_EMPTY  2
#define LIST_DATA_NOT_FOUND 3

//typedefs


typedef int data_t;
typedef int status_t;
typedef int len_t;
typedef int Bool;

typedef struct node node_t;
typedef node_t  list_t;

struct node
{
    data_t data;
    struct node* prev;
    struct node* next;
};

/*Declartions : Interface function */
list_t* create_list(void);

status_t insert_start(list_t* p_list, data_t new_data);
status_t insert_end(list_t* p_list, data_t new_data);
status_t insert_before(list_t* p_list, data_t e_data, data_t new_data);
status_t insert_after(list_t* p_list, data_t e_data,  data_t new_data);

status_t get_start(list_t* p_list, data_t* p_start_data);
status_t get_end(list_t* p_list, data_t* p_end_data);
status_t pop_start(list_t* p_list, data_t* p_start_data);
status_t pop_end(list_t* p_list, data_t* p_end_data);

status_t remove_start(list_t* p_list);
status_t remove_end(list_t* p_list);
status_t remove_data(list_t* p_list, data_t r_data);

Bool is_empty(list_t* p_list);
Bool is_memeber(list_t* p_list, data_t e_data);
len_t get_length(list_t* p_list);
void show(list_t* p_list, const char* msg);

void to_array(list_t* p_list, data_t** p_array, size_t* p_size);
list_t* to_list(data_t* p_array, size_t size);

list_t* concat(list_t* p_list_1, list_t* p_list_2);
list_t* merge(list_t* p_list_1, list_t* p_list_2);
list_t* get_reversed_list(list_t* p_list);

status_t append(list_t* p_list_1, list_t* p_list_2);
status_t reversed_list(list_t* p_list);

status_t destroy_list(list_t** pp_list);


/* Declaration: helper function */
void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end);
void generic_delete(node_t* p_delete);
node_t * search_node(list_t* p_list, data_t s_data);
node_t* get_node(data_t new_data);
void* Xcalloc(size_t nr_element, size_t size_per_element);
#endif ; /* _DOUBLY_LINKED_LIST_H */