#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "graph.h"


/* Part-1 Graph management */

/* Graph interface routines */
graph_t* create_graph(void)
{
    graph_t* g = NULL;

    g = (graph_t*)xcalloc(1, sizeof(graph_t));
    g->pv_list = create_list_v();

    g->nr_edge = 0;
    g->nr_vertices = 0;

    return (g);
}

ret_t add_vertex(graph_t* g, vertex_t v)
{
    vnode_t* pv_node = NULL;
    
    pv_node = search_node_v(g->pv_list, v);
    if(NULL != pv_node)
        return (G_VERTEX_EXISTS);

    insert_end_v(g->pv_list, v);
    g->nr_vertices++;
    return (SUCCESS);
}

ret_t remove_vertex(graph_t* g, vertex_t v)
{
    vnode_t* pv_node = NULL;
    vnode_t* pv_adj_node = NULL;
    hnode_t* ph_v_in_adj_node = NULL;
    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next = NULL;
    ret_t ret;

    pv_node = search_node_v(g->pv_list, v);
    if(NULL == pv_node)
        return (G_INVALID_VERTEX);
    
    for(
        ph_run = pv_node->ph_list->next;
        ph_run != pv_node->ph_list;
        ph_run = ph_run_next
    )
    {
        ph_run_next = ph_run->next;
        
        pv_adj_node =  search_node_v(g->pv_list, ph_run->v);
        if(NULL == pv_adj_node)
            return (G_INVALID_EDGE);

        ret  = remove_vertex_h(pv_adj_node->ph_list, v);
        assert(ret == SUCCESS);
        g->nr_edge--;
        free(ph_run);
    }

    free(pv_node->ph_list);
    generic_delete_v(pv_node);
    g->nr_vertices--;

    return (SUCCESS);
}

ret_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end, double w)
{
    vnode_t* pv_start = NULL;
    vnode_t* pv_end = NULL;
    hnode_t* ph_node = NULL;

    pv_start = search_node_v(g->pv_list, v_start);
    pv_end = search_node_v(g->pv_list, v_end);
    if(NULL == pv_start || NULL == pv_end)
        return (G_INVALID_VERTEX);
   
    ph_node = search_node_h(pv_start->ph_list, v_end);
    if(NULL != ph_node)
        return (G_EDGE_EXISTS);
 
    ph_node = search_node_h(pv_end->ph_list, v_start);
    if(NULL != ph_node)
        return (G_EDGE_EXISTS);

    
    insert_end_h(pv_start->ph_list, v_end, w);
    insert_end_h(pv_end->ph_list, v_start, w);
    g->nr_edge++;

    return (SUCCESS);
}

ret_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end)
{
    vnode_t* pv_start = NULL;
    vnode_t* pv_end = NULL;
    ret_t ret;

    pv_start = search_node_v(g->pv_list, v_start);
    pv_end = search_node_v(g->pv_list, v_end);
    if(NULL == pv_start || NULL == pv_end)
        return (G_INVALID_VERTEX);
    
    ret = remove_vertex_h(pv_start->ph_list, v_end);
    if(ret == HLIST_DATA_NOT_FOUND)
        return (G_INVALID_EDGE);
    
    ret  = remove_vertex_h(pv_end->ph_list, v_start);
    if(ret == HLIST_DATA_NOT_FOUND)
        return (G_INVALID_EDGE);
    
    g->nr_edge--;
    return (SUCCESS);
}

void print_graph(graph_t* g, const char *msg)
{
    vnode_t* pv_run = NULL;
    hnode_t* ph_run = NULL;

    if(msg)
        puts(msg);
    printf("G(V,E) : |V| = %d, |E| = %d\n", g->nr_vertices, g->nr_edge);

    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        printf("[%d]\t----->\t", pv_run->v);
        for(ph_run= pv_run->ph_list->next; ph_run != pv_run->ph_list; ph_run = ph_run->next)
        {
            printf("[%d]<->", ph_run->v);
        }
        puts("[END]");
    }
}

int get_nr_vertex(graph_t* g)
{
    return (g->nr_vertices);
}
int get_nr_edge(graph_t* g)
{
    return (g->nr_edge);
}
ret_t destroy_graph(graph_t** pp_g)
{
    graph_t* g = NULL;
    vnode_t* pv_run = NULL;
    vnode_t* pv_run_next = NULL;
    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next = NULL;

    g = *pp_g;

    for(pv_run = g->pv_list->next; pv_run!=g->pv_list; pv_run = pv_run_next)
    {
        pv_run_next = pv_run->next;
        destroy_list_h(&pv_run->ph_list);
        free(pv_run);
    }

    free(g->pv_list);
    free(g);
    *pp_g = NULL;
    return (SUCCESS);
}

