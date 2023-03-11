#include <iostream>


class graph
{
    private:
        int* pg;
        int nr_V;
        int nr_E;
    static int getij(graph& g, int i, int j);
    static void setij(graph& g, int  i, int j, int val);

    public:
        graph(int V)
        {
            nr_V = V;
            pg = (int*)calloc(nr_V * nr_V , sizeof(int));
            if(pg == NULL)  
            {
                std::runtime_error("calloc:out of memeory");
            }
            nr_E = 0;
        }
        ~graph()
        {
            free(pg);
            pg = nullptr;
        }

        int add_edge(int v_start, int e_end)
        {
            
        }

        int remove_edge(int v_start, int v_end)
        {
            //remove_edge()
        }

        friend std::ostream& operator<<(std:: ostream os, const graph& g);
};
std::ostream& operator<<(std:: ostream os, const graph& g)
{   
    int i,j;
    
    std::cout<<"|V| = "<<g.nr_V<<".|E| = "<<g.nr_E<<std::endl;

    for(i = 0; i<g.nr_V; ++i)
    {  
        std::cout<<"VERTEX["<<i <<"]\t<->\t"<<std::endl;
        for(j = 0; j<g.nr_V; ++i)
            if(graph::getij(this, i, j))
            {
                std::cout<<"["<<j<<"]<->";
            }
        std::cout<<"[END]"<<std::endl;
    }
}

int graph::getij(graph& g, int i, int j)
{
    return ( (*((g.pg) + i * g.nr_V + j)) ); 
}

void graph :: setij(graph& g, int  i, int j, int val)
{
    *(((g.pg) + i * g.nr_V) + j) = val;
}


void test_1(void);
void test_2(void);

int main(void)
{
    test_1();
    test_2();

    return (0);
}

void test_1(void)
{
    graph g(5);

    g.add_edge(1, 4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);

    std::cout<<g;
}
void test_2(void)
{
    graph* pg = new graph(5);

    pg->add_edge(0, 1);
    pg->add_edge(1, 2);
    pg->add_edge(2, 3);
    pg->add_edge(3, 4);

    std::cout<<*pg;
    delete pg;

    pg = 0
}


