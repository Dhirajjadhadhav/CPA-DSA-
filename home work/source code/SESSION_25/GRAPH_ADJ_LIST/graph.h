#ifndef _GRAPH_H
#define _GRAPH_H

#define SUCCESS             1
#define G_INVALID_VERTEX    2
#define G_INVALID_EDGE      3
#define G_VERTEX_EXISTS     4
#define G_EDGE_EXISTS       5

typedef long long vertex_t;
typedef struct hnode hnode_t;
typedef hnode_t hlist_t;

typedef struct vnode vnode_t;
typedef vnode_t vlist_t;

typedef struct graph graph_t;

typedef int status_t;

struct hnode
{
    long long v;
    struct hnode* prev;
    struct hnode* next;
};

struct vnode
{
    long long v;
    struct hnode* pv_head;

    struct vnode* prev;
    struct vnode* next;
};

struct graph
{
    struct vnode* pv_node;
    unsigned long long nr_v;
    unsigned long long nr_e;
};

graph_t* create_graph(void);
status_t add_vertex(graph_t* g, vertex_t v);
status_t remove_vertex(graph_t* g, vertex_t v);
status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end);
status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end);
void show_graph(graph_t* g, const char* msg);
status_t destroy_graph(graph** pp_g);

#endif; /*_GHAPH_H */
