#include "../headers/HashFunctions.h"
#include "../headers/LSH.h"
#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

void printVector(vector<int> *vec){
    cout << "vector:{";
    for (int i = 0 ; i < vec->size();i++){
        cout<< (*vec)[i];
    }
    cout <<"}"<<endl;
}

h_funct::h_funct(int w,int size){
    this->VectorS = new vector<int> (size);
    for(unsigned int i=0; i<(*VectorS).size(); i++) {
        (*VectorS)[i] = rand() % w; // +1 ?
    }
    printVector(this->VectorS);
}

int h_funct::hashValue(vector<int>* p, const int m, const int w, const int M) {
    
    // return h()
    long int ret = 0;
    int ekth = 0;

    for(unsigned int i=0; i< p->size(); i++) {
        cout <<(*this->VectorS)[i]<<endl;
        ret += abs(int(pow(m, ekth++)) * ai( (*p)[i], (*this->VectorS)[i], w ));
    }

    return ret % M;
}

vector<int>* h_funct::get_VectorS(){
    return this->VectorS;
}

g_funct::g_funct(int size, const int k, const int w, const int m, const int M){
    this->k = k;
    this->M = M;
    this->m = m;
    this->w = w;
    this->VectorH = (h_funct*) malloc(k * sizeof(h_funct));
    for (int i = 0 ; i < k ; i++){
        VectorH[i] = h_funct(w,size);
    }
} 

int g_funct::ghashValue(vector<int>* p) {
   // it returns g(p) wich is a concatenation of h
    int hashRet = 0;
    for(int i = 0; i < this->k; i++) {
        hashRet = concatInts( hashRet, this->VectorH[i].hashValue( p, this->m, this->w, this->M ) );
    }
    cout <<hashRet<< " ";
    hashRet = hashRet % this->M;
    cout << "hashRet is " << hashRet << endl;
    return hashRet;

}

int ai(const int pi, const int si, const int w) {
    
    return floor( float(pi - si) / float(w) );

}