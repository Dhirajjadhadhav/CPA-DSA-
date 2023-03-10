#include <iostream>
#include <stack>
#include "bst.hpp"

using namespace std;
using namespace dsa::trees;

void bst:: preorder_nodelevel(bst_node* p_node)
{
    if(p_node != nullptr)
    {
        cout<<"["<<p_node->data<<"]<->";
        preorder_nodelevel(p_node->left);
        preorder_nodelevel(p_node->right);
    }
    
}
void bst:: inorder_nodelevel(bst_node* p_node)
{
    if(p_node != nullptr)
    {
        inorder_nodelevel(p_node->left);
        cout<<"["<<p_node->data<<"]<->";
        inorder_nodelevel(p_node->right);
    }
}

void bst:: postorder_nodelevel(bst_node* p_node)
{
    if(p_node != nullptr)
    {
        postorder_nodelevel(p_node->left);
        postorder_nodelevel(p_node->right);
        cout<<"["<<p_node->data<<"]<->";
    }
}

bst_node* bst:: search_nodelevel(bst_node* root_node, data_t s_data)
{
    bst_node* p_run = nullptr;
    p_run = root_node;

    while (p_run != nullptr)
    {
        if(p_run->data == s_data)
            break;
        else if(p_run->data > s_data)
            p_run = p_run->left;
        else    
            p_run = p_run->right;
    }
    
    return (p_run);
}
bst_node* bst :: preorder_predecessor_nodelevel(bst_node* p_node)
{

}
bst_node* bst:: preorder_successor_nodelevel(bst_node* p_node)
{
    

}
bst_node* bst:: inorder_predecessor_nodelevel(bst_node* p_node)
{
    bst_node* x = nullptr;
    bst_node* y = nullptr;

    x = p_node;
    if(p_node->right != nullptr)
    {
        x = x->right;
        while(x->left != nullptr)
            x = x->left;
        return (x);
    }
    y = x->parent;
    while(y!= nullptr && y->right == x)
    {
        x = y;
        y = y->parent;
    }
    
    return (y);
}

bst_node* bst:: inorder_successor_nodelevel(bst_node* p_node)
{
    bst_node* x = nullptr;
    bst_node* y = nullptr;

    x = p_node;
    if(x->left!= nullptr)
    {
        x = x->left;
        while(x->right != nullptr)
            x = x->right;
        return (x); 
    }
    y = x->parent;
    while(y!=nullptr && y->left == x)
    {
        x = y;
        y = y->parent;
    }
    return (y);
}

bst_node* bst:: postorder_predecessor_nodelevel(bst_node* p_node)
{

}

bst_node* bst:: postorder_successor_nodelevel(bst_node* p_node)
{

}

void bst:: transplant(bst_node* u, bst_node* v)
{
    if(u->parent == nullptr)
        root_node = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else    
        u->parent->right = v;
    if(v != nullptr)
        v->parent = u->parent;
}

void bst:: insert(data_t new_data)
{
    bst_node* new_node = nullptr;
    bst_node* p_run = nullptr;
    new_node = new bst_node(new_data);

    if(root_node == NULL)
    {
        root_node = new_node;
        return ;
    }
    p_run = root_node;
    while(true)
    {
        if(new_data<=p_run->data)
        {
            if(p_run->left == nullptr)
                break;
            p_run = p_run->left;
        }
        else
        {
            if(p_run->right == nullptr)
                break;
            p_run = p_run->right;
        }
    }
     if(new_data<=p_run->data)
        p_run->left = new_node;
    else    
        p_run->right = new_node;

}

void bst :: preorder()
{
    cout<<"[START]<->";
    preorder_nodelevel(root_node);
    cout<<"[END]"<<endl;

}

void bst :: inorder()
{
    cout<<"[START]<->";
    inorder_nodelevel(root_node);
    cout<<"[END]"<<endl;
}
void bst :: postorder()
{
    cout<<"[START]<->";
    postorder_nodelevel(root_node);
    cout<<"[END]";
}

void bst :: preorder_nrc()
{
    bst_node* p_run;
    stack<bst_node*>st;

    st.push(root_node);
    p_run = root_node;

    cout<<"[START]<->";
    while(true)
    {
        while(p_run != nullptr)
        {
            st.push(p_run);
            p_run = p_run->left;
        }

       if(st.empty() == true)
        break;

        p_run = st.top();
        st.pop();
        cout<<"["<<p_run<<"]<->";
        p_run = p_run->right;
    }
    cout<<"[END]"<<endl;
}

