/*Efficent version */

#include <stdio.h>
#include <stdlib.h>

typedef struct h_rb_node h_rb_node_t;
typedef struct v_rb_node v_rb_node_t;

typedef int vertex_t;
typedef int status_t;
typedef enum color color_t;

enum color
{
    REB = 1,
    BLACK
};

struct  h_rb_node
{
    v_rb_node_t* pv_node;
    color_t color;

    struct h_rb_node* left;
    struct h_rb_node* right;
    struct h_rb_node* parent;   
};

struct h_rb_tree
{
    h_rb_node* ph_root_node;
    size_t number_of_elements;
};

struct v_rb_node
{
    vertex_t v;
    color_t color;
    h_rb_tree* ph_rb_tree;

    v_rb_node* left;
    v_rb_node* right;
    v_rb_node* parent;
};

struct v_rb_tree
{
    v_rb_node_t* pv_root_node;
    size_t nr_of_element;
};

struct graph
{
    v_rb_tree* pv_rb_root;
    size_t number_of_verttices;
    size_t number_of_edges; 
};


