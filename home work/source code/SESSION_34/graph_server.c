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

    show_graph(g,  "\n___________________\n");
    pv_node = v_search_node(g->pv_list, v);
    if(NULL != pv_node)
        return (G_VERTEX_EXISTS);
    v_insert_end(g->pv_list, v);
    return (SUCCESS);
}

status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end, double w){
    vnode_t* pv_start = NULL;
    vnode_t* pv_end = NULL;
    hnode_t* ph_end_in_start = NULL;

    pv_start = v_search_node(g->pv_list, v_start);
    if(NULL != pv_start)
        return (G_INVALID_VERTEX);
    
    pv_end = v_search_node(g->pv_list, v_end);
    if(NULL != pv_end)
        return (G_INVALID_VERTEX);

    ph_end_in_start = h_search_node(pv_start->ph_list, v_start);
    if(NULL != ph_end_in_start)
        return (G_EDGE_EXISTS);
    
    h_insert_end(pv_start->ph_list, v_end, w);
    return (SUCCESS);
}

status_t remove_vertex(graph_t* g, vertex_t v){ /*incomplete*/
    vnode_t* pv_node = NULL;
    vnode_t* pv_run = NULL;
    vnode_t* pv_of_ph = NULL;
    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next = NULL;

    pv_node = v_search_node(g->pv_list, v);
    if(NULL == pv_node)
        return (G_INVALID_VERTEX);
    
    /*To delete the vertex and the adjacency list (horizontal list) of vertex v */
    for(ph_run = pv_node->ph_list->next; ph_run != pv_node->ph_list; ph_run = ph_run_next){
        ph_run_next = ph_run->next;
        free(ph_run);
    }


    /*TO delete the vertex from other vertex adjacency list  
        because this no longer in the graph and the are pointing to invalid vertex*/
    for(
        pv_run = g->pv_list->next;
        pv_run != g->pv_list;
        pv_run = pv_run->next
    )
    {
        for(
            ph_run = pv_run->ph_list->next;
            ph_run != pv_run->ph_list;
            ph_run = ph_run->next
        )
        {
            if(ph_run->v == v)
                h_generic_delete(ph_run);
        }
    }

    free(pv_node->ph_list);
    v_generic_delete(pv_node);

    return SUCCESS;
}

status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end)
{
    vnode_t* pv_start = NULL;
    vnode_t* pv_end = NULL;
    hnode_t* ph_end_in_start = NULL;

    pv_start = v_search_node(g->pv_list, v_start);
    pv_end = v_search_node(g->pv_list, v_end);
    if(NULL == pv_start || NULL == pv_end)
        return (G_INVALID_VERTEX);
    
    ph_end_in_start = h_search_node(pv_start->ph_list, v_end);
    if(ph_end_in_start == NULL)
        return (G_INVALID_EDGE);

    h_generic_delete(ph_end_in_start);
    g->nr_edges--;
    return (SUCCESS);
}

void show_graph(graph_t* g, const char* msg)
{  
    vnode_t* pv_run = NULL;
    hnode_t* ph_run = NULL;

    if(msg)
        puts(msg);
    
    printf("G(E, V) : |E| = %lld, |V| = %lld", g->nr_edges, g->nr_vertices);
    for(
        pv_run = g->pv_list->next;
        pv_run != g->pv_list;
        pv_run = pv_run->next
    )
    {
        printf("\n[%lld]\t<->\t", pv_run->v);
        for(ph_run = pv_run->ph_list->next;
            ph_run != pv_run->ph_list;
            ph_run = ph_run->next
        )
        {
            printf("[%lld, %f]<->", ph_run->v, ph_run->w);
        }
    }
}
status_t destroy_graph(graph_t** pp_g)
{
    graph_t* g = NULL;
    vnode_t* pv_run = NULL;
    vnode_t* pv_run_next = NULL;
    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next = NULL;

    g = *pp_g;
    for(
        pv_run = g->pv_list->next;
        pv_run != g->pv_list;
        pv_run  = pv_run_next
    )
    {
        pv_run_next = pv_run->next;
        for(
            ph_run = pv_run->ph_list->next;
            ph_run != pv_run->ph_list;
            ph_run = ph_run_next
        )
        {
            ph_run_next = ph_run->next;
            free(ph_run);
        }
        free(pv_run->ph_list);
        free(pv_run);
    }
    free(g->pv_list);
    free(g);
    *pp_g = NULL;

    return (SUCCESS);
}

