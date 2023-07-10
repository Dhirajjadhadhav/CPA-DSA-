#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <assert.h> 

typedef struct edge
{
    vertex_t u;
    vertex_t v;
    double w;
}edge_t;




int main(void)
{


    int i;
    status_t status;

    edge_t edge[] = {
                        {2, 1 ,-1}, {2, 4, 4}, {1, 4, 3}, {1, 5, 1}, 
                        {1, 3, 2}, {3, 5, -3}, {5, 1, 2}, {5, 4, 5}
                    };    
    graph_t* g  = NULL;


    g = create_graph();

    for(vertex_t v = 1; v<5; ++v)
    {
       status =  add_vertex(g, v);
       assert(status == SUCCESS);
    }

    for(ssize_t i = 0; i<sizeof(edge)/sizeof(edge[0]); ++i)
    {
        status = add_edge(g, edge[i].u, edge[i].v, edge[i].w);
        assert(status == SUCCESS);
    }

    bellman_ford(g, 2);
    



}