#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
typedef long long int ssize_t;

struct vector
{
    int* p_arr;
    ssize_t N;
};

struct vector* create_vector(void);
void push_back(struct vector* p_vector, int new_ellment);
void show_vector(struct vector* p_vector);
void relese_vector(struct vector* p_vector);

int main(void)
{
    struct vector* p_vector = NULL; 
    int choice, num;

    p_vector = create_vector();

    while(TRUE)
    {
        printf("Do you want to enter another interger?[YES = 1, NO=0]:");
        scanf_s("%d", &choice);
        if(choice != 1)
        {
            break;
        }
        printf("Enter an interger:");
        scanf_s("%d", &num);
        push_back(p_vector, num);
    }

    puts("User's input:");
    show_vector(p_vector);

    relese_vector(p_vector);
    p_vector = NULL;

    return (0);
}

struct vector* create_vector(void)
{
    struct vector*  p_vector = NULL;

    p_vector = (struct vector*)malloc(sizeof(struct vector));
    if(p_vector == NULL)
    {
        fprintf(stderr, "malloc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }

    p_vector->p_arr = NULL;
    p_vector->N = 0;

    return(p_vector);

}
void push_back(struct vector* p_vector, int new_element)
{
    p_vector->p_arr = (int*)realloc(p_vector->p_arr, 
                                    (p_vector->N+1) * sizeof(int));
    if(p_vector->p_arr == NULL)
    {
        fprintf(stderr, "malloc():fatal: out of memory\n");
        exit(EXIT_FAILURE);
    }
    p_vector->N = p_vector->N + 1;
    p_vector->p_arr[p_vector->N-1] = new_element;
   
}
void show_vector(struct vector* p_vector)
{
    int i;

    for(i = 0; i<p_vector->N; i++)
        printf("p_vector->p_arr[%d]:%d\n", i, p_vector->p_arr[i]);
    
}
void relese_vector(struct vector* p_vector)
{
    if(p_vector != NULL)
    {
        if(p_vector->p_arr != NULL)
            free(p_vector->p_arr);
        free(p_vector);
    }
}
