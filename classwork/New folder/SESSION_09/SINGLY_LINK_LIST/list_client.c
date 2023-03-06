#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    struct node* p_list = NULL;
    int data;
    int status;
 
    p_list  = create_list();
    show_list(p_list, "Initil state:");

    for(data = 10; data <= 100; data += 10)
    {
        status = insert_end(p_list, data);
        assert(status == SUCCESS);
    }

    show_list(p_list, "After inserting 10 element at end:");

    status = insert_after(p_list, 50, -100);
    assert(status == SUCCESS);
    show_list(p_list, "After inserting -100 after the 50");

    status = insert_before(p_list, 50, -200);
    assert(status == SUCCESS);
    show_list(p_list, "After inserting -200 before 50");


    destory_list(p_list);
    p_list = NULL;

    exit(EXIT_SUCCESS);    

}