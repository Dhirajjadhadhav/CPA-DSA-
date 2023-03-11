#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>

#define SUCCESS             1
#define G_INVALID_VERTEX    2
#define G_INVALID_EDGE      3
#define G_VERTEX_EXISTS     4
#define G_EDGE_EXISTS       5

typedef long long vertex_t;
typedef struct hnode hnode_t;
typedef hnode_t hlist_t;

typedef struct vnode    vnode_t;
typedef vnode_t  vlist_t;

typedef struct graph graph_t ;

typedef int status_t;

struct hnode
{
    vertex_t v;
    struct hnode* prev;
    struct hnode* next;
};

struct vnode
{
    vertex_t v;
    hlist_t* ph_list;

    struct vnode* prev;
    struct vnode* next;
};

struct graph
{
    vlist_t* pv_list;
    size_t nr_v;
    size_t nr_e;
};

/*  Graph inerface routines   */
graph_t* create_graph(void);
status_t add_vertex(graph_t* g, vertex_t v);
status_t remove_vertex(graph_t* g, vertex_t* v);
status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end);
status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end);
void show_graph(graph_t* g, const char* msg);
status_t destroy_graph(graph_t** pp_g);

/*vertical list management - Interface routines*/
vlist_t* v_create_list(void);
status_t v_insert_end(vlist_t* pv_list, vertex_t v);

/*Vertical list managaement - Auxillary routines */
void v_generic_insert(vnode_t* p_beg, vnode_t* p_mid, vnode_t* p_end);
void v_generic_delete(vnode_t* p_delete_node);
vnode_t* v_search_node(vlist_t* pv_list, vertex_t v);
vnode_t* v_get_node(vertex_t v);

/*Horizontal list management - Interface routines */
hlist_t* h_create_list(void);
status_t h_insert_end(vlist_t* ph_list, vertex_t v);

/*Horizonatl list management - Auxillary routines*/
void h_generic_insert(hnode_t* p_beg, hnode_t* p_mid, hnode_t* p_end);
void h_generic_delete(hnode_t* p_delete_node);
hnode_t* h_search_node(hlist_t* ph_list, vertex_t* v);
hnode_t* h_get_node(vertex_t v);

/*Auxillary routines */
void* xcalloc(size_t nr_element, size_t size_per_element);

#endif;    /*_GRAPH_H*/
