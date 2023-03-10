#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/* Interface */
bst_t *create_bst(void)
{
    return (bst_t *)Xcalloc(1, sizeof(bst_t));
}

status_t insert_bst(bst_t *p_bst, data_t new_data)
{
    bst_node_t *p_new_node = NULL;
    bst_node_t *p_run = NULL;

    p_new_node = get_bst_node(new_data);
    p_run = p_bst->p_root_node;
    if (NULL == p_run)
    {
        p_bst->p_root_node = p_new_node;
        p_bst->nr_element++;
        return (SUCCCESS);
    }

    while (TRUE)
    {
        if (new_data <= p_run->data)
        {
            if (NULL == p_run->left)
                break;
            p_run = p_run->left;
        }
        else
        {
            if (NULL == p_run->right)
                break;
            p_run = p_run->right;
        }
    }

    if (new_data <= p_run->data)
        p_run->left = p_new_node;
    else
        p_run->right = p_new_node;
    p_new_node->parent = p_run;

    p_bst->nr_element += 1;

    return (SUCCCESS);
}
Bool search_bst(bst_t *p_bst, data_t s_data)
{
    return (search_bst_node(p_bst->p_root_node, s_data) != NULL);
}

void inorder_r(bst_t *p_bst)
{
    printf("[START]<->");
    __inorder_r(p_bst->p_root_node);
    puts("[END]");
}

void preorder_r(bst_t *p_bst)
{
    printf("[START]<->");
    __preorder_r(p_bst->p_root_node);
    puts("[END]");
}

void postorder_r(bst_t *p_bst)
{
    printf("[START]<->");
    __postorder_r(p_bst->p_root_node);
    puts("[END]");
}

void inorder_nrc(bst_t *p_bst)
{
    bst_node_t* p_run = NULL;
    stack_t* p_stack = NULL;

    p_stack = create_bstptr_stack();
    p_run = p_bst->p_root_node;

    printf("[START]");
    while(TRUE)
    {
        while(p_run!= NULL)
        {
            push_bstptr(p_stack, p_run);
            p_run = p_run->left;
        }
        if(pop_bstptr(p_stack, &p_run) == STACK_EMPTY)
            break;
        
        printf("[%d]<->",p_run->data);
        p_run = p_run->right;
    }
    
    puts("[END]");
    destory_bstptr_stack(&p_stack);

}

void preorder_nrc(bst_t *p_bst)
{
    bst_node_t* p_run = NULL;
    stack_t* p_stack = NULL;

    p_stack = create_bstptr_stack();
    p_run = p_bst->p_root_node;
    printf("[START]<->");
    while (TRUE)
    {
        while(p_run!= NULL)
        {
            printf("[%d]<->", p_run->data);
            push_bstptr(p_stack, p_run);
            p_run = p_run->left ;
        }

        if(pop_bstptr(p_stack, &p_run) == STACK_EMPTY)
            break;
        
        p_run = p_run->right;
    }
    puts("[END]");

}
void postorder_nrc(bst_t *p_bst)
{
    bst_node_t* p_run = NULL;
    stack_t* p_stack = NULL;
    color_t color;

    p_stack = create_bstptr_stack();
    p_run = p_bst->p_root_node;

    printf("[START]<->");

    while(TRUE)
    {
        while(p_run != NULL)
        {
            push_bstptr(p_stack, p_run);
            set_bstptr_top_color(p_stack, GREY);
            p_run = p_run->left;
        }

        if(get_bstptr_top_color(p_stack, &color) == STACK_EMPTY)
            break;
        
        if(color == GREY)
        {
            set_bstptr_top_color(p_stack, BLACK);
            top_bstptr(p_stack, &p_run);
            p_run = p_run->right;
            continue;
        }
        else if(color == BLACK)
        {   
            pop_bstptr(p_stack, &p_run);
            printf("[%d]<->",p_run->data);
            p_run = NULL;
        }
    }
    puts("[END]");
    destory_bstptr_stack(&p_stack);

}

status_t maximum_bst(bst_t *p_bst, data_t *p_max_data)
{
    bst_node_t *p_run = NULL;

    p_run = p_bst->p_root_node;
    if(NULL == p_run)
        return (BST_EMPTY);

    while (p_run->right != NULL)
        p_run = p_run->right;
    
    *p_max_data = p_run->data;
    return (SUCCCESS);
}

