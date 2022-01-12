#include <fstream>
#include <iostream>
#include "graph.h"
using namespace std;
char type;
int V;
int E;
int main(int argc, char *argv[])
{
    ifstream fin(argv[1]);
    ofstream fout;
    fout.open(argv[2], ios::out);
    fin >> type;
    fin >> V;
    fin >> E;
    //out << type << " " << V << " " << E << endl;

    graph graph(type, V, E);
    //graph.out(); //print type, V, E
    int s, d, w;
    for (int i = 0; i < E; i++)
    {
        fin >> s >> d >> w;
        graph.add_edge(s, d, w);
    }
    switch (type)
    {
    case 'u':
        graph.MST_Kruskal();
        break;
    case 'd':
        graph.MST_Kruskal();
        graph.add_edges_to_MST();
        break;
        //cout << "unfinished" << endl;
        //return 0;
    }
    int weight = 0;
    cout << graph.edge_set.size() << endl;

    for (int i = 0; i < graph.edge_set.size(); i++)
    {
        weight += graph.edge_set[i].w;
    }
    fout << weight << endl;
    for (int i = 0; i < graph.edge_set.size(); i++)
    {
        fout << graph.edge_set[i].s << " " << graph.edge_set[i].d << " " << graph.edge_set[i].w << endl;
    }
    if (graph.check_if_cycle())
        cout << "cycle!" << endl;
}