#include <stdio.h>
#include <stdlib.h>

#define TRUE    1


typedef long long int ssize_t;
void fill_array(int* a, ssize_t N);
void show_array(int* p, ssize_t N, const char* msg);
void sort(int* p, ssize_t N);
void merge(int* a, ssize_t p, ssize_t q, ssize_t r);
void merge_sort(int* a, ssize_t p, ssize_t r);

int main(int argc, char* argv[])
{
    int* a = NULL;
    ssize_t N;

    if(argc != 2)
    {
        fprintf(stderr, "usage Error : %s numsber of element\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoll(argv[1]);
    if(N<=0)
    {
        fprintf(stderr, "Bad size of array\n");
        exit(EXIT_FAILURE);
    }

    a = (int*)calloc(N, sizeof(int));
    if(NULL ==a)
    {
        fprintf(stderr, "calloc():fatal(): out of memory\n");
        exit(EXIT_FAILURE);
    }

    fill_array(a, N);
    show_array(a, N, "Array: Before sort");
    sort(a, N);
    show_array(a, N, "Array : After sort");

    free(a);
    a = NULL;

    return (EXIT_SUCCESS);
}

void merge(int* a, ssize_t p, ssize_t q, ssize_t r)
{
    ssize_t N1, N2;
    int* a1 = NULL;
    int* a2 = NULL; 
    ssize_t i, j, k;
    ssize_t index;

    N1 = q-p+1;
    N2 = r-q;
    
    a1 = (int*)calloc(N1, sizeof(int));
    if(NULL == a1)
    {
        fprintf(stderr, "calloc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }

    a2 = (int*)calloc(N2, sizeof(int));
    if(NULL == a2)
    {
        fprintf(stderr, "calloc():fatal:out of memeory\n");
        exit(EXIT_FAILURE);
    }

    for(index = 0; index<N1; ++index)
        a1[index] = a[p+index];

    for(index = 0; index<N2; ++index)
        a2[index] = a[q+1+index];
    
    i = 0; 
    j = 0;
    k = 0;
    
    while(TRUE)
    {
        if(a1[i]<=a2[j])
        {
            a[p+k] = a1[i];
            ++i;
            ++k;
            if(i == N1)
            {
                while(j<N2)
                {
                    a[p+k] = a2[j];
                    ++k;
                    ++j;
                }
                break;
            }
        }
        else
        {
            a[p+k] = a2[j];
            ++k;
            ++j;
            if(j == N2)
            {
                while(i<N1)
                {
                    a[p+k] = a1[i];
                    ++k;
                    ++i;
                }
                break;
            }

        }
    }

    free(a1);
    a1 = NULL;

    free(a2);
    a2 = NULL;
}

void fill_array(int* p, ssize_t N)
{   
    ssize_t i;

    srand(time(0));
    for(i = 0; i<N; ++i)
        p[i] = rand();
}

void show_array(int* a, ssize_t N, const char* msg)
{
    ssize_t i;

    if(msg)
        puts(msg);

    for(i = 0; i<N; ++i)
        printf("p[%lld] = %d\n", i, a[i]);
}

void merge_sort(int* a, ssize_t p, ssize_t r)
{
    ssize_t q;
    if(p<r)
    {
        q = (p+r)/2;
        merge_sort(a, p, q);
        merge_sort(a, q+1, r);
        merge(a, p, q, r);
    }   
}

void sort(int* p, ssize_t N)
{
    merge_sort(p, 0, N-1);
}