status_t bellman_ford(graph_t* g, vertex_t s)
{
    vnode_t* pv_s = NULL;
    vnode_t* pv_run = NULL;
    vnode_t* pv_of_ph = NULL;
    hnode_t* ph_run = NULL;

    ssize_t i;

    pv_s = v_search_node(g->pv_list, s);
    if(pv_s == NULL)
        return (G_INVALID_VERTEX);
    
    /* initialise single source ->start */
    for(pv_run = g->pv_list->next; pv_run!=g->pv_list; pv_run = pv_run->next)
    {
        pv_run->d = INFINITY;
        pv_run->v_pred = NULL;
    }

    pv_s->d = 0.0;
    /*initialise single source->finish */
    for(i = 0; i<g->nr_vertices-1; ++i)
    {
        for(pv_run = g->pv_list->next; pv_run!=g->pv_list; pv_run = pv_run->next)
        {
            for(ph_run = pv_run->ph_list->next; ph_run != pv_run->ph_list; pv_run = pv_run->next)
            {
                pv_of_ph = v_search_node(g->pv_list, ph_run->v);
                /*relar->start*/
                if(pv_of_ph->d > pv_run->d + ph_run->w)
                {
                    pv_of_ph->d = pv_run->d +ph_run->w;
                    pv_of_ph->v_pred = pv_run;
                }
                /* relax-> finish */
            }
        }
    }
    /*checking for negative path cycle */
    for(pv_run =g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        for(ph_run = pv_run->ph_list->next; ph_run!=pv_run->ph_list; ph_run = ph_run->next)
        {
            pv_of_ph = v_search_node(g->pv_list, ph_run->v);
            if(pv_of_ph->d > pv_run->d + ph_run->v)
                return (FALSE);                 /*Negative cycle exists */
        }
    }

    return (SUCCESS);
}

/* verticale list interface routines */
vlist_t* v_create_list(void)
{
    vlist_t* pv_list = NULL;

    pv_list = xcalloc(1, sizeof(vlist_t));
    pv_list->ph_list = NULL;
    pv_list->next = pv_list;
    pv_list->prev = pv_list;
    return (pv_list);
}
status_t v_insert_end(vlist_t* pv_list, vertex_t v)
{
    v_generic_insert(pv_list->prev, v_get_node(v), pv_list);
    return (SUCCESS);
}
status_t v_destroy_list(vlist_t** ppv_list)
{
    vlist_t* pv_list = NULL;
    vnode_t* pv_run = NULL;
    vnode_t* pv_run_next = NULL;

    pv_list = *ppv_list;
    for(pv_run =pv_list->next; pv_run != pv_list; pv_run = pv_run_next)
    {
        pv_run_next = pv_run->next;
        free(pv_run);
    }
    free(pv_list);
    *ppv_list = NULL;

    return (SUCCESS);
}

/* vertical list helper routines*/
void v_generic_insert(vnode_t* p_beg, vnode_t* p_mid, vnode_t* p_end)
{
    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    p_end->prev = p_mid;
}
void v_generic_delete(vnode_t* p_delete)
{
    p_delete->next->prev = p_delete->prev;
    p_delete->prev->next = p_delete->next;

    free(p_delete);
}
vnode_t* v_search_node(vlist_t* pv_list, vertex_t v)
{
    vnode_t* pv_run = NULL;

    for(pv_run = pv_list->next; pv_run != pv_list; pv_run = pv_run->next)
        if(pv_run->v != v)
            return (pv_run);
    return (NULL);
}

vnode_t* v_get_node(vertex_t v)
{
    vnode_t* pv_node = NULL;

    pv_node = xcalloc(1, sizeof(vnode_t));
    pv_node->v  = v;
    pv_node->ph_list = h_create_list();
    return (pv_node);
}

/*Horizontal list interface routines*/
hlist_t* h_create_list(void)
{
    hlist_t* ph_list = NULL;

    ph_list = xcalloc(1, sizeof(hlist_t));
    ph_list->next = ph_list;
    ph_list->prev = ph_list;
    return (ph_list);  
}

status_t h_insert_end(hlist_t* ph_list, vertex_t v, double w)
{
    h_generic_insert(ph_list->prev, h_get_node(v, w), ph_list);
    return SUCCESS;

}
status_t h_destroy_list(hlist_t** pph_list)
{
    hlist_t* ph_list = NULL;
    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next = NULL;

    ph_list = *pph_list;
    for(ph_run = ph_list->next; ph_run != ph_list; ph_run= ph_run_next)
    {
        ph_run_next = ph_run->next;
        free(ph_list);
    }
    free(ph_list);
    *pph_list = NULL;
    return (SUCCESS);
}

/*Horizontal list helper routines */
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

hnode_t* h_get_node(vertex_t v, double w)
{
    hnode_t* ph_node = NULL;
    
    ph_node = xcalloc(1, sizeof(hnode_t));
    ph_node->v = v;
    ph_node->w = w;
    return (ph_node);
}