ret_t dfs(graph_t* g)
{
    vnode_t* pv_node = NULL;
    reset(g);
    printf("[START]->");
    for(pv_node = g->pv_list->next; pv_node != g->pv_list; pv_node = pv_node->next)
    {
        if(pv_node->c == WHITE)
            dfs_visit(g, pv_node);
    }
    puts("[END]");

    return (SUCCESS);
}
ret_t bfs(graph_t* g, vertex_t v)
{
    v_queue_t* Q = NULL;
    vnode_t* pv_source = NULL;
    vnode_t* pu = NULL;
    vnode_t* pv_of_ph = NULL;
    hnode_t* ph_run = NULL;

    reset(g);

    pv_source = search_node_v(g->pv_list, v);
    if(NULL == pv_source)
        return (G_INVALID_VERTEX);
    
    pv_source->c = GREY;
    Q = v_create_queue();
    v_enqueue(Q, pv_source);
    printf("[START]->");
    while(v_is_queue_empty(Q) == FALSE)
    {
        v_dequeue(Q, &pu);
       
        printf("[%d]->", pu->v);
        for(ph_run = pu->ph_list->next; ph_run != pu->ph_list; ph_run = ph_run->next)
        {
            pv_of_ph = search_node_v(g->pv_list, ph_run->v);
            if(pv_of_ph->c == WHITE)
            {
                pu->c = GREY;
                v_enqueue(Q, pv_of_ph);
            }
        }
        pu->c = BLACK;
    }
    puts("[END]");
    assert(v_destroy_queue(&Q) && Q == NULL);

    return (SUCCESS);
}

ret_t dijikstra(graph_t* g, vertex_t s)
{
    v_prio_queue_t* PQ = NULL;
    vnode_t* pv_s = NULL;
    vnode_t* pv_u = NULL;
    vnode_t* pv_of_ph = NULL;
    vnode_t* pv_run  = NULL;
    hnode_t* ph_run = NULL;

    pv_s = search_node_v(g->pv_list, s);
    if(NULL == pv_s)
        return (G_INVALID_VERTEX);
    
    initialize_single_source(g, pv_s);

    PQ = v_create_prio_queue();
    
    for(pv_run = g->pv_list->next; pv_run!=g->pv_list; pv_run = pv_run->next)
        v_prio_enqueue(PQ, pv_run);
    
    while(v_is_prio_queue_empty(PQ) == FALSE)
    {
        pv_u = NULL;
        v_prio_dequeue_min(PQ, &pv_u);
        for(ph_run   = pv_u->ph_list->next; ph_run !=pv_u->ph_list; ph_run = ph_run->next)
        {
            pv_of_ph = search_node_v(g->pv_list, ph_run->v);
            relax(g, pv_u, pv_of_ph);
        }
    }
    v_destroy_prio_queue(&PQ);
    return (SUCCESS);
}

/* Graph - Auxillary routines for traversal algorithms */
void reset(graph_t* g)
{
    vnode_t* pv_run  = NULL;

    for(pv_run = g->pv_list->next; pv_run!= g->pv_list; pv_run = pv_run->next)
    {
        pv_run->c = WHITE;
        pv_run->u_pred = NULL;
    }
}
void dfs_visit(graph_t* g, vnode_t* pv_node)
{
    hnode_t* ph_run = NULL;
    vnode_t* pv_of_hnode = NULL;

    printf("[%d]<->", pv_node->v);
    pv_node->c = GREY;
    for(ph_run = pv_node->ph_list->next; ph_run!=pv_node->ph_list; ph_run  = ph_run->next)
    {
        pv_of_hnode = search_node_v(g->pv_list, ph_run->v);
        if(pv_of_hnode->c == WHITE)
            dfs_visit(g, pv_of_hnode);
    }
    pv_node->c = BLACK;
}

/* Graph - Auxillary routines for shortest path algorithms */
void initialize_single_source(graph_t* g, vnode_t* pv_s)
{
   vnode_t* pv_run = NULL;

   for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        pv_run->d = INFINITY;
        pv_run->u_pred = NULL;
    }

    pv_s->d = 0.0;
}

