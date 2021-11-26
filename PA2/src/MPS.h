#ifndef _MPS_H
#define _MPS_H

#include <vector>
using namespace std;

class MPS
{
    public:
        MPS(int);
        ~MPS();
        int MPSnum(int* , int, int, int);
        //int MPSnum(vector<int> , int);
        void MPSsol(int, int, int*);
        vector<int> path_node;
    private:
        int **M;
        int NN;
};

#endif