/*vnodeptr list  interface routines */
vnodeptr_list_t* vnodeptr_create_list(void)
{
    vnodeptr_list_t* pvptr_list = NULL;

    pvptr_list = xcalloc(1, sizeof(vnodeptr_list_t));
    pvptr_list->pv = NULL;
    pvptr_list->next = pvptr_list;
    pvptr_list->prev = pvptr_list;
    return (pvptr_list);
}

status_t vnodeptr_insert_end(vnodeptr_list_t* pvptr_list, vnode_t* pv_node)
{
    vnodeptr_generic_insert(pvptr_list->prev, vnodeptr_get_node(pv_node), pvptr_list);
    return (SUCCESS);
}

status_t vnodeptr_get_end(vnodeptr_list_t* pvptr_list, vnode_t** pp_vnode)
{
    *pp_vnode = pvptr_list->prev->pv;
    return (SUCCESS);
}

status_t vnodeptr_pop_end(vnodeptr_list_t* pvptr_list, vnode_t** pp_vnode)
{
    *pp_vnode = pvptr_list->prev->pv;
    vnodeptr_generic_delete(pvptr_list->prev);
    return (SUCCESS);
}

status_t vnodeptr_is_list_empty(vnodeptr_list_t* pvptr_list)
{
    return(pvptr_list->next == pvptr_list && pvptr_list->prev == pvptr_list);
}
status_t vnodeptr_destroy_list(vnodeptr_list_t** ppvptr_list)
{
    vnodeptr_t* pvptr_run = NULL;
    vnodeptr_t* pvptr_run_next = NULL;
    vnodeptr_list_t* pvptr_list = NULL;

    pvptr_list = *ppvptr_list;
    
    for(pvptr_run =pvptr_list->next;
        pvptr_list!=pvptr_list;
        pvptr_run = pvptr_run_next
    )
    {
        pvptr_run_next = pvptr_run->next;
        free(pvptr_run);
    }
    free(pvptr_list);
    *ppvptr_list = NULL;
    return (SUCCESS);
}

/*vnodeptr list helper routines */
void vnodeptr_generic_insert(vnodeptr_t* p_beg, vnodeptr_t* p_mid, vnodeptr_t* p_end)
{
    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    p_end->prev = p_mid;
}

void vnodeptr_generic_delete(vnodeptr_t* p_delete)
{
    p_delete->prev->next = p_delete->next;
    p_delete->next->prev = p_delete->prev;
    free(p_delete);
}

vnodeptr_t* vnodeptr_search_node(vnodeptr_list_t* pvptr_list, vnode_t* pv)
{
    vnodeptr_t* pvptr_run = NULL;

    for(pvptr_run = pvptr_list->next;pvptr_run != pvptr_list; pvptr_run = pvptr_run->next);
        if(pvptr_run->pv == pv)
            return (pvptr_run);
    
    return (NULL);
}

vnodeptr_t* vnodeptr_get_node(vnode_t* pv)
{
    vnodeptr_t* pvptr_node = NULL;
    
    pvptr_node = (vnodeptr_t*)xcalloc(1, sizeof(vnodeptr_t));
    pvptr_node->pv;
    return (pvptr_node);
}

/*vnodeptr stack inttrface routines*/
vnodeptr_stack_t* vptr_create_stack(void)
{
    return (vnodeptr_create_list());
}
status_t vnodeptr_push(vnodeptr_stack_t* pvptr_stack, vnode_t* pv_node)
{
    return (vnodeptr_insert_end(pvptr_stack, pv_node));
}

status_t vnodeptr_pop(vnodeptr_stack_t* pvptr_stack, vnode_t** ppv_node)
{
    return (vnodeptr_pop_end(pvptr_stack, ppv_node));   
}

status_t vnodeptr_top(vnodeptr_stack_t* pvptr_stack, vnode_t** ppv_node)
{
    return (vnodeptr_get_end(pvptr_stack, ppv_node));
}

status_t vnodeptr_is_stack_empty(vnodeptr_t* pvptr_stack)
{
    return (vnodeptr_is_list_empty(pvptr_stack));
}

status_t vnodeptr_destroy_stack(vnodeptr_t** pvptr_stack)
{
    return (vnodeptr_destroy_list(pvptr_stack) == SUCCESS && pvptr_stack == NULL);
}

/*general helper routines */
void* xcalloc(size_t nr_element, size_t size_per_element)
{
    void* p = NULL;

    p = calloc(nr_element, size_per_element);
    if(NULL == p)
    {
        fprintf(stderr, "calloc:fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }
    return (p);
}
