#include <stdio.h>
#include <stdlib.h>

typedef long long int ssize_t;

ssize_t partition(int* arr, ssize_t p, ssize_t r);
void quick_sort(int* arr, ssize_t p, ssize_t r);
void sort(int* arr,ssize_t N);
void fill_array(int* arr, ssize_t N);
void Show_array(int* arr, ssize_t N, char* msg);

int main(int argc, char* argv[])
{
    
    int* arr = NULL;

    ssize_t  N;
    if(argc != 2)
    {
        printf("usage error : quick_sort.exe   nr_elemets\n");
        exit(EXIT_FAILURE);
    }
    
    N = atoll(argv[1]);
    if(N<=0)
    {
        printf("BAD input\n");
        exit(EXIT_FAILURE);
    }

    arr = (int*)malloc(N * sizeof(int));
    if(arr == NULL)
    {
        fprintf(stderr,"malloc: fatal out of memory\n");
        exit(EXIT_FAILURE);
    }

    fill_array(arr, N);

    Show_array(arr, N, "Before quick sort\n");
    quick_sort(arr,0, N-1);
    Show_array(arr, N, "after quick sort\n");

    
    exit(EXIT_SUCCESS);
}    


ssize_t partition(int* arr, ssize_t p, ssize_t r)
{
    int pivot = arr[r];
    int i = p-1;
    int j = p;
    int tmp;

    while(j<r)
    {
        if(arr[j]<=pivot)
        {
            i = i + 1;
            tmp  = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
        ++j;
    }
    tmp  = arr[i+1];
    arr[i+1] = arr[r];
    arr[r] = tmp;

    return (i+1);

}

void quick_sort(int* arr, ssize_t p, ssize_t r)
{
    ssize_t q;
   if(p<r)
   {
        q = partition(arr, p, r);
        quick_sort(arr, p, r-1);
        quick_sort(arr, q+1, r);
   } 
}

void sort(int* arr,ssize_t N)
{
    quick_sort(arr, 0, N-1);
}
void fill_array(int* arr, ssize_t N)
{
    srand(time(0));
    for(ssize_t i = 0; i<N; ++i)
        arr[i] = rand();
}

void Show_array(int* arr, ssize_t N, char* msg)
{
    if(msg)
        puts(msg);

    for(ssize_t i = 0; i<N; ++i)
        printf("arr[%lld] = %d\n", i, arr[i]);
}