void bst:: inorder_nrc()
{
    bst_node* p_run = nullptr;
    stack<bst_node*>st;

    p_run = root_node;

    cout<<"[START]<->";
    while(true)
    {
        while(p_run != nullptr)
        {
            cout<<"["<<p_run<<"]<->";
            st.push(p_run);
            p_run = p_run->left;
        }
    }
    cout<<"[END]"<<endl;
}

void bst:: postorder_nrc()
{

}

bool bst:: search(data_t s_data)
{
    if(search_nodelevel(root_node, s_data) != nullptr);
}

void bst:: max(data_t* p_max_data)
{
    bst_node* p_run = nullptr;
    
    p_run = root_node;
    while(p_run->right != nullptr)
        p_run = p_run->right;
    
    *p_max_data = p_run->data;
}

void bst::min(data_t* p_min_data)
{
    bst_node* p_run = nullptr;

    p_run = root_node;
    while(p_run->left != nullptr)
        p_run = p_run->left;

    *p_min_data = p_run->data;

}

void bst:: inorder_successor(data_t e_data, data_t* p_succ_data)
{
    bst_node* e_node = nullptr;
    bst_node* p_succ_node = nullptr;

    e_node = search_nodelevel(root_node, e_data);
    if(e_node == nullptr)
        return;
    
    p_succ_node = inorder_successor_nodelevel(e_node);
    if(p_succ_data == nullptr)
        return;

    *p_succ_data = p_succ_node->data;
    
}
void bst:: inorder_predecessor(data_t e_data, data_t* p_pred_data)
{
    bst_node* e_node = nullptr;
    bst_node* p_pred_node = nullptr;

    e_node = search_nodelevel(root_node, e_data);
    if(e_node == nullptr)
        return ;
    
    p_pred_node = inorder_predecessor_nodelevel(e_node);
    if(p_pred_node == nullptr)
        return;
    
    *p_pred_data = p_pred_node->data;
}

void bst:: preorder_successor(data_t e_data, data_t* p_succ_data)
{   
    bst_node* e_node = nullptr;
    bst_node* p_succ_node = nullptr;

    e_node = search_nodelevel(root_node, e_data);
    if(e_node == nullptr)
        return;
    p_succ_node = preorder_successor_nodelevel(e_node);
    if(p_succ_node == nullptr)
        return;

    *p_succ_data = p_succ_node->data;
}

void bst:: preorder_predecessor(data_t e_data, data_t* p_pred_data)
{
    bst_node* e_node = nullptr;
    bst_node* p_pred_node = nullptr;

    e_node = search_nodelevel(root_node, e_data);
    if(e_node == nullptr)
        return;
    p_pred_node = preorder_predecessor_nodelevel(e_node);
    if(p_pred_node == nullptr)
        return;

    *p_pred_data = p_pred_node->data;
}

void bst:: postorder_successor(data_t e_data, data_t* p_succ_data)
{
    bst_node* e_node = nullptr;
    bst_node* p_succ_node = nullptr;

    e_node = search_nodelevel(root_node, e_data);
    if(e_node == nullptr)
        return;
    
    p_succ_node = postorder_successor_nodelevel(e_node);
    if(p_succ_node == nullptr)
        return;
    
    *p_succ_data = p_succ_node->data;
}

void bst:: postorder_predecessor(data_t e_data, data_t* p_pred_data)
{
    bst_node* e_node = nullptr;
    bst_node* p_pred_node = nullptr;

    e_node = search_nodelevel(root_node, e_data);
    if(e_node == nullptr)
        return;

    p_pred_node = postorder_predecessor_nodelevel(e_node);
    if(p_pred_node == nullptr)
        return ;
        
    *p_pred_data = p_pred_node->data;
}

void bst:: remove(data_t r_data)
{
    bst_node* z = nullptr;
    bst_node* z_succ = nullptr;

    z = search_nodelevel(root_node, r_data);
    if(z == nullptr)
        return ;
    
    if(z->left == nullptr)
        transplant(z,z->right);
    else if(z->right == nullptr)
        transplant(z, z->left);
    else
    {
        z_succ = inorder_predecessor_nodelevel(z);
        if(z->right != z_succ)
        {
            transplant(z_succ, z->right);
            z_succ->right = z->right;
            z->right->parent = z_succ;
        }
        transplant(z, z_succ);
        z_succ->left = z->left;
        z->left->parent = z_succ;
    }

    delete z;
    z = nullptr;
    nr_element--;
}
                