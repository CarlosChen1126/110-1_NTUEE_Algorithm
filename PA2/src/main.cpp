#include <iostream>
#include "MPS.h"
#include <fstream>
#include <vector>
#include "tm_usage.h"
using namespace std;
int main(int argc, char *argv[])
{
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;
    MPS mps;
    fstream fin(argv[1]);
    fstream fout;
    int j, num;
    int N;
    int i = 0;
    fin >> N;
    //int data[N];
    vector<int> data;
    vector<int> chord_table;
    while (fin >> num >> j)
    {
        data.push_back(num);
        data.push_back(j);
    }
    for(int i=0;i<data.size();i++){
        chord_table.push_back(0);
    }
    for(int i=0;i<data.size();i+=2){
        chord_table[data[i]]=data[i+1];
        chord_table[data[i+1]]=data[i];
    }
    tmusg.periodStart();
    int ans = mps.MPSnum(chord_table,N);
    cout <<"N: "<<N<<endl;
    cout<<"Ans: "<<ans<<endl;
    mps.MPSsol(0,N,chord_table);
    mps.sort(mps.path_node);
    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory
    // for(int i =0;i<mps.path_node.size();i++){
    //     cout<<mps.path_node[i]<<endl;
    // }

}