#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#define TRUE    1
#define FALSE   0
typedef long long int ssize_t;

void fill_array(int* arr, ssize_t N);
void show(int* arr, ssize_t N, const char* msg);
void sort(int* arr, ssize_t N);
void merge(int* arr, ssize_t p, ssize_t q, ssize_t r);
void merge_sort(int* arr,ssize_t p, ssize_t r);

int main(int argc, char* argv[])
{
    int* arr = NULL;
    ssize_t N;
    
    if(argc != 2)
    {
        fprintf(stderr, "Usage Error : %s Nr_of_elemet\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoll(argv[1]);
    if(N<=0)
    {
        fprintf(stderr, "Bad for array\n");
        exit(EXIT_FAILURE);
    }

    arr = (int*)calloc(N, sizeof(int));
    if(NULL == arr)
    {
        fprintf(stderr, "calloc(): fatal out of memory\n");
        exit(EXIT_SUCCESS);
    }

    fill_array(arr, N);
    show(arr, N, "array before the sort");
    sort(arr, N);
    show(arr, N, "array after the sort\n");


    free(arr);
    arr = NULL;

    return (EXIT_SUCCESS);
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
void show(int* arr, ssize_t N, const char* msg)
{
    ssize_t i;

    if(msg)
        puts(msg);
    
    for(i = 0; i<N; ++i)
        printf("arr[%lld] = %d\n", i, arr[i]);
    
}

void sort(int* arr, ssize_t N)
{
    merge_sort(arr, 0, N-1);
}

void merge(int* arr, ssize_t p, ssize_t q, ssize_t r)
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
        fprintf(stderr, "calloc():fatal out of memory\n");
        exit(EXIT_FAILURE);
    }

    
    a2 = (int*)calloc(N1, sizeof(int));
    if(NULL == a2)
    {
        fprintf(stderr, "calloc():fatal out of memory\n");
        exit(EXIT_FAILURE);
    }

    for(index = 0; index<N1; ++index)
        a1[index] = arr[p+index];

    for(index = 0; index<N2; ++index)
        a2[index] = arr[q+1+index];

    i = 0; 
    j = 0; 
    k = 0;
    while(TRUE)
    {
        if(a1[i]<=a2[j])
        {
            arr[p+k] = a1[i];
            ++i;
            ++k;
            if(i == N1)
            {
                while(j<N2)
                {
                    arr[p+k] = a2[j];
                    ++j;
                    ++k;
                }
                break;
            }
        }
        else
        {
            arr[p+k] = a2[j];
            ++j;
            ++k;
            if(j == N2)
            {
                while(i<N1)
                {
                    arr[p+k] = a1[i];
                    ++i;
                    ++k;
                }
                break;
            }
        }
    }
	
	free(a1);
	a1 = NULL;
	free(a2)
	a2 = NULL;

}	

void merge_sort(int* arr,ssize_t p, ssize_t r)
{
    ssize_t  q;

    if(p<r)
    {
        q= (p+r)/2;
        merge_sort(arr, p, q);
        merge_sort(arr, q+1, r);
        merge(arr, p, q, r);
    }
}
