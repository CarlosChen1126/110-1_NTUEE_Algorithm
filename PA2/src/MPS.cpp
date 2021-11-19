#include <iostream>
#include "MPS.h"
using namespace std;        

int MPS::MPSnum(vector<int> C, int N)
{
    int M[N][N];
    _k = new int *[N];
    for(int i=0;i<N;++i){
        _k[i]=new int[N];
    }
    for (int i = 0; i < N; ++i)
    {
        for(int j=0;j<N;j++){
            _k[i][j] = 0;
        }
    }
    //vector<int> t;
    for (int i = N - 1; i >= 0; i--)
    {
        // int k = C[i];
        //cout<< k<< endl;
        for (int j = i; j < N; j++)
        {
            //t.clear();
            int k = C[j];
            if( i == j ) M[i][j] =0;
            if (k < i || k > j)
            {
                M[i][j] = M[i][j - 1];
            }
            else if(k >= i && k <= j)
            {
                if (M[i][j - 1] > (M[i][k-1] + M[k+1][j-1]+1))
                {
                    M[i][j] = M[i][j - 1];
                }
                else {
                    M[i][j] = M[i][k-1] + M[k+1][j-1]+1;
                    //t.push_back(k);
                    //cout<< k <<" "<< j<<endl;
                }
            }
            else if( k == i )
            {
                M[i][j] = M[i+1][j-1] + 1;
                //t.push_back(j);
                //cout<< k<< " "<<j<<endl;
            }
        }
    }
    // for(int j=0; j<2*N; j++){
    //     int k = C[j];
    //     for(int i=0; i<j; i++){

    //     }


    // }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            _k[i][j]=M[i][j];
        }
    }

    return _k[0][N-1];
}

int MPS::MPSsol(int i, int j, vector<int> C){
    if(j > i){
        int k = C[j];
        if( k == i){
            path_node.push_back(j);
            MPSsol(i, j-1, C);
        }
        else if(k >= i && k <= j){

        }

    }
        
}