#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum color
{
    WHITE = 0,
    GRAY,
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
    enum color;
    struct vnode* pred_v;
    double d;

    struct vnode* prev, *next;
};

struct vptr_node
{
    struct vnode* pv;
    struct vptr_node* prev, *next;
};

struct graph
{
    struct vnode* pv_list;
    int number_of_v;
    int number_of_e;
};


struct vptr_node* vptr_create_prio_queue(void);
int vptr_enqueue(struct vptr_node* p_prio_queue, struct vnode* pv);
int vptr_dequeue(struct vptr_node* p_prio_queue, struct vnode** pp_v);
int destory_prio_queue(struct vptr_node** pp_vptr_prio_queue);
int vptr_is_prio_queue_empty(struct vptr_node* p_prio_queue);

void initialise_single_source(struct graph* g, struct vnode* pv_s)
{
    struct vnode* pv_run;

    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        pv_run->d = INFINITY;
        pv_run->pred_v = NULL;
    }

    pv_s->d = 0.0;
}

void relax(struct vnode* pv_u, struct vnode* pv_v)
{
    double w;
    struct hnode* ph_run = NULL;
    
    for(ph_run = pv_v->ph_list->next; ph_run != pv_v->ph_list; ph_run = ph_run->next)
    {
        if(ph_run->v == pv_v->v)
            break;
    }

    w = ph_run->w;
    if(pv_v->d >pv_u->d + w)
    {
        pv_v->d = pv_u->d + w;
        pv_v->pred_v = pv_u;
    } 
}


/*

    DIJIKSTRA(G, w, s)
        INITIALISE-SINGLE-SOURCE(G, s)
        PRIO_Q  = G.V
        while PRIO_Q is not EMPTY
            u = DEQUEUE_MIN(PRIO_Q)
            for all v in Adj[u]
                RELAX(u, v, w)
*/

void dijisktr(struct graph* g, int s)
{
    struct vptr_node* p_prio_queue = NULL;
    struct vnode* pv_s = NULL;
    struct vnode* pv_u = NULL;
    struct vnode* pv_v = NULL;
    struct vnode* pv_run = NULL;
    struct hnode* ph_run = NULL;
    

    pv_s = v_search_node(g->pv_list, s);
    if(pv_s == NULL)
        retunr (G_INVALID_VERTEX);
    
    initialise_single_source(g, pv_s);
    p_prio_queue = vptr_create_prio_queue();
    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
        vptr_enqueue(p_prio_queue, pv_run);

    while(vptr_enqueue(p_prio_queue) == FALSE)
    {
        vptr_dequeue(p_prio_queue, &pv_u);
        for(ph_run = pv_u->ph_list->next; ph_run != pv_u->ph_list; ph_run = ph_run->next)
        {
            pv_v = v_search_node(g->pv_list, ph_run->v);
            relax(pv_u, pv_v);
        }
    }
}