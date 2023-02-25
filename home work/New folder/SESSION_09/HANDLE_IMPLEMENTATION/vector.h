#ifndef _VECTOR_H
#define _VECTOR_H

typedef long long int ssize_t

typedef struct vector handle_table_t;

struct vector 
{
    list_t** pp_list_ptrs;
    ssize_t N;
};

handle_table_t* create_handle_table();
void push_back(ahndel_table_t* p_vec, list_t* p_list);
void destroy_handel_table(handle_table_t * p_handle_table);

extern handle_table_t* ghandel_table;
void init_handle_table();
void release_handel_table();

#endif /*_VECTOR_H */
