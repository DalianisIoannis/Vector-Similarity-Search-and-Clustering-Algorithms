#include <iostream>
#include <list>
#include <vector>

using namespace std;
typedef class HashBucket * HashBucketPtr;
typedef class HashTable * HashTablePtr;

class HashBucket{
    private:
        int Bucket_Elements;
        std::list<std::vector<int>> vector_list;
    public:
        HashBucket();
        ~HashBucket();
        void increase_Bucket_Elements();
        int get_Bucket_Elements();
        list<std::vector<int>> get_Vector_List();
        void Bucket_Insert(vector <int>);        
};


class HashTable{
    private:
        int Table_Elements;
        int Buckets_Number;
        HashBucketPtr HashBucketsArray;
        std::list<std::vector<int>> List_S_Vectors;
    public:
        HashTable(int);
        ~HashTable();
        void increase_Table_Elements();
        int get_Table_Elements();
        HashBucketPtr get_HashBucketsArray();
        int get_Buckets_Number();
        int Table_Insert(int(*function)(void*),vector <int>);
};
int funct(void*);
void printVector(vector<int>*);
