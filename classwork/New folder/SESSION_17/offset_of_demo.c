#include <stdio.h>
#include <stdlib.h>

#define OFFSET_OF(T, mem)   ((unsigned long long int)&((T*)0)->mem)

struct A
{
    int a;          //0
    char b;         //4
    float c;        //5
};

void print_instance(float* pf);

int main(void)
{
    struct A a1 = {10, 'A', 1.1}, a2 = {20, 'B', 2.2}, a3 = {30, 'c', 3.3};

    printf("OFFSET_OF(struct A, a) = %llu\n", OFFSET_OF(struct A, a));
    printf("OFFSET_OF(struct A, b) = %llu\n", OFFSET_OF(struct A, b));
    printf("OFFSET_OF(struct A, c) = %llu\n", OFFSET_OF(struct A, c));
    
    print_instance(&a1.c);
    print_instance(&a2.c);
    print_instance(&a3.c);

    return (0);
}

void print_instance(float* fp)
{

}

