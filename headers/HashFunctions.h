#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

class h_funct{
    private:
        std::vector<int> *VectorS;
    public:
        h_funct(int,int);
        int hashValue(vector<int>* p, const int m, const int w, const int M);
        vector<int>* get_VectorS();

};

class g_funct{
    private:
        h_funct* VectorH;
        int k;
        int w;
        int m;
        int M;
    public:
        g_funct(int size, const int, const int, const int, const int);
        int ghashValue(vector<int>*) ;
};