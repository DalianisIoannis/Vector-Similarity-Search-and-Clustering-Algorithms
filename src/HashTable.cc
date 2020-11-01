#include "../headers/HashTable.h"

HashBucket::HashBucket(){
    this->Bucket_Elements = 0;
    cout << "I've created a bucket" <<endl;
}

HashBucket::~HashBucket(){
    // cout << "im called" <<endl;
}

void HashBucket::increase_Bucket_Elements(){
    this->Bucket_Elements++;
}
int HashBucket::get_Bucket_Elements(){
    return this->Bucket_Elements;
}

void HashBucket::Bucket_Insert(inputForm* PictureVector){
    this->vector_list.push_back(PictureVector);    
    this->increase_Bucket_Elements();
    cout << "I've pushed the element into the vector list with " << this->Bucket_Elements <<" elements" <<endl;
}

list<inputForm*> HashBucket::get_Vector_List(){
    return this->vector_list;
}

HashTable::HashTable(int size, const int k, const int w, const int m, const int M){
    this->Buckets_Number = M;
    this->Table_Elements = 0;
    this->HashBucketsArray = new HashBucket[M];
    this->g_HashFunction = new g_funct(size,k,w,m,M);
    cout << "i've created a hash Table"<<endl;

}

HashTable::~HashTable(){
    delete[] this->HashBucketsArray;
    cout << "Destroyed HashTable" <<endl;
}

void HashTable::increase_Table_Elements(){
    this->Table_Elements++;
}

int HashTable::get_Table_Elements(){
    return this->Table_Elements;
}
HashBucketPtr HashTable::get_HashBucketsArray(){
    return this->HashBucketsArray;
}
int HashTable::get_Buckets_Number(){
    return this->Buckets_Number;
}

int HashTable::Table_Insert(inputForm* PictureVector){
    int Table_Index = this->get_Hash_Function()->ghashValue(&(PictureVector->image));
    this->HashBucketsArray[Table_Index].Bucket_Insert(PictureVector);
    this->increase_Table_Elements();
    cout <<"total "<<this->get_Table_Elements()<<" elements"<<endl;
    /*   list <vector<int>> mylist = this->HashBucketsArray[Table_Index].get_Vector_List();
    std::list<vector<int>>::iterator it;
    vector<int>::iterator ij;
    for (it = mylist.begin(); it != mylist.end(); ++it){ //prints out the list of the element you just inserted
        for (ij = it->begin() ; ij != it->end();ij++)
            cout <<*ij<<endl;
    }*/
    return Table_Index;
}

g_funct* HashTable::get_Hash_Function(){
    return this->g_HashFunction;
}
