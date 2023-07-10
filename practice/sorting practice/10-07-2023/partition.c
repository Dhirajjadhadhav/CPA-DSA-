#include <stdio.h>

void printArray(int *arr, int size, char *msg)
{
    if(msg)
        puts(msg);
    
    for(int i = 0; i<size; ++i)
    {
        printf("%d ", arr[i]);
    }
}

int partition(int *arr, int p, int r)
{
    int pivot = arr[r];
    int i = p-1;
    int j =  p;
    int tmp;


    while(j<r)
    {
        if(arr[j]<=pivot)
        {
            i = i+1;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
        ++j;
    }
    tmp = arr[i+1];
    arr[i+1] = arr[r];
    arr[r] = tmp;  
    return (i+1);
}

int main()
{

    int arr[] = {23, 45, 12, 15, 20, 32 ,48, 63, 69, 10, 2, 3, 30};

    printArray(arr, sizeof(arr)/sizeof(arr[0]), "before the partition");
    int q = partition(arr, 0 , sizeof(arr)/sizeof(arr[0])-1);
    printf("\nq = %d\n", q);
    printArray(arr, sizeof(arr)/sizeof(arr[0]), "after the partition");
    
}