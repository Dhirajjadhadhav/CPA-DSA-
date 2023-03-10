#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define SUCCESS 1

#define E_INVALID_VERTEX    2
#define E_INVALID_EDGE      3
#define E_EDGE_EXISTS       4

#define ADD_EDGE    1
#define REMOVE_EDGE 2
#define SHOW_GRAPH  3
#define EXIT_APP    4

#define GET_IJ(g, i, j)         (*((g)->pg + (i) * (g)->nr_V + (j)))
#define SET_IJ(g, i, j, val)    *((g)->pg + (i) * (g)->nr_V + (j)) = (val)


struct graph
{
    int* pg;
    int nr_V;
    int nr_E;
};

struct graph* create_graph(size_t nr_vertices);
int add_edge(struct graph* g, int v_start, int v_end);
int remove_edge(struct graph* g, int v_start, int v_end);
int show_graph(struct graph* g);
int release_graph(struct graph** pp_g);

int main(void)
{
    size_t N;
    struct graph* g = NULL;
    int choice;
    int status;

    int i,j;
    int v_start, v_end;

    printf("Enter the number of vertices :");
    scanf("%llu", &N);
    if(N<2)
    {
        puts("The graph must have at leact two vertices:");
        exit(EXIT_FAILURE);
    }

    g = create_graph(N);

    while(TRUE)
    {
        printf("1.add edge 2.remove edge 3.show graph 4.Exit\n");
        printf("Enter your choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case ADD_EDGE: 
            printf("Enter the starting vertesx:");
            scanf("%d", &v_start);
            printf("Enter the ending vertex:");
            scanf("%d", &v_end);
            status = add_edge(g,v_start, v_end);
            if(status != SUCCESS)
                printf("Adding edge:%d<->%d failed\n", v_start, v_end);
            break;
        case REMOVE_EDGE:
            printf("Enter startting vertex:");
            scanf("%d", &v_start);
            printf("Enter the ending vertex:");
            scanf("%d", &v_end);    
            status  = remove_edge(g, v_start, v_end);
            if(status != SUCCESS)
                printf("Removing edge %d<->%d failed\n", v_start, v_end);
            break;
        case SHOW_GRAPH:
            show_graph(g);
            break;
        case EXIT_APP:
            release_graph(&g);
            exit(EXIT_SUCCESS);
        default:    
            puts("Bad choice!");
            break;  
        }
    }
    exit (EXIT_SUCCESS);
}

struct graph* create_graph(size_t nr_vertices)
{
    struct graph* g = NULL;

    g = (struct graph*)malloc(sizeof(struct graph));
    if(g == NULL)
    {
        fprintf(stderr, "malloc(): fatal out of memory\n");
        exit(EXIT_FAILURE);
    }

    g->nr_V = nr_vertices;
    g->pg = (int*)malloc(nr_vertices * nr_vertices * sizeof(int));
    if(g->pg == NULL)
    {
        fprintf(stderr, "malloc():fatal out of memory");
        exit(EXIT_FAILURE);
    }
    memset(g->pg, 0, nr_vertices * nr_vertices * sizeof(int));

    g->nr_E = 0;

    return (g);
}

int add_edge(struct graph* g, int v_start, int v_end)
{
    if(v_start<0 || v_start >= g->nr_V|| v_end < 0 || v_end>=g->nr_V)
        return (E_INVALID_VERTEX);
  
    if(GET_IJ(g, v_start, v_end))
        return (E_EDGE_EXISTS);

    SET_IJ(g, v_start, v_end, 1);
    SET_IJ(g, v_end, v_start, 1);
    g->nr_E += 1;

    return (SUCCESS);
}
int remove_edge(struct graph* g, int v_start, int v_end)
{
    if(v_start<0 || v_start >= g->nr_V || v_end < 0 || v_end >= g->nr_V)
        return (E_INVALID_VERTEX);
    
    if(!GET_IJ(g, v_start, v_end))
        return (E_INVALID_EDGE);
    
    SET_IJ(g, v_start, v_end, 0);
    SET_IJ(g, v_end, v_start, 0);
    
    return (SUCCESS);
}
int show_graph(struct graph* g)
{
    int i, j;
    printf("|v| = %d. |E| = %d\n", g->nr_V, g->nr_E);
    for(i = 0; i<g->nr_V; ++i)
    {
        printf("VERTEX[%d]\t<->\t", i);
        for(j = 0; j<g->nr_V; ++j)
            if(GET_IJ(g, i, j))
                printf("[%d]<->", j);
        puts("[END]");
    }

    return (SUCCESS);
}

int release_graph(struct graph** pp_g)
{
    struct graph* g = NULL;

    g = *pp_g;
    free(g->pg);
    free(g);
    *pp_g = NULL;

    return (SUCCESS);
}