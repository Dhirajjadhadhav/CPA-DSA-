#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>
#include "singly_linked_list.h"

int main(void)
{
	list_t* p_list = NULL; 
	list_t* p_list_1 = NULL; 
	list_t* p_list_2 = NULL; 
	list_t* p_cat_list = NULL; 
	list_t* p_merged_list = NULL; 
	list_t* p_reversed_list = NULL; 
	data_t data; 
	status_t status; 


	p_list = create_list(); 

	show(p_list, "Empty list:"); 

	for (data = 0; data < 5; ++data)
	{
		status = insert_start(p_list, data); 
		assert(status); 
	}
	show(p_list, "After insert_start:"); 

	for (data = 5; data < 10; ++data)
	{
		status = insert_end(p_list, data); 
		assert(status); 
	}
	show(p_list, "After insert_end:");

	status = insert_after(p_list, 0, 100); 
	assert(status); 
	show(p_list, "After insert_after:"); 

	status = insert_before(p_list, 0, 200); 
	assert(status); 
	show(p_list, "After insert_before:"); 

	status = get_start(p_list, &data); 
	assert(status); 
	printf("Start data = %d\n", data); 
	show(p_list, "After get_start:");

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
	show(p_list, "After remove_start:"); 

	status = remove_end(p_list);
	assert(status);
	show(p_list, "After remove_end:");

	status = remove_data(p_list, 0); 
	assert(status == SUCCESS); 
	show(p_list, "After remove_data:"); 
	status = reverse_list(p_list); 
	show(p_list, "After reversing in place"); 
	while (is_empty(p_list) != TRUE)
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

	p_list_1 = create_list(); 
	p_list_2 = create_list();

	for(data = 5; data <= 55; data += 10)
		assert(insert_end(p_list_1, data) == SUCCESS);

	for(data = 10; data <= 100; data += 10) 
		assert(insert_end(p_list_2, data) == SUCCESS); 

	p_cat_list = concat(p_list_1, p_list_2); 
	show(p_cat_list, "Immutable concatenatin of list 1 & 2"); 

	p_merged_list = merge(p_list_1, p_list_2); 
	show(p_merged_list, "Merged list of list 1 & 2"); 

	p_reversed_list = get_reversed_list(p_list_2); 
	show(p_reversed_list, "Reversed version of list 2"); 

	status = append(p_list_1, p_list_2); 
	assert(status == SUCCESS); 
	show(p_list_1, "After appending list 2 to list 1");
	p_list_2 = NULL; 

	destroy_list(&p_list); 
	destroy_list(&p_list_1); 
	destroy_list(&p_cat_list); 
	destroy_list(&p_merged_list); 
	destroy_list(&p_reversed_list); 

	puts("Implementation successful!"); 

	return (EXIT_SUCCESS); 
}