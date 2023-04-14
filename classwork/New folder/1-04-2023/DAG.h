#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef long long vertex_t;
typedef struct hnode    hnode_t;
typedef  hnode_t    hlist_t;

typedef struct vnode    vnode_t;
typedef vnode_t vlist_t;

typedef enum color color_t;


struct hnode
{
    vertex_t v;
    struct hnode* next;
    struct hnode* prev;
}
