#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


struct Date
{
    int day, month, year;  
};

void  single_instance(void);
void array_of_instances(void);
void array_of_ptrs_of_instances(void);


int main(void)
{
    single_instance();
    array_of_instances();
    array_of_ptrs_of_instances();
}

void  single_instance(void)
{
    struct Date* p = NULL;

    p = (struct Date*)malloc(sizeof(struct Date));
    if(p == NULL)
    {
            fprintf(stderr, "malloc():fatal: out of memory\n");
            exit(EXIT_FAILURE);
    }
    memset(p, 0, sizeof(struct Date));

    p->day = 1;
    p->month = 1;
    p->year = 1970;

    printf("%d-%d-%d\n",p->day, p->month, p->year);

    free(p);
    p = NULL;
}
void array_of_instances(void)
{   
    struct Date * p = NULL;
    size_t N = 5;
    size_t i;

    p = (struct Date*)malloc(N * sizeof(struct Date));
    if(p == NULL)
    {
        fprintf(stderr,"malloc():fatal: out of memory\n");
        exit(EXIT_FAILURE);
    }

    memset(p, 0, N * sizeof(struct Date));

    for(i = 0; i<N; i++)
    {
        p[i].day = 1;
        p[i].month = 1;
        p[i].year = 1970;
    }

    for(i = 0; i<N; i++)
    {
        printf("%zd : %d-%d-%d\n", i +1 , p[i].day, p[i].month, p[i].year);
    }
    
    free(p);
    p = NULL;
}
void array_of_ptrs_of_instances(void)
{
    struct Date **pp = NULL;
    int N = 5;
    int i;
    
    pp =  (struct Date**)malloc(N * sizeof(struct Date*));
    if(pp == NULL)
    {
        fprintf(stderr, "malloc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    } 

   memset(pp, 0, N * sizeof(struct Date*));

   

    for( i = 0; i<N; i++)
    {   
        pp[i] = (struct Date*)malloc(sizeof(struct Date));
        memset(pp[i], 0, sizeof(struct Date));
    }
   
   printf("after the memory of ptrs allocated");
    for(i = 0; i<N; i++)
    { 
        pp[i]->day = 1;
        pp[i]->month = 1;
        pp[i]->year = 1970;
    }
   
    for(i = 0; i<N; i++)
    {
        printf("%d : %d-%d-%d\n", i + 1, pp[i]->day, pp[i]->month, pp[i]->year);
    }


    for(i = 0; i<N; i++)
    {
        free(pp[i]);
        pp[i] = NULL;
    }

    free(pp);
    pp = NULL;
}
