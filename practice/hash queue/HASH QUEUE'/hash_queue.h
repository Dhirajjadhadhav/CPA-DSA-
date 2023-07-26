#ifndef _HASH_H
#define _HASH_H

#define TRUE    1
#define FALSE   0
#define SUCCESS 1
#define LIST_DATA_NOT_FOUND 2
#define BAD_KEY LIST_DATA_NOT_FOUND

typedef size_t key_t;
typedef size_t len_t;
typedef int status_t;
typedef struct node node_t;
typedef node_t list_t;
typedef struct hashq hashq_t;


struct node
{
    key_t key;
    struct node* prev;
    struct node* next;
};

struct  hashq
{
    list_t** pp_list_arr;
    size_t bucket_size;
};

hashq_t* create_hashq(size_t bucket_size);
status_t add_key(hashq_t* p_hashq, key_t key);
status_t remove_key(hashq_t* p_hashq, key_t key);
status_t search_key(hashq_t* p_hashq, key_t key);
status_t destroy_hashq(hashq_t** pp_hashq);
void hash_stat(hashq_t* p_hashq);

list_t* create_list(void);
status_t insert_end(list_t* p_list, key_t ket);
status_t remove_data(list_t* p_list, key_t key);
status_t search_data(list_t* p_list , key_t key);
len_t get_list_length(list_t* p_list);
status_t destroy_list(list_t*  pp_list);


void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end);
void generic_delete(node_t* p_delete_node);
node_t* search_node(list_t* p_list, key_t key);
node_t* get_node(key_t key);

void* xcalloc(size_t nr_element, size_t nr_size_per_element);

inline size_t hash(key_t key, size_t bucket_size);
#endif /*_HASH_H */