void relax(graph_t* g, vnode_t* pv_u, vnode_t* pv_v)
{
    hnode_t* ph_node = NULL;    
    double w;

    ph_node = search_node_h(pv_u->ph_list, pv_v->v);
    w = ph_node->w;

    if(pv_v->d > pv_u->d+w)
    {
        pv_v->d = pv_u->d + w;
        pv_v->u_pred = pv_u;
    }
    
}

void print_shortest_path(graph_t* g, vnode_t* pv_node)
{

    v_stack_t* pvq_stack = NULL;    
    vnode_t* pv_poped_node = NULL;
    vertex_t curr_vertex_number;
    double d;

    curr_vertex_number = pv_node->v;
    d = pv_node->d;

    pvq_stack  = v_create_stack();

    while (pv_node != NULL)
    {
       
        v_push_stack(pvq_stack, pv_node);
        pv_node = pv_node->u_pred;        
    }

    printf("Shortest path to [%d]\n", curr_vertex_number);
    printf("[START]<->");
    while (v_is_stack_empty(pvq_stack) == FALSE)
    {
        pv_poped_node = NULL;
        v_pop_stack(pvq_stack, &pv_poped_node);
        printf("[%d]<->", pv_poped_node->v);
    }
    printf("[COST]:%lf\n", d);
    puts("[END]");

    v_destroy_stack(&pvq_stack);
}
void print_all_shortest_path(graph_t* g)
{

    vnode_t* pv_node = NULL;
    for(pv_node = g->pv_list->next; pv_node != g->pv_list; pv_node = pv_node->next)
        print_shortest_path(g, pv_node);
    
}

/* Graph - Auxillary routines - Part 1 vertical List management */
vlist_t* create_list_v(void)
{
    vlist_t* pv_list = NULL;

    pv_list = (vlist_t*)xcalloc(1, sizeof(vlist_t));
    
    pv_list->v = -1;
    pv_list->next = pv_list;
    pv_list->prev = pv_list;
    return (pv_list);
}

ret_t insert_end_v(vlist_t* pv_list, vertex_t v)
{
    generic_insert_v(pv_list->prev, get_node_v(v), pv_list);
    return (SUCCESS);
}
ret_t remove_vertex_v(vlist_t* pv_list, vertex_t v)
{
    vnode_t* pv_delete_node = NULL;

    pv_delete_node = search_node_v(pv_list, v);
    if(NULL == pv_delete_node)
        return (VLIST_DATA_NOT_FOUND);

    generic_delete_v(pv_delete_node);
    return(SUCCESS);
}

ret_t destroy_vertex_v(vlist_t** ppv_list)
{
    vlist_t* pv_list = NULL;
    vnode_t* pv_run = NULL;
    vnode_t* pv_run_next = NULL;


    pv_list = *ppv_list;
    for(pv_run = pv_list->next; pv_run!=pv_list; pv_run = pv_run_next)
    {
        pv_run_next = pv_run->next;
        free(pv_run);
    }
    free(pv_list);
    *ppv_list = NULL;
    return (SUCCESS);
}

/* Vertical List - Auxillary Routines */
void generic_insert_v(vnode_t* p_beg, vnode_t* p_mid, vnode_t* p_end)
{
    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    p_end->prev = p_mid;
}

void generic_delete_v(vnode_t* p_delete_node)
{
    p_delete_node->next->prev = p_delete_node->prev;
    p_delete_node->prev->next = p_delete_node->next;
    free(p_delete_node);
}

vnode_t* search_node_v(vlist_t* pv_list, vertex_t v)
{
    vnode_t* pv_run = NULL;

    for(pv_run = pv_list->next; pv_run != pv_list; pv_run = pv_run->next)
        if(pv_run->v == v)
            return (pv_run);
    return (NULL);
}

vnode_t* get_node_v(vertex_t v)
{
    vnode_t* pv_node = NULL;

    pv_node = (vnode_t*)xcalloc(1, sizeof(vnode_t));
    pv_node->v = v;
    pv_node->ph_list = create_list_h();
    pv_node->c = WHITE;
    pv_node->next = NULL;
    pv_node->prev = NULL;

    return (pv_node);
}

