#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define G_INVALID_VERTEX 2
#define TRUE    1
#define FALSE 0

enum color
{
    WHITE = 0,
    GREY,
    BLACK
};

struct hnode
{
    int v;
    double w;

    struct hnode* next, *prev;
};

struct vnode
{
    int v;
    struct hnode* ph_list;
    enum color c;
    struct vnode* pred_v;
    double d;

    struct vnode* next, *prev;
};

struct vptr_node
{
    struct vnode* pv;
    struct vptr_node* next, * prev;
};

struct graph
{
    struct vnode* pv_list;
    int number_of_e;
    int number_of_v;
};

struct vptr_node* vptr_create_prio_queue(void);
int vptr_enqueue(struct vptr_node* p_prio_queue, struct vnode* pv);
int vptr_dequeue(struct vptr_node* p_prio_queue, struct vnode** pp_v);
int vptr_destroy_prio_queue(struct vptr_node** pp_ptr_prio_queue);
int vptr_is_prio_queue_empty(struct vptr_node* p_prio_queue);

struct vptr_node* vptr_create_stack(void);
int vptr_push(struct vptr_node* p_stack, struct vnode* pv);
int vptr_pop(struct vptr_node* p_stack, struct vnode* pv);
int vptr_is_stack_empty(struct vptr_node* p_stack);
int vptr_destroy_stack(struct vptr_node** pp_stack);

void printf_shortest_path(struct graph* g, struct vnode* pv)
{
    struct vptr_node* p_stack = NULL;
    struct vnode* pv_run  = NULL;
    struct vnode* pv_pop = NULL;

    p_stack = vptr_create_stack();
    pv_run = pv;

    while(pv_run != NULL)
    {
        vptr_push(p_stack, pv_run);
        pv_run = pv_run->pred_v;   
    }

    printf("Shortest path to %d\n", pv->v);
    printf("[START]->");
    while(!vptr_is_stack_empty(p_stack))
    {
        vptr_pop(p_stack, &pv_pop);
        printf("[%d]->", pv_pop->v);
    }
    puts("[END]");
    vptr_destroy_stack(&p_stack);
}

void print_all_shortest_paths(struct graph* g)
{
    struct vnode* pv_run = NULL;

    for(pv_run = g->pv_list->next; pv_run!= g->pv_list; pv_run = pv_run->next)
        printf_shortest_path(g, pv_run);
    
}

void initialise_single_source(struct graph* g, struct vnode* pv_s)
{
    struct vnode* pv_run = NULL;

    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        pv_run->pred_v = NULL;
        pv_run->d = INFINITY;
    }

    pv_s->d = 0.0;
}

void relax(struct vnode* pv_u, struct vnode* pv_v)
{
    double w;
    struct hnode* ph_run = NULL;

    for(ph_run = pv_u->ph_list->next; ph_run != pv_u->ph_list; ph_run = ph_run->next)
    {
        if(ph_run ->v == pv_v->v);
            break;
   }
   
   w = ph_run->w;
   if(pv_v->d >pv_u->d + w)
   {
        pv_v->d = pv_u->d + w;
        pv_v->pred_v =  pv_u;
   }
}

/*
    DIJIKSTRA(g, w, s)
        INITTIALIZE-SINGLE-SOURCE(G, s)
        PRIO_Q = G.V
        while PRIO_Q is not EMPTY
            u = DEQUEUE_MIN(PRIO_Q);
            for all v in adj[u]
                RELAX(u, v, w)
*/

void dijikstra(struct graph* g, int s)
{
    struct vptr_node* p_prio_queue = NULL;
    struct vnode* pv_s = NULL;
    struct vnode* pv_u = NULL;
    struct vnode* pv_v = NULL;
    struct vnode* pv_run = NULL;
    struct hnode* ph_run = NULL;

    pv_s = v_search_node(g->pv_list, s);
    if(pv_s == NULL)
        return (G_INVALID_VERTEX);
    
    initialise_single_source(g, pv_s);
    p_prio_queue = vptr_create_prio_queue();
    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
        vptr_enqueue(p_prio_queue,  pv_run);

    while(vptr_is_prio_queue_empty(p_prio_queue) == FALSE)
    {
        vptr_dequeue(p_prio_queue, &pv_u);
        for(ph_run = pv_u->ph_list->next; ph_run != pv_u->ph_list; ph_run = ph_run->next)
        {
            pv_v = v_search_node(g->pv_list, ph_run->v);
            relax(pv_u, pv_v);
        }
    }
    vptr_destroy_prio_queue(&p_prio_queue);
}

/*

status_t add_edge(graph_t* g, vertex_t u, vertex_v, double w );

u->     v(cost w)
v->     u(cost w)


hnode_t* h_get_node(vertetx_ v, double w)
{
    hnode_t* ph_ne_node = NULL;

    ph_new_node =(hnde_t*)xcalloc(1, sizeof(hnode_t));
    ph_new_node->v = v;
    ph_new_node->w = w;

    return (ph_new_node); 
}



*/