#include <stdio.h>
#include <stdlib.h>

typedef long long int ssize_t;

void fill_array(int* arr, ssize_t N);
void show_array(int* arr, ssize_t N, const char* msg);
void sort(int* arr, ssize_t N);
void insert_at_position(int* arr, ssize_t N);
void insertion_sort(int* arr, ssize_t N);

int main(int argc, char* argv[])
{
    ssize_t N;
    int* arr = NULL;
    
    if(argc != 2)
    {
        printf("Usage Error: %s Number_of_element", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoll(argv[1]);
    if(N<=0)
    {
        printf("Bad size of array\n");
        exit(EXIT_FAILURE);
    }

    arr = (int*)calloc(N, sizeof(int));
    if(arr == NULL)
    {
        fprintf(stderr, "calloc():fatal out memory\n");
        exit(EXIT_FAILURE);
    }

    fill_array(arr, N);
    show_array(arr, N, "Before sort()\n");
    sort(arr, N);
    show_array(arr, N, "after sort()\n");

    free(arr);
    arr = NULL;

    exit(EXIT_SUCCESS);
}


void fill_array(int* arr, ssize_t N)
{
    ssize_t i;
    srand(time(0));
    for(i = 0; i<N; ++i)
    {
        arr[i] = rand();
    }
}
void show_array(int* arr, ssize_t N, const char* msg)
{
    ssize_t i;

    if(msg)
        puts(msg);

    for(i = 0; i<N; ++i)
    {
        printf("arr[%lld] = %d\n", i, arr[i]);
    }    
}

void sort(int* arr, ssize_t N)
{
    insertion_sort(arr, N);
}
void insert_at_position(int* arr, ssize_t N)
{
    int key;
    int tmp;
    ssize_t i;

    key = arr[N-1];
    i = N-2;
    while(i>-1 && key<arr[i])
    {
        arr[i+1] = arr[i];
        i--;
    } 
    arr[i+1] = key;
}
void insertion_sort(int* arr, ssize_t N)
{
    ssize_t i;
    for(i = 2; i<=N; ++i)
        insert_at_position(arr, i);
}