/* Graph - Auxillary routines - Part 2 - Horizontal List Management */
hlist_t* create_list_h(void)
{
    hlist_t* ph_list = NULL;

    ph_list = xcalloc(1, sizeof(hlist_t));
    ph_list->v = -1;
    ph_list->w = 0.0;
    ph_list->next = ph_list;
    ph_list->prev = ph_list;

    return (ph_list);
}

ret_t insert_end_h(hlist_t* ph_list, vertex_t v, double w)
{
    generic_insert_h(ph_list->prev, get_node_h(v, w), ph_list);
    return (SUCCESS);
}

ret_t remove_vertex_h(hlist_t* ph_list, vertex_t v)
{
    hnode_t* ph_delete_node = NULL;

    ph_delete_node = search_node_h(ph_list, v);
    if(NULL == ph_delete_node)
        return (HLIST_DATA_NOT_FOUND);
    
    generic_delete_h(ph_delete_node);
    return (SUCCESS);
}

ret_t destroy_list_h(hlist_t** pph_list)
{
    hlist_t* ph_list = NULL;
    hnode_t* ph_run = NULL;
    hnode_t* ph_run_next = NULL;

    ph_list = *pph_list;

    for(ph_run = ph_list->next; ph_run !=ph_list; ph_run = ph_run_next)
    {
        ph_run_next = ph_run->next;
        free(ph_run);
    }

    free(ph_list);
    *pph_list = NULL;
    return (SUCCESS);
}

/* Horizontal List - Auxillary Routines */
void generic_insert_h(hnode_t* p_beg, hnode_t* p_mid, hnode_t* p_end)
{
    p_mid->next =  p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    p_end->prev = p_mid;
}

void generic_delete_h(hnode_t* p_delete_node)
{
    p_delete_node->next->prev = p_delete_node->prev;
    p_delete_node->prev->next = p_delete_node->next;
    free(p_delete_node);
}

hnode_t* search_node_h(hlist_t* ph_list, vertex_t v)
{
    hnode_t* ph_run = NULL;
    
    for(ph_run = ph_list->next; ph_run!=ph_list; ph_run = ph_run->next)
        if(ph_run->v == v)
            return (ph_run);
    return (NULL);
}

hnode_t* get_node_h(vertex_t v, double init_w)
{
    hnode_t* ph_node = NULL;

    ph_node = (hnode_t*)xcalloc(1, sizeof(hnode_t));
    ph_node->v = v;
    ph_node->w = init_w;

    return (ph_node);
}

/* Graph -  Auxillary Routines - BFS Queue */
v_queue_t* v_create_queue(void)
{
    return (v_create_list());
}

ret_t v_enqueue(v_queue_t* pv_queue, vnode_t* pv_new_node)
{
    return (v_insert_end(pv_queue, pv_new_node));
}

ret_t v_dequeue(v_queue_t* pv_queue, vnode_t** ppv_node)
{
    return (v_remove_beg(pv_queue, ppv_node));
}

Bool v_is_queue_empty(v_queue_t* pv_queue)
{
    return (v_is_list_empty(pv_queue));
}

ret_t v_destroy_queue(v_queue_t** pp_v_queue)
{
    return (v_destroy_list(pp_v_queue));
}

/* Graph - Auxillary Rountines - Stack of vnode_t */
v_stack_t* v_create_stack(void)
{
   return (v_create_list());
}
ret_t v_push_stack(v_stack_t* pvq_stack, vnode_t* pv_new_node)
{
    return (v_insert_end(pvq_stack, pv_new_node));
}
ret_t v_pop_stack(v_stack_t* pvq_stack, vnode_t** ppv_node)
{
    return (v_remove_end(pvq_stack, ppv_node));
}
Bool v_is_stack_empty(v_stack_t* pvq_stack)
{
    return (v_is_list_empty(pvq_stack));
}
ret_t v_destroy_stack(v_stack_t** ppvq_stack)
{
    return (v_destroy_list(ppvq_stack));
}

/*Graph - Auxillary Routines -  priority queue (of  vnode_t* as satellite data,
    priority field is 'd' (cost of minimum path from source vertex to the 
    said vertetx))*/

v_prio_queue_t* v_create_prio_queue(void)
{
    return (v_create_list());
}

ret_t v_prio_enqueue(v_prio_queue_t* p_prio_queue, vnode_t* pv_node)
{
    return (v_insert_end(p_prio_queue, pv_node));
}

