#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

/* Graph Interface routines */
graph_t* create_graph(void)
{
    graph_t* g = NULL;

    g = (graph_t*)xcalloc(1, sizeof(graph_t));
    g->pv_list = v_create_list();
    g->nr_e = 0;
    g->nr_v = 0;


    return (g);
}

status_t add_vertex(graph_t* g, vertex_t v)
{
    vnode_t* pv_node = NULL;

    pv_node = v_search_node(g->pv_list, v);
    if(NULL != pv_node)
        return (G_VERTEX_EXISTS);
    v_insert_end(g->pv_list, v);
    g->nr_v += 1;

    return (SUCCESS);    
}

status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end)
{
    vnode_t* pv_start = NULL;
    vnode_t* pv_end = NULL;
    hnode_t* ph_end_in_start = NULL;
    hnode_t* ph_start_in_end = NULL;

    pv_start = v_search_node(g->pv_list, v_start);
    pv_end   = v_search_node(g->pv_list, v_end);

    if(NULL == pv_start || NULL == pv_end)
        return (G_INVALID_VERTEX);

    ph_end_in_start = h_search_node(pv_start->ph_list, v_end);
    ph_start_in_end = h_search_node(pv_end->ph_list, v_start);
 
    if(NULL != ph_end_in_start && NULL != ph_start_in_end)
        return (G_EDGE_EXISTS);
    if(NULL != ph_end_in_start || NULL != ph_start_in_end)
        return (G_CURROPT);  
    
    h_insert_end(pv_start->ph_list, v_end);
    h_insert_end(pv_end->ph_list, v_start);

    g->nr_e += 1;
    return (SUCCESS);
}

