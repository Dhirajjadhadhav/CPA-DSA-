#define _CRT_RAND_S
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"

void test_bst_normal(void);
void test_bst_extreme(void);

int main(void)
{
    test_bst_normal();
    test_bst_extreme();
}

void test_bst_normal()
{
    bst_t* p_bst = NULL;
    data_t data[] = { 100, 150, 75, 200, 65, 25, 5, 250, 125, 110, 130, 35, 40};
    size_t i;

    p_bst = create_bst();
    for(i = 0; i<sizeof(data)/sizeof(data[0]); ++i)
        assert(insert_bst(p_bst, data[i]));
    
    puts("INORDER:");
    inorder_traversal(p_bst);

    puts("PREORDER :");
    preorder_traversal(p_bst);

    puts("POSTORDER :");
    postorder_traversal(p_bst);

    printf("HEIGHT(p_bst)=%u\n", height_bst(p_bst));

    assert(destroy_bst(&p_bst) == SUCCESS && p_bst == NULL);
}

void test_bst_extreme()
{
    size_t N = 1000000;
    data_t data;
    size_t i;

    bst_t* p_bst = create_bst();
    for(i  = 0; i<N; ++i)
    {
        rand_s(&data);
        assert(insert_bst(p_bst, data) == SUCCESS);
    }

    printf("HEIGHT(p_bst) = %u\n", height_bst(p_bst));
    assert(destroy_bst(&p_bst) == SUCCESS && p_bst == NULL);
}