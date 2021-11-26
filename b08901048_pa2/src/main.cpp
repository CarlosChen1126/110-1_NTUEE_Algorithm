#include "MPS.h"
#include <fstream>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    int first, second;
    int N;
    fin >> N;
    int *chord_table;
    chord_table = new int[N];
    while (fin >> first >> second)
    {
        chord_table[first] = second;
        chord_table[second] = first;
    }
    MPS mps(N);
    int ans = mps.MPSnum(chord_table, N, 0, N - 1);
    //cout << "N: " << N << endl;
    //cout << "Ans: " << ans << endl;

    fout << ans << endl;
    mps.MPSsol(0, N - 1, chord_table);
    for (int i = 0; i < mps.path_node.size(); i++)
    {
        fout << mps.path_node[i] << " " << chord_table[mps.path_node[i]] << endl;
    }
    fin.close();
    fout.close();
    delete[] chord_table;
}