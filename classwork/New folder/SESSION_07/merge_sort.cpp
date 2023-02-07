#include <iostream>
#include <Windows.h>

using ssize_t = long long int;

#define TRUE    1

class array
{
    private:
        int* a;
        ssize_t N;

        static void merge(int* a, int p, int q, int r);
        static void merge_sort(int* a, int p, int r);
    
    public:
        array(ssize_t _N) : N(_N), a(new int[N]){}
        ~array(){ delete[] a;}

        void fill_array()
        {
            srand(time(0)); 
            for(int i = 0; i<N; ++i)
            {
                a[i] = rand();
            }
        } 

        friend std::ostream& operator<<(std::ostream& os, const array& A)
        {

        }

        void sort()
        {
            merge_sort(this->a, 0, this->N-1);
        }
};



int main(void)
{

}

static void merge(int* a, int p, int q, int r)
{
    int N1, N2;
    int* a1 = NULL;
    int* a2 = NULL;
    int i, j,k;
    int index;

    N1 = q-p-1;
    N2 = r-p;

    a1 = new int[N1];
    a2 = new int[N2];

    for(index = 0; index<N1; ++index)
        a1[index] = a[p+index];
    
    for(index = 0; index<N2; ++index)
        a2[index] = a[q+1+index];
    
    i = 0; 
    j = 0; 
    k = 0; 
    
    while(TRUE)
    {
        if(a1[i]<=a2[j])
        {
            a[p+k] = a1[i];
            ++i;
            ++k;
            if(i == N1)
            {
                while(j<N2)
                {
                    a[p+k] = a2[j];
                    ++j;
                    ++k;
                }
                break;
            }

        }
        else
        {
            a[p+k] = a2[j];
            ++j;
            ++k;
            if(j == N2)
            {
                while(i<N1)
                {
                    a[p+k] = a1[i];
                    ++i;
                    ++k;
                }
                break;
            }
        }
    }

    delete[] a1;
    delete[] a2;
}

static void merge_sort(int* a, int p, int r)
{
    int q;
    if(p<r)
    {
        q = (p+r)/2;
        merge_sort(a, p, q);
        merge_sort(a, q+1, r);
        merge(a, p, q, r);
    }
}