#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int ssize_t;
#define TRUE 1
void merge_procedure(int* arr, ssize_t p, ssize_t q, ssize_t r);
void test_merge(void);
void show_array(int* arr, ssize_t N, char* msg);

int main(void)
{
    test_merge();
    return(EXIT_SUCCESS);
}
/*
    @input-1: pointer to array
    @input-2,3,4: p, q, r : Valid indices into array.
    @return : None

    Precondition:
        1)0<=p<=q<r<N.
        2)a[p..q] and a[q+1...r] are sorted.
    Postcondition:
        1)a[p..r] are sorted.
*/
void merge_procedure(int* arr, ssize_t p, ssize_t q, ssize_t r)
{
    int* a1 = NULL;         /*pointer to sub-array 1 */
    int* a2 = NULL;         /*pointer to sub-array 2*/
    ssize_t N1, N2;         /*length of sub-array 1 & 2*/
    ssize_t i, j, k;        /*Markers into subarray and the original array*/
    ssize_t index;          /*general purpose insex varibale*/

    N1 = q - p + 1;
    N2 = r - q;

    a1 = (int*)calloc(N1, sizeof(int));
    if(a1 == NULL)
    {
        fprintf(stderr,"calloc():fatal:out of memory");
        exit(EXIT_FAILURE);
    }

    a2 = (int*)calloc(N2, sizeof(int));
    if(a2 == NULL)
    {
        fprintf(stderr, "calloc():fatal:out of memory");
        exit(EXIT_FAILURE);
    }

    for(index = 0; index<N1; ++index)
        a1[index] = arr[p+index];
    

    for(index = 0; index<N2; ++index)
        a2[index] = arr[q+index+1];
    

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
                /* sub-array a1 has exhausted */
                /* Response: Copy remaining part of a2 in arr*/
                /* Remaining part of a2: current value of j to N2-1 */
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
            ++k;
            ++j;
            if(j==N2)
            {
                /* sub-array a2 has exhausted */
                /* Responce: Copy remaining pare of a1 in arr */
                while(i<N1)
                {
                    arr[p+k] = a1[i];
                    ++k;
                    ++i;
                }
                break;
            }
        }   
    }
    

    free(a1);
    a1 =  NULL;
    free(a2);
    a2 = NULL;
}
void test_merge(void)
{
    int a1[] = {30, 21, 10, 20, 30, 40, 50, 5, 15, 35, 55, 76, 54, 100, 200};
    ssize_t N1 = (ssize_t)sizeof(a1)/sizeof(a1[0]);
    ssize_t p1 = 2, q1 = 6, r1 = 11;
    
    int a2[] = {-43, -36, 20, 10, 561, 234};
    ssize_t N2  = (ssize_t)sizeof(a2)/sizeof(a2[0]);
    size_t p2 = 2, q2 = 2, r2 = 3;

    show_array(a1 , N1, "a1 : before merge");
    merge_procedure(a1, p1, q1 ,r1);
    show_array(a1 , N1, "a1 : after merge");

    show_array(a1 , N2, "a2 : before merge");
    merge_procedure(a2, p2, q2 ,r2);
    show_array(a2 , N2, "a2 : after merge");
}
void show_array(int* arr, ssize_t N, char* msg)
{
    ssize_t i;
    if(msg)
        puts(msg);
    
    for(i = 0; i<N; i++)
        printf("a[%lld]:%d\n", i, arr[i]);
}