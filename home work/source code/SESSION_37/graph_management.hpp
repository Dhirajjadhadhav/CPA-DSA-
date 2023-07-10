#ifndef _GRAPH_HPP
#define _GRAPH_HPP

#include <iostream>
#include "graph_exception.hpp"

using vertex_t = int;

class hnode
{
    friend class hlist;
    friend class vnode;
    friend class graph;
    private:
        vertex_t v;
        hnode* prev;
        hnode* next;
        hnode(vertex_t v);
};

class hlist
{
    friend class graph;
    private:
        hnode* ph_head_node;
        static void generic_insert(hnode* beg, hnode* mid, hnode* end);
        static void generic_delete(hnode* delete_node);
        hnode* search_node(vertex_t v);
    public:
        hlist();
        void insert_end(vertex_t v);

};

class vnode
{
    friend class vlist;
    friend class graph;
    private:
        vertex_t v;
        hlist* ph_adj_list;
        vnode* prev;
        vnode* next;
        vnode(vertex_t v);   
};

class vlist
{
    friend class graph;
    private:
        vnode* p_head_node;
        static void generic_insert(vnode* beg, vnode* mid, vnode* end);
        static void generic_delete(vnode* delete_node);
        vnode* search_node(vertex_t v);
    public:
        vlist();
        void insert_end(vertex_t v);
};

class graph
{
    private:
        vlist* pv_list;
        int nr_v;
        int nr_e;
    public:
        graph();
        ~graph();
        void add_vertex(vertex_t v);
        void add_edge(vertex_t u, vertex_t v);
        void remove_vertex(vertex_t v);
        void remove_edge(vertex_t u, vertex_t v);
        friend std::ostream& operator<<(std::ostream& os, const graph& g);
};
#endif /*_GRAPH_HPP */