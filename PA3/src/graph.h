#ifndef _graph_H
#define _graph_H
#include <vector>
using namespace std;
class edge
{
public:
    edge(int, int, int);

    int s;
    int d;
    int w;
};
class vertex
{
public:
    vertex();

    int p;
    int rank;
    int number;
    int color;
    int pi;
};
class graph
{
public:
    graph(char, int, int);
    //~graph();
    void out();
    void add_edge(int, int, int);
    bool edge_is_valid(int, int);
    void make_set(int);
    int find_set(int);
    void link(int, int);
    void Union(int, int);
    void MST_Kruskal();
    static bool mycompare(edge &a, edge &b);
    void cb_u();
    void create_ADJ(edge);
    bool DFS(edge);
    bool DFS_visit(int);
    bool check_if_cycle();
    void add_edges_to_MST();

    vector<edge> edge_set;
    vector<int> *adj_set;
    vector<edge> ans_set;

private:
    char type;
    int V;
    int E;
    vertex *vertex_set;
};

#endif