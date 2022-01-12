#include <iostream>
#include "graph.h"
#include <iomanip>
#include <fstream>
using namespace std;
graph::graph(char t, int v, int e)
{
    type = t;
    V = v;
    E = e;
    vertex_set = new vertex[v];
}
edge::edge(int _s, int _d, int _w)
{
    s = _s;
    d = _d;
    w = _w;
}
vertex::vertex()
{
}
void graph::make_set(int u)
{
    vertex_set[u].number = u;
    vertex_set[u].p = u;
    vertex_set[u].rank = 0;
}
int graph::find_set(int x)
{
    if (vertex_set[x].number != vertex_set[x].p)
    {
        vertex_set[x].p = find_set(vertex_set[x].p);
    }
    return vertex_set[x].p;
}
void graph::out()
{
    //cout << type << " " << V << " " << E << endl;
    int a = 4;
    int b = 0;
    for (int i = 0; i < edge_set.size(); i++)
    {
        cout << edge_set[i].s << " " << edge_set[i].d << endl;
    }
}

void graph::add_edge(int s, int d, int w)
{
    edge edge(s, d, w);
    edge_set.push_back(edge);
}
bool graph::edge_is_valid(int _s, int _d)
{
    for (int i = 0; i < edge_set.size(); i++)
    {
        if (edge_set[i].s == _s && edge_set[i].d == _d)
        {
            return true;
        }
        return false;
    }
}
void graph::link(int a, int b)
{
    if (vertex_set[a].rank > vertex_set[b].rank)
    {
        vertex_set[b].p = vertex_set[a].number;
    }
    else
    {
        vertex_set[a].p = vertex_set[b].number;
        if (vertex_set[a].rank == vertex_set[b].rank)
        {
            vertex_set[b].rank++;
        }
    }
}
void graph::Union(int x, int y)
{
    graph::link(graph::find_set(x), graph::find_set(y));
}
bool graph::mycompare(edge &a, edge &b)
{
    return a.w > b.w;
}
void graph::MST_Kruskal()
{
    //cout << "edge_set size: " << edge_set.size() << endl;
    vector<edge> m_edges;
    for (int i = 0; i < V; i++)
    {
        graph::make_set(i);
    }
    sort(edge_set.begin(), edge_set.end(), mycompare);
    for (int i = 0; i < edge_set.size(); i++)
    {
        if (find_set(edge_set[i].s) != find_set(edge_set[i].d))
        {
            Union(edge_set[i].s, edge_set[i].d);
        }
        else
        {
            m_edges.push_back(edge_set[i]);
        }
    }
    edge_set = m_edges;
    //cout << "m_edge_set size: " << m_edges.size() << endl;
    // for (int i = 0; i < m_edges.size(); i++)
    // {
    //     cout << m_edges[i].s << " " << m_edges[i].d << endl;
    // }
}
