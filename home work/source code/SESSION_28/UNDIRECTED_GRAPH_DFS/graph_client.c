#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

typedef struct edge edge_t;
typedef int status_t;

struct edge
{
    vertex_t v_start;
    vertex_t v_end;
};

void test_graph_managent(void);
void test_dfs(void);

int main(void)
{
    test_graph_managent();
    test_dfs();
    exit(EXIT_SUCCESS);
}

void test_graph_managent(void)
{
    graph_t* g = NULL;
    vertex_t V[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t i;
    status_t status;

    edge_t E[] = {
        {1,2}, {2,3}, {3,4}, {4,5}, {5, 6}, {6,7},
        {7, 8}, {8, 9}, {9, 10}, {4, 1}, {6,1}, {10, 1},
        {5,3}, {3, 7}, {3, 9}, {2, 9}, {9, 6}, {10, 4},
        {10, 8}, {10, 2}
    };

    g = create_graph();
    for(i = 0; i<sizeof(V)/sizeof(V[0]); ++i)
    {
        status = add_vertex(g, V[i]);
        assert(status == SUCCESS);
    }

    for(i = 0; i<sizeof(E)/sizeof(E[0]); ++i)
    {
        status = add_edge(g, E[i].v_start, E[i].v_end);
        assert(status == SUCCESS);
    }
    show_graph(g, "Intial State");

    status = add_vertex(g, 11);
    assert(status == SUCCESS);

    status = add_edge(g,3,11);
    assert(status == SUCCESS);

    status = add_edge(g, 5, 11);
    assert(status == SUCCESS);

    status = add_edge(g, 7, 11);
    assert(status == SUCCESS);

    show_graph(g, "After adding vertex 11, and edege (3, 11), (5, 11), (7, 11):");

    status = remove_edge(g,1, 6);
    assert(status == SUCCESS);

    status = remove_edge(g, 5, 3);
    assert(status == SUCCESS);

    status = remove_edge(g, 8, 7);
    assert(status == SUCCESS);

    show_graph(g, "After removing edges (1, 6), (5, 3), (8,7):");

    status = remove_vertex(g, 9);
    assert(status == SUCCESS);

    show_graph(g, "After removing the vertex 9");

    status = destroy_graph(&g);
    assert(status == SUCCESS && g == NULL); 
}

void test_dfs(void)
{
    graph_t* g = NULL;
    vertex_t V[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t i;
    status_t status;

    edge_t E[] = {
        {1,2}, {2,3}, {3,4}, {4,5}, {5, 6}, {6,7},
        {7, 8}, {8, 9}, {9, 10}, {4, 1}, {6,1}, {10, 1},
        {5,3}, {3, 7}, {3, 9}, {2, 9}, {9, 6}, {10, 4},
        {10, 8}, {10, 2}
    };

    g = create_graph();
    for(i = 0; i<sizeof(V)/sizeof(V[0]); ++i)
    {
        status = add_vertex(g, V[i]);
        assert(status == SUCCESS);
    }

    for(i = 0; i<sizeof(E)/sizeof(E[0]); ++i)
    {
        status = add_edge(g, E[i].v_start, E[i].v_end);
        assert(status == SUCCESS);
    }
    show_graph(g, "Intitial State:");

    for(i = 0; i<sizeof(V)/sizeof(V[0]); ++i)
    {
        printf("DFS(g) startting from vertext %lld\n", V[i]);
        status = dfs(g, V[i]);
        assert(SUCCESS);
    }

    status = destroy_graph(&g);
    assert(status == SUCCESS && g == NULL);

    puts("test_dfs() success");
}

