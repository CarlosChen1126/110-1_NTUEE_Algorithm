#include <iostream>
#include "MPS.h"
#include <fstream>
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
    MPS mps;
    fstream fin(argv[1]);
    fstream fout;
    //fout.open(argv[2], ios::out);
    //fin.getline(buffer, 200);
    int j, num;
    int N;
    int i = 0;
    fin >> N;
    //int data[N];
    vector<int> data;
    vector<int> chord_table;
    while (fin >> num >> j)
    {
        // data[i] = num;
        // i++;
        // data[i] = j;
        // i++;
        // cout << data[i - 2] << " " << data[i - 1] << endl;
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
    int ans = mps.MPSnum(chord_table,N);
    cout <<"N: "<<N<<endl;
    cout<<"Ans: "<<ans<<endl;
    // for(int i=0;i<data.size();i++){
    //     cout<<chord_table[i]<<endl;
    // }
}