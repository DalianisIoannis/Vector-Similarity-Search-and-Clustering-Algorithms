#include "../headers/HashTable.h"

HashBucket::HashBucket(){
    this->Bucket_Elements = 0;
    // cout << "im called" <<endl;
}
void HashBucket::increase_Bucket_Elements(){
    this->Bucket_Elements++;
}
int HashBucket::get_Bucket_Elements(){
    return this->Bucket_Elements;
}

void HashBucket::Bucket_Insert(std::vector <int> PictureVector){
    this->vector_list.push_back(PictureVector);    
    this->increase_Bucket_Elements();
    cout << "I've pushed the element into the vector list" <<endl;
}

list<vector<int>> HashBucket::get_Vector_List(){
    return this->vector_list;
}

HashTable::HashTable(int Buckets_Num){
    this->Buckets_Number = Buckets_Num;
    this->Table_Elements = 0;
    this->HashBucketsArray = new HashBucket[Buckets_Num];
    cout << "i've created a hash Table"<<endl;

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

int funct(void * x){
int* y = (int*) x;
//cout << *y<<endl;
return 1;
}

int HashTable::Table_Insert(int(*HashFunction)(void*),std::vector <int> PictureVector){
    int y = 3;
    int Table_Index = (*HashFunction)(&y);
    this->HashBucketsArray[Table_Index].Bucket_Insert(PictureVector);
    this->increase_Table_Elements();
    /*   list <vector<int>> mylist = this->HashBucketsArray[Table_Index].get_Vector_List();
    std::list<vector<int>>::iterator it;
    vector<int>::iterator ij;
    for (it = mylist.begin(); it != mylist.end(); ++it){ //prints out the list of the element you just inserted
        for (ij = it->begin() ; ij != it->end();ij++)
            cout <<*ij<<endl;
    }*/
    return Table_Index;
}
