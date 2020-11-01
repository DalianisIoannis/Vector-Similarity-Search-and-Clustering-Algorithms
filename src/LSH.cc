#include <bits/stdc++.h>
#include "../headers/HashTable.h"
#include <iostream>

int manhattanDistance(vector<int>* x, vector<int>* y) {
    
    int sum = 0;

    // cout << "Size of vector x is " << x->size() << endl;
    // cout << "Size of vector y is " << y->size() << endl;

    if(x->size() != y->size()) {
        cerr << "Vectors should be of the same size!\n";
        return -1;
    }

    for (unsigned int i = 0; i < x->size(); i++) {
        
        // cout << (*x)[i] << " and " << (*y)[i] << " and abs " << abs( (*x)[i] - (*y)[i] ) << endl;

        sum += abs( (*x)[i] - (*y)[i] );

    }
    return sum;
}

 listinfo kNearestNeighbors(HashTablePtr* L,int L_Num,int kneigh,vector<int>* CheckVector){
    int Max_Distance = -1;
    int i,TableIndex;
    ///////////////
    listinfo returnlist = CreateList();         //initialise useful variables
    HashBucketPtr BucketsArray;
    list<inputForm*> vectorlist;
    std::list<inputForm*>::iterator it;
    int manhattanValue,currNum = 0;
    ///////////////
    for (i = 0 ; i < L_Num ; i++ ){                                         //search all Hash Tables
        BucketsArray = L[i]->get_HashBucketsArray();                        //fetch buckets array
        TableIndex = L[i]->get_Hash_Function()->ghashValue(CheckVector);    //compute hash function of query vector
        vectorlist = BucketsArray[TableIndex].get_Vector_List();            //we fetch vectors list of hash index
        for (it = vectorlist.begin() ; it != vectorlist.end() ; ++it){          //parse bucket
            manhattanValue = manhattanDistance(CheckVector,&(*it)->image);      //compute manhattan distance for each elem of bucket
            //cout <<"Manhattan:"<<manhattanValue<<endl;
            if (currNum < kneigh){
                if (SearchKNearestList(returnlist,(*it)->Id,manhattanValue) == NULL){                          //search of duplicate elements,if Manhattan is better delete
                    InsertKNearestList(returnlist,(*it),manhattanValue,kneigh);
                    currNum++;
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
        }
    }
    // PrintList(returnlist);
    return returnlist;

}


listinfo RangeSearch(HashTablePtr* L,int L_Num,int r,vector<int>* CheckVector){
    int i,TableIndex;
    listinfo returnlist = CreateList();         //initialise useful variables
    HashBucketPtr BucketsArray;
    list<inputForm*> vectorlist;
    std::list<inputForm*>::iterator it;
    int manhattanValue;
    for (i = 0 ; i < L_Num ; i++){
        BucketsArray = L[i]->get_HashBucketsArray();                        //fetch buckets array
        TableIndex = L[i]->get_Hash_Function()->ghashValue(CheckVector);    //compute hash function of query vector
        vectorlist = BucketsArray[TableIndex].get_Vector_List();
        for (it = vectorlist.begin() ; it != vectorlist.end() ; ++it){
            manhattanValue = manhattanDistance(CheckVector,&(*it)->image);     //compute manhattan distance for each elem of bucket
            if ( (manhattanValue <  r) && (SearchKNearestList(returnlist,(*it)->Id,manhattanValue) == NULL)){
                InsertList(returnlist,(*it),manhattanValue);
            }
        }
    }
    PrintList(returnlist);
    return returnlist;
}