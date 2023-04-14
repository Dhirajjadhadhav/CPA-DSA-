#include <stdio.h>
#include <stdlib.h>

#define TRUE    1

typedef long long int ssize_t;

void fill_array(int* arr, ssize_t N);
void show(int* arr, ssize_t N, const char* msg);
void sort(int* arr, ssize_t N);
void insertion_sort(int* arr, ssize_t N);
void insert_at_postion(int* arr, ssize_t N);

int main(int argc, char* argv[])
{
    int * arr = NULL;
    ssize_t N;

    if(argc != 2)
    {
        fprintf(stderr, "Usage Error : %s number of Element\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoll(argv[1]);

    if(N<=0)
    {
        fprintf(stderr, "Bad size of array\n");
        exit(EXIT_FAILURE);
    }   

    arr = (int*)calloc(N, sizeof(int));
    if(NULL == arr)
    {
        fprintf(stderr, "calloc():fatal Out of memory\n");
        exit(EXIT_FAILURE);
    }

    fill_array(arr, N);
    show(arr, N, "before the sort:");
    sort(arr, N);
    show(arr, N, "after the sort:");

    free(arr);
    arr = NULL;
}

void fill_array(int* arr, ssize_t N)
{
    ssize_t i;
    srand(time(0));
    for(i = 0; i<N; ++i)
        arr[i] = rand();
}

void show(int* arr, ssize_t N, const char* msg)
{
    if(msg)
        puts(msg);

    ssize_t i;
    for(i = 0; i<N; ++i)
        printf("arr[%lld] = %d\n", i, arr[i]);
}

void sort(int* arr, ssize_t N)
{
    insertion_sort(arr, N);
}
void insertion_sort(int* arr, ssize_t N)
{
    ssize_t i;

    for(i = 2; i<=N; ++i)
        insert_at_postion(arr, i);
}
void insert_at_postion(int* arr, ssize_t N)
{
    int key;
    ssize_t i;
    key = arr[N-1];

    i = N-2;
    while(i>-1 && arr[i]>key)
    {
        arr[i+1] = arr[i];
        i--;
    }
    arr[i+1] = key;
}
