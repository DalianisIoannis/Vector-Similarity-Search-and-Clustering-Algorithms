#include <iostream>
#include <math.h>
#include <string>
#include "../headers/LSH.h"

CubeTable::CubeTable(int size, const int k, const int w, const int m){
    this->Buckets_Number = pow(2,k);
    this->Table_Elements = 0;
    this->CubeBucketsArray = new HashBucket[this->Buckets_Number];
    this->f_HashFunction = new f_funct(size,k,w,m,this->Buckets_Number);
    cout << "i've created a Cube"<<endl;
}

f_funct* CubeTable::get_Hash_Function(){
    return this->f_HashFunction;
}

void CubeTable::increase_Table_Elements(){
    this->Table_Elements++;
}

int CubeTable::get_Table_Elements(){
    return this->Table_Elements;
}
HashBucketPtr CubeTable::get_HashBucketsArray(){
    return this->CubeBucketsArray;
}
int CubeTable::get_Buckets_Number(){
    return this->Buckets_Number;
}

int CubeTable::CubeTable_Insert(inputForm* PictureVector){
    string String_Index = this->get_Hash_Function()->fhashValue((PictureVector->image));
    cout << String_Index <<endl;
    int Table_Index = stoi(String_Index, 0, 2);
    cout <<"ID: "<<PictureVector->Id<<" Index----->"<<Table_Index<<endl;
    this->CubeBucketsArray[Table_Index].Bucket_Insert(PictureVector);
    this->increase_Table_Elements();
    cout <<"Total "<<this->get_Table_Elements()<<" elements"<<endl;
    /*   list <vector<int>> mylist = this->HashBucketsArray[Table_Index].get_Vector_List();
    std::list<vector<int>>::iterator it;
    vector<int>::iterator ij;
    for (it = mylist.begin(); it != mylist.end(); ++it){ //prints out the list of the element you just inserted
        for (ij = it->begin() ; ij != it->end();ij++)
            cout <<*ij<<endl;
    }*/
    return Table_Index;
}

vector<int> findNearVerticlesOne(string* String_Index){    //Finds all verticles with distance 1
    string nearindex;
    vector<int> toReturn;
    for (unsigned int i = 0 ; i < (*String_Index).length() ; i++){
        nearindex = (*String_Index);
        if (nearindex[i] == '0') {
            nearindex[i] = '1';
        }
        else {
            nearindex[i] = '0';
        }
        toReturn.push_back(stoi(nearindex,0,2));
    }
    printVector(&toReturn);
    return toReturn;
}

int hammingDistance(int n1, int n2) 
{ 
    int x = n1 ^ n2; 
    int setBits = 0; 
  
    while (x > 0) { 
        setBits += x & 1; 
        x >>= 1; 
    } 
  
    return setBits; 
}

vector<int> findNearVerticles(int BucketsNumber,string* String_Index,int distance){
    vector<int> toReturn;
    int vert = stoi(*String_Index ,0,2);
    for (int i = 0 ; i < BucketsNumber ; i++){
        if (hammingDistance(vert,i) == distance){
            toReturn.push_back(i);
        }
    }
    printVector(&toReturn);
    return toReturn;
}

