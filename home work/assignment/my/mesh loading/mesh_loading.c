#include <stdio.h>
#include <stdlib.h>
#include "mesh_loading.h"


int exatract_data(FILE* fp, Vector** pp_vert, Vector** pp_normal, Vector** pp_face)
{
    Vector* p_vert_vector = NULL;
    Vector* p_normal_vector = NULL; 
    Vector* p_face_vector = NULL; 
    
    Vertices *v = NULL;
    Normal *n = NULL;
    Face *f = NULL;
    char c1, c2;

    p_vert_vector = create_vector();
    p_normal_vector = create_vector();
    p_face_vector = create_vector();

    int x, y, z;

    while((c1 = getc(fp)) != EOF)
    {
        if(c1 == 'f')
        {   
            f = xmallco(sizeof(Face));
            

            
        }
        else if(c1 == 'v' && (c2 = getc(fp)) == ' ')
        {
            v = xmalloc(sizeof(Vertices));

            x = fscnaf(fp, %f, &v.x);
            y = fscanf(fp, %f, &v.y);
            z = fscanf(fp, %f, &v.z);

            if(x == EOF || y == EOF || z == EOF ||
               x == 0   || y == 0   || z == 0 )
            {
                fprintf(stderr, "vertices reading failed!");
                exit(EXIT_FAILURE);
            }
            push_back(p_vert_vector, v);
        }
        else
        {
            if(c2 == 't')
            {
                x = fsacnf("%f", );
                y = fscanf("%f", );
            
            }
            else if(c2 == 'n')
            {
                n = xmallco(sizeof(Normal));

            }
        }
    }
}

void* create_vector(void)
{
    void* p_vector = NULL;

    p_vector = xmalloc(sizeof(Vector));
    p_vector->p_arr = xmallco(sizeof(void*));
    p_vector->p_arr[0] = NULL;
    p_vector->N = 1;
    return (p_vector);
}

void push_back(Vector* p_vector, void* p_new_element)
{
    p_vector->p_arr = realloc(p_vector->p_arr, (N+1) * sizeof(void*));
    if(p_vector->p_arr == NULL)
    {
        fprintf(stderr, "realloc():fatal:out of memeroy\n");
        exit(EXIT_FAILURE);
    }

    p_vector->N = p_vector->N+1;
    p_vector->p_vect[N-1] = p_new_element;
}

void release_vector(void* p_vector)
{
    ssize_t i;

    if(NULL != p_vector)
    {
        if(p_vector->p_arr!= NULL)
        {   
            for(i = 0; i<p_vector->N; ++i)
            {
                free(p_vector->p_arr[i]);
            }
        }
        free(p_vector->p_arr);
    }
    free(p_vector);
    p_vector = NULL
}

void* xmalloc(ssize_t nr_of_bytes)
{
    void* p = NULL;
    
    p =  malloc(nr_of_bytes);
    if(NULL == p)
    {
        fprintf(stderr, "malloc():fatal: out of memeory\n");
        exit(EXIT_FAILURE);
    }

    return (p);
}