


#include <math.h>
#include <assert.h>

#define SUCCESS 1
#define G_INVALID_VERTEX 2
#define G_INVALID_EDDGE 3
#define G_VERTEX_EXISTS 4
#define G_EDGE_EXISTS 5

typedef int vertex_t;
typedef enum color color_t;
typedef struct hnode hnode_t;
typedef hnode_t hlist_t;
typedef struct vnode vnode_t;
typedef vnode_t vlist_t;
typedef struct vnode_ptr vnode_ptr_t;
typedef vnode_ptr_t vnode_ptr_list_t;
typedef vnode_ptr_t prio_queue_t;
typedef struct graph graph_t;
typedef int status_t;
enum color
{
    WHITE = 0,
    GRAY,
    BLACK
};
struct hnode
{
    vertex_t v;
    double w;
    struct hnode *prev;
    struct hnode *next;
};
struct vnode
{
    vertex_t v;
    hlist_t *ph_adj_list;
    color_t color;
    double r;
    struct vnode *v_pred;
    struct vnode *prev;
    struct vnode *next;
};
struct graph
{
    vlist_t *pv_list;
    unsigned int nr_v;
    unsigned int nr_e;
};
graph_t *create_graph(void);
status_t add_vertex(graph_t *g, vertex_t v);
status_t add_edge(graph_t *g, vertex_t u, vertex_t v);
status_t remove_vertex(graph_t *g, vertex_t v);
status_t remove_edge(graph_t *g, vertex_t u, vertex_t v);
void show_graph(graph_t *g, const char *msg);
status_t destroy_graph(graph_t **pp_g);
void dfs(graph_t *g, vertex_t s);
void bfs(graph_t *g);
void prims(graph_t *g, vertex_t r);
void print_mst(graph_t *g);
prio_queue_t *vptr_create_prio_queue(void);
status_t vptr_extract_max(prio_queue_t *p_prio_queue, vnode_t **ppv);
status_t vptr_extract_min(prio_queue_t *p_prio_queue, vnode_t **ppv);
status_t vptr_destroy_prio_queue(prio_queue_t *p_prio_queue);
vnode_ptr_list_t *vptr_create_list(void);
status_t insert_end(vnode_ptr_list_t *pvptr_list, vnode_t *pv);
void vptr_generic_insert(vnode_ptr_t *beg, vnode_ptr_t *mid, vnode_ptr_t *end);
void vptr_generic_delete(vnode_ptr_t *pvptr_delete_node);
vnode_ptr_node_t *vptr_search_node(vnode_ptr_t *pvptr_list, vnode_t *pv);
vlist_t *v_create_list(void);
status_t v_insert_end(vlist_t *pv_list, vertex_t v);
void v_generic_insert(vnode_t *beg, vnode_t *mid, vnode_t *end);
void v_generic_delete(vnode_t *pv_delete_node);
vnode_t *v_search_node(vlist_t *pv_list, vertex_t v);
hlist_t *h_create_list(void);
status_t h_insert_end(hlist_t *ph_list, vertex_t v, double w);
void h_generic_insert(hnode_t *beg, hnode_t *mid, hnode_t *end);
void h_generic_delete(hnode_t *ph_delete_node);
hnode_t *h_search_node(hlist_t *ph_list, vertex_t v);
hnode_t *h_get_node(vertex_t v, double w);
void *xcalloc(size_t nr_elements, size_t size_per_element);


void prims(graph_t *g, vertex_t r)
{
    prio_queue_t* PQ = NULL;
    vnode_t* pv_run = NULL;
    vnode_t* pv_r = NULL;
    vnode_t* ph_u = NULL;
    vnode_t* pv_v = NULL;

    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        pv_run->v_pred = NULL;
        pv_run->r = INFINITY;
    }
    pv_r = v_search_node(g->pv_list, r);
    assert(pv_r != NULL);

    PQ = vptr_create_prio_queue();

    

}