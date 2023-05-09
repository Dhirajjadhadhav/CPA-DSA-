#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"


#define NR_INIT_VERTICES    8
#define NR_INIT_EDGES       12

struct edge{
    vertex_t v_start;
    vertex_t v_end;
    double w;
};

int main()
{
    graph_t* g = NULL;
    vertex_t v;
    vertex_t s;
    int i;

    struct edge E[] = {
                        {1, 6, 2.0}, {1, 2, 1.0}, {2, 7, 5.0}, {2, 3, 2.0},
                        {6, 7, 3.0}, {5, 7, 1.0}, {7, 3, 1.0}, {7, 8, 3.0},
                        {3, 8, 3.0}, {5, 8, 4.0}, {5, 4, 2.0}, {3, 4, 1.0} 
                      };
    g = create_graph();
    for(v = 0; v<=NR_INIT_VERTICES; ++v)
        add_vertex(g, v);
    
    for(i = 0; i<sizeof(E)/sizeof(E[i]); ++i)
        add_edge(g, E[i].v_start, E[i].v_end, E[i].w);

    print_graph(g, "INTIAL STATE:");

    s =1;

    printf("Dijikstra : Source Vertex = %d\n", s);
    print_all_shortest_path(g);
    destroy_graph(&g);

    puts("///////////////////////////////////////////////////////////////////////");

    g = create_graph();
    for(v = 1; v<=7; ++v)
        add_vertex(g, v);

    struct edge E1[] = {
                        {1, 2, 2.0}, {2, 3, 3.0}, {3, 4, 2.0}, {4, 5, 2.0},
                        {5, 6, 4.0}, {6, 7, 1.0}, {7, 1, 4.0}, {3, 7, 1.0},
                        {5, 7, 2.0}, {4, 6, 1.0}
                      };
    for(i  = 0; i<sizeof(E1)/sizeof(E1[0]); ++i)
        add_edge(g, E1[i].v_start, E1[i].v_end, E1[i].w);

    print_graph(g, "INITIAL STATE:");
    printf("DFS:");

    s = 1;
    printf("Dijikstra: Source Vertex = %d\n", s);
    assert(dijikstra(g, s) == SUCCESS);
    print_all_shortest_path(g);

    puts("////////////////////////////////////////////////////////////////////////");
    s = 5;
    printf("Dijikstra: Source vertex  = %d\n", s);
    assert(dijikstra(g, s) == SUCCESS);
    print_all_shortest_path(g);

    destroy_graph(&g);

    return (EXIT_SUCCESS); 
}