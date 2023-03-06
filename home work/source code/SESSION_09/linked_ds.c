#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

void * xcalloc(size_t nr_element, size_t  size_per_element);
struct node* get_node(int data);

int main(void)
{
    struct node* p_start_1 = NULL;
    struct node* tmp = NULL;
    struct node* run =  NULL;
    int yes_or_no;
    int data;

    p_start_1 = get_node(10);
    while(1)
    {
        printf("DO you want to add one more integer:[YES-1][NO-Any]:");
        scanf("%d", &yes_or_no);
        if(yes_or_no != 1)
            break;
        printf("Enter an integer:");
        scanf("%d", &data);

        run = p_start_1;
        while(run->next != NULL)
            run = run->next;
        run->next = get_node(data);
    }

    /*Display */
    run = p_start_1;
    printf("[START]->");
    while(run!= NULL)
    {
        printf("[%d]->", run->data);
        run = run->next;
    }
    printf("[END]");

    /*Destroy*/
    run = p_start_1;
    while(NULL != run)
    {
        tmp = run->next;
        free(run);
        run = tmp;
    }

    p_start_1 = NULL;

    return(0);
}

void * xcalloc(size_t nr_element, size_t  size_per_element)
{
    void*  p  = NULL;
    
    p  = calloc(nr_element, size_per_element);
    if(NULL == p)
    {
        fprintf(stderr, "calloc():fatal out of VM\n");
        exit(EXIT_FAILURE);
    }
    return(p);

}
struct node* get_node(int data)
{
    struct node* p_node = NULL;

    p_node = (struct node*)xcalloc(1, sizeof(struct node));
    
    p_node->data = data;
    p_node->next = NULL;

    return(p_node);
}
