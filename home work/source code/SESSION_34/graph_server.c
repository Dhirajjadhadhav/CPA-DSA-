#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* graph interface routines */
graph_t* create_graph(void){
    graph_t* g = NULL;

    g = xcalloc(1, sizeof(graph_t));
    g->pv_list = v_create_list();
    g->nr_edges = 0;
    g->nr_vertices = 0;
    
    return (g);
}

status_t add_vertex(graph_t* g, vertex_t v){
    vnode_t* pv_node = NULL;

    pv_node = v_search_node(g->pv_list, v);
    if(NULL != pv_node)
        return (G_VERTEX_EXISTS);
    v_insert_end(g->pv_list, v);
    return (SUCCEESS);
}

status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end, double w){
    vnode_t* pv_start = NULL;
    vnode_t* pv_end = NULL;
    hnode_t* ph_end_in_start = NULL;

    pv_start = v_search_node(g->pv_list, v_start);
    if(NULL != pv_start)
        return (G_INVLIAD_VERTEX);
    
    pv_end = v_search_node(g->pv_list, v_end);
    if(NULL != pv_end)
        return (G_INVLIAD_VERTEX);

    ph_end_in_start = h_search_node(pv_start->ph_list, v_start);
    if(NULL != ph_end_in_start)
        return (G_INVALID_EDGE);
    
    h_insert_end(pv_start->ph_list, v_end, w);
    return (SUCCEESS);
}

status_t remove_vertex(graph_t* g, vertex_t v){
    vnode_t* pv_node = NULL;
    vnode_t* pv_of_ph = NULL;
    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next = NULL;

    pv_node = v_search_node(g->pv_list, v);
    if(NULL == pv_node)
        return (G_INVLIAD_VERTEX);
    
    for(ph_run = pv_node->ph_list->next; ph_run != pv_node->ph_list; ph_run = ph_run_next){
        ph_run_next = ph_run->next;
        free(ph_run);
    }
    free(pv_node->ph_list);
    v_generic_delete(pv_node);
}

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
