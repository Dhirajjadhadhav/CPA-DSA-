#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>

#define SUCCESS             1
#define TRUE                1
#define FALSE               0
#define G_INVALID_VERTEX     2
#define G_INVALID_EDEGE     3
#define G_VERTEX_EXISTS     4
#define G_EDGE_EXISTS       5
#define G_CURROPT           6

#define VPTR_LIST_EMPTY     7
#define VPTR_QUEUE_EMPTY    VPTR_LIST_EMPTY

typedef long long vertex_t;

typedef struct hnode hnode_t;
typedef hnode_t hlist_t;

typedef struct vnode vnode_t;
typedef vnode_t vlist_t;

typedef struct vptrnode vptrnode_t;
typedef vptrnode_t vptrlist_t;
typedef vptrlist_t vptrqueue_t;

typedef struct graph graph_t;

typedef int status_t;
typedef int Bool;

typedef enum color color_t;

struct  hnode   
{
    vertex_t v;
    struct hnode* next;
    struct hnode* prev; 
};

struct vnode
{
    vertex_t v;
    hlist_t* ph_list;
    color_t color;
    struct vnode* pv_pred;

    struct vnode* prev;
    struct vnode* next;

};

struct vptrnode
{
    vnode_t* pv;

    struct vptrnode* prev;
    struct vptrnode* next;
};

struct graph
{
    vlist_t* pv_list;
    size_t nr_v;
    size_t nr_e;
};

enum color
{
    WHITE = 0,
    GRAY,
    BLACK
};

/* Graph Interface routines */
graph_t* create_graph(void);
status_t add_vertex(graph_t* g, vertex_t v);
status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end);
status_t remove_vertex(graph_t* g, vertex_t v);
status_t remove_edge(graph_t* g ,vertex_t v_start, vertex_t v_end);
void show_graph(graph_t* g, const char* msg);
status_t destroy_graph(graph_t** pp_g);

status_t dfs(graph_t* g, vertex_t v);
status_t bsf(graph_t* g, vertex_t v);

/* Graph Auxillary routines */
void dfs_visit(graph_t* g, vnode_t* pv);
void reset(graph_t* g);

/* Vertical list management - Interface routines */
vlist_t* v_create_list(void);
status_t v_insert_end(vlist_t* pv_list, vertex_t v);

/* Vertical list management - Auxillary routines */
void v_generic_insert(vnode_t* p_beg, vnode_t* p_mid, vnode_t* p_end);
void v_generic_delete(vnode_t* p_delete_node);
vnode_t* v_search_node(vlist_t* pv_list, vertex_t v);
vnode_t* v_get_node(vertex_t v);

/* Horizontal list management  -Interface routines */
hlist_t* h_create_list(void);
status_t h_insert_end(hlist_t* ph_list, vertex_t v);

/* Horizonal list management - Auxillary routines */
void h_generic_insert(hnode_t* p_beg, hnode_t* p_mid, hnode_t* p_end);
void h_generic_delete(hnode_t* p_delete_node);
hnode_t* h_search_node(hlist_t* ph_list, vertex_t v);
hnode_t* h_get_node(vertex_t v);

/* vptrnode queue management - Interface routines */
vptrqueue_t* vptr_create_queue(void);
status_t vptr_enqueue(vptrqueue_t* pvptr_queue, vnode_t* pv);
status_t vptr_dequeue(vptrqueue_t* pvptr_queue, vnode_t** pp_v);
Bool vptr_is_queue_emepty(vptrqueue_t* pvptr_queue);
status_t vptr_destroy_queue(vptrqueue_t** pp_queue);

/* vptrnode list management - interface routines */
vptrlist_t* vptr_create_list(void);
status_t vptr_insert_end(vptrlist_t* pvptr_list, vnode_t* v);
status_t vptr_pop_start(vptrlist_t* pvptr_list, vnode_t** pp_v);
status_t vptr_destory_list(vptrlist_t** pp_vptr_list);

/* vptrnode list management - Auxillary routines */
void vptr_generic_insert(vptrnode_t* p_beg, vptrnode_t* p_mid, vptrnode_t* p_end);
void vptr_generic_delete(vptrnode_t* p_delete_node);
vptrnode_t* vptr_search_node(vptrlist_t* pvptr_list, vnode_t* pv);
vptrnode_t* vptr_get_node(vnode_t* pv_new_node);

/* Auxillary routines */
void* xcalloc(size_t nr_element, size_t size_per_element);

#endif; /*_GRAPH_H*/