status_t minimum_bst(bst_t *p_bst, data_t *p_min_data)
{
    bst_node_t* p_run = NULL;
    
    p_run = p_bst->p_root_node;
    if(NULL == p_run)
        return (BST_EMPTY);

    while(p_run->left != NULL)
        p_run = p_run->left;
    *p_min_data = p_run->data;
    
    return (SUCCCESS);
}

status_t inorder_successor(bst_t *p_bst, data_t e_data, data_t *p_succ_data)
{
    bst_node_t* e_node = NULL;
    bst_node_t* p_succ_node = NULL;

    e_node = search_bst_node(p_bst->p_root_node, e_data);
    if(NULL == e_node)
        return (BST_DATA_NOT_FOUND);
    
    p_succ_node = inorder_successor_nodelevel(e_node);
    if(NULL == p_succ_node )
        return (BST_NO_SUCCESSOR);
    
    *p_succ_data = p_succ_node->data;
    return (SUCCCESS);
}

status_t inorder_predecessor(bst_t *p_bst,data_t e_data, data_t *p_pred_data)
{
    bst_node_t* e_node = NULL;
    bst_node_t* p_pred_node = NULL;

    e_node = search_bst_node(p_bst->p_root_node, e_data);
    if(NULL == e_node)
        return (BST_DATA_NOT_FOUND);
    
    p_pred_node = inorder_predecessor_nodelevel(e_node);
    if(NULL == p_pred_node )
        return (BST_NO_PREDECESSOR);
    
    *p_pred_data = p_pred_node->data;
    return (SUCCCESS);
}
status_t preorder_successor(bst_t* p_bst, data_t e_data, data_t* p_pre_succ_data)
{   
    bst_node_t* pe_node = NULL;
    bst_node_t* p_pre_succ_node = NULL;

    pe_node = search_bst_node(p_bst->p_root_node, e_data);
    if(NULL == pe_node)
        return (BST_DATA_NOT_FOUND);
    
    p_pre_succ_node = preorder_successor_nodelevel(pe_node);
    if(NULL == p_pre_succ_node)
        return (BST_NO_SUCCESSOR);
    
    *p_pre_succ_data  = p_pre_succ_node->data;
    return (SUCCCESS);
}

status_t preorder_predecessor(bst_t* p_bst, data_t e_data, data_t* p_pre_pred_data)
{
    bst_node_t* pe_node = NULL;
    bst_node_t* p_pre_pred_node = NULL;

    pe_node = search_bst_node(p_bst->p_root_node, e_data);
    if(NULL == pe_node)
        return (BST_DATA_NOT_FOUND);
    
    p_pre_pred_node  = preorder_predecessor_nodelevel(pe_node);
    if(NULL == p_pre_pred_node)
        return (BST_NO_PREDECESSOR);

    *p_pre_pred_data = p_pre_pred_node->data;
    return (SUCCCESS);
}

status_t* postorder_successor(bst_t* p_bst, data_t* e_data, data_t* p_pre_succ_data)
{
    bst_node_t* pe_node = NULL;
    bst_node_t* p_post_succ_node = NULL;

    pe_node = search_bst_node(p_bst->p_root_node, e_data);
    if(NULL == pe_node)
        return (BST_DATA_NOT_FOUND);
    
    p_post_succ_node = postorder_successor_nodelevel(pe_node);
    if(NULL == p_post_succ_node)
        return (BST_NO_SUCCESSOR);
    
    *p_pre_succ_data = p_post_succ_node->data;
    return (SUCCCESS);
}

status_t* postorder_predecessor(bst_t* p_bst, data_t* e_data, data_t* p_post_pred_data)
{
    bst_node_t* pe_node = NULL;
    bst_node_t* p_post_pred_node = NULL;

    pe_node = search_bst_node(p_bst->p_root_node, e_data);
    if(NULL == pe_node)
        return (BST_DATA_NOT_FOUND);
    
    p_post_pred_node = postorder_predecessor_nodelevel(pe_node);
    if(NULL == p_post_pred_node)
        return (BST_NO_PREDECESSOR);

    *p_post_pred_data = p_post_pred_node->data;
    return (SUCCCESS);
}

