#ifndef _MESH_LOADING_H
#define _MESH_LOADING_H


typedef long long int ssize_t;

typedef struct tagVertices
{
    float x;
    float y;
    float z;
}Vertices;

typedef struct tagNormal
{
    float x
    float y
    float x;

}Normal;

typedef struct tagFace 
{
    ssize_t index1;
    ssize_t index2;
    ssize_t index3;
}Face;

typedef struct tagVector
{
    void* p_arr;
    ssize_t N;
}Vector;

/*
    @author:    Dhiraj jadhav
    @param1:    pointer to the file.
    @param2:    pointer to the vector of vertices.
    @param3:    pointer to the vector of normal.
    @param3:    pointer to the vector of faces.
    @return:    YET to desice.
*/
int exatract_data(FILE* fp, vert* p_vert, normal* p_normal, face* p_face);

void create_vector(void);

void push_back(void* p_vect, void* p_new_element);

void release_vector(void* p_vec);

void* xmalloc(ssize_t nr_of_byte);

#endif      //_MESH_LOADING_H
