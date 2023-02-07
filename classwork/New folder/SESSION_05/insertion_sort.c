#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int ssize_t;

void insert_at_sorting_position(int* arr, ssize_t N);
void sort(int* arr, ssize_t N);
void show_array(int* arr, ssize_t N, char* msg);
void fill_array(int* arr, ssize_t N);

int main(int argc, char* argv[])
{
    int* a = NULL;
    ssize_t N = 0;

    if(argc != 2)
    {
        fprintf(stderr, "Usage Error:%s number of element\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoll(argv[1]);
    a = (int*)calloc(N, sizeof(int));
    if(NULL == a)
    {
        fprintf(stderr,"Calloc():fatal:out of memory");
        exit(EXIT_FAILURE);
    }

    fill_array(a, N);
    show_array(a, N, "Array : before sort");
    sort(a, N);
    show_array(a, N, "Array : after sort");
    free(a);
    a = NULL;

    exit(EXIT_SUCCESS);
}

void insert_at_sorting_position(int* arr, ssize_t N)
{
    ssize_t i;
    int key;
    key = arr[N-1];
    i = N-2;
    while(i>=0 && key<arr[i])
    {
        arr[i+1] = arr[i];
        i--;
    }
    arr[i+1] = key;
}
void sort(int* arr, ssize_t N)
{
    ssize_t i;
    for(i = 2; i<=N; i++)
    {
        insert_at_sorting_position(arr, i);
    }
}
void show_array(int* arr, ssize_t N, char* msg)
{
    if(msg)
        puts(msg);

    for(ssize_t i = 0; i<N; i++)
    {
        printf("arr[%lld] = %d\n", i, arr[i]);
    }
}
void fill_array(int* arr, ssize_t N)
{
    ssize_t i;
    srand(time(0));
    for(i = 0; i<N; i++)
    {
        arr[i]  = rand();
    }
}
