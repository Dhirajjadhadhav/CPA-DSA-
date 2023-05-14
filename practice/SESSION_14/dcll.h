#ifndef _DCLL_H
#define _DCLL_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS             1
#define TRUE                1
#define FALSE               0
#define LIST_EMPTY          2
#define LIST_DATA_NOT_FOUND 3

typedef int data_t;
typedef int len_t;
typedef int Bool;
typedef struct node node_t;
typedef node_t list_t;
typedef int status_t;

struct node
{
    data_t data;
    struct node* prev;
    struct node* next;
};

/*list interface routines */

list_t* create_list(void);
status_t insert_start(list_t* p_list, data_t new_data);
status_t insert_end(list_t* p_list, data_t new_data);
status_t insert_after(list_t* p_list, data_t e_data, data_t new_data);
status_t insert_before(list_t* p_list, data_t e_data, data_t new_data);

status_t get_start(list_t* p_list, data_t* p_start_data);
status_t get_end(list_t* p_list, data_t* p_end_data);
status_t pop_start(list_t* p_list, data_t* p_start_data);
status_t pop_end(list_t* p_list, data_t* p_end_data);

status_t remove_start(list_t* p_list);
status_t remove_end(list_t* p_list);
status_t remove_data(list_t* p_list, data_t e_data);

Bool is_empty(list_t* p_list);
Bool is_member(list_t* p_list, data_t data);
len_t get_len(list_t* p_list);
void show(list_t* p_list, const char* msg);

void to_array(list_t* p_list, data_t** p_array, size_t* p_size);
list_t* to_list(data_t* p_array, size_t size);


/*inter list routines */
list_t* concat_list(list_t* p_list_1, list_t* p_list_2);
list_t* merge_list(list_t* p_list_1, list_t* p_list_2);
list_t* get_reversed_list(list_t* p_list);

status_t append_list(list_t* p_list_1, list_t* p_list_2);
status_t reverse_list(list_t* p_list);
status_t destroy_list(list_t** pp_list);


/*helper routines */
static void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end);
static void generic_delete(node_t* p_delete_node);
node_t* search_node(list_t* p_list, data_t s_data);
node_t* get_node(data_t new_data);
void* xcalloc(size_t nr_element, size_t nr_per_size);

#endif /* _DCLL_H */