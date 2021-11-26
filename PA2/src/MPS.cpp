#include <iostream>
#include "MPS.h"
#include <iomanip>
#include <fstream>
using namespace std;        
MPS::MPS(int N){
    M = new int *[N];
    for(int i=0;i<N;++i){
        M[i]=new int[N];
    }
    for (int i = 0; i < N; i++)
    {
        for(int j=0;j<N;j++){
            M[i][j]=-1;
        }
    }
    NN=N;
}
MPS::~MPS(){
    for (int i = 0; i < NN; ++i)
        delete[] M[i];
    delete[] M;

}
// int MPS::MPSnum(vector<int> C, int N)
// {
//     M = new int *[N];
//     for(int i=0;i<N;++i){
//         M[i]=new int[N];
//     }
//     for (int i = 0; i < N; i++)
//     {
//         for(int j=0;j<i;j++){
//             M[i][j]=-1;
//         }
//     }
//     for (int l = 1; l < N; l++)
//     {
//         for (int i = 0; i < N-l; i++)
//         {
//             int j = i+l; 
//             int k = C[j];
//             if( i >= j ) M[i][j] =0;
//             if (k < i || k > j)
//             {
//                 M[i][j] = M[i][j - 1];
//             }
//             else if( k == i )
//             {
//                 M[i][j] = M[i+1][j-1] + 1;
//             }
//             else 
//             {
//                 if (M[i][j - 1] > (M[i][k-1] + M[k+1][j-1]+1))
//                 {
//                     M[i][j] = M[i][j - 1];
//                 }
//                 else {
//                     M[i][j] = M[i][k-1] + M[k+1][j-1]+1;
//                 }
//             }
//         }
//     }
//     int ans =M[0][N-1];
//     return ans;
// }

int MPS::MPSnum(int* C, int N,int i, int j)
{
    int ans=M[i][j];
    if(M[i][j]<0){
        int k = C[j];
        if( i >= j ) {
            ans=0;
        }
        else if (k < i || k > j)
        {
            ans= MPSnum(C, N, i, j-1);
            //ans=M[i][j-1];
        }
        else if( k == i )
        {
            if(j == i+1){
                ans=1;
            }
            else ans=MPSnum(C, N, i+1, j-1)+1;
            //ans=M[i+1][j-1]+1;
        }
        else 
        {
            // if (MPSnum(C, N, i, j-1) > (MPSnum(C, N, i, k-1) + MPSnum(C, N, k+1, j-1)+1))
            // //if(M[i][j-1]>M[i][k-1]+M[k+1][j-1]+1)
            // {
            //    //ans=MPSnum(C, N, i, j-1);
            //    ans=M[i][j-1];
            // }
            // else {
            //     //M[i][j] = M[i][k-1] + M[k+1][j-1]+1;
            //     //ans=MPSnum(C, N, i, k-1)+MPSnum(C, N, k+1, j-1)+1;
            //     ans=M[i][k-1] + M[k+1][j-1]+1;
            // }
            ans=ans=MPSnum(C, N, i, k-1)+MPSnum(C, N, k+1, j-1)+1;
            if(ans<MPSnum(C, N, i, j-1)){
                ans=M[i][j-1];
            }
        }
    }
    M[i][j]=ans;
    return ans;
}
void MPS::MPSsol(int i, int j, int* C){
    if(j > i){
        int k = C[j];
        if (k < i || k > j)
        {
            MPSsol(i,j-1,C);
        }
        else if( k == i){
                path_node.push_back(k);
                MPSsol(i+1, j-1, C);
        }
        else 
        {
            if (MPSnum(C, NN, i, j-1) > (MPSnum(C, NN, i, k-1) + MPSnum(C, NN, k+1, j-1)+1))
            {
                MPSsol(i, j-1, C);
            }
            else {
                MPSsol(i,k-1,C);
                path_node.push_back(k);
                MPSsol(k+1,j-1,C);
            }
        }

    }
        
}