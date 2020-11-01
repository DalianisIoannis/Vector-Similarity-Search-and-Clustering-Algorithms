#include <iostream>
#include "../headers/HashTable.h"

typedef class CubeTable* CubeTablePtr;


class CubeTable{
    private:
        int Table_Elements;
        int Buckets_Number;
        HashBucketPtr CubeBucketsArray;
        f_funct* f_HashFunction;
    public:
        CubeTable(int, const int, const int , const int );
        ~CubeTable();
        void increase_Table_Elements();
        int get_Table_Elements();
        HashBucketPtr get_HashBucketsArray();
        int get_Buckets_Number();
        int CubeTable_Insert(inputForm*);
        f_funct* get_Hash_Function();
};
int hammingDistance(int, int);
vector<int> findNearVerticlesOne(string*);
vector<int> findNearVerticles(int,string*,int);
listinfo knNearestNeighbors(CubeTablePtr*,int,int,int,vector<int>*);
listinfo cubeRangeSearch(CubeTablePtr* L,int probes,int M,vector<int>* Query,int R);