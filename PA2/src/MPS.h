#ifndef _MPS_H
#define _MPS_H

#include <vector>
using namespace std;

class MPS
{
    public:
        int MPSnum(vector<int> , int);
        void MPSsol(int, int, vector<int>);
        vector<int> path_node;
        void sort(vector<int>&);
    private:
        int **M;
};

#endif