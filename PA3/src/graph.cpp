#include <iostream>
#include "graph.h"
#include <iomanip>
#include <fstream>
using namespace std;
#define WHITE 0
#define GRAY 1
#define BLACK 2
graph::graph(char t, int v, int e)
{
    type = t;
    V = v;
    E = e;
    vertex_set = new vertex[v];
    adj_set = new vector<int>[v];
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
    adj_set[s].push_back(d);
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

//check whether to add this edge(1: cyclic, 0:acyclic)
bool graph::DFS(edge e)
{
    //reset color of all vertices
    for (int i = 0; i < V; i++)
    {
        vertex_set[i].color = WHITE;
        //vertex_set[i].pi = -1;
    }

    vertex_set[e.s].color = GRAY;
    return DFS_visit(e.d);
}
bool graph::DFS_visit(int u)
{
    vertex_set[u].color = GRAY;
    for (int i : adj_set[u])
    {
        if (vertex_set[i].color == WHITE)
        {
            //vertex_set[i].pi = u;
            if (DFS_visit(i))
                return true;
        }
        else if (vertex_set[i].color == GRAY)
        {
            //cycle exist
            return true;
            //cout << "cycle!" << endl;
        }
    }
    vertex_set[u].color = BLACK;
    return false;
}
void graph::add_edges_to_MST()
{
    //update adjacent nodes
    for (edge e : edge_set)
    {
        //for (int i = 0; i < adj_set[e.s].size(); i++)
        //{
        //use iterator+find to find the element in vector
        vector<int>::iterator finding = std::find(adj_set[e.s].begin(), adj_set[e.s].end(), e.d);
        if (finding != adj_set[e.s].end())
        {
            adj_set[e.s].erase(finding);
        }
        //}
    }
    //此時的edge_set呈descending
    for (int i = 0; i < edge_set.size(); i++)
    {
        if (edge_set[i].w < 0)
            break;
        if (DFS(edge_set[i]))
            continue;
        else
        {
            adj_set[edge_set[i].s].push_back(edge_set[i].d);
            edge_set.erase(edge_set.begin() + i);
            i--;
        }
    }
}
bool graph::check_if_cycle()
{
    for (int i = 0; i < V; i++)
    {
        vertex_set[i].color = WHITE;
        vertex_set[i].pi = -1;
    }
    for (int i = 0; i < V; i++)
    {
        if (DFS_visit(i))
            return true;
    }
    return false;
}
/*void graph::delete_cycle(int j)
{
    //edge NIL(0, 0, -1);
    vector<int> v_cycle;
    vector<edge> edge_cycle;
    int l = j;
    v_cycle.push_back(l);
    while (vertex_set[l].pi != j)
    {
        l = vertex_set[l].pi;
        if (l == j)
            break;
        v_cycle.push_back(l);
    }
    // cout << edge_set.size() << endl;
    for (int i = v_cycle.size() - 1; i >= 0; i--)
    {
        for (int s = 0; s < edge_set.size(); s++)
        {
            if (edge_set[s].s == v_cycle[i] && edge_set[s].d == v_cycle[i - 1])
            {
                edge_cycle.push_back(edge_set[s]);
            }
        }
    }
    sort(edge_cycle.begin(), edge_cycle.end(), mycompare);

    for (int i = 0; i < edge_set.size(); i++)
    {
        if (edge_set[i].s == edge_cycle[0].s && edge_set[i].d == edge_cycle[0].d && edge_set[i].w == edge_cycle[0].w)
        {
            ans_set.push_back(edge_cycle[0]);
            edge_set.erase(edge_set.begin() + (i - 1));
            int ii = 0;
            for (int w : adj_set[edge_set[i].s])
            {
                if (w == edge_set[i].d)
                {
                    adj_set[edge_cycle[0].s].erase(adj_set[edge_cycle[0].s].begin() + ii);
                }
                ii++;
            }
        }
    }

}*/