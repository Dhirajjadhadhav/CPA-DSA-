#include <stdio.h> 
#include <stdlib.h> 
#include "graph.h"

/* Graph interface routines */
graph_t* create_graph(void)
{
    graph_t* g = NULL; 

    g = (graph_t*)xcalloc(1, sizeof(graph_t)); 
    g->pv_list = v_create_list(); 
    g->nr_v = 0; 
    g->nr_e = 0; 

    return (g); 
}

status_t add_vertex(graph_t* g, vertex_t v)
{
    vnode_t* pv_node = NULL; 

    pv_node = v_search_node(g->pv_list, v); 
    if(pv_node != NULL)
        return (G_VERTEX_EXISTS); 
    v_insert_end(g->pv_list, v); 
    g->nr_v += 1; 

    return (SUCCESS); 
}

status_t remove_vertex(graph_t* g, vertex_t v)
{
    vnode_t* pv_node = NULL; 
    vnode_t* pv_of_hvertex = NULL; 
    hnode_t* ph_run = NULL; 
    hnode_t* ph_run_next = NULL; 
    hnode_t* ph_of_v_in_hlist = NULL; 

    pv_node = v_search_node(g->pv_list, v); 
    if(pv_node == NULL)
        return (G_INVALID_VERTEX); 
    
    for(ph_run = pv_node->ph_list->next; 
        ph_run != pv_node->ph_list; 
        ph_run = ph_run_next)
    {
        ph_run_next = ph_run->next; 
        pv_of_hvertex = v_search_node(g->pv_list, ph_run->v); 
        
        if(pv_of_hvertex == NULL)
            return (G_CORRUPT); 
        
        ph_of_v_in_hlist =  h_search_node(pv_of_hvertex->ph_list, v); 
        if(ph_of_v_in_hlist == NULL)
            return (G_CORRUPT); 
       
        h_generic_delete(ph_of_v_in_hlist); 
        h_generic_delete(ph_run); 
        g->nr_e -= 1; 
    }

    free(pv_of_hvertex->ph_list); 
    v_generic_delete(pv_node); 
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
    if(pv_end == NULL)
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

    if(ph_end_in_start == NULL || ph_start_in_end == NULL)
        return (G_INVALID_EDGE); 

    h_generic_delete(ph_end_in_start); 
    h_generic_delete(ph_start_in_end); 

    g->nr_e -= 1; 

    return (SUCCESS); 
}

void show_graph(graph_t* g, const char* msg)
{
    vnode_t* pv_run = NULL; 
    hnode_t* ph_run = NULL; 

    if(msg)
        puts(msg); 

    printf("G(V,E):|V|=%llu, |E|=%llu\n", g->nr_v, g->nr_e); 
    
    for(pv_run = g->pv_list->next; 
        pv_run != g->pv_list; 
        pv_run = pv_run->next)
    {
        printf("[%lld]\t->\t", pv_run->v); 
        for(ph_run = pv_run->ph_list->next; 
            ph_run != pv_run->ph_list; 
            ph_run = ph_run->next)
            printf("[%lld]<->", ph_run->v); 
        puts("[END]"); 
    }
}

status_t destroy_graph(graph_t** pp_g)
{
    graph_t* g = NULL; 
    vnode_t* pv_run = NULL; 
    vnode_t* pv_run_next = NULL; 
    hnode_t* ph_run = NULL; 
    hnode_t* ph_run_next = NULL; 

    //puts("start"); 
    g = *pp_g; 
    for(pv_run = g->pv_list->next; 
        pv_run != g->pv_list; 
        pv_run = pv_run_next)
    {
       // puts("outer1"); 
        //printf("pv_run->v = %lld\n", pv_run->v); 
        pv_run_next = pv_run->next;
        for(ph_run = pv_run->ph_list->next; 
            ph_run != pv_run->ph_list; 
            ph_run = ph_run_next)
        {
           // puts("\tinner"); 
            ph_run_next = ph_run->next; 
            free(ph_run); 
        }
        //puts("outer2"); 
        free(pv_run->ph_list); 
        free(pv_run); 
    }

   // puts("end1"); 
    free(g->pv_list); 
    free(g); 
    *pp_g = NULL; 
   // puts("end2"); 
    return (SUCCESS); 
}

