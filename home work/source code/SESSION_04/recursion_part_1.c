#include <stdio.h>
#include <stdlib.h>

typedef long long int ssize_t;

ssize_t factorial(ssize_t);
int recursive_sum(int* pa, int i);
int bin_search(int* pa, int i, int j, int SE);

void test_fact(void);
void test_sum(void);
void tesct_bin_search(void);

int main(void)
{
    test_fact();
    test_sum();
    tesct_bin_search();
    return (0);
}

ssize_t factorial(ssize_t i)
{
    if(i<0)
        return (-1);
    if(i == 0)
        return (1);
    return (i * factorial(i-1));
}
int  recursive_sum(int* pa, int i)
{
   if(i == -1)
        return (0); 
        printf("%d\n", pa[i]);
    return (pa[i] + recursive_sum(pa, i-1)); 
}
int bin_search(int* pa, int i, int j, int SE)
{
   int mid_index;

   if(i<=j)
   {
        mid_index = (i + j)/2;
        if(pa[mid_index] == SE)
            return(mid_index);
        else if(pa[mid_index]<SE)
            return (bin_search(pa, mid_index + 1 , j, SE));
        else    
            return(bin_search(pa, i, mid_index-1, SE));
   }
    return -1;
}

void test_fact(void)
{
    ssize_t N1 = 5, N2 = 20, N3 = 13;
    ssize_t fact_N1, fact_N2, fact_N3;

    fact_N1 = factorial(N1);
    fact_N2 = factorial(N2);
    fact_N3 = factorial(N3);

    printf("%lld! = %lld, %lld! = %lld, %lld! = %lld\n", N1, fact_N1, N2, fact_N2, N3, fact_N3);
}
void test_sum(void)
{   
   const size_t N = 8;
    int A[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    ssize_t s = 0;
    size_t i;
    s =  recursive_sum(A, N-1);
    for(int i = 0; i<N; i++)
    {
        printf("A[%u] = %d\n", i , A[i]);
    }
    
    puts("Summation of all the element in array:");
    printf(" s = %lld\n", s);

}
void tesct_bin_search(void)
{
    int A[8] =  {10, 20, 30, 40, 50, 60, 70, 80};
    int B[12] = {
                 10, 15, 20, -40, 30, 40, 
                 50, 55, 60, 66,  70, 80
                };

    int i = 0, SE, search_index, NA = 8, N = 12;
    for( i = 0; i<N; i++)
    {
        SE = B[i];
        search_index = bin_search(A, 0, NA-1, SE);
        if(search_index == -1)
            printf("%d is not found in A\n", SE);
        else   
            printf("%d is found at index at %d\n",SE, search_index);
    }
}