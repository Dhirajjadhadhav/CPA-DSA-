#ifndef _GRAPH_EXCEPTIONS_HPP
#define _GRAPH_EXCEPTIONS_HPP

#include <iostream>   
#include <stdexcept>

class invalid_vertex : public std::domain_error
{
    public:
        invalid_vertex(const char* msg):std::domain_error(msg){}
};

class invalid_edge : public std::domain_error
{
    public:
        invalid_edge(const char* msg):std::domain_error(msg){}
};

class vertex_exists : public std::runtime_error
{
    public: 
        vertex_exists(const char* msg):std::runtime_error(msg){}
};

class edge_exists : public std::runtime_error
{
    public:
        edge_exists(const char* msg):std::runtime_error(msg){}
};

#endif /* _GRAPH_EXCEPTION_HPP */