#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "singly_circular_linked_list.h"

int main(void)
{
    list_t* p_list = NULL;
    data_t data;
    status_t status;

    p_list = create_list();
    puts("SINGLY CIRCULAR LINKED LIST");
    show(p_list, "Empty list:");

    for(data = 0; data<5; ++data)
    {
        status = insert_start(p_list, data);
        assert(status);
    }
    show(p_list, "After insert_start:");

    for(data = 5; data<10; ++data)
    {
        status = insert_end(p_list, data);
        assert(status);
    }   
    show(p_list, "After insert_end:");

    status = insert_after(p_list, 0, 100);
    assert(status);
    show(p_list, "After insert_after:");

    status = insert_before(p_list ,0, 200);
    assert(status);
    show(p_list, "After insert_before");

    status = get_start(p_list, &data);
    assert(status);
    printf("Start data = %d\n,", data);
    show(p_list, "After get_satrt:");

    status = get_end(p_list, &data);
    assert(status);
    printf("End data = %d\n", data);
    show(p_list, "After get_end:");

    status = pop_start(p_list, &data);
    assert(status);
    printf("Start data = %d\n", data);
    show(p_list, "After pop_start:");

    status = pop_end(p_list, &data);
    assert(status);
    printf("End data = %d\n", data);
    show(p_list, "After pop_end:");

    status = remove_start(p_list);
    assert(status);
    show(p_list, "After the remove_start:");

    status = remove_end(p_list);
    assert(status);
    show(p_list, "After remove_end:");

    status  = remove_data(p_list, 0);
    assert(status);
    show(p_list, "After remove_data:");

    status = reverse_list(p_list);
    show(p_list, "After reversing in place:");

    while(is_empty(p_list)!= TRUE)
    {
        status = remove_start(p_list);
        assert(status);
    }
    show(p_list, "Empty list:");

   p_list = create_list();
	show(p_list, "Before reversing in place 1:");
	reverse_list(p_list);
	show(p_list, "After reversing in place 1:");

	insert_end(p_list, 100);
	show(p_list, "Before reversing in place 2:");
	reverse_list(p_list);
	show(p_list, "After reversing in place 2:");

	insert_end(p_list, 200);
	show(p_list, "Before reversing in place 3:");
	reverse_list(p_list);
	show(p_list, "After reversing in place 3:");

    return (EXIT_SUCCESS);
}