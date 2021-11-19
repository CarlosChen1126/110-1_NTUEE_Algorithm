#ifndef _MPS_H
#define _MPS_H

#include <vector>
using namespace std;

class MPS
{
    public:
        int MPSnum(vector<int> , int);
        int MPSsol(int, int, vector<int>);
        vector<int> path_node;
        int **_k;
        vector<vector<int> > AA;
    private:
        int N;
};

#endif