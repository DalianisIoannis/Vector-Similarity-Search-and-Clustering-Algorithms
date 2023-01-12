#include "../headers/LSH.h"
#include <iostream>
#include <cmath>
#include <math.h>
#include <random>
#include <string>

using namespace std;

void printVector(vector<int> *vec){
    cout << "vector:{ ";
    for (unsigned int i = 0 ; i < vec->size();i++){
        cout<< (*vec)[i]<<" ";
    }
    cout <<"}"<<endl;
}

h_funct::h_funct(int w,int size){
    this->VectorS = new vector<int> (size);
    this->powers = new vector<int> ;
    for(unsigned int i=0; i<(*VectorS).size(); i++) {
        (*VectorS)[i] = (int)uniformNUMBERFUN( (float)w)  ;
    }
    // printVector(this->VectorS);
}

int h_funct::hashValue(vector<int>* p, const int m, const int w, const int M) {
    
// return h()
    long int ret = 0;

    for(long unsigned int i=0; i < p->size(); i++) {
       if ((this->powers->size()-1) < i){
            powers->push_back((int)pow(m % M,i));
       }
        ret += abs((*powers)[i] * (ai( (*p)[i], (*this->VectorS)[i], w ) % M) % M);
    }
    return ret;
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
    uint32_t hashRet = 0;
    for(int i = 0; i < this->k; i++) {
        hashRet = hashRet << 32 / this-> k;
        hashRet = hashRet | this->VectorH[i].hashValue( p, this->m, this->w, this->M );
    }
    // cout <<hashRet<< " ";
    hashRet = hashRet % this->M;
    // cout << "hashRet is " << hashRet << endl;
    return hashRet;

}

int ai(const int pi, const int si, const int w) {
    
    return floor( float(pi - si) / float(w) );

}


f_funct::f_funct(int size,const int k,const int w,const int m,const int M){
    this->RedBlackMatch = Rbtcreate();
    this->k = k;
    this->M = M;
    this->m = m;
    this->w = w;
    this->VectorH = (h_funct*)malloc(k * sizeof(h_funct));
    for (int i = 0 ; i < k ; i++){
        VectorH[i] = h_funct(w,size);
    }
}

string f_funct::fhashValue(vector<int>* p){
    int hvalue,fvalue;
    node retnode;
    random_device rd;
    string toRet;
	mt19937 gen (rd ());
	uniform_int_distribution <> dis (0, 1);
    for (int i = 0 ; i < this->k ; i++){
        hvalue = this->VectorH[i].hashValue(p,this->m,this->w,this->M);
        if ( (retnode = RBsearch(this->RedBlackMatch,hvalue)) == NULL){
            fvalue = dis(gen);
            RBdataPtr toInsert = SetupRBdata(hvalue,fvalue);
            insert(this->RedBlackMatch,toInsert);
        }
        else{
            fvalue = Returnfval(returnData(retnode));
        }
        if (i == 0){
            toRet = to_string(fvalue);
        }
        else {
            toRet = toRet + to_string(fvalue);
        }
    }
    return toRet;
}

float uniformNUMBERFUN(const float maxSize) {
    std::random_device rd;      //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());     //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> distrib(0.0, maxSize);
    return distrib(gen);
}