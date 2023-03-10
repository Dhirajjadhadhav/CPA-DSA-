#include <stdexcept>

namespace dsa
{
    typedef int data_t;
    namespace trees
    {
        class bst_node
        {
            friend class bst;
        
            private:
                data_t data;
                bst_node* left;
                bst_node* right;
                bst_node* parent;
                bst_node(data_t _data = 0)
                :data(_data), left(nullptr), right(nullptr), parent(nullptr){}
        };

        class bst
        {
            friend class inorder_iterator;
            private:
                bst_node* root_node;
                size_t nr_element;
                static void preorder_nodelevel(bst_node* p_node);
                static void inorder_nodelevel(bst_node* p_node);
                static void postorder_nodelevel(bst_node* p_node);
                static bst_node* search_nodelevel(bst_node* root_node, data_t s_data);
                static bst_node* preorder_predecessor_nodelevel(bst_node* p_node);
                static bst_node* preorder_successor_nodelevel(bst_node* p_node);
                static bst_node* inorder_predecessor_nodelevel(bst_node* p_node);
                static bst_node* inorder_successor_nodelevel(bst_node* p_node);
                static bst_node* postorder_predecessor_nodelevel(bst_node* p_node);
                static bst_node* postorder_successor_nodelevel(bst_node* p_node);
                void transplant(bst_node* u, bst_node* v);
            public:
                //create_bst()
                bst()
                {
                    root_node  = nullptr;
                    nr_element = 0;
                }
                //destroy_bst()
                ~bst()
                {

                }
                //no copy constructor
                bst(const bst& other) = delete;
                //no move semantic
                bst(const bst&& other) = delete;
                //no copy assignment
                bst& operator=(const bst& other) = delete;
                //no  move assignment 
                bst& operator=(const bst&& other) = delete;

                void insert(data_t new_data);    
                void preorder();
                void inorder();
                void postorder();
                void preorder_nrc();
                void inorder_nrc();
                void postorder_nrc();
                bool search(data_t s_data);
                void max(data_t* p_max_data);
                void min(data_t* p_min_data);
                void inorder_successor(data_t e_data, data_t* p_succ_data);
                void inorder_predecessor(data_t e_data, data_t* p_pred_data);
                void preorder_successor(data_t e_node, data_t* p_succ_data);
                void preorder_predecessor(data_t e_node, data_t* p_succ_data);
                void postorder_successor(data_t e_data, data_t* p_succ_data);
                void postorder_predecessor(data_t e_node, data_t* p_pred_data);
                void remove(data_t r_data);

                class preorder_iterator
                {

                };

                class inorder_iterator
                {
                    private:
                        bst_node* p_node;
                    public:
                        inorder_iterator(bst_node* _p = 0):p_node(_p){}

                        inorder_iterator operator++()
                        {
                            p_node = bst::inorder_successor_nodelevel(p_node);
                            return *this;
                        }
                        
                        inorder_iterator operator--()
                        {
                            p_node = bst::inorder_predecessor_nodelevel(p_node);
                            return (*this);
                        }

                        inorder_iterator operator++()
                        {
                            inorder_iterator tmp_iter(p_node);
                            p_node = bst::inorder_predecessor_nodelevel(p_node);
                            return (tmp_iter);
                        }

                        inorder_iterator operator--()
                        {
                            inorder_iterator tmp_iter(p_node);
                            p_node = bst::inorder_predecessor_nodelevel(p_node);
                            return (tmp_iter);
                        }
                }; 

                class postorder_iterator
                {

                }; 
        };
        class bst_data_not_found : public std::runtime_error
        {

        };

        class bst_empty: public std::runtime_error
        {

        };

        class bst_no_successor : public std::runtime_error
        {

        };

        class bst_no_predecessor : public std::runtime_error
        {

        };
    }
}