ret_t v_prio_dequeue_min(v_prio_queue_t* p_prio_queue, vnode_t** pp_vnode)
{
    v_node_t* pv_run = NULL;
    v_node_t* pv_min= NULL;
    
    pv_min = p_prio_queue->next;
    for(pv_run = p_prio_queue->next; pv_run !=p_prio_queue; pv_run = pv_run->next)
    {
        if(pv_min->pv_node->v > pv_run->pv_node->v)
        {   
            pv_min = pv_run;
        }
    }

    *pp_vnode  = pv_min->pv_node;
    generic_delete_vq(pv_min);
    return (SUCCESS);
}
Bool v_is_prio_queue_empty(v_prio_queue_t* p_prio_queue)
{
    return (v_is_list_empty(p_prio_queue));
}
ret_t v_destroy_prio_queue(v_prio_queue_t** pp_prio_queue)
{
    return (v_destroy_list(pp_prio_queue));
}


/* Graph - BSF QUEUE - List */
v_list_t* v_create_list(void)
{
    v_list_t* pvptr_list = NULL;

    pvptr_list = (v_list_t*)xcalloc(1, sizeof(v_list_t));
    pvptr_list->pv_node = NULL;
    pvptr_list->next = pvptr_list;
    pvptr_list->prev = pvptr_list;
    
    return (pvptr_list);
}

ret_t v_insert_beg(v_list_t* pvq_list, vnode_t* pv_new_node)
{
   generic_insert_vq(pvq_list->prev, get_node_vq(pv_new_node), pvq_list);
   return (SUCCESS);
}
ret_t v_insert_end(v_list_t* pvq_list, vnode_t* pv_new_node)
{
    generic_insert_vq(pvq_list->prev,get_node_vq(pv_new_node), pvq_list);
    return (SUCCESS);
}
ret_t v_remove_beg(v_list_t* pvq_list, vnode_t** ppv_beg_node)
{
    
    if(v_is_list_empty(pvq_list) == TRUE)
        return (V_LIST_EMPTY);
    *ppv_beg_node = pvq_list->next->pv_node;

    generic_delete_vq(pvq_list->next);
    return (SUCCESS);
}

ret_t v_remove_end(v_list_t* pvq_list, vnode_t** ppv_end_node)
{
    if(v_is_list_empty(pvq_list) == TRUE)
        return (V_LIST_EMPTY);

    *ppv_end_node = pvq_list->prev->pv_node;
    generic_delete_vq(pvq_list->prev);
    return (SUCCESS);
}

Bool v_is_list_empty(v_list_t* pvq_list)
{
    return (pvq_list->next == pvq_list && pvq_list->prev == pvq_list);
}
ret_t v_destroy_list(v_list_t** ppvq_list)
{
    v_list_t* pvq_list = NULL;
    v_node_t* pvptr_run = NULL;
    v_node_t* pvptr_run_next = NULL;

    pvq_list = *ppvq_list;

    for(pvptr_run = pvq_list->next; pvptr_run != pvq_list; pvptr_run = pvptr_run_next)
    {
        pvptr_run_next = pvptr_run->next;
        free(pvptr_run);
    }
    free(pvq_list);
    *ppvq_list = NULL;
    return (SUCCESS);
}

/* Graph - BSF QUEUE -List -Auxillary */
void generic_insert_vq(v_node_t* pvq_beg, v_node_t* pvq_mid, v_node_t* pvq_end)
{
    pvq_mid->next = pvq_end;
    pvq_mid->prev = pvq_beg;
    pvq_beg->next = pvq_mid;
    pvq_end->prev = pvq_mid;
}

void generic_delete_vq(v_node_t* pvq_delete_node)
{
    pvq_delete_node->next->prev = pvq_delete_node->prev;
    pvq_delete_node->prev->next = pvq_delete_node->next;
    free(pvq_delete_node);
}
v_node_t* get_node_vq(vnode_t* pv_new_node)
{
    v_node_t* pvptr_node = NULL;

    pvptr_node = (v_node_t*)xcalloc(1, sizeof(v_node_t));
    pvptr_node->pv_node = pv_new_node;
    return (pvptr_node);
}

/* Graph - Auxillary Routines -Part- Misc. */
void* xcalloc(size_t nr_element, size_t size_per_element)
{
    void* p = NULL;

    p = calloc(nr_element, size_per_element);
    if(p == NULL)
    {
        fprintf(stderr, "calloc():falat:out of memory\n");
        exit(EXIT_FAILURE);
    }

    return (p);
}


