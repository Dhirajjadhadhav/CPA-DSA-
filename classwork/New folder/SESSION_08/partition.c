#include <stdio.h>
#include <stdlib.h>

typedef long long int ssize_t;

/*
    Precondtition: 0<= p<r<N;
    PostCondition:
        Permute the element of a[p...r]
        in such a way that
        i)  the element at a[r] at beginning of 
        algorithm in shifted to index q(p <= q <= r) and
        ii) a a[p...q-1] <= a[q]
        iii)a[q+1 ... r]  > a[q]
        iv) return q
*/

int partition(int* a, int p, int r);
void test_partition(void);
void swap(int*a , int* b);
void show(int* a, ssize_t start, ssize_t end, const char * msg);

int main(void)
{
    test_partition();
    return (EXIT_SUCCESS);
}

int partition(int* a, int p, int r)
{
    int pivot;
    int j;
    int i;
    int tmp;

    pivot = a[r];
    i = p-1;
    j = p;
    while(j<r)
    {
        if(a[j]<pivot)
        {
            i = i + 1;
            swap(&a[i], &a[j]);
        }
        j = j+1;
    }
    swap(&a[i+1], &a[r]);

    return (i+1);
}
void swap(int*a , int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void test_partition(void)
{
    int a[] = { -1, -1, -1, 25, 50, 32, 6, 8, 2, 
                10, 18, 60, 70, 20, -1, -1, -1};
    ssize_t p = 3;
    ssize_t r = 13;
    ssize_t q;

    show(a, p, r, "a[p...r] before partitiion:");
    q = partition(a, p, r);
    printf("q = %lld, a[%lld ] = %d\n", q, q, a[q]);
    show(a, p, q-1, "a[p ...q-1]:");
    show(a, q+1, r, "a[q+1...r]:"); 
}

void show(int* a, ssize_t start, ssize_t end, const char * msg)
{
    ssize_t i;
    
    if(msg)
        puts(msg);

    for(i = start; i<=end; ++i)
        printf("a[%lld]:%d\n", i, a[i]);
}
