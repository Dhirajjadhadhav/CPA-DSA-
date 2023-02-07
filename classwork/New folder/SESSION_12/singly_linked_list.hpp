#ifndef _SINGLY_LINKED_LIST_HPP
#define _SINGLY_LINKED_LIST_HPP

#include <iostream>

const int SUCCESS = 1;

using data_t = int;
using status_t = int;
using len_t  = int;

class node
{
    friend class list;
    private:
        data_t data;
        node* next;
        node(data_t new_data);
};

class list 
{
    private:
        node* p_head_node;
        static void generic_insert(node* p_beg, node* p_mid,node* p_end);
        static void generic_delete(node* p_prev_node, node* p_del_node);
        node* search_node(data_t s_data);
        void get_node_and_prev(data_t s_data, node** pp_node, node** pp_prev_node);
        void get_last_node(node** pp_last_node);
        void get_last_node_and_prev(node** pp_node, node** pp_prev_node);
    
    public:
        list();         // replaces create_list()
        ~list();        // replaces destory_list()

        list(const list&) = delete;
        list& operator = (const list&) = delete;

        status_t insert_start(data_t new_data);
        status_t insert_end(data_t new_data);
        status_t insert_after(data_t  e_data, data_t new_data);
        status_t insert_before(data_t e_data, data_t new_data);

        status_t get_start(data_t* p_start_data);
        status_t get_end(data_t* p_end_data);

        status_t pop_start(data_t* p_start_data);
        status_t pop_end(data_t* p_end_data);

        status_t remove_start();
        status_t remove_end();
        status_t remove_data(data_t r_data);

        bool is_empty() const;
        bool is_member(data_t data) const;
        len_t get_length() const;
        friend std:: ostream& operator<<(std:: ostream&, const list& lst_object);

        list* concat(const list* other) const;
        list* merge(const list* other)const;
        list* get_reversed_list()const;
        
        status_t append(list* other);
        status_t reverse();

};

#endif  /* _SINGLY_LINKED_LIST_HPP */  