status_t dfs(graph_t* g, vertex_t v)
{
    vnode_t* pv_start = NULL; 
    vnode_t* pv_run = NULL; 
    
    reset(g); 

    pv_start = v_search_node(g->pv_list, v); 
    if(pv_start == NULL)
        return (G_INVALID_VERTEX); 

    printf("[START]<->"); 
    dfs_visit(g, pv_start); 

    /* 
        In case of graph which is not connected but contains 
        serveral connected components, then dfs_visit() must 
        be called on one vertex from each connected component 
        while its color is WHITE 
    */

   for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
        if(pv_run->color == WHITE)
            dfs_visit(g, pv_run); 

    puts("[END]"); 
    return (SUCCESS); 
}

/* Graph auxillary routines */
void dfs_visit(graph_t* g, vnode_t* pv)
{
    hnode_t* ph_run = NULL; 
    vnode_t* pv_adj = NULL; 

    pv->color = GRAY; 
    printf("[%lld]<->", pv->v); 

    for(ph_run = pv->ph_list->next; ph_run != pv->ph_list; ph_run = ph_run->next)
    {
        pv_adj = v_search_node(g->pv_list, ph_run->v); 
        if(pv_adj->color == WHITE)
            dfs_visit(g, pv_adj); 
    }

    pv->color = BLACK; 
}

void reset(graph_t* g)
{
    vnode_t* pv_run = NULL; 

    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        pv_run->color = WHITE; 
        pv_run->pv_pred = NULL; 
    }
}

/* Vertical list management - Interface routines */
vlist_t* v_create_list(void)
{
    vlist_t* pv_list = NULL; 

    pv_list = (vlist_t*)xcalloc(1, sizeof(vnode_t)); 
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

/* Vertical list management - Auxillary routines */
void v_generic_insert(vnode_t* p_beg, vnode_t* p_mid, vnode_t* p_end)
{
    p_mid->next = p_end; 
    p_mid->prev = p_beg; 
    p_beg->next = p_mid; 
    p_end->prev = p_mid; 
}

void v_generic_delete(vnode_t* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next; 
    p_delete_node->next->prev = p_delete_node->prev; 
    free(p_delete_node); 
}

vnode_t* v_search_node(vlist_t* pv_list, vertex_t v)
{
    vnode_t* pv_run = NULL; 

    for(pv_run = pv_list->next; pv_run != pv_list; pv_run = pv_run->next)
        if(pv_run->v == v)
            return (pv_run); 
    
    return (NULL); 
}

vnode_t* v_get_node(vertex_t v)
{
    vnode_t* pv_node = NULL; 

    pv_node = (vnode_t*)xcalloc(1, sizeof(vnode_t)); 

    pv_node->v = v; 
    pv_node->ph_list = h_create_list(); 
    pv_node->color = WHITE; 
    pv_node->pv_pred = NULL; 

    return (pv_node); 
}

/* Horizontal list management - Interface routines */
hlist_t* h_create_list(void)
{
    hlist_t* ph_list = NULL; 

    ph_list = h_get_node(-1); 
    ph_list->prev = ph_list; 
    ph_list->next = ph_list; 

    return (ph_list); 
}

status_t h_insert_end(hlist_t* ph_list, vertex_t v)
{
    h_generic_insert(ph_list->prev, h_get_node(v), ph_list); 
    return (SUCCESS); 
}

/* Horizontal list management - Auxillary routines */
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
}

hnode_t* h_search_node(hlist_t* ph_list, vertex_t v)
{
    hnode_t* ph_run = NULL; 

    for(ph_run = ph_list->next; ph_run != ph_list; ph_run = ph_run->next)
        if(ph_run->v == v)
            return (ph_run); 

    return (NULL); 
}

hnode_t* h_get_node(vertex_t v)
{
    hnode_t* ph_new_node = NULL; 

    ph_new_node = (hnode_t*)xcalloc(1, sizeof(hnode_t)); 
    ph_new_node->v = v; 

    return (ph_new_node); 
}

/* Auxillary routines */
void* xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL; 

    p = calloc(nr_elements, size_per_element); 
    if(p == NULL)
    {
        fprintf(stderr, "calloc():fatal:out of memory\n"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
}