listinfo knNearestNeighbors(CubeTablePtr* L,int kneigh,int probes,int M,vector<int>* Query){
    ////////////////
    int Max_Distance = -1;
    string String_Index;
    int i,HammingDistance = 2,TableIndex,numProbes = 0;
    listinfo returnlist = CreateList();         //initialise useful variables
    HashBucketPtr BucketsArray;
    list<inputForm*> vectorlist;
    vector<int> ProbsIndex;
    std::list<inputForm*>::iterator it;
    int manhattanValue,PhotosCheck = 0;
    vector<list<inputForm*>> allprobs;
    /////////////////
    if (probes > (*L)->get_Buckets_Number()){
        cout <<"Max probes is "<<(*L)->get_Buckets_Number()<<endl;
        probes = (*L)->get_Buckets_Number();
    }
    BucketsArray = (*L)->get_HashBucketsArray();                        //fetch buckets array
    String_Index = (*L)->get_Hash_Function()->fhashValue(Query);    //compute hash function of query vector
    TableIndex = stoi(String_Index,0,2);
    
    allprobs.push_back(BucketsArray[TableIndex].get_Vector_List());
    numProbes++;
    if (probes > 1){
        ProbsIndex = findNearVerticlesOne(&String_Index);
        for (unsigned int i = 0 ; i < ProbsIndex.size() ; i++){
            allprobs.push_back(BucketsArray[i].get_Vector_List());
            numProbes++;
            if (numProbes == probes){
                break;
            }
        }
    }
    while (numProbes < probes){
        ProbsIndex = findNearVerticles((*L)->get_Buckets_Number(),&String_Index,HammingDistance);
        for (unsigned i = 0 ; i < ProbsIndex.size() ; i++){
            allprobs.push_back(BucketsArray[i].get_Vector_List());
            numProbes++;
            if (numProbes == probes){
                break;
            }
        }
        HammingDistance++;
    }
    for (i = 0 ; i < probes ; i++){
        cout << "Prob :"<<i<<endl;        
        vectorlist = allprobs[i];
        for (it = vectorlist.begin() ; it != vectorlist.end() ; ++it){          //parse bucket
            manhattanValue = manhattanDistance(Query,(*it)->image);      //compute manhattan distance for each elem of bucket
            cout <<"ID "<< (*it)->Id <<" Manhattan Distance:"<<manhattanValue<<endl;
            if (PhotosCheck < kneigh){
                if (SearchKNearestList(returnlist,(*it)->Id,manhattanValue) == NULL){                          //search of duplicate elements,if Manhattan is better delete
                    InsertKNearestList(returnlist,(*it),manhattanValue,kneigh);
                }
                if (manhattanValue > Max_Distance){
                    Max_Distance = manhattanValue;
                }
            }
            else if (manhattanValue < Max_Distance){
                if (SearchKNearestList(returnlist,(*it)->Id,manhattanValue) == NULL){
                    InsertKNearestList(returnlist,(*it),manhattanValue,kneigh);
                }
                Max_Distance = returnlist->tail->manh_dist;
            }
            PhotosCheck++;
            if (PhotosCheck >= M){
                cout <<"M is reached"<<endl;
                return returnlist;
            }
        }
    }
    // PrintList(returnlist);
    return returnlist;
}    

// listinfo cubeRangeSearch(CubeTablePtr* L,int probes,int M,vector<int>* query){
//    int Max_Distance = -1;
//     string String_Index;
//     int i,HammingDistance = 2,TableIndex,numProbes = 0;
//     listinfo returnlist = CreateList();         //initialise useful variables
//     HashBucketPtr BucketsArray;
//     list<inputForm*> vectorlist;
//     vector<int> ProbsIndex;
//     std::list<inputForm*>::iterator it;
//     int manhattanValue,PhotosCheck = 0;
//     vector<list<inputForm*>> allprobs;
//     /////////////////
//     if (probes > (*L)->get_Buckets_Number()){
//         cout <<"Max probes is "<<(*L)->get_Buckets_Number()<<endl;
//         probes = (*L)->get_Buckets_Number();
//     }
//     BucketsArray = (*L)->get_HashBucketsArray();                        //fetch buckets array
//     String_Index = (*L)->get_Hash_Function()->fhashValue(Query);    //compute hash function of query vector
//     TableIndex = stoi(String_Index,0,2);
    