status_t remove_vertex(graph_t* g, vertex_t v)
{
    vnode_t* pv_node = NULL;
    vnode_t* pv_adj_node = NULL;
    hnode_t* ph_node_in_adj_node = NULL;
    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next = NULL;
    
    pv_node = v_search_node(g->pv_list, v);
    if(NULL == pv_node)
        return (G_INVALID_VERTEX);
    
    for(
        ph_run = pv_node->ph_list->next;
        ph_run != pv_node->ph_list;
        ph_run = ph_run_next
    )
    {
        ph_run_next = ph_run->next;
        pv_adj_node = v_search_node(g->pv_list, ph_run->v);
        if(NULL == pv_adj_node)
            return (G_CURROPT);
        ph_node_in_adj_node = h_search_node(pv_adj_node->ph_list, v);
        if(NULL == ph_node_in_adj_node)
            return (G_CURROPT);
        
        h_generic_delete(ph_node_in_adj_node);
        h_generic_delete(ph_run);

        g->nr_e -= 1;
    }
    free(pv_node->ph_list);
    v_generic_delete(pv_node);
    g->nr_v -=1;
    return (SUCCESS);
}
status_t remove_edge(graph_t* g ,vertex_t v_start, vertex_t v_end)
{
    vnode_t* pv_start = NULL;
    vnode_t* pv_end = NULL;
    hnode_t* ph_start_in_end = NULL;
    hnode_t* ph_end_in_start = NULL;

    pv_start = v_search_node(g->pv_list, v_start);
    pv_end = v_search_node(g->pv_list, v_end);

    if(NULL == pv_start || NULL == pv_end)
        return (G_INVALID_VERTEX);

    ph_end_in_start = h_search_node(pv_start->ph_list, v_end);   
    ph_start_in_end = h_search_node(pv_end->ph_list, v_start);

    if(NULL == ph_end_in_start && NULL == ph_start_in_end)
        return (G_INVALID_EDEGE);

    if(NULL == ph_end_in_start || NULL == ph_start_in_end)
        return (G_CURROPT);

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

    printf("G(E,V) : |V| = %llu, |E| = %llu\n", g->nr_v, g->nr_e);

    for(
        pv_run = g->pv_list->next;
        pv_run != g->pv_list;
        pv_run = pv_run->next
    )
    {
        printf("[%lld]\t<->\t", pv_run->v);
        for(
            ph_run = pv_run->ph_list->next;
            ph_run != pv_run->ph_list;
            ph_run = ph_run->next
        )
        {
            printf("[%lld]<->", ph_run->v);
        }
        puts("END");
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
        pv_run = pv_run_next
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


status_t dfs(graph_t* g, vertex_t v)
{
    vnode_t* pv_start = NULL;
    vnode_t* pv_run = NULL;

    reset(g);

    pv_start = v_search_node(g->pv_list, v);
    if(NULL == pv_start)
        return (G_INVALID_VERTEX);

    printf("[START]<->");
    dfs_visit(g, pv_start);

    for(pv_run = g->pv_list->next; pv_run!= g->pv_list; pv_run = pv_run->next)  
    {
        if(pv_run->color == WHITE)
            dfs_visit(g, pv_run);
    }
    puts("[END]");
    return (SUCCESS);
}
status_t bsf(graph_t* g, vertex_t s)
{
    vnode_t* pv_s = NULL;
    vnode_t* pv_u = NULL;
    hnode_t* ph_run = NULL;
    vnode_t* pv_adj = NULL;

    vptrqueue_t* pvptr_queue;
    status_t status;
    
    reset(g);
    pv_s = v_search_node(g->pv_list, s);
    if(NULL == pv_s)
        return (G_INVALID_VERTEX);
    
    pvptr_queue = vptr_create_queue();
    pv_s->color = GRAY;

    status = vptr_enqueue(pvptr_queue, pv_s);
    assert(status == SUCCESS);

    printf("[START]<->");
    while (!vptr_is_queue_emepty(pvptr_queue))
    {
        status  = vptr_dequeue(pvptr_queue, &pv_u);
        assert(status == SUCCESS);
        printf("[%lld]<->",pv_u->v);
        for(ph_run = pv_u->ph_list->next; 
            ph_run != pv_u->ph_list; 
            ph_run = ph_run->next)
        {
            pv_adj = v_search_node(g->pv_list, ph_run->v);
            if(pv_adj->color == WHITE)
            {
                pv_adj->color = GRAY;
                pv_adj->pv_pred = pv_u;
                vptr_enqueue(pvptr_queue, pv_adj);
            }
        }

        pv_u->color =BLACK;
    }
    puts("[END]");
    vptr_destroy_queue(&pvptr_queue);

    return (SUCCESS);
}

/* Graph Auxillary routines */
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
        {
            pv_adj->pv_pred = pv;
            dfs_visit(g, pv_adj);
        }
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

    pv_list = (vlist_t*)xcalloc(1, sizeof(vlist_t));
    pv_list->v = -1;
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


/* Vertical list management - Auxillary routines */
void v_generic_insert(vnode_t* pv_beg, vnode_t* pv_mid, vnode_t* pv_end)
{
    pv_mid->next = pv_end;
    pv_mid->prev = pv_beg;
    pv_beg->next = pv_mid;
    pv_end->prev = pv_mid;
}

void v_generic_delete(vnode_t* pv_delete_node)
{
    pv_delete_node->next->prev = pv_delete_node->prev;
    pv_delete_node->prev->next = pv_delete_node->next;
    free(pv_delete_node);
}

vnode_t* v_search_node(vlist_t* pv_list, vertex_t v)
{
    vnode_t* pv_run = NULL;

    for(pv_run = pv_list->next; pv_run !=pv_list; pv_run = pv_run->next)
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

/* Horizontal list management  -Interface routines */
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

/* Horizonal list management - Auxillary routines */
void h_generic_insert(hnode_t* ph_beg, hnode_t* ph_mid, hnode_t* ph_end)
{
    ph_mid->next = ph_end;
    ph_mid->prev = ph_beg;
    ph_beg->next = ph_mid;
    ph_end->prev = ph_mid;
}

void h_generic_delete(hnode_t* ph_delete_node)
{
    ph_delete_node->next->prev = ph_delete_node->prev;
    ph_delete_node->prev->next = ph_delete_node->next;
    free(ph_delete_node);
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
    hnode_t* ph_node = NULL;

    ph_node = (hnode_t*)xcalloc(1, sizeof(hnode_t));
    ph_node->v = v;

    return (ph_node);
}


/* vptrnode queue management - Interface routines */
vptrqueue_t* vptr_create_queue(void)
{
    return (vptr_create_list());
}
status_t vptr_enqueue(vptrqueue_t* pvptr_queue, vnode_t* pv)
{
    return (vptr_insert_end(pvptr_queue, pv));
}
status_t vptr_dequeue(vptrqueue_t* pvptr_queue, vnode_t** pp_v)
{
    return (vptr_pop_start(pvptr_queue, pp_v));
}
Bool vptr_is_queue_emepty(vptrqueue_t* pvptr_queue)
{
    return (pvptr_queue->next == pvptr_queue && pvptr_queue->prev == pvptr_queue);
}
status_t vptr_destroy_queue(vptrqueue_t** pp_queue)
{
    return (vptr_destory_list(pp_queue));
}

/* vptrnode list management - interface routines */
vptrlist_t* vptr_create_list(void)
{
    vptrlist_t* pvptrv_list = NULL;

    pvptrv_list = (vptrlist_t*)xcalloc(1, sizeof(vptrlist_t));

    pvptrv_list->pv = NULL;
    pvptrv_list->next = pvptrv_list;
    pvptrv_list->prev = pvptrv_list;

    return (pvptrv_list);
}

status_t vptr_insert_end(vptrlist_t* pvptr_list, vnode_t* pv)
{
    vptr_generic_insert(pvptr_list->prev, vptr_get_node(pv), pvptr_list);
    return (SUCCESS);
}

status_t vptr_pop_start(vptrlist_t* pvptr_list, vnode_t** pp_v)
{
    if(pvptr_list->next == pvptr_list && pvptr_list->prev == pvptr_list)
        return (VPTR_LIST_EMPTY);
    *pp_v = pvptr_list->next->pv;
    vptr_generic_delete(pvptr_list->next);

    return (SUCCESS);
}

status_t vptr_destory_list(vptrlist_t** pp_vptr_list)
{
    vptrlist_t* p_vptr_list = NULL;
    vptrnode_t* pvptr_run = NULL;
    vptrnode_t* pvptr_run_next  = NULL;

    p_vptr_list = *pp_vptr_list;
    for(pvptr_run = p_vptr_list->next; pvptr_run!= p_vptr_list; pvptr_run = pvptr_run_next)
    {
        pvptr_run_next = pvptr_run->next;
        free(pvptr_run);
    }
    free(p_vptr_list);
    *pp_vptr_list = NULL;
    return (SUCCESS);
}

/* vptrnode list management - Auxillary routines */
void vptr_generic_insert(vptrnode_t* pvptr_beg, vptrnode_t* pvptr_mid, vptrnode_t* pvptr_end)
{
    pvptr_mid->next = pvptr_end;
    pvptr_mid->prev = pvptr_beg;
    pvptr_beg->next = pvptr_mid;
    pvptr_end->prev = pvptr_mid;
}

void vptr_generic_delete(vptrnode_t* pvptr_delete_node)
{
    pvptr_delete_node->next->prev = pvptr_delete_node->prev;
    pvptr_delete_node->prev->next = pvptr_delete_node->next;
    free(pvptr_delete_node);
}
vptrnode_t* vptr_search_node(vptrlist_t* pvptr_list, vnode_t* pv)
{
    vptrnode_t* pvptr_run = NULL;

    for(pvptr_run = pvptr_list->next;pvptr_run != pvptr_list; pvptr_run = pvptr_run->next)
        if(pvptr_run->pv == pv)
            return (pvptr_run);
    return (NULL);
}
vptrnode_t* vptr_get_node(vnode_t* pv_node)
{
    vptrnode_t* pvptr_node = NULL;

    pvptr_node = (vptrnode_t*)xcalloc(1, sizeof(vptrnode_t));
    pvptr_node->pv = pv_node;
    
    return (pvptr_node);
}

/* Auxillary routines */
void* xcalloc(size_t nr_element, size_t size_per_element)
{
    void* p = NULL;

    p = calloc(nr_element, size_per_element);
    if(NULL == p)
    {
        fprintf(stderr, "calloc():fatal out of memory\n");
        exit(EXIT_FAILURE);
    }
    return (p);
}


