#include <iostream>
#include <fstream>
#include <chrono>

#include "../headers/HashTable.h"
#include "../headers/input.h"
#include "../headers/LSH.h"
#include "../headers/kMeans.h"

using namespace std;

int main(void) {

    cout << "Only just started!" << endl;
    auto start = std::chrono::high_resolution_clock::now();

    // dataInput *s = new dataInput("train-images.idx3-ubyte");
    dataInput *s = new dataInput("t10k-images.idx3-ubyte");
    // KMeans *kM = new KMeans(5);
    KMeans *kM = new KMeans(4);

    s->readMnist();

    s->tryVector();

    kM->Clusterify(s);

    delete kM;
    delete s;
    
    // cout << "DOKIMI" << endl;
    // vector<int> p(35);
    // srand((unsigned) time(0));
    // for(unsigned int i=0; i<p.size(); i++){
    //     p[i] = rand() % 255 + 1;
    //    // cout <<p[i]<<endl;
    // }
    // HashTablePtr table = new HashTable(35,6,52,1,3) ;
    // cout << table->Table_Insert(&p)<<endl;

    // delete table;

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    return 0;
}
// k : poses hash functions 
// size: idios arithmos me ta stoixeia tou dianismatos ths eikonas
// w : modarei ta ai
// m : varoi
// M :panw akro tou m tou vragmenou
// g_funct::g_funct(int size, const int k, const int w, const int m, const int M){