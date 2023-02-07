#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TRUE 1
typedef long long int ssize_t;

struct vector
{
    int* p_arr;
    ssize_t size;
};

struct vector* Create_vector(void);
void push_back(struct vector* p_vector, int new_val);
void show_vector(struct vector* p_vector);
void relese_vector(struct vector* p_vector);

int main(void)
{
    struct vector* p_vector = NULL;
    int choice, element;

    p_vector = Create_vector();

    while(TRUE)
    {
        printf("Do you wan to add another number:[1:yes][0:no]\n");
        scanf("%d", &choice);
        if(choice != 1)
            break;
        printf("Enter an integer:\n");
        scanf("%d", &element);
        push_back(p_vector, element);
    }

    show_vector(p_vector);
    relese_vector(p_vector);

    return(EXIT_SUCCESS);
}

struct vector* Create_vector(void)
{
    struct vector* p_vector = NULL;

    p_vector = (struct vector*)malloc(sizeof(struct vector));
    if(NULL == p_vector)
    {
        fprintf(stderr, "malloc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }

    p_vector->p_arr = NULL;
    p_vector->size = 0;
    
    return(p_vector);
}
void push_back(struct vector* p_vector, int new_val)
{
    p_vector->p_arr = (int*)realloc(p_vector->p_arr, (p_vector->size+1) * sizeof(int));
    if(NULL == p_vector->p_arr)
    {
        fprintf(stderr,"realloc():fatal:out of memeory\n");
        exit(EXIT_FAILURE);
    }
    p_vector->size = p_vector->size+1;
    p_vector->p_arr[p_vector->size-1] = new_val;
}
void show_vector(struct vector* p_vector)
{
    int i;
    for(i = 0; i<p_vector->size; i++)
    {
        printf("p_vector->p_arr[%d] = %d\n", i, p_vector->p_arr[i]);

    }
}
void relese_vector(struct vector* p_vector)
{
    if(NULL != p_vector)
    {
        if(NULL != p_vector->p_arr)
            free(p_vector->p_arr);
        free(p_vector);
        p_vector = NULL;
    }
}