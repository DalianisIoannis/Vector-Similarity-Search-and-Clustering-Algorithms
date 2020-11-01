#include <iostream>
#include <list>
#include <vector>
#include "HashFunctions.h"
#include "list.h"

using namespace std;
typedef class HashBucket * HashBucketPtr;
typedef class HashTable * HashTablePtr;

class HashBucket{
    private:
        int Bucket_Elements;
        std::list<inputForm*> vector_list;
    public:
        HashBucket();
        ~HashBucket();
        void increase_Bucket_Elements();
        int get_Bucket_Elements();
        list<inputForm*> get_Vector_List();
        void Bucket_Insert(inputForm*);        
};


class HashTable{
    private:
        int Table_Elements;
        int Buckets_Number;
        HashBucketPtr HashBucketsArray;
        g_funct* g_HashFunction;
    public:
        HashTable(int, const int, const int , const int , const int );
        ~HashTable();
        void increase_Table_Elements();
        int get_Table_Elements();
        HashBucketPtr get_HashBucketsArray();
        int get_Buckets_Number();
        int Table_Insert(inputForm*);
        g_funct* get_Hash_Function();
};
void printVector(vector<int>*);
