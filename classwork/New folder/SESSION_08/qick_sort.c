#include <stdio.h>
#include <stdlib.h>

#define TRUE    1

typedef long long int ssize_t;

void fill_array(int* p, ssize_t N);
void show_array(int* p, ssize_t N, const char* msg);
void sort(int* p, ssize_t N);
int partition(int*a, ssize_t p, ssize_t r);
void quick_sort(int* a, ssize_t p, ssize_t r);

int main(int argc, char* argv[])
{
    int* a = NULL;
    ssize_t N = 0;

    if(argc != 2)
    {
        fprintf(stderr, "Usage Error : %s number of element\n", argv[0]);
        exit(EXIT_FAILURE);
    } 

    N = atoll(argv[1]);
    if(N<=0)
    {
        fprintf(stderr, "Bad size for array\n");
        exit(EXIT_FAILURE);
    }

    a = (int*)malloc(N * sizeof(int));
    if(NULL == a)
    {
        fprintf(stderr, "malloc():fatal:out of memory");
        exit(EXIT_FAILURE);
    }

    fill_array(a, N);
    
    show_array(a, N, "Array : Before sort");
    sort(a, N);
    
    show_array(a, N, "Array : After sort");
   
    free(a);
    a = NULL;

    return (EXIT_SUCCESS);
}

void fill_array(int* p, ssize_t N)
{
    ssize_t i;
    srand(time(0));
    for(i  = 0; i<N; ++i)
        p[i] = rand();
}
void show_array(int* p, ssize_t N, const char* msg)
{
    if(msg)
        puts(msg);
    ssize_t i;
    for(i = 0; i<N; ++i)
        printf("a[%lld] = %d\n", i, p[i]);
}

void sort(int* p, ssize_t N)
{
    quick_sort(p, 0, N-1);
}

int partition(int*a, ssize_t p, ssize_t r)
{
    int pivot;
    int j;
    int i;

    int tmp;

    pivot = a[r];
    i = p-1;
    j = p;

    while(j<r)
    {
        if(a[j]<pivot)
        {
            i = i+1;

            tmp = a[j];
            a[j] = a[i];
            a[i] = tmp;
        }
        j = j+1;
    }

    tmp = a[i+1];
    a[i+1] = pivot;
    a[r] = tmp;

    return(i+1);
}

void quick_sort(int* a, ssize_t p, ssize_t r)
{
    ssize_t q;

    if(p<r)
    {
        q = partition(a, p, r);
        quick_sort(a, p , q-1);
        quick_sort(a, q+1, r);
    }
}
