#include <stdio.h>
#include <stdlib.h>

typedef long long int ssize_t;

#define TRUE    1

void fill_arry(int* arr, ssize_t N);
void show_array(int* arr, ssize_t N, const char* msg);
void sort(int* arr, ssize_t N);
void quick_sort(int* arr, ssize_t p, ssize_t q);
ssize_t partition(int* arr, ssize_t p, ssize_t q);

int main(int argc, char* argv[])
{
    int* arr = NULL;
    ssize_t N;

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

    arr = (int*)calloc(N, sizeof(int));
    if(NULL == arr)
    {
        fprintf(stderr, "calloc():fatal out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    fill_arry(arr, N);
    show_array(arr, N, "Array Befoer sort:");
    sort(arr, N);
    show_array(arr, N, "Array After the sort:");

    free(arr);
    arr = NULL;
}

void fill_arry(int* arr, ssize_t N)
{
    ssize_t i;

    srand(time(0));
    for(i = 0; i<N; ++i)
        arr[i] = rand();
}

void show_array(int* arr, ssize_t N, const char* msg)
{
    ssize_t i;
    if(msg)
        puts(msg);
    for(i = 0; i<N; ++i)
        printf("arr[%lld] = %d\n", i, arr[i]);
    
}

void sort(int* arr, ssize_t N)
{
    quick_sort(arr, 0, N-1);
}

void quick_sort(int* arr, ssize_t p, ssize_t r)
{
    ssize_t q;
    if(p<r)
    {
        q= partition(arr, p, r);
        quick_sort(arr, p, q-1);
        quick_sort(arr, q+1, r);
        
    }
}
ssize_t partition(int* arr, ssize_t p, ssize_t r)
{

    ssize_t i, j;
    int pivot;
    int tmp;

    pivot = arr[r];
    i = p-1;
    j = p;

    while(j<r)
    {
        if(arr[j]<pivot)
        {
            i = i+1;
            tmp  = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
        j = j+1;
    }

    tmp = arr[i+1];
    arr[i+1] = pivot;
    arr[r] = tmp;

    return (i+1);
}
