#ifndef _MESH_LOADING_H
#define _MESH_LOADING_H


typedef long long ssize_t;

typedef struct vertices
{
    float x;
    float y;
    float z;
}vert;

typedef struct normal
{
    float x
    float y
    float x;

}normal;

typedef struct face 
{
    ssize_t index1;
    ssize_t index2;
    ssize_t index3;
}face;

/*
    @author:    Dhiraj jadhav
    @param1:    pointer to the file.
    @param2:    pointer to the vector of vertices.
    @param3:    pointer to the vector of normal.
    @param3:    pointer to the vector of faces.
    @return:    YET to desice.
*/
int exatract_data(FILE* fp, vert* p_vert, normal* p_normal, face* p_face);
#endif      //_MESH_LOADING_H
