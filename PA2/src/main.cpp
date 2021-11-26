#include "MPS.h"
#include <fstream>
#include <iostream>
#include "tm_usage.h"
using namespace std;
int main(int argc, char *argv[])
{
    // CommonNs::TmUsage tmusg;
    // CommonNs::TmStat stat;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    int j, num;
    int N;
    int i = 0;
    fin >> N;
    //int data[N];
    int *chord_table;
    //vector<int> chord_table;
    // for(int i=0;i<N;i++){
    //     //chord_table.push_back(0);
    //     chord_table[i]=new int;
    // }
    chord_table = new int;
    while (fin >> num >> j)
    {
        // chord_table.push_back(num);
        // chord_table.push_back(j);
        chord_table[num]=j;
        chord_table[j]=num;
    }
    //tmusg.periodStart();
    MPS mps(N);
    int ans = mps.MPSnum(chord_table,N, 0, N-1);
    //int ans = mps.MPSnum(chord_table,N);
    cout <<"N: "<<N<<endl;
    cout<<"Ans: "<<ans<<endl;
    //mps.sort(mps.path_node);
    //tmusg.getPeriodUsage(stat);
    //cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    //cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory
    fout<<ans<<endl;
    mps.MPSsol(0,N-1,chord_table);
    for(int i =0;i<mps.path_node.size();i++){
        //cout<<mps.path_node[i]<<endl;
        fout<<mps.path_node[i]<<" "<< chord_table[mps.path_node[i]]<<endl;
        //cout<<mps.path_node.size()<<endl;
    }
    fin.close();
    fout.close();
    delete []chord_table;

}