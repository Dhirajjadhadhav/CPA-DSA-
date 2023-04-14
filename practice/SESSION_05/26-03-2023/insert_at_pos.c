#include <stdio.h>
#include <stdlib.h>

/*
    @input-1: Pointer to first element of array : p_arr
    @input-2: Size of array element in array : N
    @return : void

    pre-conditon:
        1) N >= 2
        2) subarray from p_arr[0] to p_arr[N-2] is sorted i non-decreasing order.
            p_arr[0]<=p_arr[1]<=p_arr[2]<= .....<=p_arr[N-2]
        3) p_arr[N-1] may not be necessarily maintain the  sorting order.

    Post-conditon:
        1)p_arr is sorted in non-decreasing order. 
*/
void insert_at_sorting_position(int* arr, int N);
void test_insert_at_sorting_position(void);
void show(int* p_arr, int N, const char* msg);

int main(void)
{
    test_insert_at_sorting_position();
    return (0);
}

void insert_at_sorting_position(int* p_arr, int N)
{   
    int key;
    int i;

    key = p_arr[N-1];
    i = N-2;

    while(i>-1 && p_arr[i]>key)
    {
        p_arr[i+1] = p_arr[i];
        i = i-1;
    }

    p_arr[i+1] = key;
}

void test_insert_at_sorting_position(void)
{   
    int a1[] = {10, 20, 30, 40, 50, 60, 70, 35};
    int N1 = (int)(sizeof(a1)/sizeof(a1[0]));

    int a2[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 2};
    int N2 = (int)(sizeof(a2)/sizeof(a2[0]));

    int a3[] = {20, 2};
    int N3 = (int)sizeof(a3)/sizeof(a3[0]);

    show(a1, N1 , "a1 before insert at soring position");
    insert_at_sorting_position(a1, N1);
    show(a1, N1 , "a1 after insert at soring position");

    show(a2, N2 , "a2 before insert at soring position");
    insert_at_sorting_position(a2, N2);
    show(a2, N2, "a2 after insert at sorting position");

    show(a3, N3, "a3 after insert at sorting position");
    insert_at_sorting_position(a3, N3);
    show(a3, N3, "a3 after insert at sorting position");

}
void show(int* p_arr, int N, const char* msg)
{
    if(msg)
        puts(msg);
    for(int i = 0; i<N; ++i)
        printf("a[%d]:%d\n", i, p_arr[i]);
}