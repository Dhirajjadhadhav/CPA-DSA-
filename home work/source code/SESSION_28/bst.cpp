#include <iostream>
#include <cstdlib>

class bst_node
{
    friend class bst;
    private:
        int data;
        bst_node* left;
        bst_node* right;
        bst_node* parent;
        bst_node(int _data):    data(_data),
                                left(0),
                                right(0),
                                parent(0)
        {}

};

class bst
{
    class inorder_iterator;
    friend class inorder_iterator;

    private:
        bst_node* root_node;
        size_t* nr_elements;

        static void inorder_nodelevel(bst_node* p_node)
        {
            if(p_node != NULL)
            {
                inorder_nodelevel(p_node->left);
                printf("[%d]<-> ", p_node->data);
                inorder_nodelevel(p_node->right);
            }
        }

        static void destory_nodelevel(bst_node* p_node)
        {
            if(p_node!= 0)
            {
                destory_nodelevel(p_node->left);
                destory_nodelevel(p_node->right);
                delete p_node;
            }
        }

        static bst_node* inorder_successor(bst_node* p_node)
        {
            bst_node* x, *y;

            /*case 1*/
            if(p_node->right != NULL)
            {
                p_node = p_node->right;
                while(p_node->left != NULL)
                    p_node = p_node->left;
                return (p_node);
            }

            /*case 2*/
            x = p_node;
            y = p_node->parent;
            while(y != NULL && y->right == x)
            {
                x = y;
                y = y->parent;
            }

            return (y);
        }

        static bst_node* inorder_predecessor(bst_node* p_node)
        {
            bst_node* x, *y;

            /*case 1*/
            if(p_node->left != NULL)
            {
                p_node = p_node->left;
                 while(p_node->right != NULL)
                    p_node = p_node->right;
                return (p_node);
            }

            /*case 2*/
            x = p_node;
            y = x->parent;

            while(y != NULL && x == y->left)
            {
                x = y;
                y = x->parent;
            }
            return (y);
        }

    public:
        bst(): root_node(0), nr_elements(0){ }

        ~bst()
        {
            destory_nodelevel(root_node);
        }

        void insert(int new_data)
        {
            bst_node* run = 0;

            if(root_node == 0)
            {
                root_node = new bst_node(new_data);
                ++nr_elements;
                return;
            }

            run = this->root_node;
            while (true)
            {
                if(new_data<=run->data)
                {
                    if(run->left == 0)
                    {
                        run->left = new bst_node(new_data);
                        run->left->parent = run;
                        nr_elements++;
                        return;
                    }
                    run = run->left;
                }
                else
                {
                    if(run->right == 0)
                    {
                        run->right = new bst_node(new_data);
                        run->right->parent = run;
                        ++nr_elements;
                        return;
                    }
                    run = run->right;
                }
            }
        }

        void inorder()
        {
            printf("[BEGIN]<->");
            inorder_nodelevel(root_node);
            puts("[END]");
        }

        //TODO : Insert rest of the function from the c version

        //ITEEATOR IMPLEMNTATION
        inorder_iterator inorder_begin()
        {
            bst_node* p_node = root_node;
            if(p_node)
                while(p_node->left != NULL)
                    p_node = p_node->left;

                return inorder_iterator(p_node);
        }

        inorder_iterator inorder_end()
        {
            return (inorder_iterator(NULL));
        }

        class inorder_iterator
        {
            private:
                bst_node* p_node;
            public:
                inorder_iterator(bst_node* _p_node = 0) : p_node(_p_node)
                {}

                inorder_iterator operator++()
                {
                    this->p_node = bst::inorder_successor(this->p_node);
                    return (*this);
                }

                inorder_iterator operator--()
                {
                    this->p_node = bst::inorder_predecessor(this->p_node);
                    return (*this);
                }

                inorder_iterator operator++(int)
                {
                    inorder_iterator tmp_itr(this->p_node);
                    this->p_node = bst::inorder_successor(this->p_node);
                    return (tmp_itr);
                }

                inorder_iterator operator--(int)
                {
                    inorder_iterator tmp_iter(this->p_node);
                    this->p_node = bst::inorder_predecessor(this->p_node);
                    return (tmp_iter);
                }

                int operator*()
                {
                    return (p_node->data);
                }

                bool operator==(const inorder_iterator& other)
                {
                    return (p_node == other.p_node);
                }

                bool operator!=(const inorder_iterator& other)
                {
                    return (p_node != other.p_node);
                }

        };

        //TODO : Implement preorder and postorder interators

};

int main(void)
{
    bst B;
    int data[] = {40, 20, 30, 5, 60, 70, 55, 80, 90, 32, 78, 91, 87, 95, 99};   
    size_t i;

    for(i = 0; i<sizeof(data)/sizeof(data[0]); ++i)
        B.insert(data[i]);
    
    B.inorder();

    for(bst::inorder_iterator iter = B.inorder_begin();
        iter != B.inorder_end();
        iter++)
        std::cout<<"*iter "<<*iter<<std::endl;

        return (0);
}       