//     allprobs.push_back(BucketsArray[TableIndex].get_Vector_List());
//     numProbes++;
//     if (probes > 1){
//         ProbsIndex = findNearVerticlesOne(&String_Index);
//         for (unsigned int i = 0 ; i < ProbsIndex.size() ; i++){
//             allprobs.push_back(BucketsArray[i].get_Vector_List());
//             numProbes++;
//             if (numProbes == probes){
//                 break;
//             }
//         }
//     }
//     while (numProbes < probes){
//         ProbsIndex = findNearVerticles((*L)->get_Buckets_Number(),&String_Index,HammingDistance);
//         for (unsigned i = 0 ; i < ProbsIndex.size() ; i++){
//             allprobs.push_back(BucketsArray[i].get_Vector_List());
//             numProbes++;
//             if (numProbes == probes){
//                 break;
//             }
//         }
//         HammingDistance++;
//     }
//     for (i = 0 ; i < probes ; i++){
//         cout << "Prob :"<<i<<endl;        
//         vectorlist = allprobs[i];
//         for (it = vectorlist.begin() ; it != vectorlist.end() ; ++it){          //parse bucket
//             manhattanValue = manhattanDistance(Query,(*it)->image);      //compute manhattan distance for each elem of bucket
//             cout <<"ID "<< (*it)->Id <<" Manhattan Distance:"<<manhattanValue<<endl;
//             if (PhotosCheck < kneigh){
//                 if (SearchKNearestList(returnlist,(*it)->Id,manhattanValue) == NULL){                          //search of duplicate elements,if Manhattan is better delete
//                     InsertKNearestList(returnlist,(*it),manhattanValue,kneigh);
//                 }
//                 if (manhattanValue > Max_Distance){
//                     Max_Distance = manhattanValue;
//                 }
//             }
//             else if (manhattanValue < Max_Distance){
//                 if (SearchKNearestList(returnlist,(*it)->Id,manhattanValue) == NULL){
//                     InsertKNearestList(returnlist,(*it),manhattanValue,kneigh);
//                 }
//                 Max_Distance = returnlist->tail->manh_dist;
//             }
//             PhotosCheck++;
//             if (PhotosCheck >= M){
//                 cout <<"M is reached"<<endl;
//                 return returnlist;
//             }
//         }
//     }
//     // PrintList(returnlist);
//     return returnlist;
// }




listinfo cubeRangeSearch(CubeTablePtr* L,int probes,int M,vector<int>* Query,int R){
    string String_Index;
    int i,HammingDistance = 2,TableIndex,numProbes = 0;
    listinfo returnlist = CreateList();         //initialise useful variables
    HashBucketPtr BucketsArray;
    list<inputForm*> vectorlist;
    vector<int> ProbsIndex;
    std::list<inputForm*>::iterator it;
    int manhattanValue,PhotosCheck = 0;
    vector<list<inputForm*>> allprobs;
    /////////////////
    if (probes > (*L)->get_Buckets_Number()){
        cout <<"Max probes is "<<(*L)->get_Buckets_Number()<<endl;
        probes = (*L)->get_Buckets_Number();
    }
    BucketsArray = (*L)->get_HashBucketsArray();                        //fetch buckets array
    String_Index = (*L)->get_Hash_Function()->fhashValue(Query);    //compute hash function of query vector
    TableIndex = stoi(String_Index,0,2);
    
    allprobs.push_back(BucketsArray[TableIndex].get_Vector_List());
    numProbes++;
    if (probes > 1){
        ProbsIndex = findNearVerticlesOne(&String_Index);
        for (unsigned int i = 0 ; i < ProbsIndex.size() ; i++){
            allprobs.push_back(BucketsArray[i].get_Vector_List());
            numProbes++;
            if (numProbes == probes){
                break;
            }
        }
    }
    while (numProbes < probes){
        ProbsIndex = findNearVerticles((*L)->get_Buckets_Number(),&String_Index,HammingDistance);
        for (unsigned i = 0 ; i < ProbsIndex.size() ; i++){
            allprobs.push_back(BucketsArray[i].get_Vector_List());
            numProbes++;
            if (numProbes == probes){
                break;
            }
        }
        HammingDistance++;
    }
    for (i = 0 ; i < probes ; i++){
        vectorlist = allprobs[i];
        for (it = vectorlist.begin() ; it != vectorlist.end() ; ++it){          //parse bucket
            manhattanValue = manhattanDistance(Query,(*it)->image);      //compute manhattan distance for each elem of bucket
            // cout <<"ID "<< (*it)->Id <<" Manhattan Distance:"<<manhattanValue<<endl;
            if (manhattanValue < R){
                if (SearchKNearestList(returnlist,(*it)->Id,manhattanValue) == NULL){
                    InsertList(returnlist,(*it),manhattanValue);
                }                
            }
            PhotosCheck++;
            if (PhotosCheck >= M){
                cout <<"M is reached"<<endl;
                return returnlist;
            }
        }
    }
    cout << "Reached Max Probes"<<endl;
    // PrintList(returnlist);
    return returnlist;
}

