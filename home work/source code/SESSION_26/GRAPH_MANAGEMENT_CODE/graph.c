#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

/*  Graph inerface routines   */
graph_t* create_graph(void)
{
    graph_t* g = NULL;

    g = (graph_t*)xcalloc(1, sizeof(graph_t));

    g->nr_e = 0;
    g->nr_v = 0;
    g->pv_list = v_create_list();

    return (g);
}

status_t add_vertex(graph_t* g, vertex_t v)
{
    vnode_t* pv_node = NULL;
    pv_node = v_search_node(g->pv_list, v);
    if(pv_node != NULL)
        return (G_VERTEX_EXISTS);
    
    return (v_insert_end(g->pv_list, v));
}

status_t remove_vertex(graph_t* g, vertex_t v)
{
    vnode_t* pv_delete_node = NULL;
    vnode_t* pv_adj_node_in_list = NULL;
    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next;
    hnode_t* ph_delete_vertex_entry_inadj_list_of_adj_vertex = NULL;

    pv_delete_node = v_search_node(g->pv_list, v);
    if(pv_delete_node == NULL)
        return (G_INVALID_VERTEX);
    for(
        ph_run = pv_delete_node->next;
        ph_run != pv_delete_node;
        ph_run = ph_run_next
    )
    {
        ph_run_next = ph_run->next;
        pv_adj_node_in_list = v_search_node(g->pv_list, ph_run->v);
        ph_delete_vertex_entry_inadj_list_of_adj_vertex = h_search_node(pv_adj_node_in_list->ph_list, v);
        h_generic_delete(ph_delete_vertex_entry_inadj_list_of_adj_vertex);
        free(ph_run);
        g->nr_e -= 1;
    }
    free(pv_delete_node->ph_list);
    v_generic_delete(ph_run);
    g->nr_v -= 1;

    return (SUCCESS);
}

status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end)
{
    vnode_t* pv_start = NULL;
    vnode_t* pv_end = NULL;
    hnode_t* ph_start_in_end = NULL;
    hnode_t* ph_end_in_start = NULL;

    pv_start = v_search_node(g->pv_list, v_start);
    if(pv_start == NULL)
        return (G_INVALID_VERTEX);
    pv_end = v_search_node(g->pv_list, v_end);
    if(pv_end = NULL)
        return (G_INVALID_VERTEX);
    
    ph_end_in_start = h_search_node(pv_start->ph_list, v_end);
    ph_start_in_end = h_search_node(pv_end->ph_list, v_start);

    if(ph_end_in_start != NULL && ph_start_in_end != NULL)
        return (G_EDGE_EXISTS);
    h_insert_end(pv_start->ph_list, v_end);
    h_insert_end(pv_end->ph_list, v_start);

    g->nr_e += 1;
    return (SUCCESS);
}

status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end)
{
    vnode_t* pv_start = NULL;
    vnode_t* pv_end = NULL;
    hnode_t* ph_end_in_start = NULL;
    hnode_t* ph_start_in_end = NULL;

    pv_start = v_search_node(g->pv_list, v_start);
    pv_end = v_search_node(g->pv_list, v_end);

    if(pv_start == NULL || pv_end == NULL)
        return (G_INVALID_VERTEX);
    
    ph_end_in_start = h_search_node(pv_start->ph_list, v_end);
    ph_start_in_end = h_search_node(pv_end->ph_list, v_start);

    if(ph_end_in_start == NULL || ph_end_in_start == NULL)
        return (G_INVALID_EDGE);
    
    h_generic_delete(ph_start_in_end);
    h_generic_delete(ph_end_in_start);

    g->nr_e -= 1;

    return (SUCCESS);
}

void show_graph(graph_t* g, const char* msg)
{

}
status_t destroy_graph(graph_t** pp_g)
{

}

/*vertical list management - Interface routines*/
vlist_t* v_create_list(void)
{
    vlist_t* pv_list = NULL;

    pv_list  = (vlist_t*)xcalloc(1, sizeof(vnode_t));

    pv_list->v = -1;
    pv_list->ph_list = NULL;
    pv_list->prev = pv_list;
    pv_list->next = pv_list;

    return (pv_list);
}

status_t v_insert_end(vlist_t* pv_list, vertex_t v)
{
    v_generic_insert(pv_list->prev, v_get_node(v), pv_list);
    return (SUCCESS);
}

/*Vertical list managaement - Auxillary routines */
void v_generic_insert(vnode_t* p_beg, vnode_t* p_mid, vnode_t* p_end)
{
    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    p_end->prev = p_mid;
}

void v_generic_delete(vnode_t* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next ;
    p_delete_node->next->prev   = p_delete_node->prev;
    free(p_delete_node);
    p_delete_node = NULL;
}

vnode_t* v_search_node(vlist_t* pv_list, vertex_t v)
{
    vnode_t* pv_run = NULL;

    pv_run = pv_list->next;
    while(pv_run->next != pv_list)
    {
        if(pv_run->v == v)
            return (pv_run);
        pv_run = pv_run->next;
    }

    return (NULL);
}

vnode_t* v_get_node(vertex_t v)
{
    vnode_t* pv_node = NULL;

    pv_node = (vnode_t*)xcalloc(1, sizeof(vnode_t));
    
    pv_node->v = v;
    pv_node->ph_list = h_create_list();

    return (pv_node);
}

/*Horizontal list management - Interface routines */
hlist_t* h_create_list(void)
{
    hlist_t* ph_list = NULL;

    ph_list = h_get_node(-1);
    ph_list->next = ph_list;
    ph_list->prev = ph_list;

    return (ph_list);
}

status_t h_insert_end(vlist_t* ph_list, vertex_t v)
{
    h_generic_insert(ph_list->prev, h_get_node(v), ph_list);
    return (SUCCESS);
}

/*Horizonatl list management - Auxillary routines*/
void h_generic_insert(hnode_t* p_beg, hnode_t* p_mid, hnode_t* p_end)
{
    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    p_end->prev = p_mid;
}

void h_generic_delete(hnode_t* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next;
    p_delete_node->next->prev = p_delete_node->prev;
    free(p_delete_node);
    p_delete_node = NULL; 
}

hnode_t* h_search_node(hlist_t* ph_list, vertex_t* v)
{
    hnode_t* ph_run = NULL;

    ph_run = ph_list->next;
    while(ph_run != ph_list)
    {
        if(ph_run->v == v)
            return (ph_run);
        ph_run = ph_run->next;
    }
}

hnode_t* h_get_node(vertex_t v)
{
    hnode_t* ph_node = NULL;

    ph_node = (hnode_t*)calloc(1, sizeof(hnode_t));
    ph_node->v = v;

    return (ph_node);
}

/*Auxillary routines */
void* xcalloc(size_t nr_element, size_t size_per_element)
{
    void* p = NULL;
    p = calloc(nr_element, size_per_element);
    if(p == NULL)
    {
        fprintf(stderr, "calloc():fatal out of memory\n");
        exit(EXIT_FAILURE);
    }

    return (p);
}
