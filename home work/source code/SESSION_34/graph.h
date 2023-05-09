#ifndef _GRAPH_H
#define _GRAPH_H

/* Header files*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/*defines */
#define SUCCEESS            1
#define TRUE                1
#define FALSE               0
#define G_INVLIAD_VERTEX    2
#define G_INVALID_EDGE      3
#define G_VERTEX_EXISTS     4
#define G_VERTEX_EXISTS     5

/*typedef declaratioon */
typedef long long int ssize_t;
typedef long long int vertex_t;
typedef struct hnode hnode_t;
typedef hnode_t hlist_t;
typedef struct vnode vnode_t;
typedef vnode_t vlist_t;
typedef struct vnodeptr vnodeptr_t;
typedef vnodeptr_t vnodeptr_list_t;
typedef vnodeptr_list_t vnodeptr_stack_t;
typedef struct graph graph_t;
typedef enum color color_t;
typedef int status_t;

/* Definations of data structure*/
enum color{
        WHITE = 0,
        GRAY,
        BLACK
};

struct hnode{

    vertex_t v;
    double w;

    struct hnode* next; 
    struct hnode* prev;
};

struct vnode{

    vertex_t v;
    color_t color;
    double d;
    hlist_t* ph_list;
    struct vnode* v_pred;

    struct vnode* prev;
    struct vnode* next;
};

struct vnodeptr{
    vnode_t* pv;
    struct vnodeptr* next;
    struct vnodeptr* prev;
};

struct graph{
    vlist_t* pv_list;
    ssize_t nr_vertices;
    ssize_t nr_edges;
};

/* graph interface routines */
graph_t* create_graph(void);
status_t add_vertex(graph_t* g, vertex_t v);
status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end, double w);
status_t remove_vertex(graph_t* g, vertex_t v);
status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end);
void show_graph(graph_t* g, const char* msg);
status_t destroy_graph(graph_t** pp_g);
status_t bellman_foed(graph_t* g, vertex_t s);

/*verticale list interface routines */
vlist_t* v_create_list(void);
status_t v_insert_end(vlist_t* pv_list, vertex_t v);
status_t v_destroy_list(vlist_t** ppv_list);

/* verttical list helper routines*/
void v_generic_insert(vnode_t* p_beg, vnode_t* p_mid, vnode_t* p_end);
void v_generic_delete(vnode_t* p_delete);
vnode_t* v_search_node(vlist_t* pv_list, vertex_t v);
vnode_t* v_get_node(vertex_t v);

/*Horizontal list interface routines*/
hlist_t* h_create_list(void);
status_t h_insert_end(hlist_t* ph_list, vertex_t v);
status_t h_destroy_list(hlist_t** pph_list);

/*Horizontal list helper routines */
void h_generic_insert(hnode_t* p_beg, hnode_t* p_mid, hnode_t* p_end);
void h_generic_delete(hnode_t* p_delete_node);
hnode_t* h_search_node(hlist_t* ph_list, vertex_t v);
hnode_t* h_get_node(vertex_t v, double w);

/*vnodeptr list  interface routines */
vnodeptr_list_t* vnodeptr_create_list(void);
status_t vnodeptr_insert_end(vnodeptr_list_t* pvptr_list, vnode_t* pv_node);
status_t vnodeptr_get_end(vnodeptr_list_t* pvptr_list, vnode_t** pp_vnode);
status_t vnodeptr_pop_end(vnodeptr_list_t* pvptr_list, vnode_t** pp_vnode);
status_t vnodeptr_is_list_empty(vnodeptr_list_t* pvptr_list);
status_t vnodeptr_destroy_list(vnodeptr_list_t** ppvptr_list);

/*vnodeptr list helper routines */
void vnodeptr_generic_insert(vnodeptr_t* p_beg, vnodeptr_t* p_mid, vnodeptr_t* p_end);
void vnodeptr_generic_delete(vnodeptr_t* p_delete);
vnodeptr_t* vnodeptr_search_node(vnodeptr_list_t* pvptr_list, vnode_t* pv);
vnodeptr_t* vnodeptr_get_node(vnode_t* pv);

/*vnodeptr stack inttrface routines*/
vnodeptr_stack_t* vptr_create_stack(void);
status_t vnodeptr_push(vnodeptr_stack_t* pvptr_stack, vnode_t* pv_node);
status_t vnodeptr_pop(vnodeptr_stack_t* pvptr_stack, vnode_t** ppv_node);
status_t vnodeptr_top(vnodeptr_stack_t* pvptr_stack, vnode_t** ppv_node);
status_t vnodeptr_is_stack_empty(vnodeptr_t* pvptr_stack);
status_t vnodeptr_destroy_stack(vnodeptr_t** pvptr_stack);

/*general helper routines */
void* xcalloc(size_t nr_element, size_t size_per_element);

#endif /* _GRAPH_H */