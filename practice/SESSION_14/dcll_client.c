#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include "dcll.h" 

int main(void)
{
    list_t* p_list  = NULL;
    list_t* p_list_1 = NULL;
    list_t* p_list_2 = NULL;
    list_t* p_merge_list = NULL;
    list_t* p_cat_list  = NULL;
    status_t status;
    data_t data;
    int i;
    
    p_list = create_list();
    for( i = 0; i<5; ++i)
        assert(insert_start(p_list, i) == SUCCESS);
    for(i = 5; i<10; ++i)
        assert(insert_end(p_list, i)== SUCCESS);

    show(p_list, "initial list:");

    status = insert_after(p_list, 0, 100);
    assert(status == SUCCESS);
    
    show(p_list, "100 inserted after 0");
    
    status =  insert_before(p_list, 0, 200);
    assert(status == SUCCESS);

    show(p_list, "200 insert before 0");

    pop_start(p_list, &data);
    printf("start data = %d\n", data);
    show(p_list, "after pop_start:");

    pop_end(p_list, &data);
    printf("end data = %d\n", data);
    show(p_list, "After pop_end:");

    remove_start(p_list);
    show(p_list, "after the remove start");

    remove_end(p_list);
    show(p_list, "After the remove end");

    remove_data(p_list, 0);
    show(p_list, "after removing 0");

    reverse_list(p_list);
    show(p_list, "after the reverse_list");

    srand(time(0));
    p_list_1 = create_list();
    for(i = 0; i<5;++i)
    {
        insert_end(p_list_1, 100+2*i);
    }
    show(p_list_1, " p_list_1 :");
    p_list_2 = create_list();
    for(i = 0; i<10; ++i)
        insert_end(p_list_2, 100+i);
    show(p_list_2, "p_list_2 :");
    

    p_cat_list = concat_list(p_list_1, p_list_2);
    show(p_cat_list, "concat list of p_list_1 and p_list_2");

    p_merge_list =  merge_list(p_list_1,p_list_2);
    show(p_merge_list, "p_meregd_list");

    assert(SUCCESS ==  destroy_list(&p_list) &&p_list == NULL);

    return (EXIT_SUCCESS);
}