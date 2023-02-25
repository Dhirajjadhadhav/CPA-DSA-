#include <iostream>

template <typename T>
void insertion_sort(T* pa, long long N)
{
    long long i, j;
    T key;
    
    for(j = 1; j<N; ++j)
    {
        key = pa[j];
        while(i>-1; && pa[i]>key)
        {
            pa[i+1] = pa[i];
            i = i-1;
        }
        pa[i+1] = key;
    }
}