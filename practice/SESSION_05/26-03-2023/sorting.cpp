#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using ssize_t = long long;

class array
{
    private:
        int* a;
        ssize_t N;
        
        static void insert_at_sorting_postion(int* a, ssize_t N)
        {
            int key;
            ssize_t i;

            key = a[N-1];
            for(i = N-2; i>-1 && a[i]>key; --i)
                a[i+1] = a[i];
            a[i+1] = key;
        }
    public:
        array(ssize_t _N)
        {
            if(_N<=0)
                throw std::domain_error("Bad size of array");
            a = new int[_N];
            N = _N;
        }

        void fill_array()
        {
            srand(time(0));
            for(ssize_t i = 0; i<N; ++i)
                a[i] = rand();

        }

        void sort()
        {
            for(ssize_t n = 2; n<=N; ++n)
                insert_at_sorting_postion(a, n);
        }

        friend std::ostream& operator<<(std::ostream& os, const array& A)
        {
            for(ssize_t i = 0; i<A.N; ++i)
                os<<"a["<<i<<"]:"<<A.a[i]<<std::endl;
            return os;
        }

        ~array()
        {
            delete[] a;
            a = nullptr;
        }

        array(const array& other) = delete;
        array(const array&& other) = delete;
        array& operator=(const array& other) = delete;
        array& operator=(const array&& other) = delete;
};

int main(int argc, char* argv[])
{
    ssize_t N;

    if(argc != 2)
    {
        std::cerr<<"Usage Error : "<<argv[0]<<"Number of element"<<std::endl;
        exit(EXIT_FAILURE);
    }

    N = atoll(argv[1]);
    if(N<=0)
    {
        std::cerr<<"Bad size for array"<<std::endl;
        exit(EXIT_FAILURE);
    }
    array* pA = new array(N);
    pA->fill_array();

    std::cout<<"Array before sort"<<std::endl<<*pA;
    pA->sort();
    std::cout<<"Array after sort"<<std::endl<<*pA;

    delete pA;
    pA = nullptr;

    return (EXIT_FAILURE);
}