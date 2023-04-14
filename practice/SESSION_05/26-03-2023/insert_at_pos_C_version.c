#include <stdio.h>
#include <stdlib.h> 

typedef long long ssize_t;
void fill_array(int* p, ssize_t N);
void insert_at_sorting_postition(int* p_arr, ssize_t N);
void insertion_sort(int* p_arr, ssize_t N);
void show(int*  arr, ssize_t N, const char* msg);

int main(int argc, char* argv[])
{
    int* a = NULL;
    size_t N = 0;

    if(argc != 2)
    {
        fprintf(stderr, "Usage Error: %s number of elements\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoll(argv[1]);
    if(N<=0)
    {
        fprintf(stderr, "Bad size of arry");
        exit(0);
    }

    a =(int*)calloc(N, sizeof(int));
    if(a == NULL)
    {
        fprintf(stderr, "calloc():fatal:out of memroy\n");
        exit(EXIT_FAILURE);   
    } 

    fill_array(a, N);
    show(a, N, "before sort ");
    insertion_sort(a, N);
    show(a, N, "after sort");

    free(a);
    a = NULL;
}

void insert_at_sorting_postition(int* p_arr, ssize_t N)
{
    int key;
    ssize_t i;

    key = p_arr[N-1];
    i = N-2;
    while (i>-1 && p_arr[i]>key)
    {
        p_arr[i+1] = p_arr[i];
        i = i-1;
    }

    p_arr[i+1] = key;
}

void insertion_sort(int* p_arr, ssize_t N)
{
    for(ssize_t i = 2; i<=N; ++i)
        insert_at_sorting_postition(p_arr, i);

}
void show(int*  arr, ssize_t N, const char* msg)
{
    if(msg)
        puts(msg);

    for(ssize_t i = 0; i<N; ++i)
        printf("a[%lld]:%d\n", i, arr[i]);
}

void fill_array(int* p, ssize_t N)
{
    ssize_t i;

    srand(time(0));

    for(i = 0; i<N; ++i)
        p[i] = rand();
}