status_t remove_bst(bst_t *p_bst, data_t r_data)
{
    bst_node_t* z = NULL;       /*Address of node to be deleted */
    bst_node_t* y = NULL;       /*Address of successor node */

    z = search_bst_node(p_bst->p_root_node, r_data);
    if(NULL == z)
        return (BST_DATA_NOT_FOUND);
    
    if(NULL == z->left)
        transplant_bst(p_bst, z, z->right);
    else if(NULL == z->right)
        transplant_bst(p_bst, z, z->left);
    else 
    {
        y = z->right;
        while(NULL != y->left )
            y = y->left;
        
        if(z->right != y)
        {
            transplant_bst(p_bst, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant_bst(p_bst, z, y);
        y->left = z->left;
        y->left->parent  = y;

    }
    free(z);
    z = NULL;
    p_bst->nr_element--;
    return (SUCCCESS);
}

status_t destroy_bst(bst_t **pp_bst)
{
    bst_t* p_bst = NULL;

    p_bst = *pp_bst;
    __destory_bst_r(p_bst->p_root_node);
    free(p_bst);
    *pp_bst = NULL;
    
    return (SUCCCESS);
}

status_t remove_bst_extended(bst_t *p_bst, data_t r_data)
{
    bst_node_t* z= NULL;
    bst_node_t* y = NULL;

    z = search_bst_node(p_bst->p_root_node, r_data);
    if(z == NULL)
        return (BST_DATA_NOT_FOUND);
   
    
    if(z->left == NULL)
    {
        if(z->parent == NULL)
            p_bst->p_root_node = z->right;
        else if(z == z->parent->left)
            z->parent->left = z->right;
        else
            z->parent->right = z->right;
        if(z->right != NULL)
            z->right->parent = z->parent;
    }
    else if(z->right == NULL)
    {
        if(z->parent == NULL)
            p_bst->p_root_node = z->left;
        else if(z == z->parent->left)
            z->parent->left  = z->left;
        else    
            z->parent->right  = z->left;
        if(z->left != NULL)
            z->left->parent = z->parent;
    }
    else
    {
        y = z->right;
        while(y->left!=NULL)
            y = y->left;
        
        if(z->right != y)
        {
            if(y == y->parent->left)
                y->parent->left = y->right;
            else    
                y->parent->right = y->parent;
            
            y->right = z->right;
            y->right->parent = y;
        }

        if(z->parent == NULL)
            p_bst->p_root_node = y;
        else if(z == z->parent->left)
            z->parent->left  = y;
        else    
            z->parent->right = y;

        y->parent = z->parent;
        y->left  = z->left;
        z->left->parent = y;
    }
    free(z);
    z = NULL;
    p_bst->nr_element--;

    return (SUCCCESS);
}

/* BST Auxilarry */
bst_node_t *search_bst_node(bst_node_t *p_root_node, data_t search_data)
{
    bst_node_t* p_run = NULL;

    p_run = p_root_node;
    while(p_run != NULL)
    {
        if(search_data == p_run->data)
            break;
        else if(search_data < p_run->data)
            p_run = p_run->left;
        else    
            p_run = p_run->right;
    }

    return (p_run);
}

bst_node_t *get_bst_node(data_t new_data)
{
    bst_node_t* p_node = NULL;

    p_node = (bst_node_t*)Xcalloc(1, sizeof(bst_node_t));
    p_node->data = new_data;
    return (p_node);
}

bst_node_t *inorder_successor_nodelevel(bst_node_t *p_bst_node)
{
    bst_node_t* x = NULL;
    bst_node_t* y = NULL;
    bst_node_t* p_run = NULL;

   x = p_bst_node;
   /* case 1*/
   if(x->right != NULL)
   {    
        p_run = x->right;
        while(p_run->left != NULL)
            p_run = p_run->left;
        return (p_run);
   }
    /*case 2*/
   y = p_bst_node->parent;
   while(y != NULL && x == y->right)
   {
        x = y;
        y = y->parent;
   }

    return (y);
}

bst_node_t *inorder_predecessor_nodelevel(bst_node_t *p_bst_node)
{
    bst_node_t* p_run = NULL;
    bst_node_t* x = NULL;
    bst_node_t* y = NULL;

    x = p_bst_node;
    /*case 1*/
    if(x->left != NULL)
    {
        p_run = x->left;
        while(p_run->right != NULL)
            p_run = p_run->right;
        return (p_run);
    }

    /* case 2 */
    y = x->parent;

    while(y != NULL && x == y->left)
    {
        x = y;
        y = y->parent;
    }

    return (y);
}
bst_node_t* preorder_successor_nodelevel(bst_node_t* p_bst_node)
{
    bst_node_t* x = NULL;
    bst_node_t* y = NULL;

    x = p_bst_node;
    if(NULL != x->left)
    {
        /*case 1*/
        return (x->left);
    }
    else if(NULL != x->right)
    {
        /*case 2*/
        return (x->right);
    }

    /*case 3*/
    y = x->parent;
    while(y != NULL )
    {
        if(y->data > p_bst_node->data && y->right != NULL)
            break;
        y = y->parent;
    }
    y = y->right ? y->right : NULL;
    
    return (y);
}

bst_node_t* preorder_predecessor_nodelevel(bst_node_t* p_bst_node)
{
    bst_node_t* x = NULL;
    bst_node_t* y = NULL;

    x = p_bst_node;
    
    if(p_bst_node->parent == NULL)      /*case 1 root_node no preorder pred*/
        return (NULL);
    else if(x->parent->left == NULL || x->parent->left == x)       /*case 2 node is left child of parent */
    {
        return (x->parent);
    } 

    /*case 3 root is right child of parent */
    /*observation : leaf  and right child have predecessor also leaf node */
    //still some thung are wrong 
    y = y->parent->left;
    while(TRUE)
    {
        while(y->right == NULL && y->left != NULL)
            y = y->left;
        if(y->right == NULL && y->left == NULL)
            break;      
        if(y->right != NULL)
           y =  y->right;
    }
   

    return (y);
}
bst_node_t* postorder_successor_nodelevel(bst_node_t* p_bst_node)
{
    bst_node_t* x = NULL;
    bst_node_t* y = NULL;

 

}
bst_node_t* postorder_predecessor_nodelevel(bst_node_t* p_bst_node)
{
    
}

void __inorder_r(bst_node_t *p_root_node)
{
    if(p_root_node != NULL)
    {
        __inorder_r(p_root_node->left);
        printf("[%d]<->",p_root_node->data);
        __inorder_r(p_root_node->right);
    }
}

void __preorder_r(bst_node_t *p_root_node)
{
    if(p_root_node != NULL)
    {
          printf("[%d]<->", p_root_node->data);
        __preorder_r(p_root_node->left);
        __preorder_r(p_root_node->right);
    }
}

void __postorder_r(bst_node_t *p_root_node)
{
    if(p_root_node != NULL)
    {
        __postorder_r(p_root_node->left);
        __postorder_r(p_root_node->right);
        printf("[%d]<->", p_root_node->data);
    }
}

void __destory_bst_r(bst_node_t* p_root_node)
{
    if(p_root_node != NULL)
    {
        __destory_bst_r(p_root_node->left);
        __destory_bst_r(p_root_node->right);
        free(p_root_node);
    }
}

void transplant_bst(bst_t *p_bst, bst_node_t *u, bst_node_t *v)
{
    if(u->parent == NULL)
        p_bst->p_root_node = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if(v!= NULL)
        v->parent = u->parent;

}

/*BST auxillary - Stack Interface */
stack_t *create_bstptr_stack()
{
    return (create_bstptr_list());
}

status_t push_bstptr(stack_t *p_stack, bst_node_t *p_bst_node)
{
    return (insert_bstptr_end(p_stack, p_bst_node));
}

status_t top_bstptr(stack_t *p_stack, bst_node_t **pp_bst_node)
{
    return (examine_bstptr_end(p_stack, pp_bst_node));
}

status_t pop_bstptr(stack_t *p_stack, bst_node_t **pp_bst_node)
{
    return (examine_and_delete_bstptr_end(p_stack, pp_bst_node));
}

status_t set_bstptr_top_color(stack_t *p_stack, color_t new_color)
{

    if(is_bstptr_stack_empty(p_stack))
        return (STACK_EMPTY);
   
    p_stack->prev->color = new_color;
    return (SUCCCESS);
}
status_t get_bstptr_top_color(stack_t *p_stack, color_t *p_top_color)
{
    if(is_bstptr_stack_empty(p_stack))
        return (STACK_EMPTY);
        
    *p_top_color = p_stack->prev->color;
    return (SUCCCESS);
}

Bool is_bstptr_stack_empty(stack_t *p_stack)
{
    return (is_bstptr_list_empty(p_stack));
}

status_t destory_bstptr_stack(stack_t **pp_stack)
{
    return (destroy_bstptr_list(pp_stack));
}

/* BST auxillary - List interface*/

list_t *create_bstptr_list(void)
{
    list_t* p_new_list = NULL;

    p_new_list =  get_bstptr_node(NULL);
    p_new_list->next  = p_new_list;
    p_new_list->prev  = p_new_list;

    return (p_new_list);
}

status_t insert_bstptr_end(list_t *p_list, bst_node_t *p_bst_node)
{
    bstptr_node_t* p_new_bstptr_node = NULL;

    p_new_bstptr_node = get_bstptr_node(p_bst_node);
    generic_bstptr_insert(p_list->prev, p_new_bstptr_node, p_list);

    return (SUCCCESS);
}

status_t examine_bstptr_end(list_t *p_list, bst_node_t** pp_bst_node)
{
    if(is_bstptr_list_empty(p_list))
        return (LIST_EMPTY);

    *pp_bst_node = p_list->prev->p_bst_node;
    return (SUCCCESS);
}

status_t examine_and_delete_bstptr_end(list_t *p_list, bst_node_t **pp_bst_node)
{
    if(is_bstptr_list_empty(p_list))
        return (LIST_EMPTY);
    *pp_bst_node = p_list->prev->p_bst_node;
    generic_bstptr_delete(p_list->prev);
    return (SUCCCESS);
}
Bool is_bstptr_list_empty(list_t *p_list)
{
    return (p_list->next == p_list && p_list->prev == p_list);
}

status_t destroy_bstptr_list(list_t **pp_list)
{
    list_t* p_list = NULL;
    bstptr_node_t* p_run = NULL;
    bstptr_node_t* p_run_next = NULL;

    p_list = *pp_list;
    
    for(p_run = p_list->next;
        p_run != p_list;
        p_run = p_run_next
    )
    {
        p_run_next = p_run->next;
        free(p_run);
    }

    free(p_list);
    *pp_list = NULL;
    return (SUCCCESS);
}

/* BST Auxillary -list interface - List auxillary */
void generic_bstptr_insert(bstptr_node_t *p_beg, bstptr_node_t *p_mid, bstptr_node_t *p_end)
{
    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    p_end->prev = p_mid;
}

void generic_bstptr_delete(bstptr_node_t *p_bstptr_node)
{
    p_bstptr_node->prev->next = p_bstptr_node->next;
    p_bstptr_node->next->prev = p_bstptr_node->prev;
    free(p_bstptr_node);
    p_bstptr_node = NULL;
}

bstptr_node_t *search_bstptr_node(list_t *p_list, bst_node_t *p_bst_node)
{
    bstptr_node_t* p_run = NULL;

    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
    {
        if(p_run->p_bst_node == p_bst_node)
            return (p_run);
    }

    return (NULL);
}

bstptr_node_t *get_bstptr_node(bst_node_t *p_bst_node)
{
    bstptr_node_t* p_bstptr_node = NULL;

    p_bstptr_node = Xcalloc(1, sizeof(bstptr_node_t));
    p_bstptr_node->p_bst_node = p_bst_node;
    p_bstptr_node->color = WHITE;

    return (p_bstptr_node);
}

/* generic auxillary routines */
void *Xcalloc(size_t n, size_t s)
{
    void* p = NULL;
    
    p = calloc(n, s);
    if(p == NULL)
    {
        fprintf(stderr, "callloc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }
    return (p);
}
