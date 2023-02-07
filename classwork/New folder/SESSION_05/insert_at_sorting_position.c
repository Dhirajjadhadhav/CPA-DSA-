#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*
    @input-1 : Pointer to first element of array : p_arr
    @input-2 : Size of elenemt in array : N
    @return: void

    Pre-Condition:
        1)N >= 2
        2)Subarray from p_arr[0] to p_arr[N-2] is sorted in non-decreasing  order.
            p_arr[0]<=p_arr[1]<=.. . . . <=p_arr[N-2]
        3)p_arr[N-1] may not necessarily maintain the sorted order.

    Post-Condition:
        1)p_arr is sorted in non-decreasing order. 
*/
void insert_at_sorting_position(int* p_arr, int N);
void show_arry(int* arr, int size, char* msg);
int main(void)
{
    int arr[] = {10, 20, 30, 40, 50, 60, 70 ,90, 25};
    int N = sizeof(arr)/sizeof(arr[0]);

    show_arry(arr, N, "before call to insert_at_sorting_position()");
    insert_at_sorting_position(arr, N);
    show_arry(arr, N, "after call to insert_at_sorting_position()");
}

void insert_at_sorting_position(int* p_arr, int N)
{
    int key, i;

    key = p_arr[N-1];
    i = N-2;
    while(i>=0 && key<p_arr[i])
    {
        p_arr[i+1] = p_arr[i];
        i = i-1;
    }
    p_arr[i+1] = key;
}
void show_arry(int* arr, int size, char* msg)
{
    if(msg)
        puts(msg);
    
    for(int i = 0; i<size; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

}